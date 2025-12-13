#include "memory.hpp"
#include "process.hpp"
#include <iomanip>
#include <iostream>

void allocate(PCB_t &process, memory_t &memory, AllocationType type)
{
    switch (type)
    {
    case AllocationType::PAGING:
    {

        page_t &page = memory.frames[memory.first_free_frame];
        page.free = false;
        page.pid = process.pid;
        process.starting_addr = page.start_addr;
        memory.first_free_frame++;
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

void print_page(const page_t &page, const int i)
{
    std::cout << std::left
              << std::setw(15) << (i)
              << std::setw(15) << (page.size)
              << std::setw(15) << (page.free ? "Y" : "N")
              << std::setw(15) << (page.pid == INVALID ? -1 : page.pid)
              << std::setw(15) << (page.start_addr)
              << "\n";
}

void print_memory(memory_t &memory)
{
    // Headers
    std::cout << std::left
              << std::setw(15) << "frame"
              << std::setw(15) << "size"
              << std::setw(15) << "free"
              << std::setw(15) << "allocated pid"
              << std::setw(15) << "start addr"
              << "\n";

    for (int i = 0; i < NUM_PAGES; i++)
    {
        print_page(memory.frames[i], i);
    }
    std::cout << "\n";
}

page_t make_page()
{
    static int index = 0;
    page_t p{};
    p.start_addr = index++ * PAGE_SIZE;
    return p;
}