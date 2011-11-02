
#include "COLLISION.H"

/* CLASS BoundingBox3D */
BoundingBox::BoundingBox()
{}
BoundingBox::BoundingBox( int x, int y, int z, int height, int width, int length )
{
	boxHeight = height;
	boxWidth = width;
	boxLength = length;
	update( x, y, z );
}
void BoundingBox::update( int x, int y, int z)
{
	/* Calculate min and max coordinates */
	min.x = x;
	min.y = y;
	min.z = z;
	max.x = x + boxWidth;
	max.y = y + boxHeight;	// y is up
	max.z = z + boxLength;
}
void BoundingBox::update( Vertex3i position )
{
	update( position.x, position.y, position.z );
}
Vertex3i BoundingBox::getMin()
{
	return min;
}
Vertex3i BoundingBox::getMax()
{
	return max;
}
void BoundingBox::corners2D( Vertex3i* corners )
{
	/* Clockwise ABCD (A is in the top left corner) */
	(*corners) = min;
	corners++;
	(*corners).x = max.x;						(*corners).z = min.z;		// y is up
	corners++;
	(*corners) = max;
	corners++;
	(*corners).x = min.x;						(*corners).z = max.z;

	//Vertex3i corners[BOX_2D];	
	///* Clockwise ABCD (A is in the top left corner) */
	//corners[0] = min;
	//corners[1].x = max.x;						corners[1].z = min.z;		// y is up
	//corners[2] = max;
	//corners[3].x = min.x;						corners[3].z = max.z;
	//return corners;
}
/* Check if a point is inside a box */
bool checkBox2D( BoundingBox box, Vertex3i point )
{
	Vertex3i min = box.getMin();
	Vertex3i max = box.getMax();
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
	Vertex3i min = box.getMin();
	Vertex3i max = box.getMax();
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
/* Get the Area??? of a triangle */
int sign( Vertex3i p0, Vertex3i p1, Vertex3i p2 )
{
	return (p0.x - p2.x) * (p1.y - p2.y) - (p1.x - p2.x) * (p0.y - p2.y);
}
/* Check if a point is inside a triangle */
bool checkTriangle( Vertex3i point, Vertex3i p0, Vertex3i p1, Vertex3i p2 )
{
	bool b1, b2, b3;
  b1 = sign(point, p0, p1) < 0;
  b2 = sign(point, p1, p2) < 0;
  b3 = sign(point, p2, p0) < 0;
  return ((b1 == b2) && (b2 == b3));
}