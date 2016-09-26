//
// Created by gautier on 15.05.16.
//

#include "Scene.h"
#include "Sphere.h"

Scene::Scene()
        : primitives_(), lights_() {
    Sphere *sphere = new Sphere(Point(0, 0, 0), 100);
    Material material(Color::Zero());
    //Material material(255*Color::Ones());
    //material.setPhong(0,1,0);
    sphere->setMaterial(material);
    addPrimitive(sphere);
}

Scene::~Scene() {
    for (Primitive *primitive : primitives_) {
        delete primitive;
    }

    for (Light *light : lights_) {
        delete light;
    }
}

unsigned long Scene::getNumberOfPrimitive() const {
    return primitives_.size();
}

Primitive *Scene::getPrimitive(unsigned int index) const {
    if (index >= primitives_.size()) {
        throw std::out_of_range("The index is out of the range of the primitives");
    }
    return primitives_[index];
}

int Scene::getFirstCollision(Ray const &ray, double &distance, double minimal_distance,
                             double maximal_distance) const {
    double min_dist = std::numeric_limits<double>::max();
    int min_primitive_index = -1;

    for (unsigned int i(0); i < primitives_.size(); ++i) {
        double temp_dist = std::numeric_limits<double>::max();

        bool test = primitives_[i]->intersect(ray, temp_dist, minimal_distance);

        if (test && min_dist > temp_dist && temp_dist < maximal_distance) {
            min_dist = temp_dist;
            min_primitive_index = i;
        }
    }

    if (min_primitive_index != -1) {
        distance = min_dist;
    }

    return min_primitive_index;
}

Primitive *Scene::removePrimitive(unsigned int index) {
    std::vector<Primitive *>::iterator iterator = primitives_.begin();
    std::advance(iterator, index);

    Primitive *primitive = *iterator;

    primitives_.erase(iterator);

    return primitive;
}

bool Scene::addPrimitive(Primitive *primitive) {
    if (std::find(primitives_.begin(), primitives_.end(), primitive) != primitives_.end()) {
        return false;
    }

    primitives_.push_back(primitive);
    return true;
}

Light *Scene::removeLight(unsigned int index) {
    std::vector<Light *>::iterator iterator = lights_.begin();
    std::advance(iterator, index);

    Light *light = *iterator;

    lights_.erase(iterator);

    return light;
}

bool Scene::addLight(Light *light) {
    if (std::find(lights_.begin(), lights_.end(), light) != lights_.end()) {
        return false;
    }

    lights_.push_back(light);
    return true;
}

Color Scene::computeLightColor(MaterialPoint const &materialPoint) const {
    Color totalColor(Color::Zero());
    Point const &point(materialPoint.position);
    Vector const &normal(materialPoint.normal);
    Color diffuseColor(Color::Zero());
    Color specularColor(Color::Zero());

    for (Light *light : lights_) {
        diffuseColor = Color::Zero();
        specularColor = Color::Zero();

        Point lightDirection = light->getCenter() - point;
        double ligthDistance = lightDirection.norm();
        lightDirection.normalize();

        double temp;
        // if there something between the light and the point
        if (getFirstCollision(Ray(point, lightDirection), temp, 0.001, ligthDistance) != -1) {
            continue;
        }

        const Color &lightColor = light->computeColor(lightDirection, ligthDistance);

        //diffuse component
        float cosPhi = (lightDirection.dot(normal));

        // if the light is under the horizon from the point
        if (cosPhi < 0) {
            continue;
        }

        diffuseColor = cosPhi * lightColor.cwiseProduct(materialPoint.material.getColor());
        // diffuseColor = diffuseColor.cwiseProduct(materialPoint.material.getColor());

        //specular component
        Vector reflected = static_cast<Vector>(2 * cosPhi * normal) - lightDirection;
        double cosOmega = reflected.dot(materialPoint.incident);

        for (unsigned int i(0); i < specularColor.size(); ++i) {
            specularColor[i] = static_cast<float>(pow(cosOmega, materialPoint.material.getShininess()[i]))
                               * specular_enhancement_ * materialPoint.material.getSpecular()[i];
        }
        specularColor = lightColor.cwiseProduct(specularColor);

        totalColor += diffuseColor + specularColor;
    }

    return totalColor;
}


std::ostream& operator<<(std::ostream& os, Scene const& scene) {
	os << "===================================" << std::endl
		<< "Scene :" << std::endl;
	for (Primitive* primitive : scene.primitives_)
	{
		os << "***********************************" << std::endl
			<< primitive->toString() << std::endl;
	}

	for (Light* light : scene.lights_)
	{
		os << "***********************************" << std::endl
			<< *light << std::endl;
	}

	return os;
}













