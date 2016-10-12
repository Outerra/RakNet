#include "PacketDataPool.h"

#ifdef COMM
#include <comm/atomic/stack_base.h>

//#include <comm/singleton.h>
//#include <comm/binstream/stdstream.h>

using namespace coid;

namespace RakNet {
    const char *TRACK_NAME = "raknet::packet_data_pool";
    atomic::stack_base<unsigned char *> pool;
    
    //LOCAL_SINGLETON(coid::stdoutstream) out;

    unsigned  char *PacketDataPool::get(int size) {
        unsigned char *data;

        if (pool.pop(data)) {
            if (comm_array_allocator::size(data) < size) {
                data = (unsigned char *) comm_array_allocator::realloc(data, size, 1, TRACK_NAME);
            }
        }
        else {
            data = (unsigned char *) comm_array_allocator::alloc(std::max(MIN_POOLED_PACKET_DATA_SIZE, size), 1, TRACK_NAME);
        }

        //*out << "get: ";
        //out->append_num(16, (uints)data);
        //*out << "\n";

        comm_array_allocator::set_count(data, size);
        return data;
    }

    void PacketDataPool::put(unsigned char *data) {
        //*out << "put: ";
        //out->append_num(16, (uints)data);
        //*out << "\n";

        if (comm_array_allocator::size(data) <= MAX_POOLED_PACKET_DATA_SIZE) {
            pool.push(data);
        }
        else {
            comm_array_allocator::free(data);
        }
    }
}

#else

#include "RakMemoryOverride.h"

namespace RakNet {
    unsigned char *PacketDataPool::get(int size) {
        return (unsigned char *) rakMalloc(size);
    }

    void PacketDataPool::put(unsigned char *data) {
        rakFree(data);
    }
}

#endif