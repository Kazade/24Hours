#ifndef TWF_HOURS_LEVEL_H
#define TWF_HOURS_LEVEL_H

#include <cstdint>
#include <vector>
#include <tr1/memory>

const int TILE_SIZE = 64;
const int TILES_ACROSS_CHUNK = 8;
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
    uint32_t tiles[64];
};

class Level {
private:
    CollisionLayer active_collision_layer_;
    std::vector<Tile::ptr> all_tiles_;
    std::vector<Chunk::ptr> chunks_;
    
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
};

#endif
