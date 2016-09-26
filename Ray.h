//
// Created by gautier on 14.05.16.
//

#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H


#include "utils.h"

class Ray {
private:
    Point origin_;
    Vector direction_;

public:
    Ray(Point start, Vector direction);

    Point getOrigin() const;
    Vector getDirection() const;
};


#endif //RAYTRACER_RAY_H
