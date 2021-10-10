#pragma once

#include <math.h>

// 3-Component Floating-Point Vector
typedef struct {
	float x;
	float y;
	float z;
} vec3;

vec3 float3(float x, float y, float z)
{
	vec3 vector;
	vector.x = x;
	vector.y = y;
	vector.z = z;
	return vector;
}

vec3 float3f(float x)
{
	vec3 vector;
	vector.x = x;
	vector.y = x;
	vector.z = x;
	return vector;
}

vec3 add_vec3(vec3 vector, vec3 vector_)
{
	vector.x += vector_.x;
	vector.y += vector_.y;
	vector.z += vector_.z;
	return vector;
}

vec3 add_vec3f(vec3 vector, float x)
{
	vector.x += x;
	vector.y += x;
	vector.z += x;
	return vector;
}

vec3 subtract_vec3(vec3 vector, vec3 vector_)
{
	vector.x -= vector_.x;
	vector.y -= vector_.y;
	vector.z -= vector_.z;
	return vector;
}

vec3 subtract_vec3f(vec3 vector, float x)
{
	vector.x -= x;
	vector.y -= x;
	vector.z -= x;
	return vector;
}

vec3 multiply_vec3(vec3 vector, vec3 vector_)
{
	vector.x *= vector_.x;
	vector.y *= vector_.y;
	vector.z *= vector_.z;
	return vector;
}

vec3 multiply_vec3f(vec3 vector, float x)
{
	vector.x *= x;
	vector.y *= x;
	vector.z *= x;
	return vector;
}

vec3 divide_vec3(vec3 vector, vec3 vector_)
{
	vector.x /= vector_.x;
	vector.y /= vector_.y;
	vector.z /= vector_.z;
	return vector;
}

vec3 divide_vec3f(vec3 vector, float x)
{
	vector.x /= x;
	vector.y /= x;
	vector.z /= x;
	return vector;
}

float dot3(vec3 vector, vec3 vector_)
{
	vector.x *= vector_.x;
	vector.y *= vector_.y;
	vector.z *= vector_.z;
	return vector.x+vector.y+vector.z;
}

float dotp3(vec3 vector)
{
	vector.x *= vector.x;
	vector.y *= vector.y;
	vector.z *= vector.z;
	return vector.x+vector.y+vector.z;
}

float length3(vec3 vector)
{
	vector.x *= vector.x;
	vector.y *= vector.y;
	vector.z *= vector.z;
	return sqrtf(vector.x+vector.y+vector.z);
}

vec3 normalize3(vec3 vector)
{
	vec3 vector_ = vector;
	vector_.x *= vector_.x;
	vector_.y *= vector_.y;
	vector_.z *= vector_.z;
	float magnitude = sqrtf(vector_.x+vector_.y+vector_.z);
	vector.x /= magnitude;
	vector.y /= magnitude;
	vector.z /= magnitude;
	return vector;
}