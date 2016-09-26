//
// Created by gautier on 15.05.16.
//

#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H


#include "Primitive.h"
#include "Light.h"
#include <vector>

class Scene {
	friend class Serializer;
public:
    Scene();
    ~Scene();

    unsigned long getNumberOfPrimitive() const;
    Primitive* getPrimitive(unsigned int index) const;
    int getFirstCollision(Ray const &ray, double &distance, double minimal_distance,
                          double maximal_distance = std::numeric_limits<double>::max()) const;

    Primitive* removePrimitive(unsigned int index);
    bool addPrimitive(Primitive* primitive);

    Light* removeLight(unsigned int index);
    bool addLight(Light *light);

    Color computeLightColor(MaterialPoint const &materialPoint) const;

private:
    std::vector<Primitive*> primitives_;
    std::vector<Light*> lights_;
    float specular_enhancement_ = 10;

	friend std::ostream& operator<<(std::ostream& os, Scene const& scene);
};

std::ostream& operator<<(std::ostream& os, Scene const& scene);


#endif //RAYTRACER_SCENE_H
