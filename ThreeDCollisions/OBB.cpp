#include "Shapes.h"

class ShapeOBB : Shape {
private:
	Vector3* position;
	Vector3* size;
	Matrix4x4* orientation;
public:
	void Set(const Vector3* position, const Vector3* size, const Matrix4x4* orientation) {
		this->position->Set(position);
		this->size->Set(size);
		this->orientation->Set(orientation);
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