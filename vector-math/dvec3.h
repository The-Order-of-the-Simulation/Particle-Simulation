#pragma once

#include <math.h>

class dvec3
{
	public:
		double x;
		double y;
		double z;
};

dvec3 double3(double x, double y, double z)
{
	dvec3 vector;
	vector.x = x;
	vector.y = y;
	vector.z = z;
	return vector;
}

dvec3 double3f(double x)
{
	dvec3 vector;
	vector.x = x;
	vector.y = x;
	vector.z = x;
	return vector;
}