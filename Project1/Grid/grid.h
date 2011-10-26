#ifndef _GRID_H
#define _GRID_H


/* Constants */
const int DIVX = 10;							// Dividant
const int DIVY = 10;
const int WORLD_WIDTH = 1200;			// World size
const int WORLD_HEIGHT = 900;

/* STRUCTS */
struct Vertex3i
{
	int x,y,z;
};

struct Volume
{
	int w,l,h;
};

struct BoundingBox2D
{
	Vertex3i min;
	Vertex3i max;
	BoundingBox2D();
	BoundingBox2D(Vertex3i pos, Volume vol);
	void update(Vertex3i pos, Volume vol);
};

struct BoundingBox3D
{
	Vertex3i min;
	Vertex3i max;
	BoundingBox3D();
	BoundingBox3D(Vertex3i pos, Volume vol);
	void update(Vertex3i pos, Volume vol);
};

/* foo declaration class */
class Entity							//
{													//
public:										//
	int id;							//
	Vertex3i position;			//
	Volume volume;					//
	BoundingBox3D box;			//
};												//
/*                       */

struct Node
{
	Entity* entity;
	Node* nextNode;
	// Create func to construct
	Node(Entity* regEntity, Node* regNextNode);
	~Node();
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
	bool exist(int id);
	void add(Entity* newEntity);
	// add Entity* search() 
	Entity* get(Vertex3i Position);
	bool remove(int id);
};

class Grid
{
private:
	int width;	// World size:
	int height;
	int divw;		// Divisor width / Height
	int divh;
	EntityList** grid;
	//EntityList grid[DIVX][DIVY];
protected:
	Grid();
	Grid(int worldWidth, int worldHeight, int divisorW, int divisorH);
	~Grid();
	int findWidth(int xCoord);
	int findHeight(int yCoord);
	void allocateEntity(Entity& entity);
	void update();
};
#endif