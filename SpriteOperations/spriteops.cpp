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

	// sprite sampling
	unsigned int sample(unsigned int* data, int w, int h, float u, float v) {
		return sample_pixel(data, w, h, u * w, v * h);
	}

	unsigned int sample_pixel(unsigned int* data, int w, int h, float x, float y) {
		// might implement texture wrapping some other day but right now i dont feel like it
		x = std::clamp(x, 0.0f, w - 1.0f);
		y = std::clamp(y, 0.0f, h - 1.0f);
		int address_ul = GET_INDEX(floor(x), floor(y), w);
		int address_ur = GET_INDEX(ceil(x), floor(y), w);
		int address_ll = GET_INDEX(floor(x), ceil(y), w);
		int address_lr = GET_INDEX(ceil(x), ceil(y), w);
		float horizontal_lerp = fmod(x, 1);
		float vertical_lerp = fmod(y, 1);
		int colour_ul = data[address_ul];
		int colour_ur = data[address_ur];
		int colour_ll = data[address_ll];
		int colour_lr = data[address_lr];
		int colour_l = merge(colour_ul, colour_ll, vertical_lerp);
		int colour_r = merge(colour_ur, colour_lr, vertical_lerp);
		return merge(colour_l, colour_r, horizontal_lerp);
	}

	unsigned int sample_unfiltered(unsigned int* data, int w, int h, float u, float v) {
		return sample_pixel_unfiltered(data, w, h, u * w, v * h);
	}

	unsigned int sample_pixel_unfiltered(unsigned int* data, int w, int h, float x, float y) {
		// might implement texture wrapping some other day but right now i dont feel like it
		x = std::clamp(x, 0.0f, w - 1.0f);
		y = std::clamp(y, 0.0f, h - 1.0f);
		return data[(int)GET_INDEX(floor(x), floor(y), w)];
	}

	// help
	unsigned int merge(unsigned int a, unsigned int b, float f) {
		unsigned int rr1 = (a & 0x000000ff);
		unsigned int gg1 = (a & 0x0000ff00) >> 8;
		unsigned int bb1 = (a & 0x00ff0000) >> 16;
		unsigned int aa1 = (a & 0xff000000) >> 24;
		unsigned int rr2 = (b & 0x000000ff);
		unsigned int gg2 = (b & 0x0000ff00) >> 8;
		unsigned int bb2 = (b & 0x00ff0000) >> 16;
		unsigned int aa2 = (b & 0xff000000) >> 24;

#define LERP(a, b, f) ((unsigned int)((a) + (f) * ((b) - (a))))

		return LERP(rr1, rr2, f) | (LERP(gg1, gg2, f) << 8) | (LERP(bb1, bb2, f) << 16) | (LERP(aa1, aa2, f) << 24);

#undef LERP
	}
}