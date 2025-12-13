#ifndef PROCESS_HPP
#define PROCESS_HPP

#include <cstdint>
#include <deque>

#define INVALID -1

enum class ProcessState
{
    NEW,
    READY,
    RUNNING,
    WAITING,
    TERMINATED
};

typedef struct process
{
    int pid = INVALID;
    int arrival_time = INVALID;
    int execution_time = INVALID;
    int io_length = INVALID;
    ProcessState state = ProcessState::NEW;
    int starting_addr = INVALID;

} process_t;

void print_queue(std::deque<process_t> process_queue);
void run_process(process_t &process);
void print_process(const process_t &p);

#endif