#ifndef FS_H
#define FS_H

#include "../cpu/types.h"

#define MAXLEN 128

#define FS_FILE        0x01
#define FS_DIRECTORY   0x02

// vfs 接口定义
// open close

typedef void (* open_func_t) (struct fs_node*);
typedef void (*close_func_t) (struct fs_node *);


//读写

typedef u32 (* read_func_t)(struct fs_node* , u32*, u32, u8*);

typedef u32 (* write_func_t) (struct fs_node* , u32*, u32, u8*);




//目录操作

typedef struct dirent* (* readdir_func_t) (struct fs_node *, u32);

typedef struct dirent* (* finddir_func_t) (struct fs_node *, char* name);



struct dirent
{
    char name[MAXLEN];
    u32 inode;
};


typedef struct fs_node {
    char name[MAXLEN]; //名称
    u32 inode;
    
    u32 flags;       // Includes the node type. See #defines above.

    union 
    {
        u32 length;   // Size of the file, in bytes. or childs count
        u32 dir_children;
    };
    

   read_func_t read;
   write_func_t write;
   open_func_t open;
   close_func_t close;
   readdir_func_t readdir;
   finddir_func_t finddir;

} fs_node_t;


extern fs_node_t *fs_root; // The root of the filesystem.


u32 read_fs(fs_node_t* node, u32 offset, u32 size, u8* buffer);

u32 write_fs(fs_node_t* node, u32 offset, u32 size, u8* buffer);

void open_fs(fs_node_t* node, u8 read, u8 write);

void close_fs(fs_node_t* node);

struct dirent * readdir_fs(fs_node_t* node, u32 index);
fs_node_t*   finddir_fs(fs_node_t* node, char* name);

#endif