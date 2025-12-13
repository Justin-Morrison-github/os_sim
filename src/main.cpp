#include <stdio.h>
#include <deque>
#include <iostream>
#include <string>
#include <iomanip>
#include <chrono>
#include <thread>

#include "memory.hpp"
#include "process.hpp"
#include "scheduler.hpp"

int main()
{
    Algorithm algo = Algorithm::FIFO;
    AllocationType alloc_type = AllocationType::PAGING;
    process_t active;
    std::deque<process_t> wait_queue;
    memory_t memory;

    for (int i = 0; i < NUM_PAGES; i++)
    {
        memory.frames[i] = make_page();
    }

    memory.first_free_frame = 0;

    printf("\n\n");

    process_t process1 = {
        1,
        0,
        2,
        3,
    };
    allocate(process1, memory, alloc_type);
    process_t process2 = {
        2,
        2,
        6,
        4,
    };
    allocate(process2, memory, alloc_type);

    wait_queue.push_back(process1);
    wait_queue.push_back(process2);
    print_memory(memory);
    std::cout << "--------------------------------------\n";

    print_queue(wait_queue);

    std::cout << "--------------------------------------\n";

    while (!wait_queue.empty())
    {
        active = schedule(algo, wait_queue);
        run_process(active);

        // std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}