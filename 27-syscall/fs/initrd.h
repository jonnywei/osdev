#ifndef INITRD_H
#define INITRD_H
#include "../cpu/types.h"
#include "fs.h"

typedef struct 
{
    /* data */
    u32 nfiles;
}initrd_header_t;



typedef struct 
{
    /* data */
    u8 magic;
    s8 name[64];
    u32 offset;
    u32 length;


}initrd_file_header_t;


fs_node_t* init_initrd(u32 location);


#endif