#ifndef _COLLISION_H
#define _COLLISION_H

/* Constants */
const int BOX_2D = 4;

/* STRUCTS */
struct Vertex3i
{
	int x,y,z;
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
	void update( Vertex3i position );
	Vertex3i getMin();
	Vertex3i getMax();
	void corners2D( Vertex3i* corners );
	//Vertex3i* corners3D();
};

class Collision
{
};

bool checkBox2D( BoundingBox box, Vertex3i point );
bool checkBox3D( BoundingBox box, Vertex3i point );
int sign( Vertex3i p0, Vertex3i p1, Vertex3i p2 );
bool checkTriangle( Vertex3i point, Vertex3i p0, Vertex3i p1, Vertex3i p2 );

#endif