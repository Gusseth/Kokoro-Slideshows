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
            image[i / 4] =
                  byteData[i]     << 24   // r
                | byteData[i + 1] << 16   // g
                | byteData[i + 2] << 8    // b
                | byteData[i + 3];        // a
        }

        return true;
    }

    bool PNG::WriteFile(fs::path path)
    {
        unsigned char* byteData = new unsigned char[_width * _height * 4];

        for (unsigned i = 0; i < _width * _height; i++) {
            unsigned pixel = image[i];
            byteData[(i * 4)]       = pixel              >> 24;  // r
            byteData[(i * 4) + 1]   = pixel & 0x00FF0000 >> 16;  // g
            byteData[(i * 4) + 2]   = pixel & 0x0000FF00 >> 8;   // b
            byteData[(i * 4) + 3]   = pixel & 0x000000FF;        // a
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
}