#include "memory.hpp"
#include "process.hpp"
#include "utils.hpp"
#include <iomanip>
#include <iostream>
#include <cmath> // Required for ceil()

void allocate(PCB_t &process, memory_t &memory, AllocationType type)
{
    switch (type)
    {
    case AllocationType::PAGING:
    {
        int num_pages_needed = (process.size + PAGE_SIZE - 1) / PAGE_SIZE;
        int size_remaining = process.size;
        for (int i = 0; i < num_pages_needed; i++)
        {
            int index = memory.free_frames->front();
            memory.free_frames->pop_front();
            page_t &page = memory.frames[index];
            page.free = false;
            page.pid = process.pid;

            if (i < num_pages_needed - 1)
            {
                page.used = PAGE_SIZE;
            }
            else
            {
                page.used = size_remaining;
            }

            process.page_table[i] = index;
            size_remaining -= PAGE_SIZE;
        }

        break;
    }

    case AllocationType::SEGMENTATION:
    {
        std::cout << "Not implemented";
        throw new std::runtime_error("Not implemented");
        break;
    }
    default:
    {
        break;
    }
    }
}

void allocate(PCB_t &process, memory_t &memory, AllocationType type, AllocationStrategy strat)
{
    switch (type)
    {
    case AllocationType::CONTIGOUS:
        switch (strat)
        {
        case AllocationStrategy::FIRST_FIT:
            std::cout << "Not implemented";
            throw new std::runtime_error("Not implemented");
            break;

        case AllocationStrategy::BEST_FIT:
            std::cout << "Not implemented";
            throw new std::runtime_error("Not implemented");
            break;
        default:
            std::cout << "ERROR";
            throw new std::runtime_error("Invalid type passed");
            break;
        }
    default:
        break;
    }
}

void free_pcb(PCB_t &process, memory_t &memory, AllocationType type)
{
    switch (type)
    {
    case AllocationType::PAGING:
    {
        for (auto &pair : process.page_table)
        {
            int physical_page_index = pair.second;
            page_t &page_in_mmem = memory.frames[physical_page_index];
            page_in_mmem.free = true;
            page_in_mmem.pid = INVALID;
            page_in_mmem.used = INVALID;
        }

        break;
    }

    case AllocationType::SEGMENTATION:
    {
        std::cout << "Not implemented";
        throw new std::runtime_error("Not implemented");
        break;
    }
    default:
    {
        break;
    }
    }
}

void print_page(const page_t &page, const int i)
{
    std::cout << std::left
              << std::setw(15) << (i)
              << std::setw(15) << (page.size)
              << std::setw(15) << (page.free ? "Y" : "N")
              << std::setw(15) << (page.pid == INVALID ? -1 : page.pid)
              << std::setw(15) << (page.start_addr)
              << std::setw(15) << (page.used)
              << "\n";
}

#define MMEM_TABLE_WIDTH 100

void print_memory(memory_t &memory)
{

    std::cout << "Main Memory\n";
    std::cout << fill_n('-', MMEM_TABLE_WIDTH) << std::endl;

    // Headers
    std::cout << std::left
              << std::setw(15) << "frame"
              << std::setw(15) << "size"
              << std::setw(15) << "free"
              << std::setw(15) << "pid"
              << std::setw(15) << "start addr"
              << std::setw(15) << "used"
              << "\n";

    for (int i = 0; i < NUM_PAGES; i++)
    {
        print_page(memory.frames[i], i);
    }
    std::cout << fill_n('-', MMEM_TABLE_WIDTH) << std::endl;
}

std::string memory_trace_string(memory_t &memory, const int curr_time)
{
    const int col_width = 12; // width of each column
    const int num_cols = 6;   // frame, size, free, allocated pid, start addr, used
    const int width = col_width * num_cols;
    const std::string separator = "+";

    std::stringstream buffer;
    buffer << "\nTime: " << curr_time << "\n ";

    // Print top border
    buffer
        << separator;
    for (int i = 0; i < num_cols; ++i)
        buffer << std::setfill('-') << std::setw(col_width) << separator;
    buffer << "\n";

    buffer << std::setfill(' ');

    // Print headers
    buffer << "|"
           << std::setw(col_width - 1) << "frame" << "|"
           << std::setw(col_width - 1) << "size" << "|"
           << std::setw(col_width - 1) << "free" << "|"
           << std::setw(col_width - 1) << "pid" << "|"
           << std::setw(col_width - 1) << "start addr" << "|"
           << std::setw(col_width - 1) << "used" << "|"
           << "\n";

    // Print header-bottom border
    buffer << separator;
    for (int i = 0; i < num_cols; ++i)
        buffer << std::setfill('-') << std::setw(col_width) << separator;
    buffer << "\n";
    buffer << std::setfill(' ');

    // Print each row
    int frame_num = 0;
    for (const auto &page : memory.frames)
    {
        buffer << "|"
               << std::setw(col_width - 1) << frame_num << "|"
               << std::setw(col_width - 1) << page.size << "|"
               << std::setw(col_width - 1) << page.free << "|"
               << std::setw(col_width - 1) << page.pid << "|"
               << std::setw(col_width - 1) << page.start_addr << "|"
               << std::setw(col_width - 1) << page.used << "|"
               << "\n";
        ++frame_num;
    }

    // Print bottom border
    buffer << separator;
    for (int i = 0; i < num_cols; ++i)
        buffer << std::setfill('-') << std::setw(col_width) << separator;
    buffer << "\n";
    buffer << std::setfill(' ');

    return buffer.str();
}

page_t make_page()
{
    static int index = 0;
    page_t p{};
    p.start_addr = index++ * PAGE_SIZE;
    return p;
}