#include <iostream>
//#include "Bullet/bulletgml.h"
#include "SpriteOperations/spriteops.h"
#include "main/dragomath.h"

using namespace std;

void bullet_tests() {
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
}

void sprite_tests() {
	unsigned int data[25] = {
		0, 10, 20, 50, 100,
		0, 100, 200, 255, 255,
		0, 100, 200, 255, 255,
		0, 100, 200, 255, 255,
	};
	/*
	cout << spriteops::sample(data, 5, 5, 0.0f, 0.0f) << endl;
	cout << spriteops::sample(data, 5, 5, 0.10f, 0.10f) << endl;
	cout << spriteops::sample(data, 5, 5, 0.15f, 0.15f) << endl;
	cout << spriteops::sample(data, 5, 5, 0.20f, 0.60f) << endl;
	cout << spriteops::sample(data, 5, 5, 0.25f, 0.25f) << endl;
	cout << spriteops::sample(data, 5, 5, 0.30f, 0.30f) << endl;
	cout << spriteops::sample(data, 5, 5, 0.35f, 0.35f) << endl;
	cout << spriteops::sample(data, 5, 5, 0.40f, 0.40f) << endl;
	cout << spriteops::sample(data, 5, 5, 0.45f, 0.45f) << endl;
	cout << spriteops::sample(data, 5, 5, 0.5f, 0.5f) << endl;
	*/

	unsigned int a = 98;
	unsigned int b = 99;
	unsigned int c = 94;
	unsigned int d = 95;

	float f = 0.0;
	unsigned int f1 = spriteops::merge(a, b, f);
	unsigned int f2 = spriteops::merge(c, d, f);
	cout << f1 << ", " << f2 << ": " << spriteops::merge(f1, f2, f) << endl;

	a = 61;
	b = 61;
	c = 59;
	d = 59;

	f = 0.5;
	f1 = LERP(a, b, f);
	f2 = LERP(c, d, f);
	cout << f1 << ", " << f2 << ": " << LERP(f1, f2, f) << endl;

	f = 1.0;
	f1 = spriteops::merge(a, b, f);
	f2 = spriteops::merge(c, d, f);
	cout << f1 << ", " << f2 << ": " << spriteops::merge(f1, f2, f) << endl;
}

void matrix_tests() {
	Matrix4x4 transform = Matrix4x4::Transform(10, 10, 10, 0, 0, 0, 1, 2, 1);
	Vector4 point = Vector4(5, 5, 0, 1);

	point = transform * point;

	cout << "Transform matrix:\n";

	for (int i = 0; i < 16; i++) {
		cout << transform.asArray[i] << " ";
	}

	cout << "\nFinal position:\n";

	cout << point.x << ", " << point.y << ", " << point.z;

	cout << endl;

	
}

int main() {
	matrix_tests();
	return 0;
}