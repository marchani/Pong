#pragma once
#include <winsock2.h>
#include <Windows.h>
#include "NetworkServices.h"
#include <ws2tcpip.h>
#include <map>
#include "NetworkData.h"
using namespace std; 
#pragma comment (lib, "Ws2_32.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "6881" 

//
// ServerNetwork()
//
class ServerNetwork
{

	public:

		// constructor()
		ServerNetwork();

		// destructor()
	    ~ServerNetwork();

		// sendToAll()
	    void sendToAll( char* packets, int totalSize );

		// receiveData()
	    int receiveData( unsigned int client_id, char* recvbuf );
	
		// acceptNewClient()
	    bool acceptNewClient( unsigned int& id );

		// Socket to listen for new connections
		SOCKET ListenSocket;

		// Socket to give to the clients
		SOCKET ClientSocket;

		// for error checking return values
		int iResult;

		// table to keep track of each client's socket
		std::map<unsigned int, SOCKET> sessions; 
};