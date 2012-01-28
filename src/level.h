#ifndef TWF_HOURS_LEVEL_H
#define TWF_HOURS_LEVEL_H

#include <cstdint>
#include <vector>
#include <tr1/memory>

#include "level/tile_template.h"
#include "level/collision_chunk_grid.h"
#include "level/colour_chunk_grid.h"

enum CollisionLayer {
    COLLISION_LAYER_BACK = 0,
    COLLISION_LAYER_FRONT = 1,
    COLLISION_LAYER_MAX
};

class Level {
private:
    CollisionLayer active_collision_layer_;    
    CollisionChunkGrid collision_maps_[COLLISION_LAYER_MAX];

    std::vector<ColourChunkGrid> colour_layers_;

    uint32_t chunks_across_;
    uint32_t chunks_down_;
    
    std::string tile_base_path_;
    std::string locate_file(const std::string& filename);

public:
    typedef std::tr1::shared_ptr<Level> ptr;

    Level(uint32_t chunks_across, uint32_t chunks_down, 
        std::string tile_base_path="", 
        uint32_t colour_layers=1
    );
    
    void load_colour_tile(const std::string& filename, uint32_t colour_layer=0);
    void load_solidity_tile(const std::string& filename, CollisionLayer layer);

    CollisionChunkGrid& collision_layer(CollisionLayer layer);
    ColourChunkGrid& colour_layer(uint32_t i);
};

#endif
