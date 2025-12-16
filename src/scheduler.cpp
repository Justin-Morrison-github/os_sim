#include <iostream>
#include "scheduler.hpp"

PCB_t FIFO(std::deque<PCB_t> &process_queue)
{
    PCB_t p = process_queue.front();
    process_queue.pop_front();
    return p;
}

PCB_t SJF(std::deque<PCB_t> &process_queue)
{
    if (process_queue.empty())
    {
        throw std::runtime_error("Process queue is empty");
    }

    size_t min_index = 0;
    for (size_t i = 1; i < process_queue.size(); ++i)
    {
        if (process_queue[i].execution_time < process_queue[min_index].execution_time)
        {
            min_index = i;
        }
    }
    PCB_t shortest_job = process_queue.at(min_index);
    process_queue.erase(process_queue.begin() + min_index);
    return shortest_job;
}

PCB_t RR(std::deque<PCB_t> &process_queue)
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
    case Algorithm::RR:
        return RR(process_queue);
    case Algorithm::SJF:
        return SJF(process_queue);
    default:
        return err;
    }
}
