#include "Shapes.h"

class ShapeLine : Shape {
private:
	Vector3* position;
	Vector3* direction;
public:
	void Set(const Vector3* position, const Vector3* direction) {
		this->position->Set(position);
		this->direction->Set(direction);
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