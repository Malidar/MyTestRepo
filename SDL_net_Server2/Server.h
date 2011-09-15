#ifndef __SERVER_H
#define __SERVER_H

#include <SDL_net.h>
#include <SDL_thread.h>

#include "CONST.H"
#include "PEOPLE.H"

class Server
{
protected:
	People people[MAX_CLIENTS];
	SDL_Thread *netThread;
	TCPsocket tcpSock;
	UDPsocket udpSock;
	SDLNet_SocketSet socketSet;		
public:
	Server();
	// init
	void initSDLNet();
	void initChannels();
	void allocateSockets();
	void createTCPSocket();
	void createUDPSocket();
	void cleanup(int exitcode);

	void findInactivePersonSlot(int &which);
	void roomFull(TCPsocket newsock);
	void HandleServer(void);
	/* Send a "new client" notification */
	void SendNew(int about, int to);
	void SendID(int which);
	void notifyAllConnectionClosed(char data[], int which);
	//void deleteConnection(int which);
	void HandleClient(int which);
	void checkEvents();		// #include <SDL.h>
};

#endif