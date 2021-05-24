#include "bulletgml.h"

namespace bullet_drago {
	const char* version() {
		return __DRAGO_BULLET;
	}

	int get_world_count() {
		return (int)worlds.size();
	}

	int world_create() {
		worlds.push_back(new bullet_wrapper::DragoBulletWorld());
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

	int world_set_gravity(int world, float x, float y, float z) {
		if (world >= 0 && world < worlds.size()) {
			worlds.at(world)->SetGravity(x, y, z);
			return 1;
		}
		return 0;
	}

	int world_get_gravity(int world, float* address) {
		if (world >= 0 && world < worlds.size()) {
			worlds.at(world)->GetGravity(address);
			return 1;
		}
		return 0;
	}
}