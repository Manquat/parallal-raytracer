//
// Created by gautier on 25.05.16.
//

#include "Light.h"

Light::Light(Point const &center, Color const &color)
: center_(center), color_(color)
{ }

Color Light::computeColor(const Vector &incomingDirection, double distance) const {
    return 1/(distance * distance) * color_;
}

Point Light::getCenter() const {
    return center_;
}

Color Light::getColor() const {
    return color_;
}

Light* Light::structToLight(Light::sLight const& s_light) {
	return new Light(Point(s_light.center), Color(s_light.color));
}

Light::sLight const& Light::lightToStruct(Light const& light) {
	Light::sLight s_light;

	Point const& c(light.getCenter());
	Eigen::Map<Point>(s_light.center, c.rows(), c.cols()) = c;

	Color const& col(light.getColor());
	Eigen::Map<Point>(s_light.color, col.rows(), col.cols()) = col;

	return s_light;
}

std::ostream& operator<<(std::ostream& os, Light const& light) {
	os << "Light : Center : " << light.getCenter() << std::endl
		<< "\tColor : " << light.getColor() << std::endl;
	return os;
}







