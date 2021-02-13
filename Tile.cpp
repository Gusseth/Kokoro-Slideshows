#include "Tile.h"

namespace TilerUtils {
    PNG Tiler::AverageTiler(PNG& target)
    {
        return target;
    }

    PNG Tiler::ExpandTiler(PNG& target)
    {
        Shameimaru::ThreadPool a = Shameimaru::ThreadPool(8);
        unsigned width = target.Width();
        unsigned height = target.Height();
        PNG image(width * tileSize, height * tileSize);
        

        for (unsigned x = 0; x < width - 1; x++) {
            for (unsigned y = 0; y < height - 1; y++) {
                a.enqueue([&] {
                    
                    unsigned* oldPixel = target.GetPixel(x, y);
                    if (IntToChar(*oldPixel, 3) > 25) {
                        unsigned nn = tree.FindNearestNeighbor(*oldPixel);

                        PNG thumb = tiles[nn];

                        for (unsigned x1 = 0; x1 < tileSize; x1++) {
                            for (unsigned y1 = 0; y1 < tileSize; y1++) {
                                unsigned* currentPixel = image.GetPixel(x * tileSize + x1, y * tileSize + y1);
                                *currentPixel = *thumb.GetPixel(x1, y1);
                            }
                        }
                    }
                    else {
                        for (unsigned x1 = 0; x1 < tileSize; x1++) {
                            for (unsigned y1 = 0; y1 < tileSize; y1++) {
                                    unsigned* currentPixel = image.GetPixel(x * tileSize + x1, y * tileSize + y1);
                                    *currentPixel = 0; 
                            }
                        }
                    }
                    });
            }
        }
        return image;
    }

    map<unsigned, PNG> Tiler::BuildTile(fs::path path, unsigned tilesize)
    {
        map<unsigned, PNG> tilemap;
        for (const auto& tileFile : fs::directory_iterator(path)) {
            PNG t(tileFile.path());
            tilemap.insert({ GetAveragePixel(t, tilesize),t });
        }

        tiles = tilemap;
        tree = RGBATree(tilemap);
        return tilemap;
    }
}