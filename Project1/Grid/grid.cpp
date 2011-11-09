
#include <stdio.h>
#include "GRID.H"

/* STRUCT Node */
Node::Node( Entity* regEntity, Node* regNextNode )
{
	entity = regEntity;
	nextNode = regNextNode;
}

/* CLASS EntityList */
EntityList::EntityList()
{
	tail = new Node( NULL, tail );
	head = new Node( NULL, tail );
}
EntityList::~EntityList()
{
	delete head;
	delete tail;
}
bool EntityList::empty()
{
	if( head->nextNode == tail )
		return true;
	else
		return false;
}
bool EntityList::exist( int id )
{
	Node* tempNode;
	tempNode = head->nextNode;

	while( tempNode != tail )
	{
		if( id == tempNode->entity->id )
		{
			return true;
		}
		tempNode = tempNode->nextNode;
	}
	return false;
}
void EntityList::add( Entity* newEntity )
{
	Node* newNode = new Node( newEntity, head->nextNode );
	head->nextNode = newNode;
}
/* Get first entry in list */
Entity* EntityList::get()
{
	if( head->nextNode != tail )
	{
		return head->nextNode->entity;
	}
	return NULL;
}
/* Get the entry after the given one */
Entity* EntityList::get( Entity* entity )
{
	Node* tempNode;
	tempNode = head->nextNode;
	while( tempNode != tail )
	{
		if( tempNode->entity->id == entity->id )
		{
			if( tempNode->nextNode != tail )
			{
				return tempNode->nextNode->entity;
			}
		}
		tempNode = tempNode->nextNode;
	}
	return NULL;
}
Entity* EntityList::get( Vertex3i position )
{
	Node* tempNode;
	tempNode = head->nextNode;
	// y is up
		while( tempNode != tail )
		{
			if( tempNode->entity->position.x == position.x && 
					tempNode->entity->position.z == position.z )
			{
				return tempNode->entity;
			}
			tempNode = tempNode->nextNode;
		}
	return NULL;
}
bool EntityList::remove(int id)
{
	Node* tempNode;
	Node* tempNodeNext;
	tempNode = head->nextNode;
	tempNodeNext = tempNode->nextNode;
	
	while( tempNode != tail )
	{/* pointing at the node before the target*/
		if( id == tempNodeNext->entity->id )
		{
			/* Point tempNode at targets->nextNode, and remove target */
			tempNode->nextNode = tempNodeNext->nextNode;
			delete tempNodeNext;
			return true;
		}
		tempNode = tempNode->nextNode;
		tempNodeNext = tempNode->nextNode;
	}	
	return false;
}
/* See if any of the entities in the list collides with the position */
bool EntityList::collision( Vertex3i position )
{
	Node* tempNode;
	tempNode = head->nextNode;

	while( tempNode != tail )
	{
		if( checkBox2D( tempNode->entity->box, position )	)
		{
			return true;
		}
		tempNode = tempNode->nextNode;
	}
	return false;
}

