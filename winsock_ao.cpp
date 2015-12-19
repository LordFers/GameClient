#include "winsock_ao.hpp"
#include "gamedata.hpp"
#include "Protocol.hpp"
#include <stdio.h>
#include <iostream>

cWinsock* cWinsock::pI = NULL;

void cWinsock::Init_cWinsock(void) {

    WSADATA wsaData;
    Socket = INVALID_SOCKET;

    struct addrinfo *result = NULL,
                    *ptr = NULL,
                    hints;

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);

    if (iResult != 0) {
		const char* msgnow = "Falló al intentar conectar con el Servidor. Error (WSAStartup): ";
		msgnow += iResult;
		MessageBoxA(NULL, msgnow, "Argentum Online", NULL);
		return;
    }

    // set address info
    ZeroMemory( &hints, sizeof(hints) );
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    iResult = getaddrinfo(cGameData::p_cGIn()->IpDelServidor(), DEFAULT_PORT, &hints, &result);

    if( iResult != 0 )
    {
        WSACleanup();
		const char* msgnow = "El servidor no se encuentra Online, por favor intenta más tarde.";
		MessageBoxA(NULL, msgnow, "Argentum Online", NULL);
        //exit(1);
    }

    // Attempt to connect to an address until one succeeds
    for(ptr=result; ptr != NULL ;ptr=ptr->ai_next) {

        // Create a SOCKET for connecting to server
        Socket = socket(ptr->ai_family, ptr->ai_socktype,
            ptr->ai_protocol);

        if (Socket == INVALID_SOCKET) {
            WSACleanup();
            exit(1);
        }

        // Connect to server.
        iResult = connect(Socket, ptr->ai_addr, (int)ptr->ai_addrlen);

        if (iResult == SOCKET_ERROR)
        {
			const char* msgnow = "Socket Out. Invalid Operation.";
			MessageBoxA(NULL, msgnow, "Argentum Online", NULL);

            closesocket(Socket);
            Socket = INVALID_SOCKET;
			return;
        }
    }

    // no longer need address info for server
    freeaddrinfo(result);

    // if connection failed
    if (Socket == INVALID_SOCKET)
    {
		const char* msgnow = "Socket Out. Invalid Operation.";
		MessageBoxA(NULL, msgnow, "Argentum Online", NULL);
        WSACleanup();
		return;
    }

    // Set the mode of the socket to be nonblocking
    u_long iMode = 1;

    iResult = ioctlsocket(Socket, FIONBIO, &iMode);
    if (iResult == SOCKET_ERROR)
    {
		const char* msgnow = "Socket Out. Invalid Operation.";
		MessageBoxA(NULL, msgnow, "Argentum Online", NULL);

        closesocket(Socket);
        WSACleanup();
		return;
    }

    //disable nagle
    char value = 1;
    setsockopt( Socket, IPPROTO_TCP, TCP_NODELAY, &value, sizeof( value ) );
}

int cWinsock::sendMessage(SOCKET curSocket, char * message, int messageSize)
{
    return send(curSocket, message, messageSize, 0);
}

int cWinsock::receiveMessage(SOCKET curSocket, char * buffer, int bufSize)
{
    return recv(curSocket, buffer, bufSize, 0);
}

void cWinsock::SocketReceive()
{
    if (cGameData::p_cGIn()->incomingData.length() <= 0)
    {   char* data = network_data;
        iResult = cWinsock::p_cGIn()->receiveMessage(Socket, data, MAX_PACKET_SIZE);
        if (iResult <= 0) return;
        cGameData::p_cGIn()->incomingData.WriteBlock(data, iResult);
        HandleIncomingData();
    }
}
