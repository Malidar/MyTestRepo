

/* Constants */
const int DIVX = 10;		// Dividant
const int DIVY = 10;
const int WORLD_WIDTH = 1200;			// World size
const int WORLD_HEIGHT = 900;

/* Structs */
struct Vertex
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
	Vertex position;				//
	Volume volume;					//		
};												//
/*                       */

struct Node
{
	Vertex entityPos;
	Entity entity;
	Node* nextNode;
};

/* Classes */
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
		if(head->nextNode == tail)
			return true;
		else
			return false;
	}
	bool exist(Entity entity)
	{
		Node* tempNode;
		tempNode = head->nextNode;
		if(!empty())
		{
			while( entity.name != tempNode->entity.name )
			{
				if(tempNode->nextNode != tail)
				{
					tempNode = tempNode->nextNode;
				}
				else
					return false;
			}
			return true;
		}
	}
	void add(Entity newEntity)
	{
		Node* newNode;
		//entityPos = newEntity->position;
		newNode->entity = newEntity;
		newNode->nextNode = head->nextNode;
		head->nextNode = newNode;
	}
	Entity get(Vertex Position) //Entity get()
	{
		Node* tempNode;
		tempNode = head->nextNode;
		if(!empty())
		{
			while(tempNode->entityPos.x != Position.x && 
						tempNode->entityPos.y != Position.y)
			{
				if(tempNode->nextNode != tail)
				{
					tempNode = tempNode->nextNode;	
				}
				//else return nothing found
			}	
			return tempNode->entity;
		}
	}
};

/* Global Var */
//int* worldMatrix;
EntityList worldMatrix[DIVX][DIVY];

/* Functions */
void allocateEntity();

int main()
{
	return 0;
}

/* Allocate Entity in the worldMatrix */
void allocateEntity(Entity entity)
{
	int indexA, indexB;
	Vertex entPos;
	Volume entVol;
	Vertex abcd[4];	// the bounding box 4 vertexes A,B,C and D

	entPos = entity.position;
	entVol = entity.volume;
	/* Clockwise ABCD (A is in the top left corner) */
	abcd[0] = entPos;
	abcd[1].x = entPos.x + entVol.w;	abcd[1].y = entPos.y;
	abcd[2].x = entPos.x + entVol.w;	abcd[2].y = entPos.y + entVol.l;
	abcd[3].x = entPos.x;	abcd[3].y = entPos.y + entVol.l;

	for( int i = 0; i < 4; i++ )
	{
		/* Check in which indexes the entity will be stored (in worldMatrix) */
		indexA = ( abcd[i].x / WORLD_WIDTH ) * DIVX;	// (x / width) * dividant 
		indexB = ( abcd[i].y / WORLD_HEIGHT ) * DIVY;
		/* Add the entity to the matrix if it does not exist in that index */
		if( !worldMatrix[indexA][indexB].exist( entity ) )
		{
			worldMatrix[indexA][indexB].add( entity );
		}
	}
}