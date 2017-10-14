
#ifndef EJEMPLO_BIBLIOTECA_H
#define EJEMPLO_BIBLIOTECA_H


#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <cstdlib>
#include <arpa/inet.h>
#include <string>
#include <sstream>


using namespace std;

class rmRef_h{
public:
    rmRef_h* next;
    int data;
    char* key;
    int data_size;

    rmRef_h(){
        key = NULL;
        data = 0;
        next = NULL;
        data_size = 0;
    }

    void printValues(){
        cout << "Key " << key << endl;
        cout << "Data " << data << endl;
        cout << "Data_size " << data_size << endl;
    }

    ~rmRef_h();



    bool operator==(const rmRef_h& target){
        bool result = false;
        if (this == &target){
            if (this->data != target.data){
                result = true;
            }
        }
        return result;
    }

    bool operator!=(const rmRef_h& target){
        bool result = false;
        if (this != &target){
            if (this->data != target.data){
                result = true;
            }
        }
        return result;
    }

    rmRef_h& operator=(const rmRef_h& target){
        if (this != &target){
            data = target.data;
            data_size =target.data_size;
        }
        return *this;
    }
};

int ClientSocket=0, portNo, portNoHA;
const char* ipAdd;
const char* ipAddHA;

bool testConnection();
void createSocket();
void closeSocket();
void sendCommand(string parameters);

struct sockaddr_in ServerAddress;

rmRef_h* getptr = new rmRef_h();

void init (const char* ip, int port, const char* ipHA, int portHA) {
    struct hostent *server,*serverHA;
    portNo = port;
    portNoHA = portHA;
    ipAdd = ip;
    ipAddHA = ipHA;

    if((portNo > 65535) || (portNo < 2000))
    {
        cout<<"Please enter port number between 2000 - 65535"<<endl;
        exit(1);
    }


    // Get the server IP
    server = gethostbyname(ipAdd);
    serverHA = gethostbyname(ipAddHA);

    if(server == NULL)
    {
        cout << "Active Server Invalid IP" << endl;
        exit(1);
    }
    if(serverHA == NULL)
    {
        cout << "Passive Server Invalid IP" << endl;
        exit(1);
    }


    ServerAddress.sin_family = AF_INET;
    ServerAddress.sin_addr.s_addr = inet_addr(ip);
    ServerAddress.sin_port = htons(portNo);

    if (!testConnection()){
        exit(1);
    }
    closeSocket();
}

void createSocket(){
    if (ClientSocket == 0){
        ClientSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    }else if(ClientSocket <0) {
        cout << "Can't create the socket" << endl;
    }
}

void closeSocket(){
    if(ClientSocket != 0) {
        ClientSocket = 0;
    }
}

bool testConnection(){
    createSocket();

    for (int i = 0; i<2;i++){
        if (connect(ClientSocket,(sockaddr*)&ServerAddress, sizeof(ServerAddress))==0) {
            if (i == 0) {
                cout << "Connected to Active Server" << endl;
                return true;
            }
            if(i == 1){
                cout << "Connected to Passive Server" << endl;
                return true;
            }
        }else{
            if(i == 0){
                cout << "Cannot connected Active Server" << endl;
            }
            if (i == 1){
                cout << "Cannot connected to any Server" << endl;
                return false;;
            }
            ServerAddress.sin_addr.s_addr = inet_addr(ipAddHA);
            ServerAddress.sin_port = htons(portNoHA);
        }
    }
}

void sendCommand(string parameters){
    if (!testConnection()){
        cout << "error" << endl;
        exit(1);
    }
    const char* message = parameters.c_str();

    write(ClientSocket,message,parameters.size());

    closeSocket();
}

void rm_new(char* key,void* value, int value_size){
    ostringstream os;
    os << "*" << "n" <<"/"<< key <<"/" <<*(int*)value << "/" << value_size << "*" << endl;
    sendCommand(os.str());
}

rmRef_h* rm_get(char* key){
    ostringstream os;
    os << "*" << "g" <<"/"<< key << "*" << endl;

    if (!testConnection()){
        cout << "error" << endl;
        exit(1);
    }

    write(ClientSocket, os.str().c_str(), os.str().size());

    char* buff = new char(100);
    ssize_t readed = read(ClientSocket,buff,100);
    closeSocket();

    if (readed != -1){
        string tester(buff);

        if (tester.compare(0, 2, "*/") == 0) {
            bool reading = true;
            int start = 2;
            int bits = 0;
            int pos = 2;
            int items = 0;
            char *key_;
            int value_ = 0;
            int value_size_ = 0;

            while (reading) {
                if (tester.compare(pos, 1, "/") == 0) {
                    if (items == 0) {
                        key_ = (char *) tester.substr(start, bits).c_str();
                        start = pos + 1;
                        bits = 0;
                        items++;
                    } else if (items == 1) {
                        value_ = atoi(tester.substr(start, bits).c_str());
                        start = pos + 1;
                        bits = 0;
                        items++;
                    } else {
                        cout << "to many parameters to assign" << endl;
                    }
                } else if (tester.compare(pos, 1, "*") == 0) {
                    value_size_ = atoi(tester.substr(start, bits).c_str());
                    reading = false;
                } else {
                    bits++;
                }
                pos++;
            }

            getptr->key = key_;
            getptr->data = value_;
            getptr->data_size = value_size_;
        }
    }else{
        cout << "can't read" << endl;
    }

    return getptr;

}

void rm_delete(rmRef_h* handler){
    ostringstream os;
    os << "*" << "d" <<"/"<< handler->key << "*" << endl;
    sendCommand(os.str());
}


#endif //EJEMPLO_BIBLIOTECA_H
