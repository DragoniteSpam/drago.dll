#ifndef __DRAGO_BULLET
#define __DRAGO_BULLET "0.0.1"

#include "bullet/btBulletDynamicsCommon.h"
#include <vector>

namespace bullet {
	class DragoBullet {
	public:
		btDiscreteDynamicsWorld* World();
		btDefaultCollisionConfiguration* CollisionConfiguration();
		btCollisionDispatcher* Dispatcher();
		btBroadphaseInterface* OverlappingPairCache();
		btSequentialImpulseConstraintSolver* Solver();
	private:
		btDiscreteDynamicsWorld* world;
		btDefaultCollisionConfiguration* collisionConfiguration;
		btCollisionDispatcher* dispatcher;
		btBroadphaseInterface* overlappingPairCache;
		btSequentialImpulseConstraintSolver* solver;
	};
	
	const char* version();
	int get_world_count();

	int world_create();
	int world_destroy(int);

	std::vector<bullet::DragoBullet*> worlds;
}

#endif