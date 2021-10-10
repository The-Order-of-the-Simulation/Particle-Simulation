#pragma once

#include <math.h>

typedef struct {
		float x;
		float y;
		float z;
		float w;
} vec4;

vec4 float4(float x, float y, float z, float w)
{
	vec4 vector;
	vector.x = x;
	vector.y = y;
	vector.z = z;
	vector.w = w;
	return vector;
}

vec4 float4f(float x)
{
	vec4 vector;
	vector.x = x;
	vector.y = x;
	vector.z = x;
	vector.w = x;
	return vector;
}

vec4 add_vec4(vec4 vector, vec4 vector_)
{
	vector.x += vector_.x;
	vector.y += vector_.y;
	vector.z += vector_.z;
	vector.w += vector_.w;
	return vector;
}