#pragma once

#include "main/dragomath.h"

class ShapePoint;
class ShapeSphere;
class ShapeSphere;
class ShapeAABB;
class ShapeOBB;
class ShapePlane;
class ShapeTriangle;
class ShapeMesh;
class ShapeModel;
class ShapeCapsule;
class ShapeRay;
class ShapeLine;

class Shape {
public:
	virtual bool CheckPoint(const ShapePoint* point) const = 0;
	virtual bool CheckSphere(const ShapeSphere* sphere) const = 0;
	virtual bool CheckAABB(const ShapeAABB* aabb) const = 0;
	virtual bool CheckOBB(const ShapeOBB* obb) const = 0;
	virtual bool CheckPlane(const ShapePlane* plane) const = 0;
	virtual bool CheckCapsule(const ShapeCapsule* capsule) const = 0;
	virtual bool CheckTriangle(const ShapeTriangle* triangle) const = 0;
	virtual bool CheckMesh(const ShapeMesh* mesh) const = 0;
	virtual bool CheckModel(const ShapeModel* model) const = 0;
	virtual bool CheckLine(const ShapeLine* line) const = 0;
	virtual bool CheckRay(const ShapeRay* ray) const = 0;
};

class ShapePoint: Shape {
public:
	Vector3* position;
	void Set(const Vector3* position);
	bool CheckPoint(const ShapePoint* point) const override;
	bool CheckSphere(const ShapeSphere* sphere) const override;
	bool CheckAABB(const ShapeAABB* aabb) const override;
	bool CheckOBB(const ShapeOBB* obb) const override;
	bool CheckPlane(const ShapePlane* plane) const override;
	bool CheckCapsule(const ShapeCapsule* capsule) const override;
	bool CheckTriangle(const ShapeTriangle* triangle) const override;
	bool CheckMesh(const ShapeMesh* mesh) const override;
	bool CheckModel(const ShapeModel* model) const override;
	bool CheckLine(const ShapeLine* line) const override;
	bool CheckRay(const ShapeRay* ray) const override;
};

class ShapeSphere: Shape {
public:
	Vector3* position;
	float radius;
	void Set(const Vector3* position, float radius);
	bool CheckPoint(const ShapePoint* point) const override;
	bool CheckSphere(const ShapeSphere* sphere) const override;
	bool CheckAABB(const ShapeAABB* aabb) const override;
	bool CheckOBB(const ShapeOBB* obb) const override;
	bool CheckPlane(const ShapePlane* plane) const override;
	bool CheckCapsule(const ShapeCapsule* capsule) const override;
	bool CheckTriangle(const ShapeTriangle* triangle) const override;
	bool CheckMesh(const ShapeMesh* mesh) const override;
	bool CheckModel(const ShapeModel* model) const override;
	bool CheckLine(const ShapeLine* line) const override;
	bool CheckRay(const ShapeRay* ray) const override;
};

class ShapeAABB: Shape {
public:
	Vector3* position;
	Vector3* half;
	void Set(const Vector3* position, const Vector3* half);
	bool CheckPoint(const ShapePoint* point) const override;
	bool CheckSphere(const ShapeSphere* sphere) const override;
	bool CheckAABB(const ShapeAABB* aabb) const override;
	bool CheckOBB(const ShapeOBB* obb) const override;
	bool CheckPlane(const ShapePlane* plane) const override;
	bool CheckCapsule(const ShapeCapsule* capsule) const override;
	bool CheckTriangle(const ShapeTriangle* triangle) const override;
	bool CheckMesh(const ShapeMesh* mesh) const override;
	bool CheckModel(const ShapeModel* model) const override;
	bool CheckLine(const ShapeLine* line) const override;
	bool CheckRay(const ShapeRay* ray) const override;
};

class ShapeOBB: Shape {
public:
	Vector3* position;
	Vector3* size;
	Matrix4x4* orientation;
	void Set(const Vector3* position, const Vector3* size, const Matrix4x4* orientation);
	bool CheckPoint(const ShapePoint* point) const override;
	bool CheckSphere(const ShapeSphere* sphere) const override;
	bool CheckAABB(const ShapeAABB* aabb) const override;
	bool CheckOBB(const ShapeOBB* obb) const override;
	bool CheckPlane(const ShapePlane* plane) const override;
	bool CheckCapsule(const ShapeCapsule* capsule) const override;
	bool CheckTriangle(const ShapeTriangle* triangle) const override;
	bool CheckMesh(const ShapeMesh* mesh) const override;
	bool CheckModel(const ShapeModel* model) const override;
	bool CheckLine(const ShapeLine* line) const override;
	bool CheckRay(const ShapeRay* ray) const override;
};

class ShapePlane: Shape {
public:
	Vector3* normal;
	float distance;
	void Set(const Vector3* normal, float distance);
	bool CheckPoint(const ShapePoint* point) const override;
	bool CheckSphere(const ShapeSphere* sphere) const override;
	bool CheckAABB(const ShapeAABB* aabb) const override;
	bool CheckOBB(const ShapeOBB* obb) const override;
	bool CheckPlane(const ShapePlane* plane) const override;
	bool CheckCapsule(const ShapeCapsule* capsule) const override;
	bool CheckTriangle(const ShapeTriangle* triangle) const override;
	bool CheckMesh(const ShapeMesh* mesh) const override;
	bool CheckModel(const ShapeModel* model) const override;
	bool CheckLine(const ShapeLine* line) const override;
	bool CheckRay(const ShapeRay* ray) const override;
};

