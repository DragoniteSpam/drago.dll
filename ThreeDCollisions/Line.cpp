#include "Shapes.h"

void ShapeLine::Set(const Vector3* start, const Vector3* end) {
	this->start->Set(start);
	this->end->Set(end);
}

bool ShapeLine::CheckPoint(const ShapePoint* point) const {
	return true;
}
bool ShapeLine::CheckSphere(const ShapeSphere* sphere) const {
	return true;
}
bool ShapeLine::CheckAABB(const ShapeAABB* aabb) const {
	return true;
}
bool ShapeLine::CheckOBB(const ShapeOBB* obb) const {
	return true;
}
bool ShapeLine::CheckPlane(const ShapePlane* plane) const {
	return true;
}
bool ShapeLine::CheckCapsule(const ShapeCapsule* capsule) const {
	return true;
}
bool ShapeLine::CheckTriangle(const ShapeTriangle* triangle) const {
	return true;
}
bool ShapeLine::CheckMesh(const ShapeMesh* mesh) const {
	return true;
}
bool ShapeLine::CheckModel(const ShapeModel* model) const {
	return true;
}
bool ShapeLine::CheckLine(const ShapeLine* line) const {
	return true;
}
bool ShapeLine::CheckRay(const ShapeRay* ray) const {
	return true;
}