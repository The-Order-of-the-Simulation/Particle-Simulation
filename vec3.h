// ####### 3-Component Floating-Point Vector #######

/*
This header contains functions for 3-Component Floating-Point Vectors in C/C++.
Yup that's right, this is C-compatible!

You may notice some of these functions could be merged and the code could be made smaller,
but this is deliberate so that the compiler (e.g. GCC with -O3) can better auto-vectorize
these for better performance. A lot of these are also not inlined, because I have found
that it can cause issues with certain compiler settings (again, e.g. GCC with -O3).
Don't worry, I have tested performance in another project inlined vs not inlined and it didn't
make a noticable difference. If you have reason to believe otherwise, please submit an issue on
GitHub.
*/

//#include <cmath>
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

vec3 add_vec3(vec3 vector, vec3 vector0)
{
	vector.x += vector0.x;
	vector.y += vector0.y;
	vector.z += vector0.z;
	return vector;
}

vec3 add_vec3f(vec3 vector, float x)
{
	vector.x += x;
	vector.y += x;
	vector.z += x;
	return vector;
}

vec3 subtract_vec3(vec3 vector, vec3 vector0)
{
	vector.x -= vector0.x;
	vector.y -= vector0.y;
	vector.z -= vector0.z;
	return vector;
}

vec3 subtract_vec3f(vec3 vector, float x)
{
	vector.x -= x;
	vector.y -= x;
	vector.z -= x;
	return vector;
}

vec3 multiply_vec3(vec3 vector, vec3 vector0)
{
	vector.x *= vector0.x;
	vector.y *= vector0.y;
	vector.z *= vector0.z;
	return vector;
}

vec3 multiply_vec3f(vec3 vector, float x)
{
	vector.x *= x;
	vector.y *= x;
	vector.z *= x;
	return vector;
}

vec3 divide_vec3(vec3 vector, vec3 vector0)
{
	vector.x /= vector0.x;
	vector.y /= vector0.y;
	vector.z /= vector0.z;
	return vector;
}

vec3 divide_vec3f(vec3 vector, float x)
{
	vector.x /= x;
	vector.y /= x;
	vector.z /= x;
	return vector;
}

float dot3(vec3 vector, vec3 vector0)
{
	vector.x *= vector0.x;
	vector.y *= vector0.y;
	vector.z *= vector0.z;
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
	vec3 vector0 = vector;
	vector0.x *= vector0.x;
	vector0.y *= vector0.y;
	vector0.z *= vector0.z;
	float magnitude = sqrtf(vector0.x+vector0.y+vector0.z);
	vector.x /= magnitude;
	vector.y /= magnitude;
	vector.z /= magnitude;
	return vector;
}