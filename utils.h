//
// Created by gautier on 09.05.16.
//

#ifndef RAYTRACER_UTILS_H
#define RAYTRACER_UTILS_H

#include "Eigen/Core"
#define _USE_MATH_DEFINES
#include <math.h>

constexpr int VECTOR_SIZE = 3;
typedef Eigen::Vector3f Point;
typedef Eigen::Vector3f Vector;

constexpr int COLOR_SIZE = 3;
typedef Eigen::Vector3f Color;
//const auto& Red = Eigen::Vector3f::UnitX;
//const auto& Green = Eigen::Vector3f::UnitY;
//const auto& Blue = Eigen::Vector3f::UnitZ;

constexpr double PI = M_PI;

#endif //RAYTRACER_UTILS_H
