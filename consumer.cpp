#include <iostream>
#include <fstream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include "function_consumer.h"

using namespace std;

int main()
{
    /////////////////////////////////SET UP SHARED MEMORY////////////////////////////////////////
    // ftok to generate unique key
    key_t key = ftok("shmfile",65);

    // shmget returns an identifier in shmid
    int shmid = shmget(key,1024,0666|IPC_CREAT);

    // shmat to attach to shared memory
    char *str = (char*) shmat(shmid,(void*)0,0);

    /////////////////////////////////READ SETTINGS////////////////////////////////////////
    // bufferLength must be less then 128 and positive
    int bufferLength;
    ifstream settingsFile;
    settingsFile.open("settings.txt");
    settingsFile >> bufferLength;

    /////////////////////////////////READ DATA////////////////////////////////////////
    // write head at bufferLength 
    // read head at bufferLength + 1
    int writeHeadIndex = bufferLength;
    int readHeadIndex = bufferLength + 1;

    int writeHead;
    while (true)
    {
        if (str[readHeadIndex] != str[writeHeadIndex])
        {
            writeHead = str[readHeadIndex];
            cout << str[writeHead] << endl;
            writeHead++;
            writeHead %= bufferLength;
            str[readHeadIndex] = writeHead;
            cout << "write head index: " << writeHead << endl;
        }
    }

    return 0;
}