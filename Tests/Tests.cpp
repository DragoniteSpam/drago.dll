#include <iostream>
//#include "Bullet/bulletgml.h"
#include "SpriteOperations/spriteops.h"

using namespace std;

int main() {
	unsigned int data[16] = {
		0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x40404040, 0x40404040, 0x40404040, 0x40404040,
		0x80808080, 0x80808080, 0x80808080, 0x80808080,
		0xb0b0b0b0, 0xb0b0b0b0, 0xb0b0b0b0, 0xb0b0b0b0
	};

	cout << (void*)spriteops::sample(data, 4, 4, 0.0f, 0.0f) << endl;
	cout << (void*)spriteops::sample(data, 4, 4, 0.10f, 0.10f) << endl;
	cout << (void*)spriteops::sample(data, 4, 4, 0.15f, 0.15f) << endl;
	cout << (void*)spriteops::sample(data, 4, 4, 0.20f, 0.20f) << endl;
	cout << (void*)spriteops::sample(data, 4, 4, 0.25f, 0.25f) << endl;
	cout << (void*)spriteops::sample(data, 4, 4, 0.30f, 0.30f) << endl;
	cout << (void*)spriteops::sample(data, 4, 4, 0.35f, 0.35f) << endl;
	cout << (void*)spriteops::sample(data, 4, 4, 0.40f, 0.40f) << endl;
	cout << (void*)spriteops::sample(data, 4, 4, 0.45f, 0.45f) << endl;
	cout << (void*)spriteops::sample(data, 4, 4, 0.5f, 0.5f) << endl;

	///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
	//btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();

	///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
	//btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);

	///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
	//btBroadphaseInterface* overlappingPairCache = new btDbvtBroadphase();

	///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
	//btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;

	//btDiscreteDynamicsWorld* dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);

	//dynamicsWorld->setGravity(btVector3(0, -10, 0));

	return 0;
}