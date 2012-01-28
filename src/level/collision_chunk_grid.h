#ifndef TWF_COLLISION_MAP_H
#define TWF_COLLISION_MAP_H

#include "level/chunk_grid.h"
#include "level/tile_template.h"

typedef TileTemplate<1> SolidityTile;

class CollisionChunkGrid : public ChunkGrid<SolidityTile> {
public:
    CollisionChunkGrid():
        ChunkGrid<SolidityTile>() {}
        
    CollisionChunkGrid(uint32_t chunks_across, uint32_t chunks_down):
        ChunkGrid<SolidityTile>(chunks_across, chunks_down) {}
        
    std::pair<Point, bool> ray_intersect(const Point& start, const Vec2f& dir) {}
};

#endif
