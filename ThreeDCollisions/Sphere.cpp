#include "Shapes.h"

void ShapeSphere::Set(const Vector3* position, float radius) {
	this->position->Set(position);
	this->radius = radius;
}

bool ShapeSphere::CheckPoint(const ShapePoint* point) const {
	return point->CheckSphere(this);
}
bool ShapeSphere::CheckSphere(const ShapeSphere* sphere) const {
	return this->position->Distance(sphere->position) <= (this->radius + sphere->radius);
}
bool ShapeSphere::CheckAABB(const ShapeAABB* aabb) const {
	return true;
}
bool ShapeSphere::CheckOBB(const ShapeOBB* obb) const {
	return true;
}
bool ShapeSphere::CheckPlane(const ShapePlane* plane) const {
	return true;
}
bool ShapeSphere::CheckCapsule(const ShapeCapsule* capsule) const {
	return true;
}
bool ShapeSphere::CheckTriangle(const ShapeTriangle* triangle) const {
	return true;
}
bool ShapeSphere::CheckMesh(const ShapeMesh* mesh) const {
	return true;
}
bool ShapeSphere::CheckModel(const ShapeModel* model) const {
	return true;
}
bool ShapeSphere::CheckLine(const ShapeLine* line) const {
	return true;
}
bool ShapeSphere::CheckRay(const ShapeRay* ray) const {
	return true;
}