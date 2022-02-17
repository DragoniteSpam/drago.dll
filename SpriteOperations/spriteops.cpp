#include "spriteops.h"

#include <iostream>

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

	void remove_transparent_colour(int* data, int length, int colour) {
		for (int i = 0; i < length; i++) {
			// it might be worth it to add a tolerance value here some time
			if ((data[i] & 0x00ffffff) == colour) {
				data[i] = 0;
			}
		}
	}

	void set_alpha(unsigned int* data, int length, int alpha) {
		unsigned int alpha_mask = alpha << 24;
		for (int i = 0; i < length; i++) {
			data[i] = (data[i] & 0x00ffffff) | alpha_mask;
		}
	}

	// sprite sampling
	inline unsigned int sample(unsigned int* data, int w, int h, float u, float v) {
		return sample_pixel(data, w, h, u * w, v * h);
	}

	inline unsigned int sample_pixel(unsigned int* data, int w, int h, float x, float y) {
		// might implement texture wrapping some other day but right now i dont feel like it
		x = std::clamp(x, 0.0f, w - 1.0f);
		y = std::clamp(y, 0.0f, h - 1.0f);

		int xi = (int)x;
		int yi = (int)y;
		int xj = std::min(w - 1, xi + 1);
		int yj = std::min(h - 1, yi + 1);
		float xf = x - xi;
		float yf = y - yi;

		unsigned int a = data[(int)GET_INDEX(xi, yi, w)];
		unsigned int b = data[(int)GET_INDEX(xj, yi, w)];
		unsigned int c = data[(int)GET_INDEX(xi, yj, w)];
		unsigned int d = data[(int)GET_INDEX(xj, yj, w)];

		unsigned int la = merge(a, b, xf);
		unsigned int lb = merge(c, d, xf);

		return merge(la, lb, yf);
	}

	inline unsigned int sample_unfiltered(unsigned int* data, int w, int h, float u, float v) {
		return sample_pixel_unfiltered(data, w, h, u * (w + 0), v * (h + 0));
	}

	inline unsigned int sample_pixel_unfiltered(unsigned int* data, int w, int h, float x, float y) {
		// might implement texture wrapping some other day but right now i dont feel like it
		x = std::clamp(x, 0.0f, w - 1.0f);
		y = std::clamp(y, 0.0f, h - 1.0f);
		return data[(int)GET_INDEX(floor(x), floor(y), w)];
	}

	inline Vector4 sample_vec4(unsigned int* data, int w, int h, float u, float v) {
		return sample_vec4_pixel(data, w, h, u * w, v * h);
	}

	inline Vector4 sample_vec4_pixel(unsigned int* data, int w, int h, float x, float y) {
		// might implement texture wrapping some other day but right now i dont feel like it
		x = std::clamp(x, 0.0f, w - 1.0f);
		y = std::clamp(y, 0.0f, h - 1.0f);

		int xi = (int)x;
		int yi = (int)y;
		int xj = std::min(w - 1, xi + 1);
		int yj = std::min(h - 1, yi + 1);
		float xf = x - xi;
		float yf = y - yi;

		unsigned int a = data[(int)GET_INDEX(xi, yi, w)];
		unsigned int b = data[(int)GET_INDEX(xj, yi, w)];
		unsigned int c = data[(int)GET_INDEX(xi, yj, w)];
		unsigned int d = data[(int)GET_INDEX(xj, yj, w)];

		Vector4 va{
			((a & 0xff) >> 0x00) / 255.0f,
			((a & 0xff) >> 0x08) / 255.0f,
			((a & 0xff) >> 0x10) / 255.0f,
			((a & 0xff) >> 0x18) / 255.0f,
		};

		Vector4 vb{
			((b & 0xff) >> 0x00) / 255.0f,
			((b & 0xff) >> 0x08) / 255.0f,
			((b & 0xff) >> 0x10) / 255.0f,
			((b & 0xff) >> 0x18) / 255.0f,
		};

		Vector4 vc{
			((c & 0xff) >> 0x00) / 255.0f,
			((c & 0xff) >> 0x08) / 255.0f,
			((c & 0xff) >> 0x10) / 255.0f,
			((c & 0xff) >> 0x18) / 255.0f,
		};

		Vector4 vd{
			((d & 0xff) >> 0x00) / 255.0f,
			((d & 0xff) >> 0x08) / 255.0f,
			((d & 0xff) >> 0x10) / 255.0f,
			((d & 0xff) >> 0x18) / 255.0f,
		};

		Vector4 vla = merge(va, vb, xf);
		Vector4 vlb = merge(vc, vd, xf);

		return merge(vla, vlb, yf);
	}

	inline Vector4 sample_vec4_unfiltered(unsigned int* data, int w, int h, float u, float v) {
		return sample_vec4_pixel_unfiltered(data, w, h, u * (w + 0), v * (h + 0));
	}

	inline Vector4 samplevec4__pixel_unfiltered(unsigned int* data, int w, int h, float x, float y) {
		// might implement texture wrapping some other day but right now i dont feel like it
		x = std::clamp(x, 0.0f, w - 1.0f);
		y = std::clamp(y, 0.0f, h - 1.0f);
		unsigned int value = data[(int)GET_INDEX(floor(x), floor(y), w)];
		return Vector4{
			((value >> 0x00) & 0xff) / 255.0f,
			((value >> 0x08) & 0xff) / 255.0f,
			((value >> 0x10) & 0xff) / 255.0f,
			((value >> 0x18) & 0xff) / 255.0f,
		};
	}

	// not really sampling from a sprite anymore but the math for doing it with
	// regular floats is very similar
	inline float sample_float(float* data, int w, int h, float u, float v) {
		return sample_float_pixel(data, w, h, u * w, v * h);
	}

	inline float sample_float_pixel(float* data, int w, int h, float x, float y) {
		// might implement texture wrapping some other day but right now i dont feel like it
		x = std::clamp(x, 0.0f, w - 1.0f);
		y = std::clamp(y, 0.0f, h - 1.0f);

		int xi = (int)x;
		int yi = (int)y;
		int xj = std::min(w - 1, xi + 1);
		int yj = std::min(h - 1, yi + 1);
		float xf = x - xi;
		float yf = y - yi;

		float a = data[(int)GET_INDEX(xi, yi, w)];
		float b = data[(int)GET_INDEX(xj, yi, w)];
		float c = data[(int)GET_INDEX(xi, yj, w)];
		float d = data[(int)GET_INDEX(xj, yj, w)];

		float la = LERP(a, b, xf);
		float lb = LERP(c, d, xf);

		return LERP(la, lb, yf);
	}

	inline float sample_float_unfiltered(float* data, int w, int h, float u, float v) {
		return sample_float_pixel_unfiltered(data, w, h, u * w, v * h);
	}

	inline float sample_float_pixel_unfiltered(float* data, int w, int h, float x, float y) {
		// might implement texture wrapping some other day but right now i dont feel like it
		x = std::clamp(x, 0.0f, w - 1.0f);
		y = std::clamp(y, 0.0f, h - 1.0f);
		return data[(int)GET_INDEX(floor(x), floor(y), w)];
	}

	// help
	inline unsigned int merge(unsigned int a, unsigned int b, float f) {
		unsigned int rr1 = (a & 0x000000ff);
		unsigned int gg1 = (a & 0x0000ff00) >> 8;
		unsigned int bb1 = (a & 0x00ff0000) >> 16;
		unsigned int aa1 = (a & 0xff000000) >> 24;
		unsigned int rr2 = (b & 0x000000ff);
		unsigned int gg2 = (b & 0x0000ff00) >> 8;
		unsigned int bb2 = (b & 0x00ff0000) >> 16;
		unsigned int aa2 = (b & 0xff000000) >> 24;

		return (unsigned int)(LERP(rr1, rr2, f)) | ((unsigned int)(LERP(gg1, gg2, f)) << 8) | ((unsigned int)(LERP(bb1, bb2, f)) << 16) | ((unsigned int)(LERP(aa1, aa2, f)) << 24);
	}

	inline Vector4 merge(Vector4 a, Vector4 b, float f) {
		return Vector4{
			LERP(a.r, b.r, f),
			LERP(a.g, b.g, f),
			LERP(a.b, b.b, f),
			LERP(a.a, b.a, f),
		};
	}
}