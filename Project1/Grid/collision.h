#ifndef _COLLISION_H
#define _COLLISION_H

/* Constants */
const int BOX_2D = 4;
const int BOX_3D = 8;

/* STRUCTS */
struct Vertex3i
{
	int x,y,z;
	Vertex3i();
};

struct BoundingBox
{
	/* Data */
	int height;
	int width;
	int length;
	Vertex3i min;
	Vertex3i max;
	Vertex3i corners2D[BOX_2D];
	//Vertex3i corners3D[BOX_3D];
	/* Functions */
	BoundingBox();
	BoundingBox( int x, int y, int z, int height, int width, int length );
	void update( int x, int y, int z );
	void update( Vertex3i position );
};

bool checkBox2D( BoundingBox box, Vertex3i point );
bool checkBox3D( BoundingBox box, Vertex3i point );
int sign( Vertex3i p0, Vertex3i p1, Vertex3i p2 );
bool checkTriangle( Vertex3i point, Vertex3i p0, Vertex3i p1, Vertex3i p2 );
bool checkLineIntersection( Vertex3i linePoint0, Vertex3i p0, Vertex3i p1 );

#endif