class ShapeCapsule: Shape {
public:
	ShapeLine* line;
	float radius;
	void Set(const ShapeLine* line, float radius);
	bool CheckPoint(const ShapePoint* point) const override;
	bool CheckSphere(const ShapeSphere* sphere) const override;
	bool CheckAABB(const ShapeAABB* aabb) const override;
	bool CheckOBB(const ShapeOBB* obb) const override;
	bool CheckPlane(const ShapePlane* plane) const override;
	bool CheckCapsule(const ShapeCapsule* capsule) const override;
	bool CheckTriangle(const ShapeTriangle* triangle) const override;
	bool CheckMesh(const ShapeMesh* mesh) const override;
	bool CheckModel(const ShapeModel* model) const override;
	bool CheckLine(const ShapeLine* line) const override;
	bool CheckRay(const ShapeRay* ray) const override;
};

class ShapeTriangle: Shape {
public:
	Vector3* a;
	Vector3* b;
	Vector3* c;
	void Set(const Vector3* a, const Vector3* b, const Vector3* c);
	bool CheckPoint(const ShapePoint* point) const override;
	bool CheckSphere(const ShapeSphere* sphere) const override;
	bool CheckAABB(const ShapeAABB* aabb) const override;
	bool CheckOBB(const ShapeOBB* obb) const override;
	bool CheckPlane(const ShapePlane* plane) const override;
	bool CheckCapsule(const ShapeCapsule* capsule) const override;
	bool CheckTriangle(const ShapeTriangle* triangle) const override;
	bool CheckMesh(const ShapeMesh* mesh) const override;
	bool CheckModel(const ShapeModel* model) const override;
	bool CheckLine(const ShapeLine* line) const override;
	bool CheckRay(const ShapeRay* ray) const override;
};

class ShapeMesh: Shape {
public:
	bool CheckPoint(const ShapePoint* point) const override;
	bool CheckSphere(const ShapeSphere* sphere) const override;
	bool CheckAABB(const ShapeAABB* aabb) const override;
	bool CheckOBB(const ShapeOBB* obb) const override;
	bool CheckPlane(const ShapePlane* plane) const override;
	bool CheckCapsule(const ShapeCapsule* capsule) const override;
	bool CheckTriangle(const ShapeTriangle* triangle) const override;
	bool CheckMesh(const ShapeMesh* mesh) const override;
	bool CheckModel(const ShapeModel* model) const override;
	bool CheckLine(const ShapeLine* line) const override;
	bool CheckRay(const ShapeRay* ray) const override;
};

class ShapeModel: Shape {
public:
	bool CheckPoint(const ShapePoint* point) const override;
	bool CheckSphere(const ShapeSphere* sphere) const override;
	bool CheckAABB(const ShapeAABB* aabb) const override;
	bool CheckOBB(const ShapeOBB* obb) const override;
	bool CheckPlane(const ShapePlane* plane) const override;
	bool CheckCapsule(const ShapeCapsule* capsule) const override;
	bool CheckTriangle(const ShapeTriangle* triangle) const override;
	bool CheckMesh(const ShapeMesh* mesh) const override;
	bool CheckModel(const ShapeModel* model) const override;
	bool CheckLine(const ShapeLine* line) const override;
	bool CheckRay(const ShapeRay* ray) const override;
};

class ShapeRay: Shape {
public:
	Vector3* position;
	Vector3* direction;
	void Set(const Vector3* position, const Vector3* direction);
	bool CheckPoint(const ShapePoint* point) const override;
	bool CheckSphere(const ShapeSphere* sphere) const override;
	bool CheckAABB(const ShapeAABB* aabb) const override;
	bool CheckOBB(const ShapeOBB* obb) const override;
	bool CheckPlane(const ShapePlane* plane) const override;
	bool CheckCapsule(const ShapeCapsule* capsule) const override;
	bool CheckTriangle(const ShapeTriangle* triangle) const override;
	bool CheckMesh(const ShapeMesh* mesh) const override;
	bool CheckModel(const ShapeModel* model) const override;
	bool CheckLine(const ShapeLine* line) const override;
	bool CheckRay(const ShapeRay* ray) const override;
};

class ShapeLine: Shape {
public:
	Vector3* start;
	Vector3* end;
	void Set(const Vector3* start, const Vector3* end);
	bool CheckPoint(const ShapePoint* point) const override;
	bool CheckSphere(const ShapeSphere* sphere) const override;
	bool CheckAABB(const ShapeAABB* aabb) const override;
	bool CheckOBB(const ShapeOBB* obb) const override;
	bool CheckPlane(const ShapePlane* plane) const override;
	bool CheckCapsule(const ShapeCapsule* capsule) const override;
	bool CheckTriangle(const ShapeTriangle* triangle) const override;
	bool CheckMesh(const ShapeMesh* mesh) const override;
	bool CheckModel(const ShapeModel* model) const override;
	bool CheckLine(const ShapeLine* line) const override;
	bool CheckRay(const ShapeRay* ray) const override;
};