/* CLASS Grid */
Grid::Grid()	
{}
Grid::Grid( int worldHeight, int worldWidth, int divisorH, int divisorW )
{
	height = worldHeight;
	width = worldWidth;
	divh = divisorH;
	divw = divisorW;
	/* Create grid */
	grid = new EntityList*[divh];
	for( int i = 0; i < divh; i++ )
		grid[i] = new EntityList[divw];
}
Grid::~Grid()	
{
	/* Delete grid */
	for( int i = 0; i < divh; i++ )
		delete grid[i]; 
	delete [] grid;
}
/* Find the index of the grid a certain Coordinate is in */
int Grid::findWidth( int xCoord )
{
	return ( ( xCoord * divw ) / width );
}
int Grid::findHeight( int yCoord )
{
	return ( ( yCoord * divh ) / height );
}
///* Allocate an Entity in the grid */
//void Grid::allocateEntity( Entity& entity )
//{
//	int indexH, indexW;
//	Volume entVol;
//	Vertex3i entPos;
//	Vertex3i corners[4];	// the bounding box 4 vertexes A,B,C and D
//	entPos = entity.position;
//	entVol = entity.volume;
//	/* Clockwise ABCD (A is in the top left corner) */
//	corners[0] = entPos;
//	corners[1].x = entPos.x + entVol.w;	corners[1].z = entPos.z;		// y is up
//	corners[2].x = entPos.x + entVol.w;	corners[2].z = entPos.z + entVol.l;
//	corners[3].x = entPos.x;						corners[3].z = entPos.z + entVol.l;
//	/* Check all four corners */
//	for( int i = 0; i < 4; i++ )
//	{
//	/* Check in which indexes the entity will be stored (in worldMatrix) */
//	indexH = findHeight( corners[i].z );
//	indexW = findWidth( corners[i].x );
//	
//	/* Add the entity to the matrix if it does not exist in that index */
//		if( !grid[indexH][indexW].exist( entity.id ) )
//		{
//			grid[indexH][indexW].add( &entity );
//		}
//	}
//}
/* Allocate an Entity in the grid */
void Grid::allocateEntity( Entity& entity )
{
	int indexH, indexW, 
			boxWidth, boxHeight,
			hits, line;
	Vertex3i p0, p1, ln;
	Vertex3i* box2D;
	/* Get the 4 corners from the bounding box */
	box2D = entity.box.corners2D;

	/* Check all four corners */
	for( int i = 0; i < BOX_2D; i++ )
	{
	/* Check in which indexes the entity will be stored (in worldMatrix) */
	indexH = findHeight( box2D[i].z );
	indexW = findWidth( box2D[i].x );
	
	/* Add the entity to the matrix if it does not exist in that index */
		if( !grid[indexH][indexW].exist( entity.id ) )
		{
			grid[indexH][indexW].add( &entity );
		}
	}
	boxWidth = ( width / divw );
	boxHeight = ( height / divh );
	p0 = entity.box.min;
	p1 = entity.box.max;

	/* If an entety can cross an entire gridbox WIDTH */
	if( entity.box.w > boxWidth )
	{/* Count the number of grid lines it crosses/hits */
		hits = 0; line = 0;
		ln.x = 0; ln.y = 0; ln.z = 0;
		while( !checkLineIntersection( ln, p0, p1 ) )
		{/* Loop until it hits the entity */
			line++;
			ln.x = ( boxWidth * line );
		}
		while( checkLineIntersection( ln, p0, p1 ) )
		{/* Loop until it no longer hits the entity */
			hits++;
			line++;
			ln.x = ( boxWidth * line );
		}/* If the entity crosses more than 1 gridbox/lines */
		for( int i = 1; i < hits; i++ )
		{
			grid[indexH][indexW+i].add( &entity );
		}
	}
	/* If an entety can cross an entire gridbox HEIGHT */
	if( entity.box.h > boxHeight )
	{/* Count the number of grid lines it crosses/hits */
		hits = 0; line = 0;
		ln.z = 0; ln.y = 0; ln.z = 0;
		while( !checkLineIntersection( ln, p0, p1 ) )
		{/* Loop until it hits the entity */
			line++;
			ln.z = ( boxHeight * line );
		}
		while( checkLineIntersection( ln, p0, p1 ) )
		{/* Loop until it no longer hits the entity */
			hits++;
			line++;
			ln.z = ( boxHeight * line );
		}/* If the entity crosses more than 1 gridbox/lines */
		for( int i = 1; i < hits; i++ )
		{
			grid[indexH+i][indexW].add( &entity );
		}
	}
}
/* Updates the position of an Entity in the grid */
void Grid::update( /*Entity& entity*/ )
{
	/* Update position of an entity */
	// If an entity has a 'current gridindex' you can check vs new position
	// Do findW/H of the new position and see if it equals the current..
	// if it does, do nothing. else update:
	// By updating the grid within each entity, you dont need to check the entire grid when calling update...

	/* 
	Put in entity move funcion: 
	int x = world.grid.findWidth( newPositon.x );
	int y = world.grid.findHeight( newPositon.y );
	if( x != currentGridIndex.x && y != currentGridIndex.y )
	{
		world.grid.update( entity );
	}
	*/
		
	// Check if it is outside the grid box			//If above this is not needed, because it is checked beforehand.
	// if it is remove it and allocate it again
	// OR check each corner of the bounding box ....

	/* CHANGE: make it to check if an entity has crossed a border and update relative to the direction? */
	int indexH, indexW,
			boxWidth, boxHeight,
			hits, line;
	Vertex3i p0, p1, ln;
	Entity* inList;
	BoundingBox oldBox;
	Vertex3i* box2D;
	/* Run trough the entire grid */
	for( int i = 0; i < divh; i++ )
	{
		for( int j = 0; j < divw; j++ )
		{
			inList = grid[i][j].get();						// Get first entity
			/* if there is an entity in the list */
			while( inList )
			{
				/* Update if it has moved */
				if( inList->position.x != inList->oldPosition.x ||
						inList->position.z != inList->oldPosition.z )
				{
					/* Calculate the old bounding box */
					oldBox = inList->box;
					oldBox.update( inList->oldPosition );
					box2D = oldBox.corners2D;
					/* Remove the old placeholders */
					for( int i = 0; i < BOX_2D; i++ )
					{
						/* Check in which indexes the entity is stored */
						indexH = findHeight( box2D[i].z );
						indexW = findWidth( box2D[i].x );
						/* Remove it */
						grid[indexH][indexW].remove( inList->id );
					}
					boxWidth = ( width / divw );
					boxHeight = ( height / divh );
					p0 = inList->box.min;
					p1 = inList->box.max;

					/* If an entety can cross an entire gridbox WIDTH */
					if( inList->box.w > boxWidth )
					{/* Count the number of grid lines it crosses/hits */
						hits = 0; line = 0;
						ln.x = 0; ln.y = 0; ln.z = 0;
						while( !checkLineIntersection( ln, p0, p1 ) )
						{/* Loop until it hits the entity */
							line++;
							ln.x = ( boxWidth * line );
						}
						while( checkLineIntersection( ln, p0, p1 ) )
						{/* Loop until it no longer hits the entity */
							hits++;
							line++;
							ln.x = ( boxWidth * line );
						}/* If the entity crosses more than 1 gridbox/lines */
						for( int i = 1; i < hits; i++ )
						{
							grid[indexH][indexW+i].remove( inList->id );
						}
					}
					/* If an entety can cross an entire gridbox HEIGHT */
					if( inList->box.h > boxHeight )
					{/* Count the number of grid lines it crosses/hits */
						hits = 0; line = 0;
						ln.z = 0; ln.y = 0; ln.z = 0;
						while( !checkLineIntersection( ln, p0, p1 ) )
						{/* Loop until it hits the entity */
							line++;
							ln.z = ( boxHeight * line );
						}
						while( checkLineIntersection( ln, p0, p1 ) )
						{/* Loop until it no longer hits the entity */
							hits++;
							line++;
							ln.z = ( boxHeight * line );
						}/* If the entity crosses more than 1 gridbox/lines */
						for( int i = 1; i < hits; i++ )
						{
							grid[indexH+i][indexW].remove( inList->id );
						}
					}
					/* Allocate the new positon */
					allocateEntity( *inList );
				}
				inList = grid[i][j].get( inList );	// Get next entity
			}
		}
	}
}
/* Checks if an Entity is in a given position */
bool Grid::checkGrid( Vertex3i position )
{
	int indexH = findHeight( position.z );	// y coordinate is up
	int indexW = findWidth( position.x );
	/* Search the grid in given indexes for Entities width
		 position inside theyre bounding box									*/
	if( grid[indexH][indexW].collision( position ) )
		return true;
	else 
		return false;
}