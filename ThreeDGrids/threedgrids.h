#ifndef __DRAGO_THREEDGRIDS
#define __DRAGO_THREEDGRIDS "1.0.0"

#include "main/core.h"

#define DATA_INDEX(x, y, z, height, depth) (((z) * (height) * (depth)) + ((y) * (depth)) + (x))

namespace threedgrids {
	extern double* grid;
	extern double* other;

	extern int w;
	extern int h;
	extern int d;
	extern int other_w;
	extern int other_h;
	extern int other_d;

	extern int x1;
	extern int y1;
	extern int z1;
	extern int x2;
	extern int y2;
	extern int z2;
	extern float r;

	extern double value;

	void set_region();
	void set_sphere();
	void set_region_grid();
	void set_region_sphere();

	void get_region_mean();
	void get_region_min();
	void get_region_max();
	void get_region_sum();
	void get_region_standard_deviation();
	void get_sphere_mean();
	void get_sphere_min();
	void get_sphere_max();
	void get_sphere_sum();
	void get_sphere_standard_deviation();

	void add_region();
	void add_sphere();
	void add_grid_region();
	void add_grid_sphere();
	void multiply_region();
	void multiply_sphere();
	void multiply_grid_region();
	void multiply_grid_sphere();

	void lerp_region();
	void lerp_sphere();
	void lerp_grid_region();
	void lerp_grid_sphere();

	float distance3D(float, float, float, float, float, float);
}
#endif