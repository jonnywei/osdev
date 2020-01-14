#ifndef MM_H
#define MM_H

#include "../cpu/types.h"

#define MEM_FREES 1024

#define FREE_MEM_START_ADDR 0x100000   // 1M

#define FREE_MEM_END_ADDR   0x10000000 // 256M



typedef struct struct_freeinfo {

    u32 addr;
    u32 size;

}freeinfo_t;

typedef struct mm
{
   s32 frees;  // 可用个数
   s32 max_frees;
   s32 lost_size;
   s32 losts;
   freeinfo_t free[MEM_FREES];

} mm_t;

 mm_t memman;

void mm_init(mm_t* mm);
u32 mm_total(mm_t* mm);

u32 mm_alloc(mm_t* mm , u32 size);

s32 mm_free(mm_t* mm, u32 addr, u32 size);

#endif