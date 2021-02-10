#include "PNG.h"

namespace PNGUtil {


    PNG::PNG(unsigned width, unsigned height)
    {
        _width = width;
        _height = height;
        image = new unsigned[_width * _height]();
    }

    PNG::PNG(PNG const& toCopy) {
        *this = toCopy;
    }

    PNG::~PNG()
    {
        delete[] image;
    }

    unsigned* PNG::GetPixel(unsigned x, unsigned y)
    {
        return &image[x + (y * _width)];
    }

    bool PNG::ReadFile(fs::path path)
    {
        delete[] image;

        vector<unsigned char> byteData;
        unsigned error = lodepng::decode(byteData, _width, _height, path.string());

        if (error) {
            cerr << "PNG could not be decoded: " << error << ": " << lodepng_error_text(error) << endl;
            return false;
        }

        image = new unsigned[_width * _height];

        for (unsigned i = 0; i < byteData.size(); i += 4) {
            unsigned pixel = CharToInt(
                byteData[i],        // r
                byteData[i + 1],    // g
                byteData[i + 2],    // b
                byteData[i + 3]);   // a
            image[i / 4] = pixel;
        }

        return true;
    }

    bool PNG::WriteFile(fs::path path)
    {
        unsigned char* byteData = new unsigned char[_width * _height * 4];

        for (unsigned i = 0; i < _width * _height; i++) {
            unsigned pixel = image[i];
            byteData[(i * 4)]       = IntToChar(pixel, 0);  // r
            byteData[(i * 4) + 1]   = IntToChar(pixel, 1);  // g
            byteData[(i * 4) + 2]   = IntToChar(pixel, 2);  // b
            byteData[(i * 4) + 3]   = IntToChar(pixel, 3);  // a
        }

        unsigned error = lodepng::encode(path.string(), byteData, _width, _height);
        if (error) {
            cerr << "PNG could not be encoded: " << error << ": " << lodepng_error_text(error) << endl;
        }

        delete[] byteData;
        return (error == 0);
    }

    void PNG::operator=(const PNG& other)
    {
        delete[] image;
        _width = other._width;
        _height = other._height;
        image = new unsigned[_width * _height];
        for (int i = 0; i < _width * _height; i++) {
            image[i] = other.image[i];
        }
    }

    bool PNG::operator==(const PNG& other) const {
        if (_width + _height != other._width + other._height) { return false; }

        for (unsigned i = 0; i < _width * _height; i++) {
            unsigned& p1 = image[i];
            unsigned& p2 = other.image[i];
            if (!(p1 == p2)) {
                return false;
            }
        }
        return true;
    }
    unsigned CharToInt(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
    {
        return	r << 24		// r
            | g << 16   // g
            | b << 8    // b
            | a;        // a
    }
    unsigned char IntToChar(unsigned integer, unsigned char d)
    {
        switch (d)
        {
        case 0:	// r
            return integer >> 24;
        case 1:	// g
            return (integer & 0x00FF0000) >> 16;
        case 2:	// b
            return (integer & 0x0000FF00) >> 8;
        default:// a
            return integer & 0x000000FF;
        }
    }
    unsigned GetAveragePixel(PNG& image)
    {
        unsigned r(0), g(0), b(0), a(0), pixels(image.Width() * image.Height());
        for (unsigned x = 0; x < image.Width(); x++)
            for (unsigned y = 0; y < image.Height(); y++) {
                unsigned* pixel = image.GetPixel(x, y);
                r += IntToChar(*pixel, 0);
                g += IntToChar(*pixel, 1);
                b += IntToChar(*pixel, 2);
                a += IntToChar(*pixel, 3);
            }
        return CharToInt(r / pixels, g / pixels, b / pixels, a / pixels);
    }

    unsigned GetAveragePixel(PNG& image, unsigned tileSize, unsigned xPos, unsigned yPos)
    {
        unsigned r(0), g(0), b(0), a(0), width(xPos + tileSize), height(yPos + tileSize);

        if (width >= image.Width()) width = image.Width() - xPos;		// Overflow: only process the pixels [x, width)
        if (height >= image.Height()) height = image.Height() - yPos;	// Overflow: only process the pixels [y, height)

        unsigned pixels = width * height;	// Total number of pixels in the assigned region

        for (unsigned x = xPos; x < width; x++) {
            for (unsigned y = yPos; y < height; y++) {
                unsigned* pixel = image.GetPixel(x, y);
                r += IntToChar(*pixel, 0);
                g += IntToChar(*pixel, 1);
                b += IntToChar(*pixel, 2);
                a += IntToChar(*pixel, 3);
            }
        }
        return CharToInt(r / pixels, g / pixels, b / pixels, a / pixels);
    }
}