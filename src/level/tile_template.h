#ifndef TWF_TILE_TEMPLATE_H
#define TWF_TILE_TEMPLATE_H

#include <cstdint>

const int TILE_SIZE = 64;

template <int BPP>
class TileTemplate {
public:
    typedef std::tr1::shared_ptr<TileTemplate<BPP>> ptr;    
    enum { TileSize = TILE_SIZE };
    
    TileTemplate() {
        memset(data, 0, TILE_SIZE * TILE_SIZE * BPP);
    }

    uint8_t data[TILE_SIZE * TILE_SIZE * BPP];       
};

#endif
