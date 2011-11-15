#ifndef _NPC_H
#define _NPC_H

#include <math.h>

#include "ENTITY_BASE.H"
#include "FLAG.H"
#include "GRID.H"

struct Node
{
	int value;
	Node* nextNode;
};

class PriQueue
{
private:
	Node* head;
	Node* tail;
public:
	PriQueue();
	~PriQueue();
	bool empty();
	void push(int action);
	int pop();
	//Node* pop();
};

class Npc: public Entity_base
{
private:
	int health;
	int ammo;
	int range;							// View range
	int scope;							// View scope / width
	//int bulletDamage;
	//int bulletSpread;
	//active animation
	int currentAction;
	//bool flag[NUM_FLAGS];		/* Array implementation */		// CHANGE FLAG TO ANIMATION	
	unsigned int condiFlag;		// flags of the npc holding conditions
	unsigned int animaFlag;	// TO SEND
	Entity3f position;			// Positioning inherited!
	Entity3f facing;				// forward vector
	Entity3f waypoint;
	// Entity3f* link;			// waypoints...
	PriQueue* priHIGH;			// Priority Queues keeping tasks
	PriQueue* priLOW;
	//PriQueue* link;

protected:
	Npc();
	~Npc();
	/* Position manipulation */
	Entity3f getPositon();
	void setWaypoint(Entity3f wp);
	// void addWaypoint(Entity3f wp);
	// getWaypoint();
	/* Flag functions */
	//bool getFlag(int bit);
	//void setFlag(int bit);
	//void clearFlag(int bit);
	//int createFlagInt();		/* Array implementation */
	/* Priority */
	void addAction(int action);
	/* Action loop */
	void chooseAction();
	void doAction(int action);
	void update();
	int percieve();
	/* Tasks/schemes... */
	void taskIdle();
	void taskMove();
	void taskStop();
	//void move(waypoint);
};

#endif