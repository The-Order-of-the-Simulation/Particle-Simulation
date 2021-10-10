#pragma once

typedef struct {
	double x;
	double y;
	double z;
	double w;
} dvec4;

dvec4 double4(double x, double y, double z, double w)
{
	dvec4 vector;
	vector.x = x;
	vector.y = y;
	vector.z = z;
	vector.w = w;
	return vector;
}

dvec4 double4f(double x)
{
	dvec4 vector;
	vector.x = x;
	vector.y = x;
	vector.z = x;
	vector.w = x;
	return vector;
}