#pragma once

namespace RakNet {

    const int MIN_POOLED_PACKET_DATA_SIZE = 1500;
    const int MAX_POOLED_PACKET_DATA_SIZE = 100000;
    
    class PacketDataPool {

    public:
        static unsigned char *get(int size = 0);
        static void put(unsigned char *data);

    };
}