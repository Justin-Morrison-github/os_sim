
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
              << "\n";

    // Rows
    for (const PCB_t &p : process_queue)
    {
        print_pcb(p);
    }
    std::cout << fill_n('-', TABLE_WIDTH) << std::endl;
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
