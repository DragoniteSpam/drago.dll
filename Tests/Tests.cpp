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
	
}

void matrix_building_tests(Matrix4x4 printme) {
	for (int i = 0; i < 16; i++) {
		cout << printme.asArray[i] << " ";
		if (i % 4 == 3)
			cout << "\n";
	}
}

void matrix_transform_tests() {
	Matrix4x4 transform = Matrix4x4::Transform(10, 10, 10, 15, 20, 30, 1, 2, 1);
	Vector4 point;
	point.x = 5;
	point.y = 5;
	point.z = 0;
	point.w = 1;

	point = transform * point;

	cout << "Transform matrix:\n";

	matrix_building_tests(transform);

	cout << "\nFinal position:\n";

	cout << point.x << ", " << point.y << ", " << point.z;

	cout << endl;
}

int main() {
	Matrix4x4 translate = Matrix4x4::Transform(10, 10, 10, 0, 0, 0, 1, 1, 1);
	Matrix4x4 rotate = Matrix4x4::Transform(0, 0, 0, 15, 20, 30, 1, 1, 1);
	Matrix4x4 scale = Matrix4x4::Transform(0, 0, 0, 0, 0, 0, 1, 2, 1);

	cout << "rotate scale translate" << endl;

	matrix_building_tests((rotate * scale) * translate);

	cout << "scale rotate translate" << endl;

	matrix_building_tests((scale * rotate) * translate);
	return 0;
}