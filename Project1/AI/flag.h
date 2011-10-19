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
const int LOW_HEALTH	= 0;
const int NO_AMMO			= 0;
const int TAKING_FIRE = 0;
const int FIRE				= 1;
const int SEE_ENEMY		= 2;
const int BLOCKED			= 3;
const int RUNNING			= 6;
const int	JUMPING			= 7;


/* TASKS */	/* ACTIONS */
const int FACE_ENEMY	= 0;
const int RELOAD			= 0;
const int MOVE				= 1;

/* SCHEMES */
const int HIDE				= 0;
const int SEARCH			= 0;

/* ANIMATIONS */
const int ANIMATIONS	= 16;		
const int ANIMATION1	= 4;
const int ANIMATION2	= 5;

#endif