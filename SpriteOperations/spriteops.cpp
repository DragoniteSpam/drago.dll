#include "spriteops.h"

namespace spriteops {
	const char* version() {
		return __DRAGO_SPRITE_OP;
	}

	void set_cropped_dimensions_output(float* data) {
		dimensions_output = data;
	}

	void get_cropped_dimensions(float* data, int length, int w, int h, float* out) {

	}

	void spriteops_remove_transparent_colour(float* data, int length, int colour) {

	}
}