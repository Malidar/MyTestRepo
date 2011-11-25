struct Vector3i
{
	int x,y,z;
};

struct BoundingBox
{
	Vector3i max, min;
};
/* Check if a point is inside a box */
bool checkBox3D(BoundingBox box, Vector3i point)
{
	if( point.x < box.max.x && point.x > box.min.x )
	{
		if( point.y < box.max.y && point.y > box.min.y )
		{
			if( point.z < box.max.z && point.z > box.min.z )
			{
				return true;
			}
		}
	}
	return false;
}
/* Check if a point is inside a box */
bool checkBox2D(BoundingBox box, Vector3i point)
{
	if( point.x < box.max.x && point.x > box.min.x )
	{	/* In this case y is up! */
		if( point.z < box.max.z && point.z > box.min.z )
		{
			return true;
		}
	}
	return false;
}