#include <stdlib.h>

#include "macaw.h"

#define GET_SMOOTH_INDEX(i, j, octave) ((i + j) * octave + i * h + j)

namespace macaw {
	const char* version() {
		return __DRAGO_MACAW;
	}

	void generate(float* buffer, int w, int h, int octaves) {
		float persistence = 0.5;
		float amplitude = 1.0;
		float total_amplitude = 0.0;
		float* base = _gen_white_noise(w, h);

		int tlen = w * h * octaves;
		float* smooth = new float[tlen];

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
				for (int j = 0; j < h; j++) {
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
						smooth[GET_SMOOTH_INDEX(i, j, octave)] = interpolate(top, bottom, vblend);
#pragma warning(default:6386)
					}
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

#undef GET_SMOOTH_INDEX