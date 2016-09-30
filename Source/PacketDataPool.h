#pragma once

#include <comm/dynarray.h>
#include <comm/alloc/commalloc.h>

namespace RakNet {
    class PacketDataPool {

    private:
        static const uints MIN_POOLED_DATA_SIZE;
        static const uints MAX_POOLED_DATA_SIZE;
        static const char *TRACK_NAME;

    public:
        static unsigned char *get(uints size = 0);
        static void put(unsigned char *data);
    };
}