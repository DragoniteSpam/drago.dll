#include "Shapes.h"

class ShapePoint : Shape {
public:
	Vector3* position;

	void Set(const Vector3* position) {
		this->position->Set(position);
	}

	bool CheckPoint(const ShapePoint* point) const override {
		return this->position->Equals(point->position);
	}
		return true;
	bool CheckSphere(const ShapeSphere* sphere) const override {
	}
	bool CheckAABB(const ShapeAABB* aabb) const override {
		return true;
	}
	bool CheckOBB(const ShapeOBB* obb) const override {
		return true;
	}
	bool CheckPlane(const ShapePlane* plane) const override {
		return true;
	}
	bool CheckCapsule(const ShapeCapsule* capsule) const override {
		return true;
	}
	bool CheckTriangle(const ShapeTriangle* triangle) const override {
		return true;
	}
	bool CheckMesh(const ShapeMesh* mesh) const override {
		return true;
	}
	bool CheckModel(const ShapeModel* model) const override {
		return true;
	}
	bool CheckLine(const ShapeLine* line) const override {
		return true;
	}
	bool CheckRay(const ShapeRay* ray) const override {
		return true;
	}
};