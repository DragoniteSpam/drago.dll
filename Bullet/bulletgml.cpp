#include "bulletgml.h"

namespace bullet {
	const char* version() {
		return __DRAGO_BULLET;
	}
	int get_world_count() {
		return worlds.size();
	}
}