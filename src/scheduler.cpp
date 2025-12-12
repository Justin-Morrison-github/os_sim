#include "scheduler.hpp"
#include <iostream>

process_t FIFO(std::deque<process_t> &process_queue)
{
    process_t p = process_queue.front();
    process_queue.pop_front();
    return p;
}

process_t schedule(Algorithm algo, std::deque<process_t> &process_queue)
{
    process_t err = {UINT8_MAX, UINT8_MAX, UINT8_MAX, UINT8_MAX, ProcessState::TERMINATED};
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
