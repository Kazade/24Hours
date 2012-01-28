#ifndef TWF_COLOUR_CHUNK_GRID_H
#define TWF_COLOUR_CHUNK_GRID_H

#include "level/chunk_grid.h"
#include "level/tile_template.h"

typedef TileTemplate<4> Tile;

class ColourChunkGrid : public ChunkGrid<Tile> {
public:
    ColourChunkGrid():
        ChunkGrid<Tile>() {}
        
    ColourChunkGrid(uint32_t chunks_across, uint32_t chunks_down):
        ChunkGrid<Tile>(chunks_across, chunks_down) {}
};

#endif
