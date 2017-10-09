
#include <unistd.h>
#include <cstdio>
#include <netdb.h>
#include <iostream>
#include <string>
#include <sys/socket.h>
#include "Memory.cpp"

enum Commands {RM_NEW, RM_GET, RM_DELETE,RM_EXIT};

using namespace std;

void* task1(void *);
void print();

static int ServerSocket;
const bool active = true;
Memory<const char*> memory;

int portNo,portA, portP, ClientSocket, type;
char* ip;
bool inUse;


int main() {
    cout << "Escriba el tipo de servidor" <<endl;
    cout << "1 - Activo" <<endl;
    cout << "2 - Pasivo" <<endl;
    cin >> type;

    if (type == 1){
        cout << "Escriba el puerto para el servidor"<<endl;
        cin >>portNo;
        cout << "Escriba el puerto para la comunicacion entre servidores" << endl;
        cin >> portA;
    }else if (type == 2){
        cout << "Escriba el puerto para el servidor";
        cin >>portNo;
        cout << "Escriba la ip del servidor activo" << endl;
        cin >> ip;
        cout << "Escriba el puerto del servidor activo" << endl;
        cin >> portP;
    }else{
        cout << "Tipo de servidor invalido" << endl;
        return 0;
    }

    inUse = false;
    memory = Memory<const char*>();

    socklen_t len; //store size of the address
    struct sockaddr_in serverAddress, clientAddress;


    //Set the thread Number
    pthread_t threadA[100];

    //create socket
    ClientSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    if(ClientSocket < 0)
    {
        cout << "Cannot open socket" << endl;
        return 0;
    }


    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(portNo);

    //bind socket
    if(bind(ClientSocket, (sockaddr*)&serverAddress, sizeof(serverAddress)) < 0)
    {
        cout << "Cannot bind" << endl;
        return 0;
    }

    listen(ClientSocket, 100);

    int noThread = 0;

    while (active)
    {
        socklen_t len = sizeof(clientAddress);
        //cout << "Listening" << endl;

        //this is where client connects. svr will hang in this mode until client conn
        ServerSocket = accept(ClientSocket, (struct sockaddr*)&clientAddress, &len);

        if (ServerSocket < 0)
        {
            cout << "Cannot accept connection" << endl;
            return 0;
        }
        else
        {
            cout << "Connection successful" << endl;
        }

        pthread_create(&threadA[noThread], NULL, task1, NULL);

        noThread++;
        print();
    }

    /*
    for(int i = 0; i < active; i++)
    {
        pthread_join(threadA[i], NULL);
    }
     */

    //memory.ram.print();

    return 0;
}

void print(){
    cout<<"mostrando memoria"<<endl;
    memory.ram.print();
}

void* task1 (void *dummyPt) {
    if (inUse == false){
        inUse = true;
    }else{
        while(inUse){

        }
    }

    cout << "Client Connected" << endl;
    char test[30] = {0};
    recv(ServerSocket, test, 30, 0);
    string tester(test);

    if (tester.size() != 0){
        if (tester.compare(0, 3, "*n/") == 0) {
            bool reading = true;
            int start = 3;
            int bits = 0;
            int pos = 3;
            int items = 0;
            const char* key;
            const char* value;
            int value_size = 0;

            while (reading) {
                if (tester.compare(pos, 1, "/") == 0) {
                    if (items == 0) {
                        key = tester.substr(start, bits).c_str();
                        start = pos + 1;
                        bits = 0;
                        items++;
                    } else if (items == 1) {
                        value = tester.substr(start, bits).c_str();
                        start = pos + 1;
                        bits = 0;
                        items++;
                    } else {
                        cout << "to many parameters to assign" << endl;
                    }
                } else if (tester.compare(pos, 1, "*") == 0) {
                    value_size = atoi(tester.substr(start, bits).c_str());
                    reading = false;
                }else{
                    bits++;
                }
                pos++;
            }
            memory.ram.add_end(key,value,value_size);
            print();
        }else if (tester.compare(0, 3, "*g/") == 0){

        }
    }else{
        cout << "Tester Vacio"<<endl;
    }

    inUse = false;
    cout << "\nClosing thread and conn" << endl;
    pthread_exit(NULL);
}

