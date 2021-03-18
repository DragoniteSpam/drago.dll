#include "main/core.h"

#include <iostream>

float store_x;
float store_y;
float store_z;

ex double vertex_set_position(double x, double y, double z) {
	store_x = (float)x;
	store_y = (float)y;
	store_z = (float)z;
	return 0.0;
}

ex double vertex_buffer_combine(float* combine_target, float* source_data, double length, double address) {
	int a = (int)address;
	int vertices = (int)length / 4;
	for (int i = 0; i < vertices; i += 9) {
		combine_target[a + i + 0] = source_data[i + 0] + store_x;
		combine_target[a + i + 1] = source_data[i + 1] + store_y;
		combine_target[a + i + 2] = source_data[i + 2] + store_z;
		
		combine_target[a + i + 3] = source_data[i + 3];
		combine_target[a + i + 4] = source_data[i + 4];
		combine_target[a + i + 5] = source_data[i + 5];

		combine_target[a + i + 6] = source_data[i + 6];
		combine_target[a + i + 7] = source_data[i + 7];
		
		combine_target[a + i + 8] = source_data[i + 8];
	}
	return 1.0;
}

ex double vertex_buffer_combine_single(float* combine_target, float* combine_positions, double count) {
	const int SIZE = 324;
	int tree_count = (int)count;
	int index = 0;
	for (int tree = 0; tree < tree_count; tree++) {
		for (int i = 0; i < 324; i += 9) {
			combine_target[index + i + 0] += combine_positions[tree * 3 + 0];
			combine_target[index + i + 1] += combine_positions[tree * 3 + 1];
			combine_target[index + i + 2] += combine_positions[tree * 3 + 2];
		}
		index += SIZE;
	}
	
	return 1.0;
}