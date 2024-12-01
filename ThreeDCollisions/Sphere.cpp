#include "Shapes.h"

class ShapeSphere : Shape {
private:
	Vector3* position;
	float radius;
public:
	void Set(const Vector3* position, float radius) {
		this->position->Set(position);
		this->radius = radius;
	}

	bool CheckPoint(const ShapePoint* point) const override {
		return true;
	}
	bool CheckSphere(const ShapeSphere* point) const override {
		return true;
	}
	bool CheckAABB(const ShapeAABB* point) const override {
		return true;
	}
	bool CheckOBB(const ShapeOBB* point) const override {
		return true;
	}
	bool CheckPlane(const ShapePlane* point) const override {
		return true;
	}
	bool CheckCapsule(const ShapeCapsule* point) const override {
		return true;
	}
	bool CheckTriangle(const ShapeTriangle* point) const override {
		return true;
	}
	bool CheckMesh(const ShapeMesh* point) const override {
		return true;
	}
	bool CheckModel(const ShapeModel* point) const override {
		return true;
	}
	bool CheckLine(const ShapeLine* point) const override {
		return true;
	}
	bool CheckRay(const ShapeRay* point) const override {
		return true;
	}
};