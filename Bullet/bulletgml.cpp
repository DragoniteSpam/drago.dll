#include "bulletgml.h"

namespace bullet_drago {
	const char* version() {
		return __DRAGO_BULLET;
	}

	int get_world_count() {
		return (int)worlds.size();
	}

	int world_create() {
		worlds.push_back(new bullet_wrapper::DragoBullet());
		return 1;
	}

	int world_destroy(int index) {
		if (index >= 0 && index < worlds.size()) {
			delete worlds.at(index);
			worlds.erase(worlds.begin() + index);
			return 1;
		}
		return 0;
	}
}