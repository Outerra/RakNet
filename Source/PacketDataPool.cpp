#include "PacketDataPool.h"

#include <comm/atomic/stack_base.h>

#include <comm/binstream/stdstream.h>
#include <comm/singleton.h>

using namespace coid;

namespace RakNet {
    const uints PacketDataPool::MIN_POOLED_DATA_SIZE = 1500;
    const uints PacketDataPool::MAX_POOLED_DATA_SIZE = 100000;
    const char *PacketDataPool::TRACK_NAME = "raknet::packet_data_pool";
    
    coid::stdoutstream &out = SINGLETON(coid::stdoutstream);
    atomic::stack_base<unsigned char *> pool;

    unsigned  char *PacketDataPool::get(uints size) {
        unsigned char *data;

        if (pool.pop(data)) {
            if (comm_array_allocator::size(data) < size) {
                data = (unsigned char *) comm_array_allocator::realloc(data, size, 1, TRACK_NAME);
            }
        }
        else {
            data = (unsigned char *) comm_array_allocator::alloc(std::max(MIN_POOLED_DATA_SIZE, size), 1, TRACK_NAME);
        }

        out << "get: ";
        out.append_num(16, (uints)data);
        out << "\n";

        comm_array_allocator::set_count(data, size);
        return data;
    }

    void PacketDataPool::put(unsigned char *data) {
        out << "put: ";
        out.append_num(16, (uints)data);
        out << "\n";

        if (comm_array_allocator::size(data) <= MAX_POOLED_DATA_SIZE) {
            pool.push(data);
        }
        else {
            comm_array_allocator::free(data);
        }
    }
}