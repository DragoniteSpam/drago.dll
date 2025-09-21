#include "Shapes.h"

void ShapePoint::Set(const Vector3* position) {
	this->position->Set(position);
}

bool ShapePoint::CheckPoint(const ShapePoint* point) const {
	return this->position->Equals(point->position);
}
bool ShapePoint::CheckSphere(const ShapeSphere* sphere) const {
	return this->position->Distance(sphere->position) <= sphere->radius;
}
bool ShapePoint::CheckAABB(const ShapeAABB* aabb) const {
	return
		this->position->x >= aabb->min->x &&
		this->position->x <= aabb->max->x &&
		this->position->y >= aabb->min->y &&
		this->position->y <= aabb->max->y &&
		this->position->z >= aabb->min->z &&
		this->position->z <= aabb->max->z;
}
bool ShapePoint::CheckOBB(const ShapeOBB* obb) const {
	return true;
}
bool ShapePoint::CheckPlane(const ShapePlane* plane) const {
	return fabsf(this->position->Dot(plane->normal) - 0.0f) <= 0.000000001f;
}
bool ShapePoint::CheckCapsule(const ShapeCapsule* capsule) const {
	return true;
}
bool ShapePoint::CheckTriangle(const ShapeTriangle* triangle) const {
	return true;
}
bool ShapePoint::CheckMesh(const ShapeMesh* mesh) const {
	return true;
}
bool ShapePoint::CheckModel(const ShapeModel* model) const {
	return true;
}
bool ShapePoint::CheckLine(const ShapeLine* line) const {
	return true;
}
bool ShapePoint::CheckRay(const ShapeRay* ray) const {
	return true;
}