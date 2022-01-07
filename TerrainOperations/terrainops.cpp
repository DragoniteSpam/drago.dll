#include <algorithm>
#include "terrainops.h"

namespace terrainops {
	void to_heightmap(float* data, unsigned int* out, int len, double scale) {
		int z;
		for (int i = 0; i < len; i++) {
			z = std::clamp((int)(data[i] * scale), 0, 255);
			out[i] = 0xff000000 | (z | (z << 8) | (z << 16));
		}
	}

	void from_heightmap(float* data, unsigned int* in, int len, double scale) {

	}
}