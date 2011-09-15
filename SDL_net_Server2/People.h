#ifndef __PEOPLE_H
#define __PEOPLE_H

//#include <SDL.h>
#include <SDL_net.h>

class People
{
protected:
	bool active;
	TCPsocket tcpSock;
	UDPsocket udpSock;
	IPaddress peer;
	//Unit8 name [256+1];
public:
	People();
	bool isActive();
	void initChannel();
	void addSocket();
	void deleteConnection();
};

#endif