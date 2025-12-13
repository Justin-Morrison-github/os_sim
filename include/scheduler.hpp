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

process_t schedule(Algorithm algo, std::deque<process_t> &process_queue);

#endif