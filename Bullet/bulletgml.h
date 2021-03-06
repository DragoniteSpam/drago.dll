#ifndef __DRAGO_BULLET
#define __DRAGO_BULLET "0.0.1"

#include "bullet/btBulletDynamicsCommon.h"
#include "bullet.h"
#include <vector>

namespace bullet_drago {
	const char* version();
	int get_world_count();

	int world_create();
	int world_destroy(int);

	int world_set_gravity(int, float, float, float);
	int world_get_gravity(int, float*);

	std::vector<bullet_wrapper::DragoBulletWorld*> worlds;
}

#endif