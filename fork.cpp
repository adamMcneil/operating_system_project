#include <iostream>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;

int main()
{
    fork();
    string input;
    cout << "hello" << endl;
    cin >> input;
    cout << input << endl;
    while(1)
        ;
    return 0;
}