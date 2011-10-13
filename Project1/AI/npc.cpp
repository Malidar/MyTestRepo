
#include "NPC.H"


/* PRIQUEUE CLASS */
PriQueue::PriQueue()
{
}

PriQueue::~PriQueue()
{
}

bool PriQueue::empty()
{
	if(head->nextNode == tail)
		return true;
	else
		return false;
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
	int val;
	Node* node;
	node = head->nextNode;
	head->nextNode = node->nextNode;
	val = node->value;
	delete node;
	return val;
}

//Node* PriQueue::pop()
//{
//	Node* node;
//	node = head->nextNode;
//	head->nextNode = node->nextNode;
//	node->nextNode = NULL;
//	return node;
//}

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
bool Npc::getFlag(int bit)
{
	return flag[bit];		/* Array implementation */
	/* BIT_CHECK(flag,bit); */
}

void Npc::setFlag(int bit)
{
	flag[bit] = true;		/* Array implementation */
	/* BIT_SET(flag,bit); */
}

void Npc::clearFlag(int bit)
{
	flag[bit] = false;		/* Array implementation */
	/* BIT_CLEAR(flag,bit); */
}

/* Array implementation */
int Npc::createFlagInt()
{
	int flagInt = 0;
	int i;
	for( i = 0; i < NUM_FLAGS; i++ )
	{
		if( flag[i] )		// If bit set
		{
			flagInt += pow( 2.0, i );
		}
	}
	return flagInt;
}

/* Pri */

/* Action loop */
void Npc::actionLoop()
{
	if( !priHIGH->empty() )
	{
		// stop current, start high
		currentAction = 0;
		doAction( priHIGH->pop() );
	}
	else
	{
		// continue, when done do next low
	}

}

void Npc::doAction(int action)
{
	switch( action )
	{
	case LOW_HEALTH:	break;
	default:					break;
	}
}