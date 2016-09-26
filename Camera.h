//
// Created by gautier on 15.05.16.
//

#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H

#include "Scene.h"
#include "Screen.h"
#include "Ray.h"
#include "Material.h"

class Camera {
public:
    Camera(Scene* scene, unsigned int pixelWidth, unsigned int pixelHeight, double width, double height, double screen_distance,
           Point const& origin = Point::Zero(),
           Vector const& direction = Vector::UnitX(),
           Vector const& vertical = Vector::UnitZ());

    ~Camera(){};

    void draw(Screen& screen) const;
    void setViewer(Point const& origin, Vector const& direction, Vector const& vertical);
    void setProjectionScreen(double width, double height, double screen_distance);
    void setResolution(unsigned int pixelWidth, unsigned int pixelHeight);
    void setScene(Scene* scene);
    void setRecursiveParameter(unsigned int ray_per_recursion, unsigned int max_levels);

    static Ray generateRay(MaterialPoint materialPoint, double const &epsilon1, double const &epsilon2);

private:
    Scene* scene_;
    Point origin_;
    Vector direction_;
    Vector vertical_;

    unsigned int pixelWidth_;
    unsigned int pixelHeight_;
    double width_;
    double height_;
    double screen_distance_;

    Color computeColor(Ray const &ray, unsigned int recursion_level) const;

    unsigned int RAYS_PER_RECURSION = 20;
    unsigned int MAX_LEVELS_OF_RECURSION = 3;
    constexpr static float AMBIENT_COEFFICIENT = 0.1f;
    constexpr static double MIN_DIST_COLLISION = 0.01;
};


#endif //RAYTRACER_RAYTRACER_H
