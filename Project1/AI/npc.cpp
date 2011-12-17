
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
	case SEARCH:			taskMove();	break;
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
	int linesH, linesW;
	int gridPositionH, gridPositionW;
	int gridPointH, gridPointW;
	int upperLeftCornerH, upperLeftCornerW;
	float dx, dz; // delta
	Entity3f pointRange, distance, 
		normal0, normal1, 
		trianglept0, trianglept1,
		dist0, dist1;
	// r = a + t*b Make it so that |facing| = 1
	//pointRange = position + distance; distance = range * facing

	/* View Distance ( t*b ) */
	distance.x = range * facing.x;
	distance.z = range * facing.z;
	/* Find the maximum range point ( r = a + t*b ) */
	pointRange.x = position.x + distance.x;	// FIXED the position is not centered
	pointRange.z = position.z + distance.z;
	/* Find the normals to the facing vector */
	dx = distance.x - pointRange.x;
	dz = distance.z - pointRange.z;
	normal0.x = dx;		normal0.z = -dz;
	normal1.x = -dx;	normal1.z = dz;
	/* Find the the points defining the scale of the view
		 In a Triangle ABC(A is pos) this would be B and C */
	trianglept0.x = ( normal0.x * scope / 2 ) + pointRange.x;
	trianglept0.z = ( normal0.z * scope / 2 ) + pointRange.z;
	
	trianglept1.x = ( normal1.x * scope / 2 ) + pointRange.x;
	trianglept1.z = ( normal1.z * scope / 2 ) + pointRange.z;

	/* Find the point furthest away from position */
	dist0.x = position.x - trianglept0.x;
	dist0.z = position.z - trianglept0.z;
	dist1.x = position.x - trianglept1.x;
	dist1.z = position.z - trianglept1.z;

	
	//if( SIGN( dist0.z ) > SIGN( dist1.z ) )	// z-axis:
	//{/* trianglept0 favored / furthest away */
	//	gridPointH = world.findHeight( trianglept0.z );
	//}
	//else
	//{/* trianglept1 favored / furthest away */
	//	gridPointH = world.findHeight( trianglept1.z );
	//}
	//if( SIGN( dist0.x ) > SIGN( dist1.x ) )	// x-axis:
	//{/* trianglept0 favored / furthest away */
	//	gridPointW = world.findWidth( trianglept0.x );
	//}
	//else
	//{	/* trianglept1 favored / furthest away */
	//	//gridPointW = world.findWidth( trianglept1.x );
	//}
	//
	///* Find the gridPosition of this.position */
	//gridPositionH = world.findHeight( position.z );
	//gridPositionW = world.findWidth( position.x );

	/* Count the number of grid lines it the triangle crosses */
	linesH = gridPointH - gridPositionH;
	linesW = gridPointW - gridPositionH;
	
	/* Find the upper left corner */
	if( gridPositionH < gridPointH )
		upperLeftCornerH = gridPositionH;
	else
		upperLeftCornerH = gridPointH;
	if( gridPositionW < gridPointW )
		upperLeftCornerW = gridPositionW;
	else
		upperLeftCornerW = gridPointW;

	/* Check the grid cells the triangle intersect with */
	for(int i = 0; i < linesH; i++)
	{
		for(int j = 0; i < linesW; i++)
		{
			//upperLeftCornerH+i;
			// Create func to check each corner of grid cell to see if it have a
			// point within the triangle(fov)
			// save entity positions sorted
		}
	}

	while( 1 /* rayStep() */ )
	{/* Ceck entity positions/ref to determin action */
		//world.checkGrid(position);
	}
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