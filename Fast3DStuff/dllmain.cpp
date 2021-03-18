#include "main/core.h"

ex double vertex_buffer_combine(float* combine_target, float* combine_positions, double count) {
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