/*
 * This file is protected by Copyright. Please refer to the COPYRIGHT file
 * distributed with this source distribution.
 *
 * This file is part of SCA-JTNC core.
 *
 * SCA-JTNC core is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * SCA-JTNC core is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License
 * for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see http://www.gnu.org/licenses/.
 */

#include <iostream>

#include <sca/shm/Allocator.h>
#include <sca/shm/Heap.h>

#include <sca/BufferManager.h>

#include <boost/thread.hpp>
#include <boost/scoped_ptr.hpp>

#include "Block.h"

namespace sca {
    namespace shm {
        namespace {
            static boost::once_flag heapInit = BOOST_ONCE_INIT;
            static boost::scoped_ptr<Heap> instance(0);

            static void initializeHeap()
            {
                char* shm_env = getenv("RH_SHMALLOC");
                if (shm_env && strcmp(shm_env, "disable") == 0) {
                    std::cerr << "SHM disabled" << std::endl;
                } else {
                    const std::string name = sca::shm::getProcessHeapName(getpid());
                    Heap* heap = 0;
                    try {
                        heap = new Heap(name);
                    } catch (const std::exception&) {
                        std::cerr << "Unable to create process heap, SHM disabled" << std::endl;
                    }
                    instance.reset(heap);
                }
            }
        }

        std::string getProcessHeapName(pid_t pid)
        {
            std::ostringstream oss;
            oss << "heap-" << pid;
            return oss.str();
        }

        Heap* getProcessHeap()
        {
            boost::call_once(heapInit, &initializeHeap);
            return instance.get();
        }

        bool isEnabled()
        {
            Heap* heap = getProcessHeap();
            return (heap != 0);
        }

        void* allocate(size_t bytes)
        {
            Heap* heap = getProcessHeap();
            if (!heap) {
                return 0;
            }
            return heap->allocate(bytes);
        }

        void deallocate(void* ptr)
        {
            Heap* heap = getProcessHeap();
            if (!heap) {
                throw std::logic_error("sca::shm::deallocate called without process heap");
            }
            heap->deallocate(ptr);
        }

        void* allocateHybrid(size_t bytes)
        {
            sca::shm::Heap* heap = sca::shm::getProcessHeap();
            if (!heap) {
                return sca::BufferManager::Allocate(bytes);
            }

            void* ptr = heap->allocate(bytes);
            if (ptr) {
                return ptr;
            }

            ptr = sca::BufferManager::Allocate(sizeof(Block) + bytes);
            if (ptr) {
                Block* block = new (ptr) Block(0, 0);
                return block->data();
            }

            return 0;
        }

        void deallocateHybrid(void* ptr)
        {
            sca::shm::Heap* heap = sca::shm::getProcessHeap();
            if (!heap) {
                sca::BufferManager::Deallocate(ptr);
                return;
            }

            Block* block = Block::from_pointer(ptr);
            assert(block->valid());
            if (!block->getSuperblock()) {
                // Invalidate the block and pass it on to BufferManager
                block->~Block();
                sca::BufferManager::Deallocate(block);
            } else {
                heap->deallocate(ptr);
            }
        }
    }
}
