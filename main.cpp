#pragma once
#include <iostream>
#include <filesystem>
#include "PNG.h"
#include "Tile.h"

namespace fs = std::filesystem;
using namespace TilerUtils;

int main(int argc, char* argv[]) {
	PNG input(fs::path("test/banner.png"));

	Tiler tiler(16);
	tiler.BuildTile(fs::path("test/lib/"), 16);

	//PNG output = tiler.AverageTiler(input);

	input.WriteFile(fs::path("test/test.png"));

	return 0;
}