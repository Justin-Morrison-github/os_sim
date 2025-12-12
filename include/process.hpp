#ifndef MAIN_H
#define MAIN_H

#include <cstdint>
#include <deque>

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
    uint8_t pid;
    uint8_t arrival_time;
    uint8_t execution_time;
    uint8_t io_length;
    ProcessState state;

} process_t;

void print_queue(std::deque<process_t> process_queue);
void run_process(process_t &process);
void print_process(const process_t &p);

#endif