//
// Created by gautier on 26.05.16.
//

#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H


#include "utils.h"

class Material {
public:
    Material(const Color &color, const Color &reflexion_factor, Color const &specular_factor,
                 Color const &shininess_factor);
    Material(Color const& color);

    Color getColor() const;
    Color getReflection() const;
    Color getSpecular() const;
    Color getShininess() const;

    void setColor(Color const& color);
    void setPhong(const Color &color, float reflection, float specular, float shininess = 100);
    void setReflection(Color const& reflection);
    void setSpecular(Color const& specular);
    void setShininess(Color const& shininess);
private:
    Color diffuse_;
    Color reflection_;
    Color specular_;
    Color shininess_;
};

struct MaterialPoint {
    MaterialPoint(Material const &_material, Point const &_position, Vector const &_normal, Vector const &_incident);

    Point position;
    Vector incident;
    Vector normal;
    Material material;
};


#endif //RAYTRACER_MATERIAL_H
