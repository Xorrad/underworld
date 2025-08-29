#include "Image.hpp"

#include <lodepng/lodepng.h>

Image::Image() : Image(0, 0, {}) {}

Image::Image(uint32_t width, uint32_t height) : Image(width, height, {}) {}

Image::Image(uint32_t width, uint32_t height, std::vector<Color> pixels) :
    m_Width(width),
    m_Height(height),
    m_Pixels(pixels)
{}

uint32_t Image::GetWidth() const {
    return m_Width;
}

uint32_t Image::GetHeight() const {
    return m_Height;
}

std::vector<Color>& Image::GetPixels() {
    return m_Pixels;
}

Color Image::GetPixel(uint32_t x, uint32_t y) const {
    return m_Pixels[y * m_Width + x];
}

Image Image::LoadFromFile(const std::string& filePath) {
    std::vector<uint8_t> rawPixels;
    uint32_t width = 0;
    uint32_t height = 0;

    uint32_t error = lodepng::decode(rawPixels, width, height, filePath);
    if(error) return Image();

    Image image = Image(width, height);
    std::vector<Color>& pixels = image.GetPixels();
    pixels.resize(width * height);

    for (uint32_t i = 0; i < pixels.size(); i++) {
        pixels[i].r = rawPixels[4*i];
        pixels[i].g = rawPixels[4*i+1];
        pixels[i].b = rawPixels[4*i+2];
        pixels[i].a = rawPixels[4*i+3];
    }
    
    return image;
}