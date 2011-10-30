#ifndef _GRID_H
#define _GRID_H


/* Constants */
const int DIVX = 10;							// Dividant
const int DIVY = 10;
const int WORLD_WIDTH = 1200;			// World size
const int WORLD_HEIGHT = 900;
const int BOX_2D = 4;

/* STRUCTS */
struct Vertex3i
{
	int x,y,z;
};

struct Volume
{
	int w,l,h;
};

class BoundingBox
{
private:
	int boxHeight;
	int boxWidth;
	int boxLength;
	Vertex3i min;
	Vertex3i max;
public:	
	BoundingBox();
	BoundingBox( int x, int y, int z, int height, int width, int length );
	void update( int x, int y, int z );
	Vertex3i getMin();
	Vertex3i getMax();
	void corners2D( Vertex3i* corners );
	//Vertex3i* corners3D();
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
	void allocateEntity( Entity& entity );
	void update();
	bool checkGrid( Vertex3i position );
};
#endif