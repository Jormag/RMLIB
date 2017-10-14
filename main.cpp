#include <iostream>
//#include "/home/cristian/CLionProjects/RMLIB.h"
#include "RMLIB.h"
//#include "Servers/rmRef_h.cpp"

using namespace std;
int main() {
    string ip = "192.168.0.46";
    string ipHA = "192.168.0.46";
    int port = 8080, portHA = 8000;;

    string key = "11";
    int value = 2;
    void* ptr = &value;

    string rec;


    init(ip.c_str(), port, ipHA.c_str(), portHA);

    cout << "Dijite un numero entero entre 1 y 3" << endl;
    cout << "1 -> rm_new" << endl;
    cout << "2 -> rm_get" << endl;
    cout << "3 -> rm_delete" << endl;
    cin >> rec;

    if (rec == "1") {
        cout << "Dijite un valor para el key" << endl;
        cin >> key;
        cout << "Dijite un valor entero para el value" << endl;
        cin >> rec;
        value = atoi(rec.c_str());

        rm_new((char *)key.c_str(), ptr, sizeof(value));

    }else if (rec == "2"){
        cout << "Dijite un valor para el key" << endl;
        cin >> key;
        rmRef_h* temp = rm_get((char*)key.c_str());
        temp->printValues();

    }else if (rec == "3"){
        cout << "Dijite un valor para el key" << endl;
        cin >> key;
        rmRef_h* temp = rm_get((char*)key.c_str());
        rm_delete(temp);
    }else{
        cout << "Opcion invalida" << endl;
        exit(0);
    }

    return 0;
}