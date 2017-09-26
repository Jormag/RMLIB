#include <iostream>
//#include "/home/cristian/CLionProjects/RMLIB.h"
#include "RMLIB.h"
#include "Servers/Memory.cpp"

using namespace std;

int main() {
    /*char* parameters[4]= {"192.168.0.39","8080","192.168.0.39","8000"};

    init(parameters);
    sendCommand(rm_new);
     */
    Memory<int> memory;
    memory.ram.add_end(10);
    memory.ram.add_end(30);
    memory.ram.add_end(15);
    memory.ram.print();

    memory.cache.add_end(1);
    memory.cache.add_end(3);
    memory.cache.add_end(5);
    memory.cache.print();
    return 0;
}