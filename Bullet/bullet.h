#ifndef __DRAGO_BULLET_INIT
#define __DRAGO_BULLET_INIT

#include "bullet/btBulletDynamicsCommon.h"

namespace bullet_wrapper {
	class DragoBullet {
	public:
		DragoBullet();
		~DragoBullet();
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
}

#endif