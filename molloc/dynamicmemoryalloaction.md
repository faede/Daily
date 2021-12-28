## allocators

- Explicit allocator , C
- Implicit allocator, Java, ML, Lisp

```
#include<stdlib.h>
void *malloc (size_t size)
   if(size == 0), return NULL
void free(void *p)
calloc , to 0
realloc, resize
sbrk, alloc mem
```

assumptions

Memory is word addressed (4 bytes)

any **malloc** and **free** requests

**free** request must be to a **malloc**’d block

Goals: maximize throughput and peak memory utilization

often conflict

![image-20211228020434775](/Users/zyy/Documents/GitHub/Daily/molloc/dynamicmemoryalloaction.assets/image-20211228020434775.png)



Internal Fragmentation

Extrernal Fragmentation: **depen on future**

![image-20211228021037696](/Users/zyy/Documents/GitHub/Daily/molloc/dynamicmemoryalloaction.assets/image-20211228021037696.png)



Standard method

 **header field** or **header**

Method 1 : Implicit list

![image-20211228021244780](/Users/zyy/Documents/GitHub/Daily/molloc/dynamicmemoryalloaction.assets/image-20211228021244780.png)

Method 2:  Explicit list

![image-20211228021325927](/Users/zyy/Documents/GitHub/Daily/molloc/dynamicmemoryalloaction.assets/image-20211228021325927.png)

Method 3: Segregated free list

![image-20211228021442522](/Users/zyy/Documents/GitHub/Daily/molloc/dynamicmemoryalloaction.assets/image-20211228021442522.png)

method 4: Blocks sorted by size

size :0~9. in list 0

size :10~19. in list 1

....

![image-20211228021453022](/Users/zyy/Documents/GitHub/Daily/molloc/dynamicmemoryalloaction.assets/image-20211228021453022.png)

### Method 1 : Implicit list

need size and allocation status

![image-20211228021916034](/Users/zyy/Documents/GitHub/Daily/molloc/dynamicmemoryalloaction.assets/image-20211228021916034.png)

![image-20211228022153656](/Users/zyy/Documents/GitHub/Daily/molloc/dynamicmemoryalloaction.assets/image-20211228022153656.png)

payload double-word aligned

First fit:

```c
p = start 
while((p < end) && 
			((*p & 1) || 
				(*p < = len)))
p = p + (*p & -2);
```

Next fit:

fragmentation is worse

Best fit:

slower



splitting

```c
void addblock(ptr p, int len){
	int newsize = ((len + 1) >> 1) << 1;
  int oldsize = *p & -2;
  *p = newsize | 1;
  if(newsize < oldsize)
    *(p+newsize) = oldsize - newsize
}
```



Freeing a Block

* Only clear "allocated"

* Coalescing 

  Join with next/previous blocks, if they are free

```c
void free_block(ptr p){
  *p = *p & -2; // clear alloc flag
  next = p + *p;
  if ((*next & 1) == 0)
    *p = *p + *next;
}
```

previous blocks? 

* Bidirectional Coalescing

![image-20211228023338784](/Users/zyy/Documents/GitHub/Daily/molloc/dynamicmemoryalloaction.assets/image-20211228023338784.png)

![image-20211228023358513](/Users/zyy/Documents/GitHub/Daily/molloc/dynamicmemoryalloaction.assets/image-20211228023358513.png)

![image-20211228023524596](/Users/zyy/Documents/GitHub/Daily/molloc/dynamicmemoryalloaction.assets/image-20211228023524596.png)

optimized ?

only previous is freed , we need the footer, so 

​	we can **use other bit present previous block state** (current block is freed)

if state is allocated , no long need footer



not used

because of linear-time allocatioin

### Advanced Concepts

#### Explicit Free List

![image-20211228123531151](/Users/zyy/Documents/GitHub/Daily/molloc/dynamicmemoryalloaction.assets/image-20211228123531151.png)

Allocate

![image-20211228124734881](/Users/zyy/Documents/GitHub/Daily/molloc/dynamicmemoryalloaction.assets/image-20211228124734881.png)

