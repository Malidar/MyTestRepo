
#include "COLLISION.H"

/* STRUCT constructor */
Vertex3i::Vertex3i()
{
	x = 0; 
	y = 0; 
	z = 0;
}
/* CLASS BoundingBox3D */
BoundingBox::BoundingBox()
{
}
BoundingBox::BoundingBox( int x, int y, int z, int height, int width, int length )
{
	h = height;
	w = width;
	l= length;
	update( x, y, z );
}
void BoundingBox::update( int x, int y, int z)
{
	/* Calculate min and max coordinates */
	min.x = x;
	min.y = y;
	min.z = z;
	max.x = x + w;
	max.y = y + h;	// y is up
	max.z = z + l;
	/* Clockwise ABCD (A is in the top left corner) */
	corners2D[0] = min;
	corners2D[1].x = max.x;						corners2D[1].z = min.z;		// y is up
	corners2D[2] = max;
	corners2D[3].x = min.x;						corners2D[3].z = max.z;
}
void BoundingBox::update( Vertex3i position )
{
	update( position.x, position.y, position.z );
}
/* Check if a point is inside a box */
bool checkBox2D( BoundingBox box, Vertex3i point )
{
	Vertex3i min = box.min;
	Vertex3i max = box.max;
	if( point.x < max.x && point.x > min.x )
	{	/* In this case y is up! */
		if( point.z < max.z && point.z > min.z )
		{
			return true;
		}
	}
	return false;
}
/* Check if a point is inside a box */
bool checkBox3D( BoundingBox box, Vertex3i point )
{
	Vertex3i min = box.min;
	Vertex3i max = box.max;
	if( point.x < max.x && point.x > min.x )
	{
		if( point.y < max.y && point.y > min.y )
		{
			if( point.z < max.z && point.z > min.z )
			{
				return true;
			}
		}
	}
	return false;
}
/* Get the sign of the x product */
int sign( Vertex3i p0, Vertex3i p1, Vertex3i p2 )
{
	//return (p2.x - p0.x) * (p1.y - p0.y) - (p1.x - p0.x) * (p2.y - p0.y);
	return (p2.x - p0.x) * (p1.z - p0.z) - (p1.x - p0.x) * (p2.z - p0.z);
}
/* Check if a point is inside a triangle */
bool checkTriangle( Vertex3i point, Vertex3i p0, Vertex3i p1, Vertex3i p2 )
{
	bool b0, b1, b2;
  b0 = sign( p1, p0, point ) < 0;
  b1 = sign( p2, p1, point ) < 0;
  b2 = sign( p0, p2, point ) < 0;
  return ( ( b0 == b1 ) && ( b1 == b2 ) );
}