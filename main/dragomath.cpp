#include "dragomath.h"

// See here: https://github.com/gszauer/GamePhysicsCookbook/blob/master/Code/matrices.cpp

void Vector4::Transform(Matrix4x4* transform) {
	float newx = this->x * transform->v11 + this->y * transform->v21 + this->z * transform->v31 + this->w * transform->v41;
	float newy = this->x * transform->v12 + this->y * transform->v22 + this->z * transform->v32 + this->w * transform->v42;
	float newz = this->x * transform->v13 + this->y * transform->v23 + this->z * transform->v33 + this->w * transform->v43;
	float neww = this->x * transform->v14 + this->y * transform->v24 + this->z * transform->v34 + this->w * transform->v44;
	this->x = newx;
	this->y = newy;
	this->z = newz;
	this->w = neww;
}

Matrix4x4 Matrix4x4::Rotation(float x, float y, float z) {
	return (Matrix4x4::RotationY(y) * Matrix4x4::RotationX(x)) * Matrix4x4::RotationZ(z);
}

Matrix4x4 Matrix4x4::Rotation(Vector3 rotation) {
	return Matrix4x4::Rotation(rotation.x, rotation.y, rotation.z);
}

Matrix4x4 Matrix4x4::Transform(float x, float y, float z, float xrot, float yrot, float zrot, float xscale, float yscale, float zscale) {
	return (Matrix4x4::Scale(xscale, yscale, zscale) * Matrix4x4::Rotation(xrot, yrot, zrot)) * Matrix4x4::Translation(x, y, z);
}

Matrix4x4 Matrix4x4::Transform(Vector3 position, Vector3 rotation, Vector3 scale) {
	return (Matrix4x4::Scale(scale) * Matrix4x4::Rotation(rotation)) * Matrix4x4::Translation(position);
}

Vector4 operator*(const Matrix4x4& a, const Vector4& b) {
	Vector4 result{
		b.x * a.v11 + b.y * a.v21 + b.z * a.v31 + b.w * a.v41,
		b.x * a.v12 + b.y * a.v22 + b.z * a.v32 + b.w * a.v42,
		b.x * a.v13 + b.y * a.v23 + b.z * a.v33 + b.w * a.v43,
		b.x * a.v14 + b.y * a.v24 + b.z * a.v34 + b.w * a.v44,
	};

	return result;
}

Vector4 operator*(const Vector4& a, const Matrix4x4& b) {
	Vector4 result{
		a.x* b.v11 + a.y * b.v12 + a.z * b.v13 + a.w * b.v14,
		a.x* b.v21 + a.y * b.v22 + a.z * b.v23 + a.w * b.v24,
		a.x* b.v31 + a.y * b.v32 + a.z * b.v33 + a.w * b.v34,
		a.x* b.v41 + a.y * b.v42 + a.z * b.v43 + a.w * b.v44,
	};

	return result;
}

Matrix4x4 operator*(const Matrix4x4& a, const Matrix4x4& b) {
	Matrix4x4 result;

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result.asArray[4 * i + j] = 0.0f;
			for (int k = 0; k < 4; ++k) {
				result.asArray[4 * i + j] += a.asArray[4 * i + k] * b.asArray[4 * k + j];
			}
		}
	}

	return result;
}
