
#include "PEOPLE.H"

People::People()
{
}

bool People::isActive()
{
	return active;
}

void People::initChannel()	
{		/* Init a Channel */
		active = false;
		tcpSock = NULL;
		udpSock = NULL;
}

void People::addSocket()
{
	//if(type == "TCP")
	//{
	//}
	//else if(type == "UDP")
	//{
	//}
	#ifdef DEBUG
		fprintf(stderr, "People_addSocket, para TCP/UDP!");
	#endif
}

void People::deleteConnection()
{
}