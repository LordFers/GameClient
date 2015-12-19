#ifndef _H_WINSOCK_
#define _H_WINSOCK_

#include "stdafx.h"
#include "enums.h"

#include <WinSock2.h>
#include <WS2tcpip.h>

#define DEFAULT_PORT "7666"
#define DEFAULT_BUFLEN 512
#define MAX_PACKET_SIZE 1000000

class cWinsock{
    protected:
        static cWinsock* pI;

    public:
        static cWinsock* p_cGIn(){return pI;}
        static void setWinsock(cWinsock* newWinsock){pI = newWinsock;}

        int iResult;

        char network_data[MAX_PACKET_SIZE];

        SOCKET Socket;
        void Init_cWinsock(void);

        static int sendMessage(SOCKET curSocket, char * message, int messageSize);
        static int receiveMessage(SOCKET curSocket, char * buffer, int bufSize);
        void SocketReceive();
};

#endif //WINSOCK
