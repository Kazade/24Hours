#include <cassert>
#include <SOIL/SOIL.h>

#include "kazbase/os/path.h"
#include "kazbase/fdo/base_directory.h"
#include "kazbase/exceptions.h"

#include "level.h"

Level::Level(uint32_t chunks_across, uint32_t chunks_down, std::string tile_base_path):
    tile_base_path_(tile_base_path),
    chunks_across_(chunks_across),
    chunks_down_(chunks_down) {

}

void Level::add_tile(const std::string& filename) {
    std::string final = filename;
    if(!tile_base_path_.empty()) {
        final = os::path::join(tile_base_path_, filename);
    }
    
    if(!os::path::exists(final)) {   
        final = fdo::xdg::find_data_file(final);
    }
    
    if(final.empty()) {
        throw LogicError("Unable to find file: " + filename);
    }
    
    int width, height, channels;
    unsigned char *data = SOIL_load_image(final.c_str(), &width, &height, &channels, SOIL_LOAD_AUTO);
    if(!data) {
        throw RuntimeError("Not a suitable file: " + filename);
    }
    
    if(width != TILE_SIZE || height != TILE_SIZE) {
        throw LogicError("Attempted to load a tile of an invalid size: " + filename);
    }
    
    if(channels != 4) {
        throw LogicError("Attempted to load a tile without an alpha channel: " + filename);
    }
    
    Tile::ptr new_tile(new Tile);
    std::copy(data, data + (width * height * channels), new_tile->data);    
    all_tiles_.push_back(new_tile);
    
    SOIL_free_image_data(data);
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
