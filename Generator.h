//
// Created by gautier on 03.06.16.
//

#ifndef RAYTRACER_GENERATOR_H
#define RAYTRACER_GENERATOR_H


static const int lightMultiplier = 500;

static const int shininessMultiplier = 10;

#include <random>
#include "Scene.h"

class Generator {
public:
    Generator();
    Generator(unsigned long seed);

    Scene* generate(unsigned int number_of_spheres, unsigned int number_of_lights);
private:
    std::default_random_engine generator_;
};


#endif //RAYTRACER_GENERATOR_H
