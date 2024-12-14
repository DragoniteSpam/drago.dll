#include "Shapes.h"

void ShapePlane::Set(const Vector3* normal, float distance) {
	this->normal->Set(normal);
	this->distance = distance;
}

bool ShapePlane::CheckPoint(const ShapePoint* point) const {
	return true;
}
bool ShapePlane::CheckSphere(const ShapeSphere* sphere) const {
	return true;
}
bool ShapePlane::CheckAABB(const ShapeAABB* aabb) const {
	return true;
}
bool ShapePlane::CheckOBB(const ShapeOBB* obb) const {
	return true;
}
bool ShapePlane::CheckPlane(const ShapePlane* plane) const {
	return true;
}
bool ShapePlane::CheckCapsule(const ShapeCapsule* capsule) const {
	return true;
}
bool ShapePlane::CheckTriangle(const ShapeTriangle* triangle) const {
	return true;
}
bool ShapePlane::CheckMesh(const ShapeMesh* mesh) const {
	return true;
}
bool ShapePlane::CheckModel(const ShapeModel* model) const {
	return true;
}
bool ShapePlane::CheckLine(const ShapeLine* line) const {
	return true;
}
bool ShapePlane::CheckRay(const ShapeRay* ray) const {
	return true;
}