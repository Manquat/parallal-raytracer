//
// Created by gautier on 14.05.16.
//

#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H


#include "Primitive.h"
#include "Serializer.h"

class Sphere : public Primitive{
    friend class Serializer;
private:
    Point center_;
    double radius_;

public:
    Sphere(Point const& center, double radius);

    virtual bool intersect(Ray const &ray, double &intersection, double const &minimal_distance) const;

    virtual MaterialPoint computeIntersectionMaterial(Ray const &ray, double const &distance) const;

    Point getCenter() const;
    double getRadius() const;

	virtual std::string toString() const;

private:
    struct sSphere {
        float center[VECTOR_SIZE];
        float radius;
        float color[COLOR_SIZE];
        float reflection[COLOR_SIZE];
        float specular[COLOR_SIZE];
        float shininess[COLOR_SIZE];
    };

    static Sphere* structToSphere(sSphere const& s_sphere);
    static sSphere const& sphereToStruct(Sphere const& sphere);
};

std::ostream& operator<<(std::ostream& os, Sphere const& sphere);


#endif //RAYTRACER_SPHERE_H
