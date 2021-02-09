#pragma once
#include "PNG.h"
#include <map>
#include <filesystem>
namespace fs = std::filesystem;
using namespace std;
using namespace PNGUtil;

namespace Tiler {
	class Tiler
	{
	public:
		PNG& AverageTiler(PNG& target);
		PNG& ExpandTiler(PNG& target);

		void BuildTile(fs::path path);
	private:
		map<unsigned, PNG>* tilemap;
	};
}

