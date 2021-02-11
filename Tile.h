#pragma once
#include <map>
#include <filesystem>
#include "PNG.h"
#include "RGBATree.h"

namespace fs = std::filesystem;
using namespace std;
using namespace PNGUtil;

namespace TilerUtils {
	class Tiler
	{
	public:
		Tiler(unsigned tilesize) { tileSize = tilesize; };
		Tiler(fs::path path, unsigned tilesize) { tileSize = tilesize; BuildTile(path, tilesize); };

		PNG AverageTiler(PNG& target);
		PNG ExpandTiler(PNG& target);

		map<unsigned, PNG> BuildTile(fs::path path, unsigned tileSize);
	private:
		unsigned tileSize;
		map<unsigned, PNG> tiles;
		RGBATree tree;
	};
}

