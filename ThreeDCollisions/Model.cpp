#include "Shapes.h"

bool ShapeModel::CheckPoint(const ShapePoint* point) const {
	return true;
}
bool ShapeModel::CheckSphere(const ShapeSphere* sphere) const {
	return true;
}
bool ShapeModel::CheckAABB(const ShapeAABB* aabb) const {
	return true;
}
bool ShapeModel::CheckOBB(const ShapeOBB* obb) const {
	return true;
}
bool ShapeModel::CheckPlane(const ShapePlane* plane) const {
	return true;
}
bool ShapeModel::CheckCapsule(const ShapeCapsule* capsule) const {
	return true;
}
bool ShapeModel::CheckTriangle(const ShapeTriangle* triangle) const {
	return true;
}
bool ShapeModel::CheckMesh(const ShapeMesh* mesh) const {
	return true;
}
bool ShapeModel::CheckModel(const ShapeModel* model) const {
	return true;
}
bool ShapeModel::CheckLine(const ShapeLine* line) const {
	return true;
}
bool ShapeModel::CheckRay(const ShapeRay* ray) const {
	return true;
}