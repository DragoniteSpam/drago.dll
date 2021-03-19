#include "falcon.h"

namespace falcon {
	const char* version() {
		return __DRAGO_FALCON;
	}

	void combine(float* combine_target, float* combine_positions, double count) {
		int tree_count = (int)count;
		int index = 0;
		for (int tree = 0; tree < tree_count; tree++) {
			int tree_size = combine_positions[tree * FALCON_BATCH_DATA_SIZE + 0];
			for (int i = 0; i < tree_size; i += 9) {
				combine_target[index + i + 0] = combine_target[index + i + 0] * combine_positions[tree * FALCON_BATCH_DATA_SIZE + 4] + combine_positions[tree * FALCON_BATCH_DATA_SIZE + 1];
				combine_target[index + i + 1] = combine_target[index + i + 1] * combine_positions[tree * FALCON_BATCH_DATA_SIZE + 5] + combine_positions[tree * FALCON_BATCH_DATA_SIZE + 2];
				combine_target[index + i + 2] = combine_target[index + i + 2] * combine_positions[tree * FALCON_BATCH_DATA_SIZE + 6] + combine_positions[tree * FALCON_BATCH_DATA_SIZE + 3];
			}
			index += tree_size;
		}
	}
}