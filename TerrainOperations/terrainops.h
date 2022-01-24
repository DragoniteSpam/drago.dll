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

	extern float* data;
	extern Vector3 data_size;
	extern float* vertex;

	const char* version();

	// general
	void set_active_data(float*, int, int);
	void set_active_vertex_buffers(float*);
	void to_heightmap(unsigned int*, float);
	void from_heightmap(unsigned int*, float);

	// deformation
	void flatten(float);
	void apply_scale(float);
	void deform_brush(unsigned int*, float, float);
	void deform_brush_settings(float, float);
	void deform_brush_set_position(float, float);
	// the deformation functions still use the data pointers, because theyre
	// called many times
	void deform_mold(float*, float*, int, int, int, int, float, float, float);
	void deform_average(float*, float*, int, int, int, int, float, float, float);
	void deform_zero(float*, float*, int, int, int, int, float, float, float);

	// mutation
	void mutate_set_noise(float*, int, int, float);
	void mutate_set_texture(unsigned int*, int, int, float);
	void mutate();

	// build vertex data
	void build_settings(bool, bool, bool, bool, int, int, int, float);
	long build(long long*, int);
	void generate_internal(float*);

	// helper functions
	inline float get_z(float*, int, int, int);
	inline void add_z(float*, float*, int, int, int, int, float);
	inline void set_z(float*, float*, int, int, int, int, float);
	inline void write_vertex(float*, long long*, float, float, float, float, float, float, float, float, unsigned int, float, float, float, float, float, float, float, float, float);
	void invoke_deformation(bool, void(float*, float*, int, int, int, int, float, float, float));
}

#endif