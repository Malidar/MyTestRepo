
#include <stdio.h>
#include "grid.h"

/* STRUCT Node */
Node::Node( Entity* regEntity, Node* regNextNode )
{
	entity = regEntity;
	nextNode = regNextNode;
}

/* STRUCT BoundingBox2D */
BoundingBox2D::BoundingBox2D()
{}
BoundingBox2D::BoundingBox2D( Vertex3i pos, Volume vol )
{
	update( pos, vol );
}
void BoundingBox2D::update( Vertex3i pos, Volume vol )
{
	/* Calculate min and max coordinates */
	min = pos;
	max.x = pos.x + vol.w;
	max.y = 0;	//max.y = pos.y + vol.h;
	max.z = pos.z + vol.l;
}

/* STRUCT BoundingBox3D */
BoundingBox3D::BoundingBox3D()
{}
BoundingBox3D::BoundingBox3D( Vertex3i pos, Volume vol )
{
	update( pos, vol );
}
void BoundingBox3D::update( Vertex3i pos, Volume vol )
{
	/* Calculate min and max coordinates */
	min = pos;
	max.x = pos.x + vol.w;
	max.y = pos.y + vol.h;	// y is up
	max.z = pos.z + vol.l;
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
Entity* EntityList::get( Vertex3i position ) //Entity get()
{
	Node* tempNode;
	tempNode = head->nextNode;
	// y is up
		while( tempNode->nextNode != tail )
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
		if(true/* checkBox2D( tempNode->entity->box, position8 */)	// include checkBox
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
	return ( ( xCoord / width ) * divw );
}
int Grid::findHeight( int yCoord )
{
	return ( ( yCoord / height ) * divh );
}
/* Allocate an Entity in the grid */
void Grid::allocateEntity( Entity& entity )
{
	int indexH, indexW;
	Volume entVol;
	Vertex3i entPos;
	Vertex3i corners[4];	// the bounding box 4 vertexes A,B,C and D
	entPos = entity.position;
	entVol = entity.volume;
	/* Clockwise ABCD (A is in the top left corner) */
	corners[0] = entPos;
	corners[1].x = entPos.x + entVol.w;	corners[1].z = entPos.z;		// y is up
	corners[2].x = entPos.x + entVol.w;	corners[2].z = entPos.z + entVol.l;
	corners[3].x = entPos.x;						corners[3].z = entPos.z + entVol.l;
	/* Check all four corners */
	for( int i = 0; i < 4; i++ )
	{
	/* Check in which indexes the entity will be stored (in worldMatrix) */
	indexH = findHeight( corners[i].z );
	indexW = findWidth( corners[i].x );
	
	/* Add the entity to the matrix if it does not exist in that index */
		if( !grid[indexH][indexW].exist( entity.id ) )
		{
			grid[indexH][indexW].add( &entity );
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