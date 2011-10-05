

/* Constants */
const int DIVX = 10;
const int DIVY = 10;

/* Structs */
struct Point
{
	int x,y;
};

struct Node
{
	Node* nextNode;
	//Entity* nextNode;
};

/* Class */
class List
{
private:
	Node* head;
	Node* tail;
public:
	List();
	~List();
	void add();
	void get();
};

/* Global Var */
//int* worldMatrix;
int worldMatrix[DIVX][DIVY];

/* Functions */
void createGrid();
void allocateObj();
void checkLine();
void checkGrid();

int main()
{
	return 0;
}

/**/
void createGrid()
{
}

/**/
void allocateObj()
{
}

/**/
void checkLine()
{
}

/**/
void checkGrid()
{
}