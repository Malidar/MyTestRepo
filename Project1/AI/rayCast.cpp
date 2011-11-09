
#include <stdio.h>
#include <math.h>
/* Bresenham algorithim */
void rayCast(int x0, int y0, int x1, int y1)
{
	int dx, dy, sx, sy, err = 0, e2;

	dx = abs( x1 - x0 );
	dy = abs( y1 - y0 );
	if( x0 < x1 )	sx = 1;
	else					sx = -1;
	if( y0 < y1 ) sy = 1;
	else					sy = -1;

	while( x0 < x1 && y0 < y1 )
	{
		printf(" %d , %d \n",x0,y0);
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