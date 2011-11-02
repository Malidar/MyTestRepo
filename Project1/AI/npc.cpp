
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
	waypoint = wp;
}

/* Flag functions */
//bool Npc::getFlag(int bit)
//{
//	return flag[bit];		/* Array implementation */
//	/* BIT_CHECK(flag,bit); */
//}
//
//void Npc::setFlag(int bit)
//{
//	flag[bit] = true;		/* Array implementation */
//	/* BIT_SET(flag,bit); */
//}
//
//void Npc::clearFlag(int bit)
//{
//	flag[bit] = false;		/* Array implementation */
//	/* BIT_CLEAR(flag,bit); */
//}
//
///* Array implementation */
//int Npc::createFlagInt()
//{
//	int flagInt = 0;
//	int i;
//	for( i = 0; i < NUM_FLAGS; i++ )
//	{
//		if( flag[i] )		// If bit set
//		{
//			flagInt += pow( 2.0f, i );
//		}
//	}
//	return flagInt;
//}

/* Pri */
void Npc::addAction(int action)		// void setPriority( int action ) / addAction?
{
	// if leas significant bits put in priHIGH
	if( action <= HIGH_PRI )
		priHIGH->push( action );
	// else put in priLOW
	else if( action >= LOW_PRI )
		priLOW->push( action );

}

/* Action loop */
void Npc::chooseAction()
{
	if( !priHIGH->empty() )
	{
		// stop current, start high
		currentAction = priHIGH->pop();
	}
	else
	{
		// continue, when done do next low
		if( !currentAction )	// if done with the last action cA = 0
			currentAction = priLOW->pop();
	}
	/* Do action assigned by the priQueue */
	doAction( currentAction );
}

void Npc::doAction(int action)
{
	switch( action )
	{
	case IDLE:			taskIdle();	break;
	case MOVE:			taskMove();	break;
	default:					break;
	}
}

void Npc::update()
{
	int newAction;
	// Precieve MAKE FUNC
	// register flags for new action
	newAction = percieve();
	if( newAction )
	{
		addAction( newAction );
	}
	chooseAction();
}

int Npc::percieve()
{
	// use a triangle check to represent the view. if something is inside:
	// rayCast to the entity to  see if there are no obstacles
	// if object hit return proper action
	// SEE_ENEMY / SEE_FRIENDLY / OBSTACLE / 
	return 0;
}

/* Tasks/schemes... */
void Npc::taskIdle()
{
	//if( !BIT_CHECK(condiFlag, IDLE) )
	taskStop();
	// Idle animation BIT_SET(animaFlag, ANIMATION0);
	// BIT_SET(condiFlag, IDLE);
}

void Npc::taskMove()
{
	// set speed
	// BIT_CLEAR(condiFlag, STOP);
	// set vector
	// face direction
	// if pos = wp
	// get next wp form link
	// also: make time / speed / distance calc between 2 points 
}

void Npc::taskStop()
{
	//speed = 0;
}