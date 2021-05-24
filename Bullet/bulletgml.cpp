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

	int world_set_gravity(double world, double x, double y, double z) {
		int index = (int)world;
		if (index >= 0 && index < worlds.size()) {
			worlds.at(index)->SetGravity((float)x, (float)y, (float)z);
			return 1;
		}
		return 0;
	}

	int world_get_gravity(double world, float* address) {
		int index = (int)world;
		if (index >= 0 && index < worlds.size()) {
			worlds.at(index)->GetGravity(address);
			return 1;
		}
		return 0;
	}
}