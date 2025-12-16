
#include <stdio.h>
#include <deque>
#include <iostream>
#include <string>
#include <iomanip>
#include <chrono>
#include <thread>
#include <vector>
#include <fstream>
#include <string>

#include "process.hpp"
#include "utils.hpp"

#define TABLE_WIDTH 60
void print_queue(std::deque<PCB_t> process_queue)
{

    std::cout << "\n\nProcess Queue\n";
    std::cout << fill_n('-', TABLE_WIDTH) << std::endl;
    // Headers
    std::cout << std::left
              << std::setw(8) << "pid"
              << std::setw(8) << "arrive"
              << std::setw(8) << "exec"
              << std::setw(8) << "io"
              << std::setw(8) << "size"
              << std::setw(8) << "old state"
              << std::setw(8) << "new state"
              << "\n";

    // Rows
    for (const PCB_t &p : process_queue)
    {
        print_pcb(p);
    }
    std::cout << fill_n('-', TABLE_WIDTH) << std::endl;
}

std::ostream &operator<<(std::ostream &os, const enum ProcessState &s)
{ // Overloading the << operator to make printing of the enum easier

    std::string state_names[] = {
        "NEW",
        "READY",
        "RUNNING",
        "WAITING",
        "TERMINATED",
        "NONE"};
    return (os << state_names[s]);
}

void print_pcb(const PCB_t &p)
{
    // Rows
    std::cout << std::left
              << std::setw(8) << (p.pid)
              << std::setw(8) << (p.arrival_time)
              << std::setw(8) << (p.execution_time)
              << std::setw(8) << (p.io_length)
              << std::setw(8) << (p.starting_addr)
              << "\n";
}

std::vector<std::string> split(const std::string &str, char delimiter)
{
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}

std::vector<PCB_t> read_processes_in(std::string filepath)
{
    std::vector<PCB_t> processes;

    std::ifstream infile{filepath};
    if (!infile)
    {
        std::cerr << "ERROR: " << filepath << " could not be opened\n";
        return {};
    }

    std::string strInput;
    std::getline(infile, strInput); // skip the header, only for humans
    while (std::getline(infile, strInput))
    {
        std::vector<std::string> parts = split(strInput, ',');
        int pid = stoi(parts[0]);
        int arrival_time = stoi(parts[1]);
        int execution_time = stoi(parts[2]);
        int io_length = stoi(parts[3]);
        int starting_addr = stoi(parts[4]);
        int size = stoi(parts[5]);

        PCB_t pcb = {pid, arrival_time, execution_time, io_length, ProcessState::NEW, starting_addr, size};
        processes.push_back(pcb);
    }

    return processes;
}

std::string pcb_trace_string(const PCB_t &p, const std::deque<PCB_t> wait_queue, const int curr_time, const ProcessState prev_state, const ProcessState new_state)
{

    const int col_width = 12; // width of each column
    const int num_cols = 7;   // frame, size, free, allocated pid, start addr, used
    const int width = col_width * num_cols;
    const std::string separator = "+";

    std::stringstream buffer;
    buffer << "\nTime: " << curr_time << "\n";

    // Print top border
    buffer << separator;
    for (int i = 0; i < num_cols; ++i)
        buffer << std::setfill('-') << std::setw(col_width) << separator;
    buffer << "\n";
    buffer << std::setfill(' ');

    // Print headers
    buffer << "|"
           << std::setw(col_width - 1) << "pid" << "|"
           << std::setw(col_width - 1) << "arrive" << "|"
           << std::setw(col_width - 1) << "cpu burst" << "|"
           << std::setw(col_width - 1) << "io burst" << "|"
           << std::setw(col_width - 1) << "size" << "|"
           << std::setw(col_width - 1) << "old state" << "|"
           << std::setw(col_width - 1) << "new state" << "|"
           << "\n";
    buffer << separator;
    for (int i = 0; i < num_cols; ++i)
        buffer << std::setfill('-') << std::setw(col_width) << separator;
    buffer << "\n";
    buffer << std::setfill(' ');

    buffer << "|"
           << std::setw(col_width - 1) << p.pid << "|"
           << std::setw(col_width - 1) << p.arrival_time << "|"
           << std::setw(col_width - 1) << p.execution_time << "|"
           << std::setw(col_width - 1) << p.io_length << "|"
           << std::setw(col_width - 1) << p.size << "|"
           << std::setw(col_width - 1) << prev_state << "|"
           << std::setw(col_width - 1) << new_state << "|"
           << "\n";

    // Print header-bottom border
    buffer << separator;
    for (int i = 0; i < num_cols; ++i)
        buffer << std::setfill('-') << std::setw(col_width) << separator;
    buffer << "\n";
    buffer << std::setfill(' ');

    if (wait_queue.size() > 0)
    {
        /* code */
        // Print each row
        for (const auto &process : wait_queue)
        {
            buffer << "|"
                   << std::setw(col_width - 1) << process.pid << "|"
                   << std::setw(col_width - 1) << process.arrival_time << "|"
                   << std::setw(col_width - 1) << process.execution_time << "|"
                   << std::setw(col_width - 1) << process.io_length << "|"
                   << std::setw(col_width - 1) << process.size << "|"
                   << std::setw(col_width - 1) << prev_state << "|"
                   << std::setw(col_width - 1) << new_state << "|"
                   << "\n";
        }
        // Print bottom border
        buffer << separator;
        for (int i = 0; i < num_cols; ++i)
            buffer << std::setfill('-') << std::setw(col_width) << separator;
        buffer << "\n";
        buffer << std::setfill(' ');
    }

    return buffer.str();
}
