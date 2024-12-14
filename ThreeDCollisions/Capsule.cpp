#include "Shapes.h"

void ShapeCapsule::Set(const ShapeLine* line, float radius) {
	this->line->Set(line->start, line->end);
	this->radius = radius;
}

bool ShapeCapsule::CheckPoint(const ShapePoint* point) const {
	return true;
}
bool ShapeCapsule::CheckSphere(const ShapeSphere* sphere) const {
	return true;
}
bool ShapeCapsule::CheckAABB(const ShapeAABB* aabb) const {
	return true;
}
bool ShapeCapsule::CheckOBB(const ShapeOBB* obb) const {
	return true;
}
bool ShapeCapsule::CheckPlane(const ShapePlane* plane) const {
	return true;
}
bool ShapeCapsule::CheckCapsule(const ShapeCapsule* capsule) const {
	return true;
}
bool ShapeCapsule::CheckTriangle(const ShapeTriangle* triangle) const {
	return true;
}
bool ShapeCapsule::CheckMesh(const ShapeMesh* mesh) const {
	return true;
}
bool ShapeCapsule::CheckModel(const ShapeModel* model) const {
	return true;
}
bool ShapeCapsule::CheckLine(const ShapeLine* line) const {
	return true;
}
bool ShapeCapsule::CheckRay(const ShapeRay* ray) const {
	return true;
}