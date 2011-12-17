#ifndef _COLLISION_H
#define _COLLISION_H

/* absolute value of a */
#define ABS(a) (((a)<0) ? -(a) : (a))

/* Constants */
const int BOX_2D = 4;
const int BOX_3D = 8;

/* STRUCTS */
struct Vector3f
{
	float x,y,z;
	Vector3f();
};

struct BoundingBox
{
	/* Data */
	int height;
	int width;
	int length;
	Vector3f min;
	Vector3f max;
	Vector3f corners2D[BOX_2D];
	/* Functions */
	BoundingBox();
	BoundingBox( float x, float y, float z, int height, int width, int length );
	void update( float x, float y, float z );
	void update( Vector3f position );
};

bool checkBox2D( BoundingBox box, Vector3f point );
bool checkBox3D( BoundingBox box, Vector3f point );
int sign( Vector3f p0, Vector3f p1, Vector3f p2 );
bool checkTriangle( Vector3f point, Vector3f p0, Vector3f p1, Vector3f p2 );
bool checkLineIntersection( Vector3f p0, Vector3f p1, Vector3f linePoint0, Vector3f linePoint1 );
bool rayStep(int &x0, int &y0, int x1, int y1);

#endif