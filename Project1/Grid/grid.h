#ifndef _GRID_H
#define _GRID_H

#include "COLLISION.H"

struct Volume
{
	int w,l,h;
};

/* foo declaration class */
class Entity							//
{													//
public:										//
	int id;									//
	Vertex3i position;			//
	Vertex3i oldPosition;		//
	Volume volume;					//
	BoundingBox box;				//
};												//
/*                       */

struct Node
{
	Entity* entity;
	Node* nextNode;
	Node( Entity* regEntity, Node* regNextNode );
};

/* CLASSES */
class EntityList
{
private:
	Node* head;
	Node* tail;
public:
	EntityList();
	~EntityList();
	bool empty();
	bool exist( int id );
	void add( Entity* newEntity );
	Entity* get();
	Entity* get( Entity* entity );
	Entity* get( Vertex3i position );
	bool remove( int id );
	bool collision( Vertex3i position );
};

class Grid
{
private:
	int height;	// World size:
	int width;
	int divh;		// Divisor height / width: 
	int divw;
	EntityList** grid;	// EntityList grid[DIVH][DIVW]
public:
	Grid();
	Grid( int worldHeight, int worldWidth, int divisorH, int divisorW );
	~Grid();
	int findWidth( int xCoord );
	int findHeight( int yCoord );
	int findWidth( float xCoord );
	int findHeight( float yCoord );
	void allocateEntity( Entity& entity );
	void update();
	bool checkGrid( Vertex3i position );
};
#endif