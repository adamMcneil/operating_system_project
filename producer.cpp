#include <iostream>
#include <fstream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

using namespace std;

int main()
{
    /////////////////////////////////SET UP SHARED MEMORY////////////////////////////////////////
    // ftok to generate unique key
    key_t key = ftok("shmfile",65);

    // shmget returns an identifier in shmid
    int shmid = shmget(key,1024, 0666|IPC_CREAT);

    // shmat to attach to shared memory
    char *str = (char*) shmat(shmid,(void*)0,0);

    /////////////////////////////////READ SETTINGS////////////////////////////////////////
    // bufferLength must be less then 128 and positive
    int bufferLength;
    ifstream settingsFile;
    settingsFile.open("settings.txt");
    settingsFile >> bufferLength;

    /////////////////////////////////WRITE DATA////////////////////////////////////////
    
    string input;
    int writeHead = 0;
    int readHead = 0;

    // write head at bufferLength 
    // read head at bufferLength + 1
    int writeHeadIndex = bufferLength;
    int readHeadIndex = bufferLength + 1;
    str[writeHeadIndex] = 0;
    str[readHeadIndex] = 0;

    while (true)
    {
        writeHead = str[writeHeadIndex];
        readHead = (str[readHeadIndex] - 1) % bufferLength;
        if (writeHead != readHead)
        {
            writeHead = str[writeHeadIndex];
            cout << "Write Data : ";
            cin >> input;
            for (int i = 0; i < input.length(); i++)
            {
                str[writeHead % writeHeadIndex] = input[i];
                writeHead++;
            }
            str[writeHeadIndex] = writeHead % writeHeadIndex;

            cout << "write head index: " << writeHead % bufferLength << endl;
        }
    }

    return 0;
}