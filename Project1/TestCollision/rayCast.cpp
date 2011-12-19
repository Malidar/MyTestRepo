
#include <stdio.h>

/* absolute value of a */
#define ABS(a) (((a)<0) ? -(a) : (a))

/* Returns the next point on the line */
void i_StepLine(int &x0, int &y0, int x1, int y1)
{/* Bresenham algorithim */
	int dx, dy, sx, sy, err, e2;

	dx = ABS( x1 - x0 );
	dy = ABS( y1 - y0 );
	if( x0 < x1 )	sx = 1;
	else					sx = -1;
	if( y0 < y1 ) sy = 1;
	else					sy = -1;

	err = dx-dy;

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
	}
}

void f_StepLine(float &x0, float &y0, float x1, float y1)
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

	if( x0 <= x1 && y0 <= y1 )
	{
		x0 = x0 + x;
		y0 = y0 + y;	
	}
}
//int main()
//{
//	int x0 = 0, y0 = 0,		// x,y
//			x1 = 5, y1 = 20;		// x,y
//
//	rayCast(x0,y0,x1,y1);
//
//	return 0;
//}