#include "Shapes.h"

class ShapeLine : Shape {
public:
	Vector3* start;
	Vector3* end;

	void Set(const Vector3* start, const Vector3* end) {
		this->start->Set(start);
		this->end->Set(end);
	}

	bool CheckPoint(const ShapePoint* point) const override {
		return true;
	}
	bool CheckSphere(const ShapeSphere* sphere) const override {
		return true;
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