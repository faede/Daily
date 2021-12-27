## 1 


if it is success



```c
void *p = malloc(s);

uint64_t header_addr = (uint64_t)p - 4;
uint32_t header_value = *((uint32_t *)header_addr);
uint32_t block_size = header_value & 0xFFFFFFFFE; // oimt exit bit
int allocated = header_value & 0x1;


uint64_t next_header_addr = header_addr + block_size;
```



```c
uint64_t heap_start_address = xxx;

void *malloc(uint32_t size){
  uint64_t p = heap_start_address;
  
  while(1){
    uint32_t header_value = *((uint32_t *)p);
    uint32_t p_allocated = header_value & 0x1;
    uint32_t p_block_size = header_value & 0xFFFFFFFFE;
    
    if(p_allocated == 0 && p_block_size - sizeof(uint32_t) >= size){
      
      // return (void *)(p + 4); 
      // need split to (size | remains)
      
      uint32_t request_block_size = 4 + size;
      if(request_block_size 0x7 != 0){
        // over 8 bytes
        request_block_size = request_block_size & 0xFFFFFFFE + 0x8;
      }
      
      uint32_t next_block_header_addr = p + request_block_size;
      
      *(uint32_t *)next_block_header_addr = p_block_size - request_block_size;//size
      
      
      *(uint32_t *)p = request_block_size; //set size
      *(uint32_t *)p = *(uint32_t *)p | 0x1 ;// allocated
      
      return (void *)(p + 4);
    }else{
      p = p + p_block_size; // check next block
    }
    
  }
}

void free(void *p){
  // single driection merge later (recursive )
  uint64_t payload_addr = (uint64_t)p;
  uint64_t header_addr = payload_addr - 4;
  
  uint32_t allocated =  (*(uint32_t *)header_addr) & 0x1;
  
  if(allocated == 0){
    printf ("free twice");
    return ;
  }
  
  // allocated == 1
  
  uint32_t block_size =  (*(uint32_t *)header_addr) & 0xFFFFFFFE;
  
  uint64_t q = header_addr + block_size; // next
  uint32_t q_allocated = get_allocation(q);
  uint32_t q_block_size = get_blocksize(q);
  
  if(q_allocated == 1){
    set_free(p);
    return;
  }else{
    // merge p & q
    set_size(header_addr, block_size + q_block_size);
    set_free(header_addr);
    clear(q);
  }
}
```







```c
```











