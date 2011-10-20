#include <stdio.h>

/* find maximum of a and b */
#define MAX(a,b) (((a)>(b))?(a):(b))

/* absolute value of a */
#define ABS(a) (((a)<0) ? -(a) : (a))

/* take sign of a, either -1, 0, or 1 */
#define ZSGN(a) (((a)<0) ? -1 : (a)>0 ? 1 : 0)

struct point3d
{
    int x, y, z;
};

void line3d( int x1, int y1, int z1, int x2, int y2, int z2);
void line3D(int x1, int y1, int z1, int x2, int y2, int z2);
//point3d(x, y, z)
//    int x, y, z;

int main()
{
	line3d(1,0,1,5,0,8);
	line3D(1,0,1,5,0,8);
	return 0;
}


void line3d( int x1, int y1, int z1, int x2, int y2, int z2)
{
    int xd, yd, zd;
    int x, y, z;
    int ax, ay, az;
    int sx, sy, sz;
    int dx, dy, dz;

    dx = x2 - x1;
    dy = y2 - y1;
    dz = z2 - z1;

    ax = ABS(dx) << 1;
    ay = ABS(dy) << 1;
    az = ABS(dz) << 1;

    sx = ZSGN(dx);
    sy = ZSGN(dy);
    sz = ZSGN(dz);

    x = x1;
    y = y1;
    z = z1;

    if (ax >= MAX(ay, az))            /* x dominant */
    {
        yd = ay - (ax >> 1);
        zd = az - (ax >> 1);
        for (;;)
        {
           // point3d(x, y, z);
            if (x == x2)
            {
                return;
            }

            if (yd >= 0)
            {
                y += sy;
                yd -= ax;
            }

            if (zd >= 0)
            {
                z += sz;
                zd -= ax;
            }

            x += sx;
            yd += ay;
            zd += az;
																					printf("%d %d %d\n", x, y, z);
        }
    }
    else if (ay >= MAX(ax, az))            /* y dominant */
    {
        xd = ax - (ay >> 1);
        zd = az - (ay >> 1);
        for (;;)
        {
          //  point3d(x, y, z);
            if (y == y2)
            {
                return;
            }

            if (xd >= 0)
            {
                x += sx;
                xd -= ay;
            }

            if (zd >= 0)
            {
                z += sz;
                zd -= ay;
            }

            y += sy;
            xd += ax;
            zd += az;
																				printf("%d %d %d\n", x, y, z);
        }
    }
    else if (az >= MAX(ax, ay))            /* z dominant */
    {
        xd = ax - (az >> 1);
        yd = ay - (az >> 1);
        for (;;)
        {
           // point3d(x, y, z);
            if (z == z2)
            {
                return;
            }

            if (xd >= 0)
            {
                x += sx;
                xd -= az;
            }

            if (yd >= 0)
            {
                y += sy;
                yd -= az;
            }

            z += sz;
            xd += ax;
            yd += ay;
																												printf("%d %d %d\n", x, y, z);
        }
    }
}
			/* Personal modification */
void line3D(int x1, int y1, int z1, int x2, int y2, int z2)
{
	int xd, yd, zd;
	int x, y, z;
	int ax, ay, az;
	int sx, sy, sz;
	int dx, dy, dz;

	dx = x2 - x1;
	dy = y2 - y1;
	dz = z2 - z1;

	ax = ABS(dx) << 1;
	ay = ABS(dy) << 1;
	az = ABS(dz) << 1;

	sx = ZSGN(dx);
	sy = ZSGN(dy);
	sz = ZSGN(dz);

	x = x1;
	y = y1;
	z = z1;

	if (ax >= MAX(ay, az))            /* x dominant */
	{
		yd = ay - (ax >> 1);
		zd = az - (ax >> 1);

		while(x != x2)
		{
																		printf("%d %d %d\n", x, y, z);
			if (yd >= 0)
			{
				y += sy;
				yd -= ax;
			}

			if (zd >= 0)
			{
				z += sz;
				zd -= ax;
			}

			x += sx;
			yd += ay;
			zd += az;										
		}
	}

	else if (ay >= MAX(ax, az))            /* y dominant */
	{
		xd = ax - (ay >> 1);
		zd = az - (ay >> 1);
		
		while(y != y2)
		{
															printf("%d %d %d\n", x, y, z);
			if (xd >= 0)
			{
				x += sx;
				xd -= ay;
			}

			if (zd >= 0)
			{
				z += sz;
				zd -= ay;
			}

			y += sy;
			xd += ax;
			zd += az;
		}
	}
	else if (az >= MAX(ax, ay))            /* z dominant */
	{
		xd = ax - (az >> 1);
		yd = ay - (az >> 1);

		while(z != z2)
		{
															printf("%d %d %d\n", x, y, z);
			if (xd >= 0)
			{
				x += sx;
				xd -= az;
			}

			if (yd >= 0)
			{
				y += sy;
				yd -= az;
			}

			z += sz;
			xd += ax;
			yd += ay;
		}
	}
}