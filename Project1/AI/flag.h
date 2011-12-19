#ifndef _FLAG_H
#define _FLAG_H

/* a=target variable, b=bit number to act upon 0-n */
#define BIT_SET(a,b) ((a) |= (1<<(b)))
#define BIT_CLEAR(a,b) ((a) &= ~(1<<(b)))
#define BIT_TOGGLE(a,b) ((a) ^= (1<<(b)))
#define BIT_CHECK(a,b) ((a) & (1<<(b)))

/* FLAGS */
const int NUM_FLAGS = 12;	// Array implementation

/* PRIORITY */
const int HIGH_PRI		= 16;
const int LOW_PRI			= 32;

/* CONDITONS */
const int IDLE				= 0;
const int LOW_HEALTH	= 1;
const int NO_AMMO			= 2;
const int TAKING_FIRE = 3;
const int SHOOT				= 4;
const int SEE_ENEMY		= 5;
const int BLOCKED			= 6;
const int RUNNING			= 7;
//const int	JUMPING			= 8;


/* TASKS */	/* ACTIONS */
const int FACE_ENEMY	= 9;
const int RELOAD			= 10;

/* SCHEMES */
const int HIDE				= 11;
const int SEARCH			= 12;

/* ANIMATIONS */
const int ANIMATIONS	= 16;		
const int ANIMATION1	= 17;
const int ANIMATION2	= 18;

#endif