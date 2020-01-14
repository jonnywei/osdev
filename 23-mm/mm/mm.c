#include "mm.h"


void mm_init(mm_t* mm){

    mm->frees =0;
    mm->max_frees =0;
    mm->lost_size =0;
    mm->losts = 0;
    return;

}
u32 mm_total(mm_t* mm){

    u32 i , total = 0;
    for(i =0; i < mm->frees; i++){
        total += mm->free[i].size;
    }
    return total;

}
u32 mm_alloc(mm_t* mm , u32 size){
    u32 i ,j =0;
    u32 addr;
    for(i =0; i < mm->frees; i++){
        freeinfo_t* free = &(mm->free[i]);
        if(free->size < size){
            continue;
        }else {
             addr = free->addr;
             free->addr += size;
             free->addr -= size;
             if(free->size == 0){
                  mm->frees--;
                  for(j =i; j < mm->frees; j++){
                      mm->free[j] = mm->free[j+1];
                  }
             }
             
             return addr;
        }
    }
    return 0;

}


s32 mm_free(mm_t* mm, u32 addr, u32 size){
    u32 i ,j =0;
    for(i =0; i < mm->frees; i++){
        if(  mm->free[i].addr > addr ){
            break;
        }
    }
    if(i > 0){
        if( mm->free[i-1].addr + mm->free[i-1].size == addr){ //和前一个合并
            if(addr + size < mm->free[i].addr){ //没有和下一个合并
                mm->free[i-1].size += size; 
                return 0;
            }else if(addr +size == mm->free[i].addr) { //合并下一个
                mm->free[i-1].size += size; 
                mm->free[i-1].size += mm->free[i].size;

                mm->frees--;

                for(; i <mm->frees; i++){
                     mm->free[ i] = mm->free[ i+1];
                }
                return 0;
            }
        }else { //在中间
            if(addr +size == mm->free[i].addr) { //合并下一个
                mm->free[i].size += size; 
                mm->free[i].addr = addr;
                return 0;
               
            } else if (addr + size < mm->free[i].addr){ //没有和下一个合并,需要插入一个新的条目
                if(mm->frees > MEM_FREES){
                    mm->lost_size += size;
                    mm->losts++;
                    return -1;
                }
                for(j = mm->frees; j>i; j--){
                    mm->free[j] = mm->free[j-1]; 
                }
                mm->free[i].addr = addr;
                mm->free[i].size = size;
                mm->frees++;
                return 0;
            }
        }
    }else {
        if(mm->frees > 0){
            if(addr +size == mm->free[i].addr) { //合并下一个
                mm->free[i].size += size; 
                mm->free[i].addr = addr;
                return 0;
               
            } else if (addr + size < mm->free[i].addr){ //没有和下一个合并,需要插入一个新的条目
                if(mm->frees > MEM_FREES){
                    mm->lost_size += size;
                    mm->losts++;
                    return -1;
                }
                for(j = mm->frees; j>i; j--){
                    mm->free[j] = mm->free[j-1]; 
                }
                mm->free[i].addr = addr;
                mm->free[i].size = size;
                mm->frees++;
                return 0;
            }
        }else{
                mm->free[i].addr = addr;
                mm->free[i].size = size;
                mm->frees++;
                return 0;
        }

    }

    return 0;

}


