#ifndef _NPC_H
#define _NPC_H

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
protected:
	PriQueue();
	~PriQueue();
	void push(int action);
	int pop();
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
	//current action?
	//unsigned int flag;		// flags of the npc holding conditions	
	int flag[NUM_FLAGS];
	PriQueue* priHIGH;			// Priority Queues keeping tasks
	PriQueue* priLOW;

protected:
	Npc();
	~Npc();
	/* Position manipulation */
	Entity3f getPositon();
	void setWaypoint(Entity3f wp);
	/* Flag functions */
	int getFlag(int bit);
	void setFlag(int bit);
	void clearFlag(int bit);
	/* Pri */
	
	/* Action loop */
	void action();
};

#endif