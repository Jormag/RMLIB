#include <iostream>
//#include "/home/cristian/CLionProjects/RMLIB.h"
#include "RMLIB.h"
#include "Servers/rmRef_h.cpp"

using namespace std;
int main() {
    string ip = "192.168.0.28";
    string ipHA = "192.168.0.28";
    int port = 8080, portHA = 8000;;

    string key = "";
    string value = "";
    void* ptr = &value;


    init(ip.c_str(), port, ipHA.c_str(), portHA);

    cin >> key;
    cin >> value;

    rm_new(key.c_str(),ptr,sizeof(value));

    return 0;
}