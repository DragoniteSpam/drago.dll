#ifndef __DRAGO_TERRAIN_OP
#define __DRAGO_TERRAIN_OP "0.0.1"

#include "main/core.h"
#include "SpriteOperations/spriteops.h"
#include <math.h>

namespace terrainops {
	extern bool save_all;
	extern bool save_swap_zup;
	extern bool save_swap_uv;
	extern bool save_centered;
	extern int save_density;
	extern int save_width;
	extern int save_height;
	extern float save_scale;

	extern float* mutate_noise;
	extern float mutate_noise_length;
	extern float mutate_noise_strength;
	extern unsigned int* mutate_texture;
	extern float mutate_texture_length;
	extern float mutate_texture_strength;

	const char* version();

	// general
	void to_heightmap(float*, unsigned int*, int, float);
	void from_heightmap(float*, unsigned int*, int, float);
	void flatten(float*, float*, int, float);
	void apply_scale(float*, float*, int, float);

	// mutation
	void mutate_set_noise(float*, int);
	void mutate_set_texture(unsigned int*, int);
	void mutate_set_parameters(float, float);
	void mutate(float*, int, int);

	// build vertex data
	void build_settings(bool, bool, bool, bool, int, int, int, float);
	long build(float*, long long*, int, int);
	void generate(float*, float*, int, int);

	// helper functions
	inline float get_z(float*, int, int, int);
	inline float add_z(float*, int, int, int, float);
	inline void write_vertex(float*, long long*, float, float, float, float, float, float, float, float, unsigned int, float, float, float, float, float, float, float, float, float);
}

#endif