#include <cassert>
#include <SOIL/SOIL.h>

#include "level.h"

Level::Level(uint32_t chunks_across, uint32_t chunks_down):
    chunks_across_(chunks_across),
    chunks_down_(chunks_down) {

}

void Level::add_tile(const std::string& filename) {
    
}

void Level::add_chunk(std::vector<uint32_t> tile_indexes) {
    assert(chunks_.size() < (chunks_across_ * chunks_down_) - 1);
    
    Chunk::ptr new_chunk(new Chunk);
    int i = 0;
    for(uint32_t tile: tile_indexes) {
        new_chunk->tiles[i++] = tile;
    }
    chunks_.push_back(new_chunk);
}
