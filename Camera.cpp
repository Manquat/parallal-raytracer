//
// Created by gautier on 15.05.16.
//

#include "Primitive.h"
#include "Camera.h"
#include "Eigen/Geometry"
#include <random>
#include <time.h>
#include <numeric>
#include <mpi.h>

#ifdef _OPENMP

#include <omp.h>

#endif

Camera::Camera(Scene *scene, unsigned int pixelWidth, unsigned int pixelHeight, double width, double height,
               double screen_distance, const Point &origin, const Vector &direction, const Vector &vertical)
        : scene_(scene),
          pixelWidth_(pixelWidth),
          pixelHeight_(pixelHeight),
          width_(width),
          height_(height),
          screen_distance_(screen_distance),
          origin_(origin),
          direction_(direction.normalized()),
          vertical_(vertical.normalized()) { }

void Camera::draw(Screen &screen) const {
    if (screen.getHeight() != pixelHeight_ || screen.getWidth() != pixelWidth_) {
        screen = Screen(pixelHeight_, pixelWidth_);
    }

    double const scaleWidth = width_ / pixelWidth_;
    double const scaleHeight = height_ / pixelHeight_;

    int i;
    int j;

	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int mpi_size;
	MPI_Comm_size(MPI_COMM_WORLD, &mpi_size);

#pragma omp parallel for default(shared) schedule(dynamic) private(i,j) //collapse(2)
    for (i = 0; i < pixelWidth_; ++i) {
        for (j = rank; j < pixelHeight_; j = j + mpi_size) {
            // creating the ray
            Vector pixelPosition(
                    (i - pixelWidth_ / 2.0f) * static_cast<float>(scaleWidth),
                    (j - pixelHeight_ / 2.0f) * static_cast<float>(scaleHeight),
                    0
            );

            pixelPosition += static_cast<float>(screen_distance_) * direction_;
            Ray ray(origin_ + pixelPosition,
                    direction_);

            Color color = computeColor(ray, 0);
            screen[(j * pixelWidth_ + i)] = color;
			//screen[((j - rank)/mpi_size * pixelWidth_ + i)] = color;
        }
    }
	/* Create datatype for 1 column of array
	*/
	MPI_Datatype stype;
	MPI_Type_vector(pixelHeight_/mpi_size, pixelWidth_, mpi_size*pixelWidth_, MPI_FLOAT, &stype);
	MPI_Type_commit(&stype);

	//MPI_Gatherv(screen.data(), 1, &stype, );
}

void Camera::setViewer(Point const &origin, Vector const &direction, Vector const &vertical) {
    origin_ = origin;
    direction_ = direction;
    vertical_ = vertical;
}

void Camera::setProjectionScreen(double width, double height, double screen_distance) {
    width_ = width;
    height_ = height;
    screen_distance_ = screen_distance;
}

void Camera::setResolution(unsigned int pixelWidth, unsigned int pixelHeight) {
    pixelHeight_ = pixelHeight;
    pixelWidth_ = pixelWidth;
}

void Camera::setScene(Scene *scene) {
    scene_ = scene;
}

void Camera::setRecursiveParameter(unsigned int ray_per_recursion, unsigned int max_levels) {
    RAYS_PER_RECURSION = ray_per_recursion;
    MAX_LEVELS_OF_RECURSION = max_levels;
}

Color Camera::computeColor(Ray const &ray, unsigned int recursion_level) const {
    double distance(0);
    Color color(Color::Zero());

    int index(scene_->getFirstCollision(ray, distance, MIN_DIST_COLLISION));

    if (index < 0) { // there is a big black sphere all around the scene
        return color;
    }

    Primitive *primitive = scene_->getPrimitive((unsigned int) index);

    MaterialPoint materialIntersection = primitive->computeIntersectionMaterial(ray, distance);
    color += AMBIENT_COEFFICIENT * materialIntersection.material.getColor();

    Vector const &normal = materialIntersection.normal;

    // color due to light
    Color lightColor = scene_->computeLightColor(materialIntersection);
    color += lightColor;

    if (recursion_level < MAX_LEVELS_OF_RECURSION) {
        if (materialIntersection.material.getReflection().norm() != 0) {
            // reflexion color
            Ray reflection_ray(
                    materialIntersection.position,
                    ray.getDirection() - static_cast<Vector>(
                            ray.getDirection().dot(normal)
                            * 2 * normal
                    )
            );
            Color reflected_color = computeColor(reflection_ray, recursion_level + 1);
            color += materialIntersection.material.getReflection().cwiseProduct(reflected_color);
        }

        if (materialIntersection.material.getColor().norm() != 0) {
            // recursive part
            Color tmp(Color::Zero());
            std::vector<Color> parallel(RAYS_PER_RECURSION);
            std::default_random_engine generator(static_cast<unsigned int>(time(NULL)));
            std::uniform_real_distribution<double> distribution(0.0, 1.0);

            int i;
#pragma omp parallel for default(shared) private(i)
            for (i = 0; i < RAYS_PER_RECURSION; ++i) {
                Ray const &secondary_ray(
                        generateRay(materialIntersection,
                                    distribution(generator),
                                    distribution(generator)));
                float test = secondary_ray.getDirection().dot(normal);
                parallel[i] = test * computeColor(secondary_ray, recursion_level + 1);
            }

            tmp = std::accumulate(parallel.begin(), parallel.end(), tmp);
            tmp /= static_cast<float>(RAYS_PER_RECURSION);
            color += (materialIntersection.material.getColor() / 255.0f).cwiseProduct(tmp);
        }
    }


    return color;
}


Ray Camera::generateRay(MaterialPoint materialPoint, double const &epsilon1, double const &epsilon2) {
    double r(sqrt(epsilon1));
    double theta(2 * PI * epsilon2);

    Vector direction(
		static_cast<float>(r * cos(theta)),
		static_cast<float>(r * sin(theta)),
        static_cast<float>(sqrt(std::max(0.0, 1 - epsilon1)))
    );

    direction.normalize();

    Vector const &normal(materialPoint.normal);
    Eigen::Transform<float, 3, Eigen::Affine> rotation(Eigen::AngleAxis<float>(
            std::acos(Vector::UnitZ().dot(normal)),
            static_cast<Eigen::Vector3f>(Vector::UnitZ().cross(normal))
    ));

    /*Vector temp = (rotation.linear() * direction);
    temp.normalize();

    double test = temp.dot(normal);*/

    return Ray(materialPoint.position,
               static_cast<Vector>(rotation.linear() * direction).normalized());
}

