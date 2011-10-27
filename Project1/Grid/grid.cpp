
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
Grid::Grid(int worldWidth, int worldHeight, int divisorW, int divisorH)
{
	width = worldWidth;
	height = worldHeight;
	divw = divisorW;
	divh = divisorH;
	/* Create grid */
	grid = new EntityList*[width];
	for(int i = 0; i < height; i++)
		grid[i] = new EntityList[height];
}
Grid::~Grid()	
{
	/* Delete grid */
	for(int i = 0; i < height; i++)
		delete grid[i]; 
	delete grid;
}
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
	int indexA, indexB;
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
	indexA = findWidth(corners[i].x);
	indexB = findHeight(corners[i].y);
	/* Add the entity to the matrix if it does not exist in that index */
		if( !grid[indexA][indexB].exist( entity.id ) )
		{
			grid[indexA][indexB].add( &entity );
		}
	}
}
/* Updates the position of an Entity in the grid */
void Grid::update()
{
	// Update position 
	// Check if it is outside the grid box
	// if it is remove it and allocate it again
	// OR check each corner of the bounding box ....
}