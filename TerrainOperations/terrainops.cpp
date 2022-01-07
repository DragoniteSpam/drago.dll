#include <algorithm>
#include "terrainops.h"

namespace terrainops {
	bool swap_zup = false;
	bool swap_uv = false;

	void to_heightmap(float* data, unsigned int* out, int len, float scale) {
		int z;
		for (int i = 0; i < len; i++) {
			z = std::clamp((int)(data[i] * scale), 0, 255);
			out[i] = 0xff000000 | (z | (z << 8) | (z << 16));
		}
	}

	void from_heightmap(float* data, unsigned int* in, int len, float scale) {
		int z;
		for (int i = 0; i < len; i++) {
			// maybe you want to use the other channels to store some other information idk
			z = in[i] & 0x000000ff;
			data[i] = z / scale;
		}
	}

	void build_settings(bool swap_zup, bool swap_uv) {
		terrainops::swap_zup = swap_zup;
		terrainops::swap_uv = swap_uv;
	}

	long build(float* data, float* out, int len) {

	}
}