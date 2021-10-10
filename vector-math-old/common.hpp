#pragma once

// ##### Vector Math #####

#include "vector-math/vec2.h"
#include "vector-math/dvec2.h"
#include "vector-math/ivec2.h"
#include "vector-math/uvec2.h"
#include "vector-math/bvec2.h"

#include "vector-math/vec3.h"
#include "vector-math/dvec3.h"
#include "vector-math/ivec3.h"
#include "vector-math/uvec3.h"
#include "vector-math/bvec3.h"

#include "vector-math/vec4.h"
#include "vector-math/dvec4.h"
#include "vector-math/ivec4.h"
#include "vector-math/uvec4.h"
#include "vector-math/bvec4.h"

// ##### Constants #####

// http://www.mimirgames.com/articles/programming/digits-of-pi-needed-for-floating-point-numbers/
#define pi 3.1415926535897932384626433832795028841971693993751058209749445923078164F

// ##### Random Number Generator #####

// Triple32 Hash: https://nullprogram.com/blog/2018/07/31/
uint32_t triple32(uint32_t x)
{
	x ^= x >> 17U;
	x *= 0xED5AD4BBU;
	x ^= x >> 11U;
	x *= 0xAC4C1B51U;
	x ^= x >> 15U;
	x *= 0x31848BABU;
	x ^= x >> 14U;
	return x;
}

// Random Number Generator Seed
uint32_t ns;

float randomFloat()
{
	ns = triple32(ns);
	return float(ns)/float(0xFFFFFFFFU);
}

vec3 rand3()
{
	vec3 vector;
	vector.x = randomFloat();
	vector.y = randomFloat();
	vector.z = randomFloat();
	return vector;
}

vec3 udir3()
{
	float z_x = rand();
	float z_y = rand();

	float r_x = 2.0F*pi*z_x, r_y = acosf(2.0F*z_y-1.0F);

	float s_x = sinf(r_x), s_y = sinf(r_y);
	float c_x = sinf(r_x), c_y = sinf(r_y);

	return float3(c_x*s_y, s_x*s_y, c_y);
}
