#ifndef STORAGE_H
#define STORAGE_H
#include <stdio.h>

#if defined(__IBM_METAL__)
#define STORAGE_OBTAIN_24(addr, size)                           \
    __asm(                                                      \
        "*                                                  \n" \
        " LLGF  0,%1      = storage length                  \n" \
        "*                                                  \n" \
        " STORAGE OBTAIN,"                                      \
        "LENGTH=(0),"                                           \
        "CALLRKY=YES,"                                          \
        "LOC=(24,64),"                                          \
        "COND=NO                                            \n" \
        "*                                                  \n" \
        " ST    1,%0      -> Save storage address           \n" \
        "*                                                    " \
        : "=m"(addr)                                            \
        : "m"(size)                                             \
        : "r0", "r1", "r14", "r15");
#else
#define STORAGE_OBTAIN_24(addr, size)
#endif

#if defined(__IBM_METAL__)
#define STORAGE_RELEASE(addr, size)                             \
    __asm(                                                      \
        "*                                                  \n" \
        " LLGF  0,%1      = storage length                  \n" \
        " LLGF  1,%0      -> storage address                \n" \
        "*                                                  \n" \
        " STORAGE RELEASE,"                                     \
        "LENGTH=(0),"                                           \
        "ADDR=(1),"                                             \
        "COND=NO,"                                              \
        "CALLRKY=YES                                        \n" \
        "*                                                    " \
        :                                                       \
        : "m"(addr), "m"(size)                                  \
        : "r0", "r1", "r14", "r15");
#else
#define STORAGE_RELEASE(addr, size)
#endif

#if defined(__IBM_METAL__)
#define IARST64_GET(size, areaaddr)                             \
    __asm(                                                      \
        "*                                                  \n" \
        " LG   2,%1         Get size of storage             \n" \
        "*                                                  \n" \
        " IARST64 REQUEST=GET,"                                 \
        "AREAADDR=%0,"                                          \
        "SIZE=(2),"                                             \
        "COMMON=NO,"                                            \
        "OWNINGTASK=CURRENT,"                                   \
        "FPROT=NO,"                                             \
        "TYPE=PAGEABLE,"                                        \
        "CALLERKEY=YES,"                                        \
        "FAILMODE=ABEND,"                                       \
        "REGS=SAVE                                          \n" \
        "*                                                    " \
        : "=m"(*areaaddr)                                       \
        : "m"(*size)                                            \
        \ 
: "r0", "r1", "r2", "r14", "r15");
#else
#define IARST64_GET(size, areaaddr)
#endif

#if defined(__IBM_METAL__)
#define IARST64_FREE(areaaddr)                                  \
    __asm(                                                      \
        "*                                                  \n" \
        " IARST64 REQUEST=FREE,"                                \
        "AREAADDR=%0,"                                          \
        "REGS=SAVE                                          \n" \
        "*                                                    " \
        :                                                       \
        : "m"(*areaaddr)                                        \
        : "r0", "r1", "r14", "r15");
#else
#define IARST64_FREE(areaaddr)
#endif

static void *__ptr32 storageObtain24(int size)
{
    void *__ptr32 addr = NULL;
    STORAGE_OBTAIN_24(addr, size);
    return addr;
}

static void storageRelease(void *__ptr32 addr, int size)
{
    STORAGE_RELEASE(addr, size);
}

// IARST64 get 64-bit storage
static void *__ptr64 storageGet64(int size)
{
    void *__ptr64 storage = NULL;

    int *storageSize = &size;
    IARST64_GET(&storageSize, &storage);
    return storage;
}

// IARST64 free 64-bit storage
static void storageFree64(void *__ptr64 storage)
{
    IARST64_FREE(&storage);
}
#endif