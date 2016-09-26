//
// Created by gautier on 24.05.16.
//

#include <fstream>
#include "Screen.h"

Screen::Screen(unsigned int height, unsigned int width)
        : std::vector<Color>(height * width, Color::Zero()), height_(height), width_(width) { }

void Screen::writeInFile(std::string filename) {
    std::ofstream image(filename, std::ios_base::binary);
    if (!image) {
        return;
    }

    /// header of TGA
    image.put(0);
    image.put(0);
    image.put(2);  // not compress RGB

    image.put(0).put(0);
    image.put(0).put(0);
    image.put(0);

    image.put(0).put(0); // X origin
    image.put(0).put(0); // Y origin

    image.put(static_cast<unsigned char>(width_ & 0x00FF));
    image.put(static_cast<unsigned char>((width_ & 0xFF00) / 256));
    image.put(static_cast<unsigned char>(height_ & 0x00FF));
    image.put(static_cast<unsigned char>((height_ & 0xFF00) / 256));
    image.put(32);  // 24 bit bitmap
    image.put(0);
    /// end header

    for (unsigned int i(0); i < size(); ++i) {
        Color color = operator[](i);
        image.put(static_cast<unsigned char>(std::min(color.z(), 255.0f))); // the TGA store the color in inverse order
        image.put(static_cast<unsigned char>(std::min(color.y(), 255.0f)));
        image.put(static_cast<unsigned char>(std::min(color.x(), 255.0f)));
        image.put(static_cast<unsigned char>(255.0f));
    }

    image.close();
}

unsigned int Screen::getHeight() const {
    return height_;
}

unsigned int Screen::getWidth() const {
    return width_;
}







