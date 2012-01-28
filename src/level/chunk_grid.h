#ifndef TWF_CHUNK_GRID_H
#define TWF_CHUNK_GRID_H

#include <SOIL/SOIL.h>
#include <cstdint>
#include <vector>

#include "kazbase/exceptions.h"

#include "level/ichunk_grid.h"
#include "level/chunk.h"
#include "level/types.h"

template <typename TileType>
class ChunkGrid : public IChunkGrid {
public:
    ChunkGrid(TileType empty_tile=TileType()):
        chunks_across_(0),
        chunks_down_(0) {    
        
        tiles_.push_back(typename TileType::ptr(new TileType(empty_tile)));
    }
    
    ChunkGrid(uint32_t chunks_across, uint32_t chunks_down, TileType empty_tile=TileType()):
        chunks_across_(chunks_across),
        chunks_down_(chunks_down) {
        
        resize(chunks_across, chunks_down);
        tiles_.push_back(typename TileType::ptr(new TileType(empty_tile)));        
    }
    
    void resize(uint32_t chunks_across, uint32_t chunks_down) {
        chunks_across_ = chunks_across;
        chunks_down_ = chunks_down;
        
        chunks_.resize(chunks_across * chunks_down);
        for(Chunk::ptr& chunk_ptr: chunks_) {
            chunk_ptr.reset(new Chunk(this));
        }
    }
    
    void add_tile(const std::string& filename) {
        std::string final = filename;
        
        int width, height, channels;
        unsigned char *data = SOIL_load_image(final.c_str(), &width, &height, &channels, SOIL_LOAD_AUTO);
        if(!data) {
            throw RuntimeError("Not a suitable file: " + filename);
        }
        
        if(width != tile_size() || height != tile_size()) {
            throw LogicError("Attempted to load a tile of an invalid size: " + filename);
        }
        
        if(channels != 4) {
            throw LogicError("Attempted to load a tile without an alpha channel: " + filename);
        }
        
        typename TileType::ptr new_tile(new TileType);
        std::copy(data, data + (width * height * channels), new_tile->data);    
        tiles_.push_back(new_tile);
        
        SOIL_free_image_data(data);    
    }
    
    void set_chunk_at(uint32_t i, const std::vector<uint32_t>& tile_indexes) {
        assert(i < chunks_.size());
        
        Chunk::ptr new_chunk = chunks_[i];
        
        int j = 0;
        for(uint32_t tile: tile_indexes) {
            new_chunk->set_tile_id(j++, tile);
        }
    }
    
    std::pair<uint32_t, bool /*within_bounds*/> chunk_containing_point(const Point& p);
    
    uint32_t horizontal_chunk_count() const { return chunks_across_; }
    uint32_t vertical_chunk_count() const { return chunks_down_; }

    uint32_t tile_size() const { return TileType::TileSize; }
    uint32_t chunk_size() const { return TILES_ACROSS_CHUNK * tile_size(); }
    
private:
    uint32_t chunks_across_;
    uint32_t chunks_down_;
    
    std::vector<Chunk::ptr> chunks_;
    std::vector<typename TileType::ptr> tiles_;
};


#endif
