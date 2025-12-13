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

#define MMEM_TABLE_WIDTH 80

void print_memory(memory_t &memory)
{

    std::cout << "Main Memory\n";
    std::cout << fill_n('-', MMEM_TABLE_WIDTH) << std::endl;

    // Headers
    std::cout << std::left
              << std::setw(15) << "frame"
              << std::setw(15) << "size"
              << std::setw(15) << "free"
              << std::setw(15) << "allocated pid"
              << std::setw(15) << "start addr"
              << std::setw(15) << "used"
              << "\n";

    for (int i = 0; i < NUM_PAGES; i++)
    {
        print_page(memory.frames[i], i);
    }
    std::cout << fill_n('-', MMEM_TABLE_WIDTH) << std::endl;
}

page_t make_page()
{
    static int index = 0;
    page_t p{};
    p.start_addr = index++ * PAGE_SIZE;
    return p;
}