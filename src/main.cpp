#include <stdio.h>
#include "process.hpp"
#include <deque>
#include <iostream>
#include <string>
#include <iomanip>
#include "scheduler.hpp"
#include <chrono>
#include <thread>

int main()
{
    printf("\n\n");
    std::deque<process_t> wait_queue;

    process_t process1 = {
        1,
        0,
        2,
        3,
        ProcessState::READY};
    process_t process2 = {
        2,
        2,
        6,
        4,
        ProcessState::READY};

    wait_queue.push_back(process1);
    wait_queue.push_back(process2);
    print_queue(wait_queue);

    std::cout << "--------------------------------------\n";

    Algorithm algo = Algorithm::FIFO;
    process_t active;

    while (!wait_queue.empty())
    {
        active = schedule(algo, wait_queue);
        print_process(active);
        run_process(active);

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}