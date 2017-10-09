
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
#include <iostream>
#include <sstream>

using namespace std;


int ClientSocket=0, portNo, portNoHA;
const char* ipAdd;
const char* ipAddHA;

bool testConnection();
void createSocket();
void closeSocket();
void sendCommand(string parameters);

struct sockaddr_in ServerAddress;

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

    send(ClientSocket, message, parameters.size(),0);
    closeSocket();
}

void rm_new(const char* key,void* value, int value_size){
    string* intptr = static_cast<string*>(value);
    ostringstream os;
    os << "*" << "n" <<"/"<< key <<"/" <<*intptr << "/" << value_size << "*" << endl;
    sendCommand(os.str());
}


#endif //EJEMPLO_BIBLIOTECA_H
