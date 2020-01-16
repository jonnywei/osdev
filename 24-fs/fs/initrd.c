#include "initrd.h"
#include "../mm/mm.h"
#include "fs.h"
#include "../libc/mem.h"
#include "../libc/string.h"

 fs_node_t* initrd_root;
 initrd_header_t*  initrd_header;
 initrd_file_header_t*  initrd_file_header;
fs_node_t *root_nodes;              // List of file nodes.


struct  dirent dirent;

 struct dirent* initrd_readdir (struct fs_node_t * node, u32 index){

      if (node == initrd_root && index == 0)
    {
      strcpy(dirent.name, "initrd");
      dirent.name[6] = 0;
      dirent.inode = 0;
      return &dirent;
    }

     if(index-1 > initrd_header->nfiles){
         return 0;
     }
     strcpy(dirent.name, root_nodes[index-1].name);
     dirent.inode = root_nodes[index-1].inode;
     return &dirent;

 }



static fs_node_t *initrd_finddir(fs_node_t *node, char *name)
{
    // if (node == initrd_root &&
    //     strcmp(name, "initrd") )
    //     return initrd_root;

    int i;
    for (i = 0; i <  initrd_header->nfiles; i++)
        if (!strcmp(name, root_nodes[i].name))
            return &root_nodes[i];
    return 0;
}


static u32 initrd_read(fs_node_t *node, u32 offset, u32 size, u8 *buffer)
{
    initrd_file_header_t header = initrd_file_header[node->inode];
    if (offset > header.length)
        return 0;
    if (offset+size > header.length)
        size = header.length-offset;
    memory_copy( (u8*) (header.offset+offset),buffer, size);
    return size;
}



 fs_node_t* init_initrd(u32 location){

        initrd_header = (initrd_header_t*) location;

        initrd_file_header =  (initrd_file_header_t* ) (location + sizeof(initrd_header_t));
        initrd_root = (fs_node_t*) mm_alloc(&memman, sizeof(fs_node_t));

        strcpy(initrd_root->name, "initrd");
        initrd_root->flags = FS_DIRECTORY;

      initrd_root->read = 0;
    initrd_root->write = 0;
    initrd_root->open = 0;
    initrd_root->close = 0;
    initrd_root->readdir = &initrd_readdir;
    initrd_root->finddir = &initrd_finddir;
  
     root_nodes  = (fs_node_t*)mm_alloc(&memman,sizeof(fs_node_t) * initrd_header->nfiles);
   int i =0;
   for(; i< initrd_header->nfiles; i++){
        initrd_file_header[i].offset += location;
        strcpy(root_nodes[i].name, &initrd_file_header[i].name);
        root_nodes[i].inode = i;
        root_nodes[i].flags = FS_FILE;
        root_nodes[i].read = &initrd_read;
        root_nodes[i].write = 0;
        root_nodes[i].readdir = 0;
        root_nodes[i].finddir = 0;
        root_nodes[i].open = 0;
        root_nodes[i].close = 0;
   }

  return initrd_root;
 }

