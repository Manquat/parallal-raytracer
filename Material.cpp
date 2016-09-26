//
// Created by gautier on 26.05.16.
//

#include "Material.h"

Material::Material(const Color &color, const Color &reflexion_factor, Color const &specular_factor,
                   Color const &shininess_factor)
        : diffuse_(color), reflection_(reflexion_factor),
          specular_(specular_factor), shininess_(shininess_factor)
{ }

Material::Material(Color const &color)
        : diffuse_(color), reflection_(Color::Zero()),
          specular_(Color::Zero()), shininess_(Color::Zero())
{ }

Color Material::getColor() const {
    return diffuse_;
}

Color Material::getReflection() const {
    return reflection_;
}

Color Material::getSpecular() const {
    return specular_;
}

Color Material::getShininess() const {
    return shininess_;
}

void Material::setColor(const Color &color) {
    diffuse_ = color;
}

void Material::setPhong(const Color &color, float reflection, float specular, float shininess) {
    diffuse_ = color;
    reflection_ = reflection * Color::Ones();
    specular_ = specular * Color::Ones();
    shininess_ = shininess * Color::Ones();
}

void Material::setReflection(Color const &reflection) {
    reflection_ = reflection;
}

void Material::setSpecular(Color const &specular) {
    specular_ = specular;
}

void Material::setShininess(Color const &shininess) {
    shininess_ = shininess;
}


MaterialPoint::MaterialPoint(Material const &_material, Point const &_position, Vector const &_normal,
                             Vector const &_incident)
        : material(_material), position(_position), normal(_normal), incident(_incident) { }

