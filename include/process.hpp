#ifndef PROCESS_HPP
#define PROCESS_HPP

#include <cstdint>
#include <deque>
#include <vector>
#include <string>
#include "memory.hpp"
#include <unordered_map>

#define INVALID -1
#define PCB_TRACE_FILE "output/pcb_table.txt"

enum ProcessState
{
    NEW,
    READY,
    RUNNING,
    WAITING,
    TERMINATED,
    NONE
};

typedef struct PCB
{
    int pid = INVALID;
    int arrival_time = INVALID;
    int execution_time = INVALID;
    int io_length = INVALID;
    ProcessState state = ProcessState::NEW;
    int starting_addr = INVALID;
    int size = INVALID;
    std::unordered_map<int, int> page_table;

} PCB_t;

void print_queue(std::deque<PCB_t> process_queue);
void print_pcb(const PCB_t &p);
std::string pcb_trace_string(const PCB_t &p, const std::deque<PCB_t> wait_queue, const int curr_time, const ProcessState prev_state, const ProcessState new_state);
std::vector<PCB_t> read_processes_in(std::string filepath);
#endif