
#include <unistd.h>
#include <cstdio>
#include <netdb.h>
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <sstream>
#include "Memory.cpp"

using namespace std;

void* task1(void *);
void print();

static int ServerSocket;
const bool active = true;
Memory memory;

int portNo,portA, portP, ClientSocket, type;
char* ip;
bool inUse;
struct sockaddr_in serverAddress, clientAddress;


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
    memory = Memory();

    socklen_t len; //store size of the address



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

        //pthread_t hilo;
        pthread_create(&threadA[noThread], NULL, task1, NULL);
        //pthread_create(&hilo,NULL,task1,NULL);
        sleep(1);
        noThread++;
    }

    return 0;
}

void print(){
    cout<<"mostrando memoria"<<endl;
    memory.ram.print();
}

void* task1 (void *dummyPt) {
    cout << "thread created" <<endl;
    /*
    if (!inUse){
        inUse = true;
    }else{
        while(inUse){

        }
    }*/

    char* buffer = new char[100];
    read(ServerSocket, buffer, 100);

    string tester(buffer);

    if (tester.size() != 0){
        if (tester.compare(0, 3, "*n/") == 0) {
            bool reading = true;
            int start = 3;
            int bits = 0;
            int pos = 3;
            int items = 0;
            char* key;
            //void* value;
            int value;
            int value_size = 0;

            while (reading) {
                if (tester.compare(pos, 1, "/") == 0) {
                    if (items == 0) {
                        key = (char*)tester.substr(start, bits).c_str();
                        start = pos + 1;
                        bits = 0;
                        items++;
                    } else if (items == 1) {
                        //value = (void*)tester.substr(start, bits).c_str();
                        value = atoi(tester.substr(start, bits).c_str());
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

            if (memory.ram.searchKey(key)){
                cout << "The key is already in use" << endl;
            }else if (!memory.ram.searchKey(key)){
                memory.ram.add_end(key,value,value_size);
            }
            else{
                cout << "ERROR" <<endl;
            }

            print();
        }else if (tester.compare(0, 3, "*g/") == 0){
            bool reading = true;
            int start = 3;
            int bits = 0;
            int pos = 3;
            char* key;

            while (reading) {
                if (tester.compare(pos, 1, "*") == 0) {
                    key = (char*)tester.substr(start, bits).c_str();
                    reading = false;
                }else{
                    bits++;
                }
                pos++;
            }

            rmRef_h* temp = &memory.ram.get_rmRef(key);

            if (temp != NULL){
                temp->printValues();

                ostringstream os;
                os << "*" << "/" << key <<"/" <<temp->data << "/" << temp->data_size << "*" << endl;

                write(ServerSocket,os.str().c_str(),os.str().size());
                ServerSocket = 0;

            }else{
                cout <<"/d"<< "the key is not in use" << endl;
            }

        }else if (tester.compare(0, 3, "*d/") == 0){
            bool reading = true;
            int start = 3;
            int bits = 0;
            int pos = 3;
            char* key;

            cout << tester << endl;

            while (reading) {
                if (tester.compare(pos, 1, "*") == 0) {
                    key = (char*)tester.substr(start, bits).c_str();
                    reading = false;
                }else{
                    bits++;
                }
                pos++;
            }

            if (memory.ram.searchKey(key)){
                memory.ram.del_by_key(key);
            }else if (!memory.ram.searchKey(key)){
                cout << "The key is not in use" << endl;
            }
            else{
                cout << "ERROR" <<endl;
            }
        }

    }
    sleep(1);
    inUse = false;
    cout << "\nClosing thread and conn" << endl;
    pthread_exit(NULL);
}

