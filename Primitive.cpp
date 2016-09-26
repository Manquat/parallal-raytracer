//
// Created by gautier on 15.05.16.
//

#include "Primitive.h"

Primitive::Primitive(Material const &material)
        : material_(material)
{}

Color Primitive::getColor() const {
    return material_.getColor();
}

Color Primitive::getReflection() const {
    return material_.getReflection();
}

Color Primitive::getSpecular() const {
    return material_.getSpecular();
}

Color Primitive::getShininess() const {
    return material_.getShininess();
}

Material Primitive::getMaterial() const {
    return material_;
}

void Primitive::setColor(Color const &color) {
    material_.setColor(color);
}

void Primitive::setReflection(const Color &reflection) {
    material_.setReflection(reflection);
}

void Primitive::setMaterial(Material const &material) {
    material_ = material;
}

std::string Primitive::toString() const {
	std::stringstream ss;
	ss << "\tColor : " << getColor() << std::endl
		<< "\tReflection : " << getReflection() << std::endl
		<< "\tSpecular : " << getSpecular() << std::endl
		<< "\tShininess : " << getShininess() << std::endl;
	return ss.str();
}


std::ostream& operator<<(std::ostream& os, Primitive const& primitive) {
	os << primitive.toString();
	return os;
}

















