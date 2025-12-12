#ifndef SCHEDULER_H
#define SCHEDULER_H

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