#pragma once
#include <map>
#include <mutex>
#include <filesystem>
#include "PNG.h"
#include "RGBATree.h"
#include "ThreadPool.h"

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

		map<unsigned, PNG> BuildTile(fs::path path, unsigned tilesize);
	private:
		unsigned tileSize;
		map<unsigned, PNG> tiles;
		RGBATree tree;
		mutex m;
	};
}

