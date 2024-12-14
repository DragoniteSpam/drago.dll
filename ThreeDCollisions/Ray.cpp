#include "Shapes.h"

void ShapeRay::Set(const Vector3* position, const Vector3* direction) {
	this->position->Set(position);
	this->direction->Set(direction);
}

bool ShapeRay::CheckPoint(const ShapePoint* point) const {
	return true;
}
bool ShapeRay::CheckSphere(const ShapeSphere* sphere) const {
	return true;
}
bool ShapeRay::CheckAABB(const ShapeAABB* aabb) const {
	return true;
}
bool ShapeRay::CheckOBB(const ShapeOBB* obb) const {
	return true;
}
bool ShapeRay::CheckPlane(const ShapePlane* plane) const {
	return true;
}
bool ShapeRay::CheckCapsule(const ShapeCapsule* capsule) const {
	return true;
}
bool ShapeRay::CheckTriangle(const ShapeTriangle* triangle) const {
	return true;
}
bool ShapeRay::CheckMesh(const ShapeMesh* mesh) const {
	return true;
}
bool ShapeRay::CheckModel(const ShapeModel* model) const {
	return true;
}
bool ShapeRay::CheckLine(const ShapeLine* line) const {
	return true;
}
bool ShapeRay::CheckRay(const ShapeRay* ray) const {
	return true;
}