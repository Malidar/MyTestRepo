
#include <stdio.h>
#include "grid.h"

/* struct Node */
Node::Node(Entity* regEntity, Node* regNextNode)
{
	entity = regEntity;
	nextNode = regNextNode;
}

/* struct BoundingBox2D */
BoundingBox2D::BoundingBox2D()
{}
BoundingBox2D::BoundingBox2D(Vertex3i pos, Volume vol)
{
	update(pos, vol);
}
void BoundingBox2D::update(Vertex3i pos, Volume vol)
{
	/* Calculate min and max coordinates */
	min = pos;
	max.x = pos.x + vol.w;
	max.y = 0;	//max.y = pos.y + vol.h;
	max.z = pos.z + vol.l;
}

/* struct BoundingBox3D */
BoundingBox3D::BoundingBox3D()
{}
BoundingBox3D::BoundingBox3D(Vertex3i pos, Volume vol)
{
	update(pos, vol);
}
void BoundingBox3D::update(Vertex3i pos, Volume vol)
{
	/* Calculate min and max coordinates */
	min = pos;
	max.x = pos.x + vol.w;
	max.y = pos.y + vol.h;	// y is up
	max.z = pos.z + vol.l;
}
/* class EntityList */
EntityList::EntityList()
{
	tail = new Node(NULL, tail);
	head = new Node(NULL, tail);
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
bool EntityList::exist(int id)
{
	Node* tempNode;
	tempNode = head->nextNode;
	if( !empty() )
	{
		while( id != tempNode->entity->id ) // CHANGE
		{
			if( tempNode->nextNode != tail )
			{
				tempNode = tempNode->nextNode;
			}
			else
				return false;
		}
		return true;
	}
	return false;
}
void EntityList::add(Entity* newEntity)
{
	Node* newNode = new Node(newEntity, head->nextNode);
	head->nextNode = newNode;
}
Entity* EntityList::get(Vertex3i Position) //Entity get()
{
	Node* tempNode;
	tempNode = head->nextNode;
	if( !empty() )
	{
		while( tempNode->entity->position.x != Position.x && 
						tempNode->entity->position.y != Position.y )
		{
			if( tempNode->nextNode != tail )
			{
				tempNode = tempNode->nextNode;	
			}
			else 
				return NULL;
		}	
		return tempNode->entity;
	}
	return NULL;
}
bool EntityList::remove(int id)
{
	Node* tempNode;
	Node* tempNodeNext;
	tempNode = head->nextNode;
	tempNodeNext = tempNode->nextNode;
	if( !empty() )
	{	
		/* pointing at the node before the target*/
		while( id != tempNodeNext->entity->id )
		{
			if( tempNode->nextNode != tail )
			{
				tempNode = tempNode->nextNode;
				tempNodeNext = tempNode->nextNode;
			}
			else
				return false;
		}	
		/* Point tempNode at targets->nextNode, and remove target */
		tempNode->nextNode = tempNodeNext->nextNode;
		delete tempNodeNext;
	}
	return false;
}

/* class Grid */
Grid::Grid()	
{}
Grid::Grid(int worldHeight, int worldWidth, int divisorH, int divisorW)
{
	height = worldHeight;
	width = worldWidth;
	divh = divisorH;
	divw = divisorW;
	/* Create grid */
	grid = new EntityList*[divh];
	for(int i = 0; i < divh; i++)
		grid[i] = new EntityList[divw];
}
Grid::~Grid()	
{
	/* Delete grid */
	for(int i = 0; i < divh; i++)
		delete grid[i]; 
	delete [] grid;
}
/* Find the index of the grid a certain Coordinate is in */
int Grid::findWidth(int xCoord)
{
	return ( xCoord / width ) * divw;
}
int Grid::findHeight(int yCoord)
{
	return ( yCoord / height ) * divh;
}
/* Allocate an Entity in the grid */
void Grid::allocateEntity(Entity& entity)
{
	int indexH, indexW;
	Volume entVol;
	Vertex3i entPos;
	Vertex3i corners[4];	// the bounding box 4 vertexes A,B,C and D
	entPos = entity.position;
	entVol = entity.volume;
	/* Clockwise ABCD (A is in the top left corner) */
	corners[0] = entPos;
	corners[1].x = entPos.x + entVol.w;	corners[1].y = entPos.y;
	corners[2].x = entPos.x + entVol.w;	corners[2].y = entPos.y + entVol.l;
	corners[3].x = entPos.x;						corners[3].y = entPos.y + entVol.l;
	/* Check all four corners */
	for( int i = 0; i < 4; i++ )
	{
	/* Check in which indexes the entity will be stored (in worldMatrix) */
	indexH = findHeight(corners[i].y);
	indexW = findWidth(corners[i].x);
	
	/* Add the entity to the matrix if it does not exist in that index */
		if( !grid[indexH][indexW].exist( entity.id ) )
		{
			grid[indexH][indexW].add( &entity );
		}
	}
}
/* Updates the position of an Entity in the grid */
void Grid::update(/*Entity& entity*/)
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
bool Grid::checkGrid(Vertex3i position)
{
	int indexH;
	int indexW;
	
	return true;
}