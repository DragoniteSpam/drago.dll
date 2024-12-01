#include "Shapes.h"

class ShapeTriangle : Shape {
private:
	Vector3* a;
	Vector3* b;
	Vector3* c;
public:
	void Set(const Vector3* a, const Vector3* b, const Vector3* c) {
		this->a->Set(a);
		this->b->Set(b);
		this->c->Set(c);
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