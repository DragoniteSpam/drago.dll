#ifndef __DRAGO_BULLET
#define __DRAGO_BULLET "0.0.1"

#include "bullet/btBulletDynamicsCommon.h"
#include <vector>

namespace bullet {
	class BulletInstance {
	public:
	private:
		btDiscreteDynamicsWorld world;
	};
	
	const char* version();
	int get_world_count();

	std::vector<bullet::BulletInstance> worlds;
}

#endif