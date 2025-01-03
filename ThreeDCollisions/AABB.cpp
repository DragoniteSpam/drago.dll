#include "Shapes.h"

void ShapeAABB::Set(const Vector3* position, const Vector3* half) {
	this->position->Set(position);
	this->half->Set(half);
}

bool ShapeAABB::CheckPoint(const ShapePoint* point) const {
	return true;
}
bool ShapeAABB::CheckSphere(const ShapeSphere* sphere) const {
	return true;
}
bool ShapeAABB::CheckAABB(const ShapeAABB* aabb) const {
	return true;
}
bool ShapeAABB::CheckOBB(const ShapeOBB* obb) const {
	return true;
}
bool ShapeAABB::CheckPlane(const ShapePlane* plane) const {
	return true;
}
bool ShapeAABB::CheckCapsule(const ShapeCapsule* capsule) const {
	return true;
}
bool ShapeAABB::CheckTriangle(const ShapeTriangle* triangle) const {
	return true;
}
bool ShapeAABB::CheckMesh(const ShapeMesh* mesh) const {
	return true;
}
bool ShapeAABB::CheckModel(const ShapeModel* model) const {
	return true;
}
bool ShapeAABB::CheckLine(const ShapeLine* line) const {
	return true;
}
bool ShapeAABB::CheckRay(const ShapeRay* ray) const {
	return true;
}