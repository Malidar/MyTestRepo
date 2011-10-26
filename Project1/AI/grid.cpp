

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

/* foo declaration class */
class Entity							//
{													//
public:										//
	char* name;							//
	Vertex3i position;			//
	Volume volume;					//		
};												//
/*                       */

struct Node
{
	Vertex3i entityPos;
	Entity* entity;
	Node* nextNode;
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
		//max.y = pos.y + vol.h;
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
		max.y = pos.y + vol.h;
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
	{}
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
		Node* newNode;
		//entityPos = newEntity->position;
		newNode->entity = newEntity;
		newNode->nextNode = head->nextNode;
		head->nextNode = newNode;
	}
	Entity* get(Vertex3i Position) //Entity get()
	{
		Node* tempNode;
		tempNode = head->nextNode;
		if( !empty() )
		{
			while( tempNode->entityPos.x != Position.x && 
						 tempNode->entityPos.y != Position.y )
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
	EntityList grid[DIVX][DIVY];

protected:
	Grid()	
	{}
	~Grid()	
	{}
	/* Allocate an Entity in the grid */
	void allocateEntity(Entity& entity)
	{
		int indexA, indexB;
		Vertex3i entPos;
		Volume entVol;
		Vertex3i bbox[4];	// the bounding box 4 vertexes A,B,C and D
// CREATE A BOUNDING BOX FUNCTION / struct / class
		entPos = entity.position;
		entVol = entity.volume;
		/* Clockwise ABCD (A is in the top left corner) */
		bbox[0] = entPos;
		bbox[1].x = entPos.x + entVol.w;	bbox[1].y = entPos.y;
		bbox[2].x = entPos.x + entVol.w;	bbox[2].y = entPos.y + entVol.l;
		bbox[3].x = entPos.x;							bbox[3].y = entPos.y + entVol.l;

		for( int i = 0; i < 4; i++ )
		{
		/* Check in which indexes the entity will be stored (in worldMatrix) */
		indexA = ( bbox[i].x / WORLD_WIDTH ) * DIVX;	// (x / width) * dividant 
		indexB = ( bbox[i].y / WORLD_HEIGHT ) * DIVY;
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