#include "ThreeDCollisions.h"

namespace collisions {
	const char* version() {
		return __DRAGO_3DC;
	}

	const inline void set_epsilon(float epsilon) {
		collisions::epsilon = epsilon;
	}

	const inline static bool compare_epislon(float a, float b) {
		return abs(a - b) < collisions::epsilon;
	}
}