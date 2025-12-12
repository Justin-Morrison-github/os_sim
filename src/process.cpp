
#include "process.hpp"
#include <stdio.h>
#include <deque>
#include <iostream>
#include <string>
#include <iomanip>
#include <chrono>
#include <thread>

void print_queue(std::deque<process_t> process_queue)
{
    // Headers
    std::cout << std::left
              << std::setw(8) << "pid"
              << std::setw(8) << "arrive"
              << std::setw(8) << "exec"
              << std::setw(8) << "io"
              << "\n";

    // Rows
    for (const process_t &p : process_queue)
    {
        print_process(p);
    }
}

void print_process(const process_t &p)
{
    std::cout << std::left
              << std::setw(8) << static_cast<int>(p.pid)
              << std::setw(8) << static_cast<int>(p.arrival_time)
              << std::setw(8) << static_cast<int>(p.execution_time)
              << std::setw(8) << static_cast<int>(p.io_length)
              << "\n";
}

void run_process(process_t &process)
{
    std::cout << "PID " << static_cast<int>(process.pid) << " running\n";
    process.state = ProcessState::RUNNING;
    while (process.execution_time > 0)
    {
        std::cout << static_cast<int>(process.execution_time) << "s left\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
        process.execution_time--;
    }
}