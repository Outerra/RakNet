#pragma once

#include "MTUSize.h"

namespace RakNet {

    const int MIN_POOLED_PACKET_DATA_SIZE = MAXIMUM_MTU_SIZE;
    const int MAX_POOLED_PACKET_DATA_SIZE = 20000;
    
    class PacketDataPool {

    public:
        static unsigned char *get(int size = 0);
        static void put(unsigned char *data);

    };
}