#ifndef __CONST_H
#define __CONST_H

/* Convert four letters into a number */
#define MAKE_NUM(A, B, C, D)	(((A+B)<<8)|(C+D))

/* Defines shared between the server and client */
#define SERVER_PORT	MAKE_NUM('C','H','A','T')
//#define SERVER_TCP ....

/* The maximum clients that can chat at once*/
const int MAX_CLIENTS = 10;


#endif