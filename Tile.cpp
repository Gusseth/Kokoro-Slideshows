#include "Tile.h"

PNG& Tiler::Tiler::AverageTiler(PNG& target)
{
    PNG newImage(target.Width(), target.Height());
    return newImage;
}
