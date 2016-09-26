//
// Created by gautier on 03.06.16.
//

#include "Generator.h"
#include "Sphere.h"

Generator::Generator()
        : generator_() { }

Generator::Generator(unsigned long seed)
        : generator_(seed) { }

Scene *Generator::generate(unsigned int number_of_spheres, unsigned int number_of_lights) {
    Scene *scene = new Scene();

    std::uniform_real_distribution<double> pointDist(-25, 25);
    auto pointGen = std::bind(pointDist, generator_);

    std::uniform_real_distribution<double> radiusDist(1.0, 10);
    auto radiusGen = std::bind(radiusDist, generator_);

    std::uniform_real_distribution<double> colorDist(0.0, 255);
    auto colorGen = std::bind(colorDist, generator_);

    for (unsigned int i(0); i < number_of_spheres; ++i) {
        Point point(pointGen(), pointGen(), -std::abs(pointGen()));
        double radius(radiusGen());

        //Color color(colorGen(), colorGen(), colorGen());
        Color color(255, 0, 0);
        Color reflexion(colorGen(), colorGen(), colorGen());
        Color specular(colorGen(), colorGen(), colorGen());
        Color shininess(colorGen(), colorGen(), colorGen());
        shininess *= shininessMultiplier;
        Material material(color, reflexion, specular, shininess);

        Sphere *sphere = new Sphere(point, radius);
        sphere->setMaterial(material);
        scene->addPrimitive(sphere);
    }

    for (unsigned int j(0); j < number_of_lights; ++j) {
        Point point(pointGen(), pointGen(), -std::abs(pointGen()));
        Color color(colorGen(), colorGen(), colorGen());
        color *= lightMultiplier;

        Light *light = new Light(point, color);
        scene->addLight(light);
    }

    scene->addLight(new Light(Point(15, 10, 0), lightMultiplier * Color::Ones()));
    scene->addLight(new Light(Point(-50, 0, 0), lightMultiplier * Color::Ones()));

    return scene;
}





