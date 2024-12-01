#pragma once

#include "main/dragomath.h"

class Shape {
public:
	virtual bool CheckPoint(const ShapePoint* point) const { return true; }
	virtual bool CheckSphere(const ShapeSphere* sphere) const { return true; }
	virtual bool CheckAABB(const ShapeAABB* aabb) const { return true; }
	virtual bool CheckOBB(const ShapeOBB* obb) const { return true; }
	virtual bool CheckPlane(const ShapePlane* plane) const { return true; }
	virtual bool CheckCapsule(const ShapeCapsule* capsule) const { return true; }
	virtual bool CheckTriangle(const ShapeTriangle* triangle) const { return true; }
	virtual bool CheckMesh(const ShapeMesh* mesh) const { return true; }
	virtual bool CheckModel(const ShapeModel* model) const { return true; }
	virtual bool CheckLine(const ShapeLine* line) const { return true; }
	virtual bool CheckRay(const ShapeRay* ray) const { return true; }
};

class ShapePoint: Shape {
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

class ShapeSphere: Shape {
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

class ShapeAABB: Shape {
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

class ShapeOBB: Shape {
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

class ShapePlane: Shape {
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

class ShapeCapsule: Shape {
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

class ShapeTriangle: Shape {
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