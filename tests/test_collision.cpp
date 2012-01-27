#include <unittest++/UnitTest++.h>

#include "level.h"

TEST(collision_basic_functionality) {
    
    CollisionMap map(3, 1);
    
    CHECK_EQUAL(0, map.tile_count());
    
    //Check we can't intersect with the map
    CHECK(!map.ray_intersect(Point(0, CHUNK_SIZE / 2), Vec2f(1, 0)).second);
    
}
