#pragma once

#include "main/dragomath.h"

class Shape {
public:
	virtual bool CheckPoint(const ShapePoint* point);
	virtual bool CheckSphere(const ShapeSphere* point);
	virtual bool CheckAABB(const ShapeAABB* point);
	virtual bool CheckOBB(const ShapeOBB* point);
	virtual bool CheckPlane(const ShapePlane* point);
	virtual bool CheckCapsule(const ShapeCapsule* point);
	virtual bool CheckTriangle(const ShapeTriangle* point);
	virtual bool CheckMesh(const ShapeMesh* point);
	virtual bool CheckModel(const ShapeModel* point);
	virtual bool CheckLine(const ShapeLine* point);
	virtual bool CheckRay(const ShapeRay* point);
};

class ShapePoint: Shape {
public:
	bool CheckPoint(const ShapePoint* point) override;
	bool CheckSphere(const ShapeSphere* point) override;
	bool CheckAABB(const ShapeAABB* point) override;
	bool CheckOBB(const ShapeOBB* point) override;
	bool CheckPlane(const ShapePlane* point) override;
	bool CheckCapsule(const ShapeCapsule* point) override;
	bool CheckTriangle(const ShapeTriangle* point) override;
	bool CheckMesh(const ShapeMesh* point) override;
	bool CheckModel(const ShapeModel* point) override;
	bool CheckLine(const ShapeLine* point) override;
	bool CheckRay(const ShapeRay* point) override;
};

class ShapeSphere: Shape {
public:
	bool CheckPoint(const ShapePoint* point) override;
	bool CheckSphere(const ShapeSphere* point) override;
	bool CheckAABB(const ShapeAABB* point) override;
	bool CheckOBB(const ShapeOBB* point) override;
	bool CheckPlane(const ShapePlane* point) override;
	bool CheckCapsule(const ShapeCapsule* point) override;
	bool CheckTriangle(const ShapeTriangle* point) override;
	bool CheckMesh(const ShapeMesh* point) override;
	bool CheckModel(const ShapeModel* point) override;
	bool CheckLine(const ShapeLine* point) override;
	bool CheckRay(const ShapeRay* point) override;
};

class ShapeAABB: Shape {
public:
	bool CheckPoint(const ShapePoint* point) override;
	bool CheckSphere(const ShapeSphere* point) override;
	bool CheckAABB(const ShapeAABB* point) override;
	bool CheckOBB(const ShapeOBB* point) override;
	bool CheckPlane(const ShapePlane* point) override;
	bool CheckCapsule(const ShapeCapsule* point) override;
	bool CheckTriangle(const ShapeTriangle* point) override;
	bool CheckMesh(const ShapeMesh* point) override;
	bool CheckModel(const ShapeModel* point) override;
	bool CheckLine(const ShapeLine* point) override;
	bool CheckRay(const ShapeRay* point) override;
};

class ShapeOBB: Shape {
public:
	bool CheckPoint(const ShapePoint* point) override;
	bool CheckSphere(const ShapeSphere* point) override;
	bool CheckAABB(const ShapeAABB* point) override;
	bool CheckOBB(const ShapeOBB* point) override;
	bool CheckPlane(const ShapePlane* point) override;
	bool CheckCapsule(const ShapeCapsule* point) override;
	bool CheckTriangle(const ShapeTriangle* point) override;
	bool CheckMesh(const ShapeMesh* point) override;
	bool CheckModel(const ShapeModel* point) override;
	bool CheckLine(const ShapeLine* point) override;
	bool CheckRay(const ShapeRay* point) override;
};

class ShapePlane: Shape {
public:
	bool CheckPoint(const ShapePoint* point) override;
	bool CheckSphere(const ShapeSphere* point) override;
	bool CheckAABB(const ShapeAABB* point) override;
	bool CheckOBB(const ShapeOBB* point) override;
	bool CheckPlane(const ShapePlane* point) override;
	bool CheckCapsule(const ShapeCapsule* point) override;
	bool CheckTriangle(const ShapeTriangle* point) override;
	bool CheckMesh(const ShapeMesh* point) override;
	bool CheckModel(const ShapeModel* point) override;
	bool CheckLine(const ShapeLine* point) override;
	bool CheckRay(const ShapeRay* point) override;
};

