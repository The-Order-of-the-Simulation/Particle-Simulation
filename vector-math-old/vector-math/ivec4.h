#pragma once

#include <math.h>

typedef struct {
	int x;
	int y;
	int z;
	int w;
} ivec4;

ivec4 int4(int x, int y, int z, int w)
{
	ivec4 vector;
	vector.x = x;
	vector.y = y;
	vector.z = z;
	vector.w = w;
	return vector;
}

ivec4 int4f(int x)
{
	ivec4 vector;
	vector.x = x;
	vector.y = x;
	vector.z = x;
	vector.w = x;
	return vector;
}