#include <iostream>
#include "scheduler.hpp"

PCB_t FIFO(std::deque<PCB_t> &process_queue)
{
    PCB_t p = process_queue.front();
    process_queue.pop_front();
    return p;
}

PCB_t schedule(Algorithm algo, std::deque<PCB_t> &process_queue)
{
    PCB_t err = {-1, -1, -1, -1, ProcessState::TERMINATED};
    if (process_queue.empty())
    {
        std::cout << "ERROR: Queue empty";
        return err;
    }

    switch (algo)
    {
    case Algorithm::FIFO:
        return FIFO(process_queue);
    default:
        return err;
    }
}
