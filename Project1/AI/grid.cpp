

/* Constants */
const int DIVX = 10;							// Dividant
const int DIVY = 10;
const int WORLD_WIDTH = 1200;			// World size
const int WORLD_HEIGHT = 900;

/* Structs */
struct Vertex3i
{
	int x,y,z;
};

struct Volume
{
	int w,l,h;
};

// foo declaration
class BoundingBox3D;
/* foo declaration class */
class Entity							//
{													//
public:										//
	char* name;							//
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
	Node(Entity* regEntity, Node* regNextNode)
	{
		entity = regEntity;
		nextNode = regNextNode;
	}
	~Node()
	{
		delete entity;
		delete nextNode;
	}
};

/* CLASSES */

class BoundingBox2D
{
private:
	Vertex3i min;
	Vertex3i max;
protected:
	BoundingBox2D()
	{}
	BoundingBox2D(Entity* entity)
	{
		update(entity->position, entity->volume);
	}
	void update(Vertex3i pos, Volume vol)
	{
		/* Calculate min and max coordinates */
		min = pos;
		max.x = pos.x + vol.w;
		max.y = 0;	//max.y = pos.y + vol.h;
		max.z = pos.z + vol.l;
	}
};

class BoundingBox3D
{
private:
	Vertex3i min;
	Vertex3i max;
protected:
	BoundingBox3D()
	{}
	BoundingBox3D(Entity* entity)
	{
		update(entity->position, entity->volume);
	}
	void update(Vertex3i pos, Volume vol)
	{
		/* Calculate min and max coordinates */
		min = pos;
		max.x = pos.x + vol.w;
		max.y = pos.y + vol.h;	// y is up
		max.z = pos.z + vol.l;
	}
};

class EntityList
{
private:
	Node* head;
	Node* tail;
public:
	EntityList()
	{}
	~EntityList()
	{
		delete head;
		delete tail;
	}
	bool empty()
	{
		if( head->nextNode == tail )
			return true;
		else
			return false;
	}
	bool exist(Entity* entity)
	{
		Node* tempNode;
		tempNode = head->nextNode;
		if( !empty() )
		{
			while( entity->name != tempNode->entity->name ) // CHANGE
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
	}
	void add(Entity* newEntity)
	{
		Node* newNode = new Node(newEntity, head->nextNode);
		head->nextNode = newNode;
	}
	Entity* get(Vertex3i Position) //Entity get()
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
				//else return NULL;
			}	
			return tempNode->entity;
		}
	}
	void remove(Entity* entity)
	{
	}
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
	Grid()	
	{}
	Grid(int worldWidth, int worldHeight, int divisorW, int divisorH)
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
	~Grid()	
	{
		/* Delete grid */
		for(int i = 0; i < height; i++)
			delete grid[i]; 
		delete grid;
	}
	int findWidth(int xCoord)
	{
		return ( xCoord / width ) * divw;
	}
	int findHeight(int yCoord)
	{
		return ( yCoord / height ) * divh;
	}
	/* Allocate an Entity in the grid */
	void allocateEntity(Entity& entity)
	{
		int indexA, indexB;
		BoundingBox3D box;
		Volume entVol;
		Vertex3i corners[4];	// the bounding box 4 vertexes A,B,C and D
// CREATE A BOUNDING BOX FUNCTION / struct / class
		//entPos = entity.position;
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
			if( !grid[indexA][indexB].exist( &entity ) )
			{
				grid[indexA][indexB].add( &entity );
			}
		}
	}
	/* Updates the position of an Entity in the grid */
	void update()
	{
	}
};