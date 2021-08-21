#include <stdlib.h>

#include "macaw.h"

namespace macaw {
	const char* version() {
		return __DRAGO_MACAW;
	}

	void generate(float* buffer, int w, int h, int octaves) {

	}

	float* _gen_white_noise(int w, int h) {
		int len = w * h;

		float* noise = new float[len];
		for (int i = 0; i < len; i++) {
			noise[i] = ((float)rand()) / RAND_MAX;
		}

		return noise;
	}

	float* _gen_smooth_noise(float* base_noise, int octave) {
		return 0;
	}
}