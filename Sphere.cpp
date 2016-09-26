//
// Created by gautier on 14.05.16.
//

#include "Sphere.h"
#include "Eigen/Dense"
#include <iostream>

Sphere::Sphere(Point const &center, double radius)
        : Primitive(Material(255 * Color::UnitX())), center_(center), radius_(radius) { }


bool Sphere::intersect(Ray const &ray, double &intersection, double const &minimal_distance) const {
    Point distance = ray.getOrigin() - center_;
    Vector direction(ray.getDirection());

    if (distance.cross(direction).norm() > radius_) // the ray never intersect the circle
    {
        return false;
    }

    double b = 2 * direction.dot(distance);

    double delta = b * b - 4 * (distance.norm() * distance.norm() - radius_ * radius_);

    if (delta < 0) {
        return false;
    }

    double t0 = (-b - sqrt(delta)) / 2;
    double t1 = (-b + sqrt(delta)) / 2;

    if (t0 > minimal_distance) {
        intersection = t0;
        return true;
    }
    if (t1 > minimal_distance) {
        intersection = t1;
        return true;
    }

    return false;
}

MaterialPoint Sphere::computeIntersectionMaterial(Ray const &ray, double const &distance) const {
    MaterialPoint materialPoint(
            material_,
            ray.getOrigin() + static_cast<Vector>(static_cast<float>(distance) * ray.getDirection()),
            Vector::Zero(),
            ray.getDirection()
    );

    materialPoint.normal = (materialPoint.position - center_).normalized();

    return materialPoint;
}

Point Sphere::getCenter() const {
    return center_;
}

double Sphere::getRadius() const {
    return radius_;
}

Sphere *Sphere::structToSphere(Sphere::sSphere const& s_sphere) {
    Sphere *sphere = new Sphere(Point(s_sphere.center), s_sphere.radius);
    sphere->setMaterial(Material(
            Color(s_sphere.color),
            Color(s_sphere.reflection),
            Color(s_sphere.specular),
            Color(s_sphere.shininess)
    ));
    return sphere;
}

Sphere::sSphere const& Sphere::sphereToStruct(Sphere const& sphere) {
    Sphere::sSphere s_sphere;

	Point const& c(sphere.getCenter());
	Eigen::Map<Point>(s_sphere.center, c.rows(), c.cols()) = c;

    s_sphere.radius = static_cast<float>(sphere.getRadius());
	
	Color const& col(sphere.getColor());
	Eigen::Map<Point>(s_sphere.color, col.rows(), col.cols()) = col;
    
	Color const& ref(sphere.getReflection());
	Eigen::Map<Point>(s_sphere.reflection, ref.rows(), ref.cols()) = ref;

	Color const& spec(sphere.getSpecular());
	Eigen::Map<Point>(s_sphere.specular, spec.rows(), spec.cols()) = spec;
    
	Color const& shin(sphere.getShininess());
	Eigen::Map<Point>(s_sphere.shininess, shin.rows(), shin.cols()) = shin;

    return s_sphere;
}

std::string Sphere::toString() const {
	std::stringstream ss;
	ss << "Sphere : Center : " << getCenter() << std::endl
		<< "\tRadius : " << getRadius() << std::endl
		<<	Primitive::toString();
	return ss.str();
}


std::ostream& operator<<(std::ostream& os, Sphere const& sphere) {
    os << "Sphere : Center : " << sphere.getCenter() << std::endl
    << "\tRadius : " << sphere.getRadius() << std::endl;
    return os;
}














