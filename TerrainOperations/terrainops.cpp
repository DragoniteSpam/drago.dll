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
		int z;
		for (int i = 0; i < len; i++) {
			// maybe you want to use the other channels to store some other information idk
			z = in[i] & 0x000000ff;
			data[i] = z / scale;
		}
	}
}