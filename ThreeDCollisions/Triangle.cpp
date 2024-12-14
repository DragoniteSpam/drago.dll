#include "Shapes.h"

void ShapeTriangle::Set(const Vector3* a, const Vector3* b, const Vector3* c) {
	this->a->Set(a);
	this->b->Set(b);
	this->c->Set(c);
}

bool ShapeTriangle::CheckPoint(const ShapePoint* point) const {
	return true;
}
bool ShapeTriangle::CheckSphere(const ShapeSphere* sphere) const {
	return true;
}
bool ShapeTriangle::CheckAABB(const ShapeAABB* aabb) const {
	return true;
}
bool ShapeTriangle::CheckOBB(const ShapeOBB* obb) const {
	return true;
}
bool ShapeTriangle::CheckPlane(const ShapePlane* plane) const {
	return true;
}
bool ShapeTriangle::CheckCapsule(const ShapeCapsule* capsule) const {
	return true;
}
bool ShapeTriangle::CheckTriangle(const ShapeTriangle* triangle) const {
	return true;
}
bool ShapeTriangle::CheckMesh(const ShapeMesh* mesh) const {
	return true;
}
bool ShapeTriangle::CheckModel(const ShapeModel* model) const {
	return true;
}
bool ShapeTriangle::CheckLine(const ShapeLine* line) const {
	return true;
}
bool ShapeTriangle::CheckRay(const ShapeRay* ray) const {
	return true;
}