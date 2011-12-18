
#include "COLLISION.H"

/* STRUCT constructor */
Vector3f::Vector3f()
{
	x = 0; 
	y = 0; 
	z = 0;
}
/* CLASS BoundingBox3D */
BoundingBox::BoundingBox()
{
}
BoundingBox::BoundingBox( float x, float y, float z, int height, int width, int length )
{
	this->height = height;
	this->width = width;
	this->length = length;
	update( x, y, z );
}
//void BoundingBox::update( int x, int y, int z)
//{
//	/* Expect upper left corner as xyz */
//	/* Calculate min and max coordinates */
//	min.x = x;
//	min.y = y;
//	min.z = z;
//	max.x = x + width;
//	max.y = y + height;	// y is up
//	max.z = z + length;
//	/* Clockwise ABCD (A is in the top left corner) */
//	corners2D[0] = min;
//	corners2D[1].x = max.x;						corners2D[1].z = min.z;		// y is up
//	corners2D[2] = max;
//	corners2D[3].x = min.x;						corners2D[3].z = max.z;
//}
void BoundingBox::update( float x, float y, float z)
{
	/* Expect middle of bbox as xyz */
	/* Calculate min and max coordinates */
	min.x = x - ( width / 2 );
	min.y = y - ( height / 2 );
	min.z = z - ( length / 2 );
	max.x = x + ( width / 2 );
	max.y = y + ( height / 2 );	// y is up
	max.z = z + ( length / 2 );
	/* Clockwise ABCD (A is in the top left corner) */
	corners2D[0] = min;
	corners2D[1].x = max.x;						corners2D[1].z = min.z;		// y is up
	corners2D[2] = max;
	corners2D[3].x = min.x;						corners2D[3].z = max.z;
}
void BoundingBox::update( Vector3f position )
{
	update( position.x, position.y, position.z );
}
/* Check if a point is inside a box */
bool checkBox2D( BoundingBox box, Vector3f point )
{
	Vector3f min = box.min;
	Vector3f max = box.max;
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
bool checkBox3D( BoundingBox box, Vector3f point )
{
	Vector3f min = box.min;
	Vector3f max = box.max;
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
/* Get the sign of the x product ( p0 pivot point ) */
bool sign( Vector3f p0, Vector3f p1, Vector3f p2 )
{
	//return (p2.x - p0.x) * (p1.y - p0.y) - (p1.x - p0.x) * (p2.y - p0.y);
	return ( (p2.x - p0.x) * (p1.z - p0.z) - (p1.x - p0.x) * (p2.z - p0.z) ) > 0;
}
/* Check if a point is inside a triangle */
bool checkTriangle( Vector3f point, Vector3f p0, Vector3f p1, Vector3f p2 )
{
	bool b0, b1, b2;
  b0 = sign( p1, p0, point );
  b1 = sign( p2, p1, point );
  b2 = sign( p0, p2, point );
  return ( ( b0 == b1 ) && ( b1 == b2 ) );
}
/* Check if a line goes between two points */
bool checkLineIntersection( Vector3f p0, Vector3f p1, Vector3f linePoint0, Vector3f linePoint1 )
{
	bool b0, b1;
	b0 = sign( linePoint0, linePoint1, p0 );
	b1 = sign( linePoint0, linePoint1, p1 );
	return ( b0 != b1 );
}
/* Returns the next point on the line, false if at the end */
bool rayStep(int &x0, int &y0, int x1, int y1)
{/* Bresenham algorithim */
	int dx, dy, sx, sy, err, e2;

	dx = ABS( x1 - x0 );
	dy = ABS( y1 - y0 );
	if( x0 < x1 )	sx = 1;
	else					sx = -1;
	if( y0 < y1 ) sy = 1;
	else					sy = -1;

	err = dx-dy;
	/* Not hit the end of the line */
	if( x0 <= x1 && y0 <= y1 )
	{
		e2 = 2 * err;
		if( e2 > -dy )
		{
			err = err - dy;
			x0 = x0 + sx;
		}
		if( e2 < dx )
		{
			err = err + dx;
			y0 = y0 +sy;
		}
		return true;
	}
	return false;
}