#pragma once

#include "main/dragomath.h"

class Shape {
public:
	virtual bool CheckPoint(const ShapePoint* point) const { return true; }
	virtual bool CheckSphere(const ShapeSphere* point) const { return true; }
	virtual bool CheckAABB(const ShapeAABB* point) const { return true; }
	virtual bool CheckOBB(const ShapeOBB* point) const { return true; }
	virtual bool CheckPlane(const ShapePlane* point) const { return true; }
	virtual bool CheckCapsule(const ShapeCapsule* point) const { return true; }
	virtual bool CheckTriangle(const ShapeTriangle* point) const { return true; }
	virtual bool CheckMesh(const ShapeMesh* point) const { return true; }
	virtual bool CheckModel(const ShapeModel* point) const { return true; }
	virtual bool CheckLine(const ShapeLine* point) const { return true; }
	virtual bool CheckRay(const ShapeRay* point) const { return true; }
};

class ShapePoint: Shape {
public:
	bool CheckPoint(const ShapePoint* point) const override;
	bool CheckSphere(const ShapeSphere* point) const override;
	bool CheckAABB(const ShapeAABB* point) const override;
	bool CheckOBB(const ShapeOBB* point) const override;
	bool CheckPlane(const ShapePlane* point) const override;
	bool CheckCapsule(const ShapeCapsule* point) const override;
	bool CheckTriangle(const ShapeTriangle* point) const override;
	bool CheckMesh(const ShapeMesh* point) const override;
	bool CheckModel(const ShapeModel* point) const override;
	bool CheckLine(const ShapeLine* point) const override;
	bool CheckRay(const ShapeRay* point) const override;
};

class ShapeSphere: Shape {
public:
	bool CheckPoint(const ShapePoint* point) const override;
	bool CheckSphere(const ShapeSphere* point) const override;
	bool CheckAABB(const ShapeAABB* point) const override;
	bool CheckOBB(const ShapeOBB* point) const override;
	bool CheckPlane(const ShapePlane* point) const override;
	bool CheckCapsule(const ShapeCapsule* point) const override;
	bool CheckTriangle(const ShapeTriangle* point) const override;
	bool CheckMesh(const ShapeMesh* point) const override;
	bool CheckModel(const ShapeModel* point) const override;
	bool CheckLine(const ShapeLine* point) const override;
	bool CheckRay(const ShapeRay* point) const override;
};

class ShapeAABB: Shape {
public:
	bool CheckPoint(const ShapePoint* point) const override;
	bool CheckSphere(const ShapeSphere* point) const override;
	bool CheckAABB(const ShapeAABB* point) const override;
	bool CheckOBB(const ShapeOBB* point) const override;
	bool CheckPlane(const ShapePlane* point) const override;
	bool CheckCapsule(const ShapeCapsule* point) const override;
	bool CheckTriangle(const ShapeTriangle* point) const override;
	bool CheckMesh(const ShapeMesh* point) const override;
	bool CheckModel(const ShapeModel* point) const override;
	bool CheckLine(const ShapeLine* point) const override;
	bool CheckRay(const ShapeRay* point) const override;
};

class ShapeOBB: Shape {
public:
	bool CheckPoint(const ShapePoint* point) const override;
	bool CheckSphere(const ShapeSphere* point) const override;
	bool CheckAABB(const ShapeAABB* point) const override;
	bool CheckOBB(const ShapeOBB* point) const override;
	bool CheckPlane(const ShapePlane* point) const override;
	bool CheckCapsule(const ShapeCapsule* point) const override;
	bool CheckTriangle(const ShapeTriangle* point) const override;
	bool CheckMesh(const ShapeMesh* point) const override;
	bool CheckModel(const ShapeModel* point) const override;
	bool CheckLine(const ShapeLine* point) const override;
	bool CheckRay(const ShapeRay* point) const override;
};

class ShapePlane: Shape {
public:
	bool CheckPoint(const ShapePoint* point) const override;
	bool CheckSphere(const ShapeSphere* point) const override;
	bool CheckAABB(const ShapeAABB* point) const override;
	bool CheckOBB(const ShapeOBB* point) const override;
	bool CheckPlane(const ShapePlane* point) const override;
	bool CheckCapsule(const ShapeCapsule* point) const override;
	bool CheckTriangle(const ShapeTriangle* point) const override;
	bool CheckMesh(const ShapeMesh* point) const override;
	bool CheckModel(const ShapeModel* point) const override;
	bool CheckLine(const ShapeLine* point) const override;
	bool CheckRay(const ShapeRay* point) const override;
};