class ShapeCapsule: Shape {
public:
	bool CheckPoint(const ShapePoint* point) override;
	bool CheckSphere(const ShapeSphere* point) override;
	bool CheckAABB(const ShapeAABB* point) override;
	bool CheckOBB(const ShapeOBB* point) override;
	bool CheckPlane(const ShapePlane* point) override;
	bool CheckCapsule(const ShapeCapsule* point) override;
	bool CheckTriangle(const ShapeTriangle* point) override;
	bool CheckMesh(const ShapeMesh* point) override;
	bool CheckModel(const ShapeModel* point) override;
	bool CheckLine(const ShapeLine* point) override;
	bool CheckRay(const ShapeRay* point) override;
};

class ShapeTriangle: Shape {
public:
	bool CheckPoint(const ShapePoint* point) override;
	bool CheckSphere(const ShapeSphere* point) override;
	bool CheckAABB(const ShapeAABB* point) override;
	bool CheckOBB(const ShapeOBB* point) override;
	bool CheckPlane(const ShapePlane* point) override;
	bool CheckCapsule(const ShapeCapsule* point) override;
	bool CheckTriangle(const ShapeTriangle* point) override;
	bool CheckMesh(const ShapeMesh* point) override;
	bool CheckModel(const ShapeModel* point) override;
	bool CheckLine(const ShapeLine* point) override;
	bool CheckRay(const ShapeRay* point) override;
};

class ShapeMesh: Shape {
public:
	bool CheckPoint(const ShapePoint* point) override;
	bool CheckSphere(const ShapeSphere* point) override;
	bool CheckAABB(const ShapeAABB* point) override;
	bool CheckOBB(const ShapeOBB* point) override;
	bool CheckPlane(const ShapePlane* point) override;
	bool CheckCapsule(const ShapeCapsule* point) override;
	bool CheckTriangle(const ShapeTriangle* point) override;
	bool CheckMesh(const ShapeMesh* point) override;
	bool CheckModel(const ShapeModel* point) override;
	bool CheckLine(const ShapeLine* point) override;
	bool CheckRay(const ShapeRay* point) override;
};

class ShapeModel: Shape {
public:
	bool CheckPoint(const ShapePoint* point) override;
	bool CheckSphere(const ShapeSphere* point) override;
	bool CheckAABB(const ShapeAABB* point) override;
	bool CheckOBB(const ShapeOBB* point) override;
	bool CheckPlane(const ShapePlane* point) override;
	bool CheckCapsule(const ShapeCapsule* point) override;
	bool CheckTriangle(const ShapeTriangle* point) override;
	bool CheckMesh(const ShapeMesh* point) override;
	bool CheckModel(const ShapeModel* point) override;
	bool CheckLine(const ShapeLine* point) override;
	bool CheckRay(const ShapeRay* point) override;
};

class ShapeRay: Shape {
public:
	bool CheckPoint(const ShapePoint* point) override;
	bool CheckSphere(const ShapeSphere* point) override;
	bool CheckAABB(const ShapeAABB* point) override;
	bool CheckOBB(const ShapeOBB* point) override;
	bool CheckPlane(const ShapePlane* point) override;
	bool CheckCapsule(const ShapeCapsule* point) override;
	bool CheckTriangle(const ShapeTriangle* point) override;
	bool CheckMesh(const ShapeMesh* point) override;
	bool CheckModel(const ShapeModel* point) override;
	bool CheckLine(const ShapeLine* point) override;
	bool CheckRay(const ShapeRay* point) override;
};

class ShapeLine: Shape {
public:
	bool CheckPoint(const ShapePoint* point) override;
	bool CheckSphere(const ShapeSphere* point) override;
	bool CheckAABB(const ShapeAABB* point) override;
	bool CheckOBB(const ShapeOBB* point) override;
	bool CheckPlane(const ShapePlane* point) override;
	bool CheckCapsule(const ShapeCapsule* point) override;
	bool CheckTriangle(const ShapeTriangle* point) override;
	bool CheckMesh(const ShapeMesh* point) override;
	bool CheckModel(const ShapeModel* point) override;
	bool CheckLine(const ShapeLine* point) override;
	bool CheckRay(const ShapeRay* point) override;
};