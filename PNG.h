#pragma once

#pragma warning( disable : 26451 ) // Your memory will burn first for it to even be a problem...
#include "util/lodepng/lodepng.h"
#include <filesystem>
#include <iostream>
namespace fs = std::filesystem;
using namespace std;

namespace PNGUtil {
	class PNG
	{
	public:
		/// <summary>
		/// Creates an empty PNG file with nothing.
		/// </summary>
		PNG() { _width = 0; _height = 0; image = NULL; }

		/// <summary>
		/// Creates a PNG with specified width and height.
		/// </summary>
		/// <param name="width">Width of the image.</param>
		/// <param name="height">Height of the image.</param>
		PNG(unsigned width, unsigned height);

		/// <summary>
		/// Creates a new PNG from a copy
		/// </summary>
		/// <param name="toCopy">Master image to be copied.</param>
		PNG(PNG const& toCopy);

		/// <summary>
		/// Creates a PNG and reads a .png file from the specified path.
		/// </summary>
		/// <param name="path">Path to the .png file.</param>
		PNG(fs::path path) { ReadFile(path); }
		
		/// <summary>
		/// Deletes this instance from memory.
		/// </summary>
		~PNG();

		/// <summary>
		/// Returns the width of the image.
		/// </summary>
		/// <returns>Width of the image.</returns>
		unsigned Width() { return _width; }

		/// <summary>
		/// Returns the height of the image.
		/// </summary>
		/// <returns>Height of the image.</returns>
		unsigned Height() { return _height; }

		/// <summary>
		/// Returns a pointer to a pixel located on (x,y).
		/// 
		/// No guards, so check for segfaults. You suck if this segfaults.
		/// </summary>
		/// <param name="x">x-position of the pixel. 0 = left.</param>
		/// <param name="y">y-position of the pixel. 0 = top.</param>
		/// <returns>Pointer to pixel (x,y).</returns>
		unsigned* GetPixel(unsigned x, unsigned y);

		/// <summary>
		/// Reads a .png file into memory.
		/// </summary>
		/// <param name="path">Path to file including file name.</param>
		/// <returns>True if successful.</returns>
		bool ReadFile(fs::path path);

		/// <summary>
		/// Writes this image into a .png file.
		/// </summary>
		/// <param name="path">Path to file including file name.</param>
		/// <returns>True if successful.</returns>
		bool WriteFile(fs::path path);

		PNG const& operator= (PNG const& other);
		bool operator==(const PNG& other) const;

	private:
		void copy(const PNG & other);

		unsigned* image;		// Image data as an array of unsigned integers.
		unsigned _width;		// Width of the image.
		unsigned _height;		// Height of the image.
	};

	/// <summary>
	/// Converts three (max 4) bytes into an unsigned integer. Big endian.
	/// </summary>
	/// <param name="r">Red dimension</param>
	/// <param name="g">Green dimension</param>
	/// <param name="b">Blue dimension</param>
	/// <param name="a">Alpha dimension (Default: 255)</param>
	/// <returns>Unsigned integer of all bytes combined in big endian.</returns>
	unsigned CharToInt(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 0xFF);

	/// <summary>
	/// Returns the d-th byte in integer. Starts at 0. Big endian.
	/// </summary>
	/// <param name="integer">Master unsigned integer</param>
	/// <param name="d">Dimension of the byte</param>
	/// <returns>The d-th byte of the integer.</returns>
	unsigned char IntToChar(unsigned integer, unsigned char d);

	/// <summary>
	/// Returns the average pixel of an entire image file.
	/// </summary>
	/// <param name="image">The master image.</param>
	/// <returns>A pixel.</returns>
	unsigned GetAveragePixel(PNG& image);

	/// <summary>
	/// Returns the average pixel of region [x, x + tileSize), [y, ,y + tileSize) under trivial conditions.
	/// 
	/// Guards for boundaries, will never overflow the actual image size.
	/// </summary>
	/// <param name="image">The master image.</param>
	/// <param name="tileSize">Size of the region to be probed.</param>
	/// <param name="x">x-position of the top-left pixel of the region.</param>
	/// <param name="y">y-position of the top-left pixel of the region.</param>
	/// <returns>A pixel.</returns>
	unsigned GetAveragePixel(PNG& image, unsigned tileSize, unsigned xPos = 0, unsigned yPos = 0);
}

