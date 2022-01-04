#include <stdlib.h>

#include "macaw.h"

#define GET_3D_INDEX(i, j, k, w, h) ((w * h) * k + i * h + j)
#define GET_2D_INDEX(i, j, h) (i * h + j)

namespace macaw {
	extern double setting_height = 1.0;
	extern int setting_octaves = 6;

	const char* version() {
		return __DRAGO_MACAW;
	}

	void set_octaves(int octaves) {
		setting_octaves = octaves;
	}

	void set_height(double height) {
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
			float frequency = 1.0 / period;

			for (int i = 0; i < w; i++) {
				int i0 = (i / period) * period;
				int i1 = (i0 + period) % w;
				float hblend = (i - i0) * frequency;

				for (int j = 0; j < h; j++) {
					int j0 = (j / period) * period;
					int j1 = (j0 + period) % h;
					float vblend = (j - j0) * frequency;

					float b00 = base_noise[i0 * h + j0];
					float b01 = base_noise[i0 * h + j1];
					float b10 = base_noise[i1 * h + j0];
					float b11 = base_noise[i1 * h + j1];

					float top = interpolate(b00, b10, hblend);
					float bottom = interpolate(b01, b11, hblend);

#pragma warning(disable:6386)
					smooth[GET_3D_INDEX(i, j, octave, w, h)] = interpolate(top, bottom, vblend);
#pragma warning(default:6386)
				}
			}
		}

		return smooth;
	}

	void seed_set(unsigned int seed) {
		srand(seed);
	}

	float interpolate(float a, float b, float f) {
		return a * (1 - f) + f * b;
	}
}

#undef GET_3D_INDEX
#undef GET_2D_INDEX