#include <stdlib.h>
#include <algorithm>
#include <iostream>

#include "macaw.h"

#define GET_3D_INDEX(i, j, k, w, h) (((w) * (h)) * (k) + (i) * (h) + (j))
#define GET_2D_INDEX(i, j, h) ((i) * (h) + (j))

namespace macaw {
	extern float setting_height = 1.0;
	extern int setting_octaves = 6;

	const char* version() {
		return __DRAGO_MACAW;
	}

	void set_octaves(int octaves) {
		setting_octaves = octaves;
	}

	void set_height(float height) {
		setting_height = height;
	}

	void generate(float* perlin, int w, int h) {
		float persistence = 0.5;
		float amplitude = 1.0;
		float total_amplitude = 0.0;
		float* base = _gen_white_noise(w, h);

		int tlen = w * h * setting_octaves;
		float* smooth = _gen_smooth_noise(base, w, h, setting_octaves);

		for (int octave = setting_octaves - 1; octave >= 0; octave--) {
			amplitude *= persistence;
			total_amplitude += amplitude;

			for (int i = 0; i < w; i++) {
				for (int j = 0; j < h; j++) {
					perlin[GET_2D_INDEX(i, j, h)] += smooth[GET_3D_INDEX(i, j, octave, w, h)] * amplitude;
				}
			}
		}

		int len = w * h;
		for (int i = 0; i < len; i++) {
			perlin[i] *= setting_height / total_amplitude;
		}

		delete[] base;
		delete[] smooth;
	}

	float* _gen_white_noise(int w, int h) {
		int len = w * h;

		float* noise = new float[len];
		for (int i = 0; i < len; i++) {
			noise[i] = ((float)rand()) / RAND_MAX;
		}

		return noise;
	}

	float* _gen_smooth_noise(float* base_noise, int w, int h, int octaves) {
		int len = w * h * octaves;
		float* smooth = new float[len];

		for (int octave = 0; octave < octaves; octave++) {
			int period = 1 << octave;
			float frequency = 1.0f / period;

			for (int i = 0; i < w; i++) {
				int i0 = (i / period) * period;
				int i1 = (i0 + period) % w;
				float hblend = (i * 1.0f - i0 * 1.0f) / period;

				for (int j = 0; j < h; j++) {
					int j0 = (j / period) * period;
					int j1 = (j0 + period) % h;
					float vblend = (j * 1.0f - j0 * 1.0f) / period;

					float a = base_noise[GET_2D_INDEX(i0, j0, h)];
					float b = base_noise[GET_2D_INDEX(i1, j0, h)];
					float c = base_noise[GET_2D_INDEX(i0, j1, h)];
					float d = base_noise[GET_2D_INDEX(i1, j1, h)];

					float e = LERP_WHATEVERS_SMOOTHER_THAN_CUBIC(a, b, hblend);
					float f = LERP_WHATEVERS_SMOOTHER_THAN_CUBIC(c, d, hblend);

#pragma warning(disable:6386)
					smooth[GET_3D_INDEX(i, j, octave, w, h)] = LERP_WHATEVERS_SMOOTHER_THAN_CUBIC(e, f, vblend);
#pragma warning(default:6386)
				}
			}
		}

		return smooth;
	}

	void seed_set(unsigned int seed) {
		srand(seed);
	}

	// these arent really needed but they may be occasionally helpful
	void to_sprite(float* in, int* out, int len) {
		for (int i = 0; i < len; i++) {
			unsigned int intensity = std::min(255, std::max((int)in[i], 0));
			out[i] = intensity | (intensity << 8) | (intensity << 16) | 0xff000000;
		}
	}

	void to_vbuff(float* in, float* out, int w, int h) {
		int index = 0;
		for (int i = 0; i < w - 1; i++) {
			for (int j = 0; j < h - 1; j++) {
				float h00 = in[GET_2D_INDEX(i, j, h)];
				float h01 = in[GET_2D_INDEX(i, j + 1, h)];
				float h10 = in[GET_2D_INDEX(i + 1, j, h)];
				float h11 = in[GET_2D_INDEX(i + 1, j + 1, h)];
				out[index++] = (float)i;
				out[index++] = (float)j;
				out[index++] = h00;
				out[index++] = (float)(i + 1);
				out[index++] = (float)j;
				out[index++] = h10;
				out[index++] = (float)(i + 1);
				out[index++] = (float)(j + 1);
				out[index++] = h11;
				out[index++] = (float)(i + 1);
				out[index++] = (float)(j + 1);
				out[index++] = h11;
				out[index++] = (float)i;
				out[index++] = (float)(j + 1);
				out[index++] = h01;
				out[index++] = (float)i;
				out[index++] = (float)j;
				out[index++] = h00;
			}
		}
		std::cout << "printing something out because computers are the stupidest things ever and this literally crashes if the printout isnt here" << std::endl;
	}
}

#undef GET_3D_INDEX
#undef GET_2D_INDEX