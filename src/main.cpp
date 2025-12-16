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
#include "utils.hpp"

int main()
{
    std::cout << "\n\n";
    std::string process_file = "processes/processes.csv";
    std::vector<PCB_t> process_list = read_processes_in(process_file);

    int curr_time = 0;
    Algorithm algo = Algorithm::FIFO;
    AllocationType alloc_type = AllocationType::PAGING;
    PCB_t active;
    std::deque<PCB_t> wait_queue;
    memory_t memory;
    std::string memory_trace = "";
    std::string pcb_trace = "";

    if (alloc_type == AllocationType::PAGING)
    {
        for (int i = 0; i < NUM_PAGES; i++)
        {
            page_t page = make_page();
            memory.frames[i] = page;
            memory.free_frames->push_back(i);
        }
    }

    size_t jobs_done = 0;
    while (jobs_done < process_list.size())
    {
        for (PCB_t &pcb : process_list)
        {
            if (pcb.arrival_time == curr_time)
            {
                allocate(pcb, memory, alloc_type);
                memory_trace += memory_trace_string(memory, curr_time);

                wait_queue.push_back(pcb);
                print_queue(wait_queue);
                pcb_trace += pcb_trace_string(active, wait_queue, curr_time, active.state, ProcessState::READY);
            }

            if (active.state != ProcessState::RUNNING)
            {
                active = schedule(algo, wait_queue);
                std::cout << "\nPID " << (active.pid) << " running\n";
                pcb_trace += pcb_trace_string(active, wait_queue, curr_time, active.state, ProcessState::RUNNING);
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
                pcb_trace += pcb_trace_string(active, wait_queue, curr_time, active.state, ProcessState::TERMINATED);
                active.state = ProcessState::TERMINATED;
                jobs_done++;
                free_pcb(active, memory, alloc_type);
                memory_trace += memory_trace_string(memory, curr_time);
            }
            curr_time++;
        }
    }
    write_output(memory_trace, MEMORY_TRACE_FILE);
    write_output(pcb_trace, PCB_TRACE_FILE);
}