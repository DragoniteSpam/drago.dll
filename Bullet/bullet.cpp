#include "bullet.h"

namespace bullet_wrapper {
	DragoBulletWorld::DragoBulletWorld() {
		collisionConfiguration = new btDefaultCollisionConfiguration();
		dispatcher = new btCollisionDispatcher(collisionConfiguration);
		overlappingPairCache = new btDbvtBroadphase();
		solver = new btSequentialImpulseConstraintSolver;
		world = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);
	}

	DragoBulletWorld::~DragoBulletWorld() {
		btCollisionObjectArray objArray = world->getCollisionObjectArray();
		for (int i = objArray.size() - 1; i >= 0; i--) {
			btCollisionObject* obj = objArray[i];
			btRigidBody* body = btRigidBody::upcast(obj);
			if (body && body->getMotionState()) {
				delete body->getMotionState();
			}
			world->removeCollisionObject(obj);
			delete obj;
		}

		//delete collision shapes
		for (int i = 0; i < collisionShapes.size(); i++) {
			delete collisionShapes[i];
		}

		delete world;
		delete collisionConfiguration;
		delete dispatcher;
		delete overlappingPairCache;
		delete solver;
	}

	btDiscreteDynamicsWorld* DragoBulletWorld::World() {
		return this->world;
	}
	btDefaultCollisionConfiguration* DragoBulletWorld::CollisionConfiguration() {
		return this->collisionConfiguration;
	}
	btCollisionDispatcher* DragoBulletWorld::Dispatcher() {
		return this->dispatcher;
	}
	btBroadphaseInterface* DragoBulletWorld::OverlappingPairCache() {
		return this->overlappingPairCache;
	}
	btSequentialImpulseConstraintSolver* DragoBulletWorld::Solver() {
		return this->solver;
	}
}