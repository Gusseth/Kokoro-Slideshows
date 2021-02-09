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

		void operator=(const PNG& other);
		bool operator==(const PNG& other) const;

	private:
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
	unsigned CharToInt(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 0xFF) {
		return	r << 24		// r
				| g << 16   // g
				| b << 8    // b
				| a;        // a
	}

	/// <summary>
	/// Returns the d-th byte in integer. Starts at 0. Big endian.
	/// </summary>
	/// <param name="integer">Master unsigned integer</param>
	/// <param name="d">Dimension of the byte</param>
	/// <returns>The d-th byte of the integer.</returns>
	unsigned char IntToChar(unsigned integer, unsigned char d) {
		switch (d)
		{
		case 0:	// r
			return integer >> 24;
		case 1:	// g
			return integer & 0x00FF0000 >> 16;
		case 2:	// b
			return integer & 0x0000FF00 >> 8;
		default:// a
			return integer & 0x000000FF;
		}
	}
}

