#include <random>

#include "macaw.h"

namespace macaw {
	const char* version() {
		return __DRAGO_MACAW;
	}

	void generate(float* buffer, int w, int h, int octaves) {

	}

	float* _gen_white_noise(int w, int h) {
		#pragma warning(disable: 26451)
		float* noise = new float[w * h];
		#pragma warning(default: 26451)

		for (int i = 0; i < w * h; i++) {
			noise[i] = std::rand();
		}

		return noise;
	}

	float* _gen_smooth_noise(float* base_noise, int octave) {
		return 0;
	}
}