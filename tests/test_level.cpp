#include <unittest++/UnitTest++.h>

#include <string>
#include "kazbase/os/path.h"
#include "level.h"

const uint32_t CHUNK_COUNT = 1;
uint32_t chunk_data[CHUNK_COUNT][64] = {
    {
        1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1,
        0, 0, 0, 0, 0, 0, 0, 0
    },
};

std::string tiles [] = {
    "test-data/tile1.png",     //0
    "test-data/tile2.png"
};


TEST(test_basic_level_loading) {
    Level::ptr level(new Level(3, 2, os::path::exe_path()));
    
    CHECK_EQUAL(3, level->colour_layer(0).horizontal_chunk_count());
    CHECK_EQUAL(2, level->colour_layer(0).vertical_chunk_count());
    
    for(std::string tile: tiles) {
        level->load_colour_tile(tile);
    }
    
    for(uint32_t i = 0; i < CHUNK_COUNT; ++i) {
        std::vector<uint32_t> tile_data;
        tile_data.assign(chunk_data[i], chunk_data[i] + 64);
        level->colour_layer(0).set_chunk_at(i, tile_data);
    }
}
