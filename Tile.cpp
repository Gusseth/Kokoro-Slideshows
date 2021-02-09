#include "Tile.h"

PNG& Tiler::Tiler::AverageTiler(PNG& target)
{
    PNG newImage(target.Width(), target.Height());
    return newImage;
}

void Tiler::Tiler::BuildTile(fs::path path, unsigned tileSize)
{
    delete[] tilemap;
    tilemap = new map<unsigned, PNG>();
    for (const auto& tileFile : fs::directory_iterator(path)) {
        PNG tile(tileFile);
        tilemap->insert({ GetAveragePixel(tile), tile });
    }
}
