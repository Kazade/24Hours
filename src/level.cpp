#include <cassert>

#include "kazbase/os/path.h"
#include "kazbase/fdo/base_directory.h"
#include "kazbase/exceptions.h"

#include "level.h"

Level::Level(uint32_t chunks_across, uint32_t chunks_down, 
    std::string tile_base_path, 
    uint32_t colour_layers):
    tile_base_path_(tile_base_path) {

    colour_layers_.resize(colour_layers);

    for(uint32_t i = 0; i < colour_layers; ++i) {
        colour_layers_[i].resize(chunks_across, chunks_down);
    }    
    
    for(uint32_t i = 0; i < COLLISION_LAYER_MAX; ++i) {
        collision_maps_[i].resize(chunks_across, chunks_down);
    }    
}

std::string Level::locate_file(const std::string& filename) {
    std::string final;
    
    if(!tile_base_path_.empty()) {
        final = os::path::join(tile_base_path_, filename);
    }
    
    if(!os::path::exists(final)) {   
        final = fdo::xdg::find_data_file(final);
    }
    
    if(final.empty()) {
        throw LogicError("Unable to find file: " + filename);
    }
    
    return final;
}
    
void Level::load_colour_tile(const std::string& filename, uint32_t layer) {
    ColourChunkGrid& grid = colour_layer(layer);
    grid.add_tile(locate_file(filename));
}

void Level::load_solidity_tile(const std::string& filename, CollisionLayer layer) {    
    CollisionChunkGrid& grid = collision_layer(layer);
    grid.add_tile(locate_file(filename));
}

CollisionChunkGrid& Level::collision_layer(CollisionLayer layer) {
    return collision_maps_[layer];
}

ColourChunkGrid& Level::colour_layer(uint32_t i) {
    return colour_layers_.at(i);
}

