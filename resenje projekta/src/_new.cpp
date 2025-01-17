//
// Created by os on 8/27/22.
//

#include "../lib/mem.h"
#include "../h/syscall_c.h"

using size_t = decltype(sizeof(0));

void *operator new(size_t n)
{
    return __mem_alloc(n);
    //return mem_alloc(n);
}

void *operator new[](size_t n)
{
    return __mem_alloc(n);
    //return mem_alloc(n);
}

void operator delete(void *p) noexcept
{
__mem_free(p);
}

void operator delete[](void *p) noexcept
{
__mem_free(p);
}

//int __mem_free(void* ptr);