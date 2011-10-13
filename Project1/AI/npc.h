#ifndef _NPC_H
#define _NPC_H

#include <math.h>

#include "ENTITY_BASE.H"
#include "FLAG.H"

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
	Entity3f position;
	Entity3f waypoint;
	int health;
	int ammo;
	int range;
	//int bulletDamage;
	//int bulletSpread;
	//active animation
	int currentAction;			
	//unsigned int flag;		// flags of the npc holding conditions
	bool flag[NUM_FLAGS];		/* Array implementation */
	PriQueue* priHIGH;			// Priority Queues keeping tasks
	PriQueue* priLOW;

protected:
	Npc();
	~Npc();
	/* Position manipulation */
	Entity3f getPositon();
	void setWaypoint(Entity3f wp);
	/* Flag functions */
	bool getFlag(int bit);
	void setFlag(int bit);
	void clearFlag(int bit);
	int createFlagInt();		/* Array implementation */
	/* Pri */
	
	/* Action loop */
	void actionLoop();
	void doAction(int action);

	/* Tasks/schemes... */
};

#endif