#ifndef TWF_ICHUNK_GRID_H
#define TWF_ICHUNK_GRID_H

class IChunkGrid {
public:
    virtual ~IChunkGrid() {}
    virtual uint32_t tile_size() const = 0;
    
};

#endif
