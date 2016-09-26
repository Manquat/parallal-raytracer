//
// Created by gautier on 15.05.16.
//

#ifndef RAYTRACER_PRIMITIVE_H
#define RAYTRACER_PRIMITIVE_H


#include "Ray.h"
#include "Material.h"

class Primitive {
public:
    Primitive(Material const& material);

    virtual ~Primitive() { }

    /**
     * Test if the ray given intersects the primitive. If yes, the distance
     * of intersection is store in the intersection variable given.
     * @param ray           the ray to test
     * @param intersection  the distance of the intersection in regards of
     *                      the origin of the ray
     * @return True if it's intersect, false otherwise
     */
    virtual bool intersect(Ray const &ray, double &intersection, double const &minimal_distance) const = 0;

    virtual MaterialPoint computeIntersectionMaterial(Ray const &ray, double const &distance) const = 0;

    Color getColor() const;
    Color getReflection() const;
    Color getSpecular() const;
    Color getShininess() const;
    Material getMaterial() const;

    void setColor(Color const &color);
    void setReflection(const Color &reflection);
    void setMaterial(Material const& material);

	virtual std::string toString() const;

protected:
    /// Material of the primitive
    Material material_;
};

std::ostream& operator<<(std::ostream& os, Primitive const& primitive);

#endif //RAYTRACER_PRIMITIVE_H
