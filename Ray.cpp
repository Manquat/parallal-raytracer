//
// Created by gautier on 14.05.16.
//

#include "Ray.h"

Ray::Ray(Point start, Vector direction)
        : origin_(start), direction_(direction.normalized()) { }

Point Ray::getOrigin() const {
    return origin_;
}

Vector Ray::getDirection() const {
    return direction_;
}