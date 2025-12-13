#ifndef PROCESS_HPP
#define PROCESS_HPP

#include <cstdint>
#include <deque>
#include <vector>
#include <string>

#define INVALID -1

enum class ProcessState
{
    NEW,
    READY,
    RUNNING,
    WAITING,
    TERMINATED
};

typedef struct PCB
{
    int pid = INVALID;
    int arrival_time = INVALID;
    int execution_time = INVALID;
    int io_length = INVALID;
    ProcessState state = ProcessState::NEW;
    int starting_addr = INVALID;

} PCB_t;

void print_queue(std::deque<PCB_t> process_queue);
void print_pcb(const PCB_t &p);
std::vector<PCB_t> read_processes_in(std::string filepath);
#endif