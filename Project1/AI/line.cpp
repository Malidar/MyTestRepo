#include <stdio.h>
#include <stdlib.h>

struct Point 
{
	int x, y;
};
/* Plot a line in 2D space */
void f_plotLine(float x0, float y0, float x1, float y1);
void bresenhamLine2(Point source, Point dest);
void bresenhamLine(int x0, int y0, int x1, int y1);

//int main()
//{
//	int x0 = 0, y0 = 0,		// x,y
//			x1 = 5, y1 = 8;		// x,y
//	float xf0 = 0.0f, yf0 = 0.0f,		// x,y
//				xf1 = 5.9f, yf1 = 8.5f;		// x,y
//
//	f_plotLine(xf0,yf0,xf1,yf1);
//
//	bresenhamLine(x0,y0,x1,y1);
//	return 0;
//}

void f_plotLine(float x0, float y0, float x1, float y1)
{
	float y, m, b;					// y = mx + b
	float x = 0.1f;					// step
	bool plot = true;
	/* Slope */
	m = ( y1 - y0 ) / ( x1 - x0 );
	/* Intercept */
	b = y0 - ( m * x0);
	/* y = mx + b*/
	y = ( ( m * ( x0 + x ) ) + b - (int)( x0 + x ) );	// step

	while( plot )
	{
		printf(" %f , %f \n",x0,y0);
		if( x0 >= x1 && y0 >= y1 )  // termination flag
		{
			plot = false;		// exit loop
		} 
		else
		{
			x0 = x0 + x;
			y0 = y0 + y;	
		}
	}
}

void bresenhamLine2(Point source, Point dest)
{
	Point nextPoint = source;
	int dx, dy, sx, sy, err = 0, e2 = 0;
	bool plot = true;

	dx = abs(dest.x - source.x);					// Delta
	dy = abs(dest.y - source.y);
	if( source.x < dest.x )	sx = 1;			// Step
	else					sx = -1;
	if( source.y < dest.y ) sy = 1;
	else					sy = -1;

	while( plot )
	{
		printf(" %d , %d \n",nextPoint.x,nextPoint.y);
		if( nextPoint.x == dest.x && nextPoint.y == dest.y )  // termination flag
		{
			plot = false;	
		}
		else
		{
			e2 = 2 * err;						// Error
			if( e2 > -dy )
			{
				err = err - dy;
				nextPoint.x = nextPoint.x + sx;
			}
			if( e2 < dx )
			{
				err = err + dx;
				nextPoint.y = nextPoint.y +sy;
			}
		}	
	}
}

void bresenhamLine(int x0, int y0, int x1, int y1)
{
	int dx, dy, sx, sy, err = 0, e2;
	bool plot = true;

	dx = abs(x1-x0);
	dy = abs(y1-y0);
	if( x0 < x1 )	sx = 1;
	else					sx = -1;
	if( y0 < y1 ) sy = 1;
	else					sy = -1;

	while( plot )
	{
		printf(" %d , %d \n",x0,y0);
		if( x0 == x1 && y0 == y1 )  // termination flag
		{
			plot = false;		// exit loop
		}
		else
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
		}
	}
}

 //function line(x0, y0, x1, y1)
 //  dx := abs(x1-x0)
 //  dy := abs(y1-y0) 
 //  if x0 < x1 then sx := 1 else sx := -1
 //  if y0 < y1 then sy := 1 else sy := -1
 //  err := dx-dy
 //
 //  loop
 //    setPixel(x0,y0)
 //    if x0 = x1 and y0 = y1 exit loop
 //    e2 := 2*err
 //    if e2 > -dy then 
 //      err := err - dy
 //      x0 := x0 + sx
 //    end if
 //    if e2 <  dx then 
 //      err := err + dx
 //      y0 := y0 + sy 
 //    end if
 //  end loop
