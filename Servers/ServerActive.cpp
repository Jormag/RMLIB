
#include <unistd.h>
#include <cstdio>
#include <netdb.h>
#include <iostream>
#include <sys/socket.h>

using namespace std;

void *task1(void *);

static int ServerSocket;
const int ThreadUsable = 3;

int main()
{
    int portNo = 8080, ClientSocket;
    socklen_t len; //store size of the address
    struct sockaddr_in serverAddress, clientAddress;


    //Set the thread Number
    pthread_t threadA[ThreadUsable];

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

    listen(ClientSocket, 5);

    int noThread = 0;

    while (noThread < ThreadUsable)
    {
        socklen_t len = sizeof(clientAddress);
        cout << "Listening" << endl;

        //this is where client connects. svr will hang in this mode until client conn
        ServerSocket = accept(ClientSocket, (struct sockaddr *)&clientAddress, &len);

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
    }

    for(int i = 0; i < ThreadUsable; i++)
    {
        pthread_join(threadA[i], NULL);
    }


}

void *task1 (void *dummyPt)
{
    cout << "Thread No: " << pthread_self() << endl;
    char test[300];
    bool loop = false;
    while(!loop)
    {
        read(ServerSocket, test, 300);

        string tester (test);
        cout << tester << endl;


        if(tester == "exit")
            break;
    }
    cout << "\nClosing thread and conn" << endl;
    close(ServerSocket);
}
