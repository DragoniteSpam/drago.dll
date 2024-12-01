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

	bool CheckPoint(const ShapePoint* point) override {
		return true;
	}
	bool CheckSphere(const ShapeSphere* point) override {
		return true;
	}
	bool CheckAABB(const ShapeAABB* point) override {
		return true;
	}
	bool CheckOBB(const ShapeOBB* point) override {
		return true;
	}
	bool CheckPlane(const ShapePlane* point) override {
		return true;
	}
	bool CheckCapsule(const ShapeCapsule* point) override {
		return true;
	}
	bool CheckTriangle(const ShapeTriangle* point) override {
		return true;
	}
	bool CheckMesh(const ShapeMesh* point) override {
		return true;
	}
	bool CheckModel(const ShapeModel* point) override {
		return true;
	}
	bool CheckLine(const ShapeLine* point) override {
		return true;
	}
	bool CheckRay(const ShapeRay* point) override {
		return true;
	}
};