#ifndef OS_P1_SHARE_HPP
#define OS_P1_SHARE_HPP


#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>

#define SHM_NAME       "/shared_table"
#define SEM_EMPTY_NAME "/empty_sem"
#define SEM_FULL_NAME  "/full_sem"
#define SEM_MUTEX_NAME "/mutex_sem"
#define TABLE_SIZE     2

//buffer where the data is temporarily stored and shared
struct SharedTable {
    int table[TABLE_SIZE];

    //next index
    int in = 0;
    int out = 0;
};

#endif