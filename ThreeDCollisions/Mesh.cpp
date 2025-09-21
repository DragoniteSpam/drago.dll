#include "Shapes.h"

bool ShapeMesh::CheckPoint(const ShapePoint* point) const {
	return true;
}
bool ShapeMesh::CheckSphere(const ShapeSphere* sphere) const {
	return true;
}
bool ShapeMesh::CheckAABB(const ShapeAABB* aabb) const {
	return true;
}
bool ShapeMesh::CheckOBB(const ShapeOBB* obb) const {
	return true;
}
bool ShapeMesh::CheckPlane(const ShapePlane* plane) const {
	return true;
}
bool ShapeMesh::CheckCapsule(const ShapeCapsule* capsule) const {
	return true;
}
bool ShapeMesh::CheckTriangle(const ShapeTriangle* triangle) const {
	return true;
}
bool ShapeMesh::CheckMesh(const ShapeMesh* mesh) const {
	return true;
}
bool ShapeMesh::CheckModel(const ShapeModel* model) const {
	return true;
}
bool ShapeMesh::CheckLine(const ShapeLine* line) const {
	return true;
}
bool ShapeMesh::CheckRay(const ShapeRay* ray) const {
	return true;
}