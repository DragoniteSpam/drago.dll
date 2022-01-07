#include "spriteops.h"

namespace spriteops {
	int* cropped_dimensions_output = nullptr;

	const char* version() {
		return __DRAGO_SPRITE_OP;
	}

	void set_cropped_dimensions_output(int* out) {
		spriteops::cropped_dimensions_output = out;
	}

	void get_cropped_dimensions(int* data, int w, int h, int cutoff) {
		int out_left = 0;
		int out_top = 0;
		int out_right = w - 1;
		int out_bottom = h - 1;

		for (int i = 0; i < w; i++) {
			for (int j = 0; j < h; j++) {
				int index = GET_INDEX(i, j, w);
				if ((data[index] >> 24) > cutoff) {
					out_left = i;
					goto endLeft;
				}
			}
		}

	endLeft:

		for (int i = w - 1; i >= 0; i--) {
			for (int j = 0; j < h; j++) {
				int index = GET_INDEX(i, j, w);
				if ((data[index] >> 24) > cutoff) {
					out_right = i;
					goto endRight;
				}
			}
		}

	endRight:

		for (int j = 0; j < h; j++) {
			for (int i = 0; i < w; i++) {
				int index = GET_INDEX(i, j, w);
				if ((data[index] >> 24) > cutoff) {
					out_top = i;
					goto endTop;
				}
			}
		}

	endTop:

		for (int j = h - 1; j > 0; j--) {
			for (int i = 0; i < w; i++) {
				int index = GET_INDEX(i, j, w);
				if ((data[index] >> 24) > cutoff) {
					out_bottom = i;
					goto endBottom;
				}
			}
		}

	endBottom:

		spriteops::cropped_dimensions_output[0] = out_left;
		spriteops::cropped_dimensions_output[1] = out_top;
		spriteops::cropped_dimensions_output[2] = out_right;
		spriteops::cropped_dimensions_output[3] = out_bottom;
	}

	void spriteops_remove_transparent_colour(int* data, int length, int colour) {
		for (int i = 0; i < length; i++) {
			// it might be worth it to add a tolerance value here some time
			if ((data[i] & 0x00ffffff) == colour) {
				data[i] = 0;
			}
		}
	}
}