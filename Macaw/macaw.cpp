#include "macaw.h"

namespace macaw {
	const char* version() {
		return __DRAGO_MACAW;
	}

	void generate(float* buffer, int w, int h, int octaves) {

	}

	float* _gen_white_noise(int w, int h) {
		return 0;
	}

	float* _gen_smooth_noise(float* base_noise, int octave) {
		return 0;
	}
}