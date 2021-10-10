#pragma once

#include <math.h>

typedef struct {
	bool x;
	bool y;
	bool z;
	bool w;
} bvec4;

bvec4 bool4(bool x, bool y, bool z, bool w)
{
	bvec4 vector;
	vector.x = x;
	vector.y = y;
	vector.z = z;
	vector.w = w;
	return vector;
}

bvec4 bool4f(bool x)
{
	bvec4 vector;
	vector.x = x;
	vector.y = x;
	vector.z = x;
	vector.w = x;
	return vector;
}