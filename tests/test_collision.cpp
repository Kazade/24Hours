#include <unittest++/UnitTest++.h>

#include "level/collision_chunk_grid.h"

TEST(collision_basic_functionality) {
    
    CollisionChunkGrid map(3, 1);
    
    CHECK_EQUAL(3, map.horizontal_chunk_count());
    CHECK_EQUAL(1, map.vertical_chunk_count());
    
    //Check we can't intersect with the map
    CHECK(!map.ray_intersect(Point(0, map.chunk_size() / 2), Vec2f(1, 0)).second);
}
