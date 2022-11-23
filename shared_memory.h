#ifndef SHARED_MEMORY_H
#define SHARED_MEMORY_H

#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

using namespace std;

char* attach_memory_block(char *filename, int size);
bool detach_memory_block(char *block);
bool destory_memory_block(char *filename);

#endif //SHARED_MEMORY_H
