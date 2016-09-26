//
// Created by gautier on 25.05.16.
//

#ifndef RAYTRACER_LIGHT_H
#define RAYTRACER_LIGHT_H


#include "utils.h"
#include "Ray.h"

class Light {
	friend class Serializer;
public:
    Light(Point const& center, Color const& color);

    Color computeColor(const Vector &incomingDirection, double distance) const;

    Point getCenter() const;

    Color getColor() const;

private:
    Point center_;
    Color color_;

	struct sLight {
		float center[VECTOR_SIZE];
		float color[COLOR_SIZE];
	};

	static Light* structToLight(sLight const& s_light);
	static sLight const& lightToStruct(Light const& light);
};

std::ostream& operator<<(std::ostream& os, Light const& light);


#endif //RAYTRACER_LIGHT_H
