#pragma once

#include <math.h>

typedef struct {
	unsigned int x;
	unsigned int y;
	unsigned int z;
	unsigned int w;
} uvec4;

uvec4 uint4(unsigned int x, unsigned int y, unsigned int z, unsigned int w)
{
	uvec4 vector;
	vector.x = x;
	vector.y = y;
	vector.z = z;
	vector.w = w;
	return vector;
}

uvec4 uint4f(unsigned int x)
{
	uvec4 vector;
	vector.x = x;
	vector.y = x;
	vector.z = x;
	vector.w = x;
	return vector;
}