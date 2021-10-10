#include <iostream>
using namespace std;

#include <chrono>
#include <cstdint>
#include <fstream>
#include <thread>

#include "common.hpp"

// ##### Parameters #####

#define N_STEPS 300U
#define TIMESTEP 0.001F
#define N_PARTICLES 10000U

#define RENDER_SIZE_X 640U
#define RENDER_SIZE_Y 360U

//#define RENDER_SIZE uvec2(640, 360)

#define strength 0.05F
#define sigma 0.1F

// ##### Simulation and Rendering #####

float square(float x)
{
	return x * x;
}

typedef struct {
	vec3 position;
	vec3 velocity;
} particleData;

// ##### Main #####
int main()
{
	unsigned int n_threads = thread::hardware_concurrency();

	if(n_threads < 1U)
	{
		std::cout << "Critical Error: thread::hardware_concurrency() reported " << n_threads << " threads!" << std::endl;
		std::cout << "Please make sure your machine supports std::thread. Exiting..." << std::endl;

		return EXIT_FAILURE;
	}

	std::cout << "This machine reports " << n_threads << " hardware threads" << std::endl;

	std::cout << "Initializing.." << std::endl;

	particleData *old_buffer;
	particleData *new_buffer;
	vec3 *render_buffer;
	old_buffer = (particleData*)malloc(sizeof(particleData)*N_PARTICLES);
	new_buffer = (particleData*)malloc(sizeof(particleData)*N_PARTICLES);
	render_buffer = (vec3*)malloc(sizeof(vec3)*RENDER_SIZE_X*RENDER_SIZE_Y);

	ns = 1U;

	for(unsigned int i = 0U; i < N_PARTICLES; i++)
	{
		old_buffer[i].position = rand3()-0.5F;
		old_buffer[i].velocity = udir3();
	}

	std::cout << "Starting simulation..." << std::endl;

	for(unsigned int step = 0U; step < N_STEPS; step++)
	{
		std::cout << "Running step " << step << "..." << std::endl;

		// Simulate Timestep
		for(unsigned int i = 0U; i < N_PARTICLES; i++)
		{
			particleData old_particle = old_buffer[i];
			particleData new_particle;

			vec3 force = vec3(0.0F);

			for(unsigned int particle = 0U; particle < N_PARTICLES; particle++)
			{
				if(i == particle)
				{
					continue;
				}

				particleData neighbor_particle = old_buffer[particle];

				vec3 delta = neighbor_particle.position-old_particle.position;

				// Newtonian Attraction
				//float d = 1.0F/max(dotp3(delta), 0.1F);
				//vec3 f = multiply_vec3f(normalize3(delta), 0.0001F*d);

				// https://arxiv.org/pdf/1401.1181.pdf
				// Expression 57
				float d = std::max(dot(delta, delta), 0.01F)/(sigma*sigma);
				vec3 f = normalize(delta)*(strength*((2.0F/square(d*d*d))-(1.0F/(d*d*d))));

				force += f;
			}

			new_particle.velocity = old_particle.velocity+force;
			new_particle.position = old_particle.position+(new_particle.velocity*TIMESTEP);

			new_buffer[i] = new_particle;
		}

		// Clear Render Buffer
		for(unsigned int i = 0U; i < RENDER_SIZE_X*RENDER_SIZE_Y; i++)
		{
			render_buffer[i] = vec3(0.0F);
		}

		// Render Timestep
		for(unsigned int i = 0U; i < N_PARTICLES; i++)
		{
			particleData render_particle = new_buffer[i];
			old_buffer[i] = render_particle;

			render_particle.position.x *= 0.5F;
			render_particle.position.y *= 0.5F*(float(RENDER_SIZE_X)/float(RENDER_SIZE_Y));

			float pixelCoord_x = (render_particle.position.x+0.5F)*float(RENDER_SIZE_X);
			float pixelCoord_y = (render_particle.position.y+0.5F)*float(RENDER_SIZE_Y);

			if((pixelCoord_x < 0.0F) || (pixelCoord_x > float(RENDER_SIZE_X)) || (pixelCoord_y < 0.0F) || (pixelCoord_y > float(RENDER_SIZE_Y)))
			{
				continue;
			}

			// White Particles
			vec3 particleColor = vec3(1.0F);

			// Distance Colored Particles
			//vec3 particleColor = 1.0F/(render_particle.position.z);

			// Velocity Colored Particles
			//vec3 particleColor = float3(abs(render_particle.velocity.x), abs(render_particle.velocity.y), abs(render_particle.velocity.z));

			unsigned int iPixelCoord_x = std::min(std::max(uint(pixelCoord_x), 0U), RENDER_SIZE_X);
			unsigned int iPixelCoord_y = std::min(std::max(uint(pixelCoord_y), 0U), RENDER_SIZE_Y);

			render_buffer[std::min(iPixelCoord_x+(iPixelCoord_y*RENDER_SIZE_X), (RENDER_SIZE_X*RENDER_SIZE_Y)-1U)] = particleColor;
		}

		std::string fileName = "render/frame"+std::to_string(step)+".ppm";
		ofstream imageFile;
		imageFile.open(fileName);

		// Write Header to File
		imageFile << "P6" << std::endl << RENDER_SIZE_X << " " << RENDER_SIZE_Y << std::endl << "255" << std::endl;

		// Save Rendered Timestep
		for(unsigned int i = 0U; i < RENDER_SIZE_X*RENDER_SIZE_Y; i++)
		{
			// Quantization
			char channel_r = char(std::min(std::max(int(255.0F*render_buffer[i].x), 0), 255));
			char channel_g = char(std::min(std::max(int(255.0F*render_buffer[i].y), 0), 255));
			char channel_b = char(std::min(std::max(int(255.0F*render_buffer[i].z), 0), 255));

			imageFile << channel_r << channel_g << channel_b;
		}

		imageFile.close();
	}

	std::cout << "Cleaning up..." << std::endl;

	free(old_buffer);
	free(new_buffer);
	free(render_buffer);

	std::cout << "Done!" << std::endl;

	return EXIT_SUCCESS;
}