#include "Shapes.h"

void ShapeOBB::Set(const Vector3* position, const Vector3* size, const Matrix4x4* orientation) {
	this->position->Set(position);
	this->size->Set(size);
	this->orientation->Set(orientation);
}

bool ShapeOBB::CheckPoint(const ShapePoint* point) const {
	return true;
}
bool ShapeOBB::CheckSphere(const ShapeSphere* sphere) const {
	return true;
}
bool ShapeOBB::CheckAABB(const ShapeAABB* aabb) const {
	return true;
}
bool ShapeOBB::CheckOBB(const ShapeOBB* obb) const {
	return true;
}
bool ShapeOBB::CheckPlane(const ShapePlane* plane) const {
	return true;
}
bool ShapeOBB::CheckCapsule(const ShapeCapsule* capsule) const {
	return true;
}
bool ShapeOBB::CheckTriangle(const ShapeTriangle* triangle) const {
	return true;
}
bool ShapeOBB::CheckMesh(const ShapeMesh* mesh) const {
	return true;
}
bool ShapeOBB::CheckModel(const ShapeModel* model) const {
	return true;
}
bool ShapeOBB::CheckLine(const ShapeLine* line) const {
	return true;
}
bool ShapeOBB::CheckRay(const ShapeRay* ray) const {
	return true;
}