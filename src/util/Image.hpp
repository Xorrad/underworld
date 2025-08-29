#pragma once

class Image {
public:
    Image();
    Image(uint32_t width, uint32_t height);
    Image(uint32_t width, uint32_t height, std::vector<Color> pixels);

    uint32_t GetWidth() const;
    uint32_t GetHeight() const;
    std::vector<Color>& GetPixels();
    Color GetPixel(uint32_t x, uint32_t y) const;

    static Image LoadFromFile(const std::string& filePath);

private:
    uint32_t m_Width;
    uint32_t m_Height;
    std::vector<Color> m_Pixels;
};