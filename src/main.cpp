#include <deque>
#include <iostream>
#include <string>
#include <iomanip>
#include <chrono>
#include <thread>
#include <fstream>
#include <string>
#include <vector>

#include "memory.hpp"
#include "process.hpp"
#include "scheduler.hpp"

int main()
{
    std::cout << "\n\n";
    std::string process_file = "processes/processes.csv";
    std::vector<PCB_t> process_list = read_processes_in(process_file);

    Algorithm algo = Algorithm::FIFO;
    AllocationType alloc_type = AllocationType::PAGING;
    PCB_t active;
    std::deque<PCB_t> wait_queue;
    memory_t memory;
    int curr_time = 0;

    for (int i = 0; i < NUM_PAGES; i++)
    {
        page_t page = make_page();
        memory.frames[i] = page;
        memory.free_frames->push_back(i);
    }

    size_t jobs_done = 0;
    while (jobs_done < process_list.size())
    {
        for (PCB_t &pcb : process_list)
        {
            if (pcb.arrival_time == curr_time)
            {
                allocate(pcb, memory, alloc_type);
                print_memory(memory);

                wait_queue.push_back(pcb);
                print_queue(wait_queue);
            }
        }

        if (active.state != ProcessState::RUNNING)
        {
            active = schedule(algo, wait_queue);
            std::cout << "\nPID " << (active.pid) << " running\n";
            active.state = ProcessState::RUNNING;
        }

        if (active.execution_time > 0)
        {
            std::cout << (active.execution_time) << "s left\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
            active.execution_time--;
        }
        else
        {
            std::cout << "\nPID " << (active.pid) << " done\n";
            active.state = ProcessState::TERMINATED;
            jobs_done++;
            free_pcb(active, memory, alloc_type);
            print_memory(memory);
        }
        curr_time++;
    }
}