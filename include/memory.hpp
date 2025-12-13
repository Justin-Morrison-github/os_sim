#ifndef MEMORY_HPP
#define MEMORY_HPP

#include "process.hpp"

#define PAGE_SIZE 1024
#define MEMORY_SIZE 1024 * 16
#define NUM_PAGES MEMORY_SIZE / PAGE_SIZE

#define INVALID_ADDR -1

enum class AllocationStrategy
{
    FIRST_FIT,
    BEST_FIT,
    WORST_FIT,
    NEXT_FIT,
    NONE,
};

enum class AllocationType
{
    CONTIGOUS,
    PAGING,
    SEGMENTATION
};

typedef struct page
{
    int start_addr = INVALID_ADDR;
    int size = INVALID;
    bool free = true;
    int pid = INVALID;

} page_t;

page_t make_page();

typedef struct memory
{
    page_t frames[NUM_PAGES];
    int first_free_frame;
} memory_t;

typedef struct
{
    int frame_number;
    bool dirty;
    bool valid;
} page_table_entry_t;

extern page_table_entry_t page_table[NUM_PAGES];
void allocate(process_t &process, memory_t &memory, AllocationType type, AllocationStrategy strat);
void allocate(process_t &process, memory_t &memory, AllocationType type);

void print_memory(memory_t &memory);

#endif