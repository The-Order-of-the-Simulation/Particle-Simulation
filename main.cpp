#include <iostream>
using namespace std;

#include <chrono>
#include <fstream>
#include <thread>

#include "vec3.h"

// ##### Random Number Generator #####

#include <cstdint>

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

// ##### Simulation and Rendering #####

typedef struct {
	vec3 position;
	vec3 velocity;
} particleData;

#define N_STEPS 50U
#define TIMESTEP 0.01F
#define N_PARTICLES 4000U

#define RENDER_SIZE_X 640U
#define RENDER_SIZE_Y 360U

#define str 0.01F
#define sigma 0.1F

float square(float x)
{
	return x * x;
}

// ##### Main #####
int main()
{
	unsigned int n_threads = thread::hardware_concurrency();

	if(n_threads < 1U)
	{
		std::cout << "Critical Error: thread::hardware_concurrency() reports " << n_threads << " hardware threads!" << std::endl;
		std::cout << "Please make sure your machine supports std::thread. Exiting..." << std::endl;

		return EXIT_FAILURE;
	}

	std::cout << "This machine reports " << n_threads << " hardware threads" << std::endl;

	std::cout << "Allocating memory..." << std::endl;

	particleData *old_particle_buffer;
	particleData *new_particle_buffer;
	vec3 *render_buffer;
	old_particle_buffer = (particleData*)malloc(sizeof(particleData)*N_PARTICLES);
	new_particle_buffer = (particleData*)malloc(sizeof(particleData)*N_PARTICLES);
	render_buffer = (vec3*)malloc(sizeof(vec3)*RENDER_SIZE_X*RENDER_SIZE_Y);

	std::cout << "Initializing simulation..." << std::endl;

	ns = 1U;

	for(unsigned int i = 0U; i < N_PARTICLES; i++)
	{
		old_particle_buffer[i].position = subtract_vec3f(rand3(), 0.5F);
		old_particle_buffer[i].velocity = subtract_vec3f(rand3(), 0.5F);
	}

	std::cout << "Starting Simulation..." << std::endl;

	for(unsigned int step = 0U; step < N_STEPS; step++)
	{
		std::cout << "Running step " << step << "..." << std::endl;

		// Simulate Timestep
		for(unsigned int i = 0U; i < N_PARTICLES; i++)
		{
			particleData old_particle = old_particle_buffer[i];
			particleData new_particle;

			vec3 force = float3f(0.0F);

			for(unsigned int particle = 0U; particle < N_PARTICLES; particle++)
			{
				if(particle == i)
				{
					continue;
				}

				particleData neighbor_particle = old_particle_buffer[particle];

				vec3 delta = subtract_vec3(neighbor_particle.position, old_particle.position);

				float d = max(dotp3(delta), 0.01F)/(sigma*sigma);
				vec3 f = multiply_vec3f(normalize3(delta), str*((2.0F/square(d*d*d))-(1.0F/(d*d*d))));

				//float d = 1.0F/max(dotp3(delta), 0.1F);
				//vec3 f = multiply_vec3f(normalize3(delta), 0.0001F*d);

				force = add_vec3(force, f);
			}

			new_particle.velocity = add_vec3(old_particle.velocity, force);
			new_particle.position = add_vec3(old_particle.position, multiply_vec3f(new_particle.velocity, TIMESTEP));

			new_particle_buffer[i] = new_particle;
		}

		// Clear Render Buffer
		for(unsigned int i = 0U; i < RENDER_SIZE_X*RENDER_SIZE_Y; i++)
		{
			render_buffer[i] = float3f(0.0F);
		}

		// Render Timestep
		for(unsigned int i = 0U; i < N_PARTICLES; i++)
		{
			particleData render_particle = new_particle_buffer[i];

			float pixelCoord_x = (render_particle.position.x+0.5F)*float(RENDER_SIZE_X);
			float pixelCoord_y = (render_particle.position.y+0.5F)*float(RENDER_SIZE_Y);

			if((pixelCoord_x < 0.0F) || (pixelCoord_x > float(RENDER_SIZE_X)) || (pixelCoord_y < 0.0F) || (pixelCoord_y > float(RENDER_SIZE_Y)))
			{
				continue;
			}

			unsigned int iPixelCoord_x = min(max(uint(pixelCoord_x), 0U), RENDER_SIZE_X);
			unsigned int iPixelCoord_y = min(max(uint(pixelCoord_y), 0U), RENDER_SIZE_Y);

			render_buffer[min(iPixelCoord_x+(iPixelCoord_y*RENDER_SIZE_X), (RENDER_SIZE_X*RENDER_SIZE_Y)-1U)] = float3f(1.0F);

			old_particle_buffer[i] = render_particle;
		}

		std::string fileName = "frame"+std::to_string(step)+".ppm";
		ofstream imageFile;
		imageFile.open(fileName);

		/*
		// Write Header to File
		imageFile << "P3" << std::endl << RENDER_SIZE_X << " " << RENDER_SIZE_Y << std::endl << "255" << std::endl;

		// Save Rendered Timestep
		for(unsigned int i = 0U; i < RENDER_SIZE_X*RENDER_SIZE_Y; i++)
		{
			// Quantization
			int channel_r = min(max(int(255.0F*render_buffer[i].x), 0), 255);
			int channel_g = min(max(int(255.0F*render_buffer[i].y), 0), 255);
			int channel_b = min(max(int(255.0F*render_buffer[i].z), 0), 255);

			imageFile << channel_r << " " << channel_g << " " << channel_b << " ";
		}
		*/

		// Write Header to File
		imageFile << "P6" << std::endl << RENDER_SIZE_X << " " << RENDER_SIZE_Y << std::endl << "255" << std::endl;

		// Save Rendered Timestep
		for(unsigned int i = 0U; i < RENDER_SIZE_X*RENDER_SIZE_Y; i++)
		{
			// Quantization
			char channel_r = char(min(max(int(255.0F*render_buffer[i].x), 0), 255));
			char channel_g = char(min(max(int(255.0F*render_buffer[i].y), 0), 255));
			char channel_b = char(min(max(int(255.0F*render_buffer[i].z), 0), 255));

			imageFile << channel_r << channel_g << channel_b;
		}

		imageFile.close();
	}

	std::cout << "Cleaning up..." << std::endl;

	free(old_particle_buffer);
	free(new_particle_buffer);
	free(render_buffer);

	std::cout << "Done!" << std::endl;

	return EXIT_SUCCESS;
}