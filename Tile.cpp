#include "Tile.h"

namespace TilerUtils {
    PNG& Tiler::AverageTiler(PNG& target)
    {
        return target;
    }

    map<unsigned, PNG> Tiler::BuildTile(fs::path path, unsigned tileSize)
    {
        map<unsigned, PNG> tilemap;
        for (const auto& tileFile : fs::directory_iterator(path)) {
            PNG t;
            t.ReadFile(tileFile.path());
            unsigned pixel = GetAveragePixel(t, tileSize);
            tilemap.insert({ 1,t });
        }

        //tree.Rebuild(tilemap);
        return tilemap;
    }
}