

#include "SERVER.H"

//////////////////////CONSTRUCTORS/////////////////////////////////////////////
Server::Server()
{
	/* Init Server func */
	initSDLNet();
	initChannels();
	allocateSockets();
	createTCPSocket();
	createUDPSocket();

}
//////////////////////INIT FUNCTIONS///////////////////////////////////////////
void Server::initSDLNet()
{
	/* Initialize the network */
	if ( SDLNet_Init() < 0 ) 
	{
		fprintf(stderr, "Couldn't initialize net: %s\n",
						SDLNet_GetError());
		SDL_Quit();
		exit(1);
	}
}

void Server::initChannels()
{
	     /* Initialize the channels */
	for (int i = 0; i < MAX_CLIENTS; ++i) 
	{
		people[i].initChannel();
	}
}

void Server::allocateSockets()
{
	/* Allocate the socket set */
	socketSet = SDLNet_AllocSocketSet(MAX_CLIENTS+1);
	if ( socketSet == NULL ) 
	{
		fprintf(stderr, "Couldn't create socket set: %s\n",
						SDLNet_GetError());
		cleanup(2); 
	}
}

void Server::createTCPSocket()
{
	IPaddress serverIP;
     
     /* Create the TCP socket */
	SDLNet_ResolveHost(&serverIP, NULL, SERVER_PORT);
    printf("Server IP: %x, %d\n", serverIP.host, serverIP.port);
	tcpSock = SDLNet_TCP_Open(&serverIP);
	if ( tcpSock == NULL ) 
	{
		fprintf(stderr, "Couldn't create TCP socket: %s\n",
						SDLNet_GetError());
		cleanup(2);
	}
	SDLNet_TCP_AddSocket(socketSet, tcpSock);
}

void Server::createUDPSocket()
{
	udpSock = SDLNet_UDP_Open(0);		// Open Random port OR CLIENT_UDP / CLIENT_TCP
	if ( udpSock == NULL ) 
	{
		fprintf(stderr, "Couldn't create UDP socket: %s\n",
						SDLNet_GetError());
		cleanup(2);
	}
	SDLNet_UDP_AddSocket(socketSet, udpSock);
}

void Server::cleanup(int exitcode)
{	/* Closing Sockets */
	if ( tcpSock != NULL )	
	{
		SDLNet_TCP_Close(tcpSock);
		tcpSock = NULL;
	}
	if ( udpSock != NULL )
	{
		SDLNet_UDP_Close(udpSock);
		udpSock = NULL;
	}	/* Free the Socket Set */
	if ( socketSet != NULL ) 
	{
		SDLNet_FreeSocketSet(socketSet);
		socketSet = NULL;
	}
	SDLNet_Quit();
	printf("Exitcode %d\n", exitcode);
	exit(exitcode);
}

////////////////////* Sever functions *////////////////////////////////////////

void findInactivePersonSlot(int &which)
{
}

void roomFull(TCPsocket newsock)
{
	/* No more room... */
	//char data = GAME_BYE;

	//SDLNet_TCP_Send(newsock, &data, 1);
	//SDLNet_TCP_Close(newsock);

	#ifdef DEBUG
		fprintf(stderr, "Connection refused -- chat room full\n");
	#endif
}

void HandleServer(void)
{
}

/* Send a "new client" notification */
void SendNew(int about, int to)
{
}

void SendID(int which)
{
}

void notifyAllConnectionClosed(char data[], int which)
{
}

//void deleteConnection(int which);
void HandleClient(int which)
{
}

void checkEvents()	
{
}

