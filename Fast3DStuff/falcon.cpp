#include "falcon.h"

namespace falcon {
	int vertex_size = 9;
	int vertex_color_offset = 8;

	const char* version() {
		return __DRAGO_FALCON;
	}

	void set_vertex_size(int floats) {
		vertex_size = floats;
	}

	void set_color_offset(int floats) {
		vertex_color_offset = floats;
	}

	void combine(float* combine_target, float* combine_positions, double count) {
		int tree_count = (int)count;
		int index = 0;
		for (int tree = 0; tree < tree_count; tree++) {
			int tree_size = ((int*)(combine_positions))[tree * FALCON_BATCH_DATA_SIZE + 0] / 4;
			for (int i = 0; i < tree_size; i += vertex_size) {
				combine_target[index + i + 0] += combine_positions[tree * FALCON_BATCH_DATA_SIZE + 1];
				combine_target[index + i + 1] += combine_positions[tree * FALCON_BATCH_DATA_SIZE + 2];
				combine_target[index + i + 2] += combine_positions[tree * FALCON_BATCH_DATA_SIZE + 3];
			}
			index += tree_size;
		}
	}

	void combine_color(float* combine_target, float* combine_positions, double count) {
		int tree_count = (int)count;
		int index = 0;
		for (int tree = 0; tree < tree_count; tree++) {
			int tree_size = ((int*)(combine_positions))[tree * FALCON_BATCH_DATA_SIZE + 0] / 4;
			for (int i = 0; i < tree_size; i += vertex_size) {
				combine_target[index + i + 0] += combine_positions[tree * FALCON_BATCH_DATA_SIZE + 1];
				combine_target[index + i + 1] += combine_positions[tree * FALCON_BATCH_DATA_SIZE + 2];
				combine_target[index + i + 2] += combine_positions[tree * FALCON_BATCH_DATA_SIZE + 3];

				combine_target[index + i + vertex_color_offset] *= combine_positions[tree * FALCON_BATCH_DATA_SIZE + vertex_color_offset];
			}
			index += tree_size;
		}
	}
}