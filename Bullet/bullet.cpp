#include "bullet.h"

namespace bullet_wrapper {
	DragoBullet::DragoBullet() {
		collisionConfiguration = new btDefaultCollisionConfiguration();
		dispatcher = new btCollisionDispatcher(collisionConfiguration);
		overlappingPairCache = new btDbvtBroadphase();
		solver = new btSequentialImpulseConstraintSolver;
		world = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);
	}

	DragoBullet::~DragoBullet() {
		for (int i = world->getNumCollisionObjects() - 1; i >= 0; i--) {
			btCollisionObject* obj = world->getCollisionObjectArray()[i];
			btRigidBody* body = btRigidBody::upcast(obj);
			if (body && body->getMotionState()) {
				delete body->getMotionState();
			}
			world->removeCollisionObject(obj);
			delete obj;
		}
		delete world;
		delete collisionConfiguration;
		delete dispatcher;
		delete overlappingPairCache;
		delete solver;
	}

	btDiscreteDynamicsWorld* DragoBullet::World() {
		return this->world;
	}
	btDefaultCollisionConfiguration* DragoBullet::CollisionConfiguration() {
		return this->collisionConfiguration;
	}
	btCollisionDispatcher* DragoBullet::Dispatcher() {
		return this->dispatcher;
	}
	btBroadphaseInterface* DragoBullet::OverlappingPairCache() {
		return this->overlappingPairCache;
	}
	btSequentialImpulseConstraintSolver* DragoBullet::Solver() {
		return this->solver;
	}
}