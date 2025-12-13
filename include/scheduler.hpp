#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

#include "process.hpp"
#include <deque>

enum class Algorithm
{
    FIFO,
    SJF,
    RR
};

PCB_t schedule(Algorithm algo, std::deque<PCB_t> &process_queue);

#endif