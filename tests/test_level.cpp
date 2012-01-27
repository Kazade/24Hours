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
    
    CHECK_EQUAL(3, level->max_horizontal_chunk_count());
    CHECK_EQUAL(2, level->max_vertical_chunk_count());
    
    for(std::string tile: tiles) {
        level->add_tile(tile);
    }
    
    for(uint32_t i = 0; i < CHUNK_COUNT; ++i) {
        std::vector<uint32_t> tile_data(chunk_data[i][0], chunk_data[i][64]);
        level->add_chunk(tile_data);
    }
    
    CHECK_EQUAL(2, level->tile_count());
    CHECK_EQUAL(CHUNK_COUNT, level->chunk_count());
}
