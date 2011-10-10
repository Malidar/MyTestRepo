
#include "NPC.H"
#include "ENTITY_BASE.H"


/* PRIQUEUE CLASS */
PriQueue::PriQueue()
{
}

PriQueue::~PriQueue()
{
}

void PriQueue::push(int action)
{
	Node* newNode = new Node();
	newNode->value = action;
	newNode->nextNode = head->nextNode;
	head->nextNode = newNode;
}

int PriQueue::pop()
{
	return head->nextNode->value;
}

/* NPC CALSS */
Npc::Npc()
{
}

Npc::~Npc()
{
}

/* Position manipulation */
Entity3f Npc::getPositon()
{
	return position; 
}

void Npc::setWaypoint(Entity3f wp)
{
	position = wp;
}

/* Flag functions */
int Npc::getFlag(int bit)
{
	return 0;
}

void Npc::setFlag(int bit)
{
}

void clearFlag(int bit)
{
}

/* Pri */

/* Action loop */
void Npc::action()
{
}