Free

* LIFO ,  fragmentation worse
* address-ordered policy ,  fragmentation lower than LIFO

insert freed blocks so that free list blocks are always in address order

#### LIFO

case 1:

![image-20211228125328443](/Users/zyy/Documents/GitHub/Daily/molloc/dynamicmemoryalloaction.assets/image-20211228125328443.png)

case 2:

![image-20211228125653325](/Users/zyy/Documents/GitHub/Daily/molloc/dynamicmemoryalloaction.assets/image-20211228125653325.png)

or don't do any thing just free , but not LIFO

case 3:

![image-20211228125940171](/Users/zyy/Documents/GitHub/Daily/molloc/dynamicmemoryalloaction.assets/image-20211228125940171.png)



case 4:

![image-20211228130110184](/Users/zyy/Documents/GitHub/Daily/molloc/dynamicmemoryalloaction.assets/image-20211228130110184.png)



### Segregated List (Seglist) Allocators

Concept:

![image-20211228130447870](/Users/zyy/Documents/GitHub/Daily/molloc/dynamicmemoryalloaction.assets/image-20211228130447870.png)



**Best Allocators**

![image-20211228130630481](/Users/zyy/Documents/GitHub/Daily/molloc/dynamicmemoryalloaction.assets/image-20211228130630481.png)

More:

![image-20211228130850051](/Users/zyy/Documents/GitHub/Daily/molloc/dynamicmemoryalloaction.assets/image-20211228130850051.png)

### Garbage Collection

![image-20211228130929391](/Users/zyy/Documents/GitHub/Daily/molloc/dynamicmemoryalloaction.assets/image-20211228130929391.png)

common in mamy dynamic languages:

When can be freed?

cann't predict future

no ptr

but muust make certain assumptions about ptrs:

* memory manager can distinguish pointer from non-pointers
* all pointer point to the start of a block
* Cannot hide pointers

![image-20211228131344956](/Users/zyy/Documents/GitHub/Daily/molloc/dynamicmemoryalloaction.assets/image-20211228131344956.png)

Graph

![image-20211228131442220](/Users/zyy/Documents/GitHub/Daily/molloc/dynamicmemoryalloaction.assets/image-20211228131442220.png)

### Mark and Sweep Collceting

![image-20211228133744970](/Users/zyy/Documents/GitHub/Daily/molloc/dynamicmemoryalloaction.assets/image-20211228133744970.png)

![image-20211228134006650](/Users/zyy/Documents/GitHub/Daily/molloc/dynamicmemoryalloaction.assets/image-20211228134006650.png)

![image-20211228134018303](/Users/zyy/Documents/GitHub/Daily/molloc/dynamicmemoryalloaction.assets/image-20211228134018303.png)

![image-20211228134109632](/Users/zyy/Documents/GitHub/Daily/molloc/dynamicmemoryalloaction.assets/image-20211228134109632.png)

as bfs

Sweep

![image-20211228134219879](/Users/zyy/Documents/GitHub/Daily/molloc/dynamicmemoryalloaction.assets/image-20211228134219879.png)

in C?

![image-20211228134357955](/Users/zyy/Documents/GitHub/Daily/molloc/dynamicmemoryalloaction.assets/image-20211228134357955.png)

### Memory-related perils and pitfalls

![image-20211228134626830](/Users/zyy/Documents/GitHub/Daily/molloc/dynamicmemoryalloaction.assets/image-20211228134626830.png)

#### Pointers

![image-20211228134800060](/Users/zyy/Documents/GitHub/Daily/molloc/dynamicmemoryalloaction.assets/image-20211228134800060.png)

test:

![image-20211228135800885](/Users/zyy/Documents/GitHub/Daily/molloc/dynamicmemoryalloaction.assets/image-20211228135800885.png)

K&R P53



![image-20211228140451721](/Users/zyy/Documents/GitHub/Daily/molloc/dynamicmemoryalloaction.assets/image-20211228140451721.png)

