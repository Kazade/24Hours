#ifndef TWF_HOURS_LEVEL_H
#define TWF_HOURS_LEVEL_H

#include <cstdint>
#include <vector>
#include <tr1/memory>

const int TILE_SIZE = 64;
const int TILES_ACROSS_CHUNK = 8;
const int TILES_ACROSS_CHUNK_SQUARED = TILES_ACROSS_CHUNK * TILES_ACROSS_CHUNK;
const int CHUNK_SIZE = TILE_SIZE * TILES_ACROSS_CHUNK;

enum CollisionLayer {
    COLLISION_LAYER_BACK = 0,
    COLLISION_LAYER_FRONT = 1,
    COLLISION_LAYER_MAX
};

class Tile {
public:
    typedef std::tr1::shared_ptr<Tile> ptr;
    
    uint8_t data[TILE_SIZE * TILE_SIZE * 4];
};

struct Chunk {
    typedef std::tr1::shared_ptr<Chunk> ptr;
    uint32_t tiles[TILES_ACROSS_CHUNK_SQUARED];
};

class SolidityTile {
    typedef std::tr1::shared_ptr<SolidityTile> ptr;
    uint8_t data[TILE_SIZE * TILE_SIZE];
};

class SolidityChunk {
public:
    typedef std::tr1::shared_ptr<SolidityChunk> ptr;

private:
    uint32_t tile_indexes_[TILES_ACROSS_CHUNK_SQUARED];
    uint8_t map_[CHUNK_SIZE * CHUNK_SIZE];
};

struct Point {
    uint32_t x;
    uint32_t y;
};

struct Vec2f {
    float x;
    float y;
};

class CollisionMap {
private:
    std::vector<SolidityTile::ptr> all_tiles_;
    std::vector<SolidityChunk::ptr> chunks_;
    
public:
    typedef std::tr1::shared_ptr<CollisionMap> ptr;
    
    CollisionMap(uint32_t chunks_across, uint32_t chunks_down);

    void add_tile(const std::string& filename);
    void set_chunk_at(uint32_t i, std::vector<uint32_t> tile_indexes);

    uint32_t chunk_at(const Point& p);
    std::pair<Point, bool> ray_intersect(const Point& start, const Vec2f& dir);
};

class Level {
private:
    std::vector<Tile::ptr> all_tiles_;
    std::vector<Chunk::ptr> chunks_;

    CollisionLayer active_collision_layer_;
    CollisionMap collision_maps_[COLLISION_LAYER_MAX];
    
    std::string tile_base_path_;
    uint32_t chunks_across_;
    uint32_t chunks_down_;

public:
    typedef std::tr1::shared_ptr<Level> ptr;

    Level(uint32_t chunks_across, uint32_t chunks_down, std::string tile_base_path="");

    void add_tile(const std::string& filename);
    void add_chunk(std::vector<uint32_t> tile_indexes);
    
    uint32_t tile_count() const { return all_tiles_.size(); }
    uint32_t chunk_count() const { return chunks_.size(); }
    
    uint32_t max_horizontal_chunk_count() const { return chunks_across_; }
    uint32_t max_vertical_chunk_count() const { return chunks_down_; }
    
    CollisionMap& collision_map(CollisionLayer layer);
};

#endif
