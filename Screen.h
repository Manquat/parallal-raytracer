//
// Created by gautier on 24.05.16.
//

#ifndef RAYTRACER_SCREEN_H
#define RAYTRACER_SCREEN_H


#include <vector>
#include "utils.h"

class Screen : public std::vector<Color> {
public:
    Screen(unsigned int height, unsigned int width);

    unsigned int getHeight() const;
    unsigned int getWidth() const;

    void writeInFile(std::string filename);

private:

    unsigned int height_;
    unsigned int width_;
};


#endif //RAYTRACER_SCREEN_H
