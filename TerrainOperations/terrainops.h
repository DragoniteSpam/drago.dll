#ifndef __DRAGO_TERRAIN_OP
#define __DRAGO_TERRAIN_OP "0.0.1"

#include "main/core.h"
#include "SpriteOperations/spriteops.h"
#include <cmath>

#define DATA_INDEX(x, y, h) ((x) * (h) + (y))
#define VERTEX_INDEX(x, y, h, vertex) (3 * ((((x) * ((h) - 1) + (y)) * 6) + (vertex)))

namespace terrainops {
	extern bool save_all;
	extern bool save_swap_zup;
	extern bool save_swap_uv;
	extern bool save_centered;
	extern int save_density;
	extern int save_width;
	extern int save_height;
	extern float save_scale;

	extern unsigned int* deform_brush_texture;
	extern Vector3 deform_brush_size;
	extern Vector3 deform_brush_position;
	extern float deform_velocity;
	extern float deform_radius;

	extern float* mutate_noise;
	extern Vector3 mutate_noise_data;
	extern unsigned int* mutate_texture;
	extern Vector3 mutate_texture_data;

	const char* version();

	// general
	void to_heightmap(float*, unsigned int*, int, float);
	void from_heightmap(float*, unsigned int*, int, float);

	// deformation
	void flatten(float*, float*, int, float);
	void apply_scale(float*, float*, int, float);
	void deform_brush(unsigned int*, float, float);
	void deform_brush_settings(float, float);
	void deform_brush_set_position(int, int);
	void deform_mold(float*, float*, int, int, int, int, float, float, float);
	void deform_average(float*, float*, int, int, int, int, float, float, float);
	void deform_zero(float*, float*, int, int, int, int, float, float, float);

	// mutation
	void mutate_set_noise(float*, int, int, float);
	void mutate_set_texture(unsigned int*, int, int, float);
	void mutate(float*, float*, int, int);

	// build vertex data
	void build_settings(bool, bool, bool, bool, int, int, int, float);
	long build(float*, long long*, int, int);
	void generate(float*, float*, int, int);

	// helper functions
	inline float get_z(float*, int, int, int);
	inline void add_z(float*, float*, int, int, int, int, float);
	inline void set_z(float*, float*, int, int, int, int, float);
	inline void write_vertex(float*, long long*, float, float, float, float, float, float, float, float, unsigned int, float, float, float, float, float, float, float, float, float);
	void invoke_deformation(float*, float*, int, int, bool, void(float*, float*, int, int, int, int, float, float, float));
}

#endif