#ifndef __DRAGO_BULLET_INIT
#define __DRAGO_BULLET_INIT

#include "bullet/btBulletDynamicsCommon.h"

namespace bullet_wrapper {
	class DragoBulletWorld {
	public:
		DragoBulletWorld();
		~DragoBulletWorld();
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

		// managed
		btAlignedObjectArray<btCollisionShape*> collisionShapes;
	};
}

#endif