class ShapeCapsule: Shape {
public:
	bool CheckPoint(const ShapePoint* point) const override;
	bool CheckSphere(const ShapeSphere* point) const override;
	bool CheckAABB(const ShapeAABB* point) const override;
	bool CheckOBB(const ShapeOBB* point) const override;
	bool CheckPlane(const ShapePlane* point) const override;
	bool CheckCapsule(const ShapeCapsule* point) const override;
	bool CheckTriangle(const ShapeTriangle* point) const override;
	bool CheckMesh(const ShapeMesh* point) const override;
	bool CheckModel(const ShapeModel* point) const override;
	bool CheckLine(const ShapeLine* point) const override;
	bool CheckRay(const ShapeRay* point) const override;
};

class ShapeTriangle: Shape {
public:
	bool CheckPoint(const ShapePoint* point) const override;
	bool CheckSphere(const ShapeSphere* point) const override;
	bool CheckAABB(const ShapeAABB* point) const override;
	bool CheckOBB(const ShapeOBB* point) const override;
	bool CheckPlane(const ShapePlane* point) const override;
	bool CheckCapsule(const ShapeCapsule* point) const override;
	bool CheckTriangle(const ShapeTriangle* point) const override;
	bool CheckMesh(const ShapeMesh* point) const override;
	bool CheckModel(const ShapeModel* point) const override;
	bool CheckLine(const ShapeLine* point) const override;
	bool CheckRay(const ShapeRay* point) const override;
};

class ShapeMesh: Shape {
public:
	bool CheckPoint(const ShapePoint* point) const override;
	bool CheckSphere(const ShapeSphere* point) const override;
	bool CheckAABB(const ShapeAABB* point) const override;
	bool CheckOBB(const ShapeOBB* point) const override;
	bool CheckPlane(const ShapePlane* point) const override;
	bool CheckCapsule(const ShapeCapsule* point) const override;
	bool CheckTriangle(const ShapeTriangle* point) const override;
	bool CheckMesh(const ShapeMesh* point) const override;
	bool CheckModel(const ShapeModel* point) const override;
	bool CheckLine(const ShapeLine* point) const override;
	bool CheckRay(const ShapeRay* point) const override;
};

class ShapeModel: Shape {
public:
	bool CheckPoint(const ShapePoint* point) const override;
	bool CheckSphere(const ShapeSphere* point) const override;
	bool CheckAABB(const ShapeAABB* point) const override;
	bool CheckOBB(const ShapeOBB* point) const override;
	bool CheckPlane(const ShapePlane* point) const override;
	bool CheckCapsule(const ShapeCapsule* point) const override;
	bool CheckTriangle(const ShapeTriangle* point) const override;
	bool CheckMesh(const ShapeMesh* point) const override;
	bool CheckModel(const ShapeModel* point) const override;
	bool CheckLine(const ShapeLine* point) const override;
	bool CheckRay(const ShapeRay* point) const override;
};

class ShapeRay: Shape {
public:
	bool CheckPoint(const ShapePoint* point) const override;
	bool CheckSphere(const ShapeSphere* point) const override;
	bool CheckAABB(const ShapeAABB* point) const override;
	bool CheckOBB(const ShapeOBB* point) const override;
	bool CheckPlane(const ShapePlane* point) const override;
	bool CheckCapsule(const ShapeCapsule* point) const override;
	bool CheckTriangle(const ShapeTriangle* point) const override;
	bool CheckMesh(const ShapeMesh* point) const override;
	bool CheckModel(const ShapeModel* point) const override;
	bool CheckLine(const ShapeLine* point) const override;
	bool CheckRay(const ShapeRay* point) const override;
};

class ShapeLine: Shape {
public:
	bool CheckPoint(const ShapePoint* point) const override;
	bool CheckSphere(const ShapeSphere* point) const override;
	bool CheckAABB(const ShapeAABB* point) const override;
	bool CheckOBB(const ShapeOBB* point) const override;
	bool CheckPlane(const ShapePlane* point) const override;
	bool CheckCapsule(const ShapeCapsule* point) const override;
	bool CheckTriangle(const ShapeTriangle* point) const override;
	bool CheckMesh(const ShapeMesh* point) const override;
	bool CheckModel(const ShapeModel* point) const override;
	bool CheckLine(const ShapeLine* point) const override;
	bool CheckRay(const ShapeRay* point) const override;
};