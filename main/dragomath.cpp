#include "dragomath.h"

// See here: https://github.com/gszauer/GamePhysicsCookbook/blob/master/Code/matrices.cpp
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

Vector4 operator*(const Matrix4x4& a, const Vector4& b) {
	Vector4 result{
		b.x * a.v11 + b.y * a.v12 + b.z * a.v13 + b.w * a.v14,
		b.x * a.v21 + b.y * a.v22 + b.z * a.v23 + b.w * a.v24,
		b.x * a.v31 + b.y * a.v32 + b.z * a.v33 + b.w * a.v34,
		b.x * a.v41 + b.y * a.v42 + b.z * a.v43 + b.w * a.v44,
	};

	return result;
}

Vector4 operator*(const Vector4& a, const Matrix4x4& b) {
	Vector4 result{
		a.x* b.v11 + a.y * b.v21 + a.z * b.v31 + a.w * b.v41,
		a.x* b.v12 + a.y * b.v22 + a.z * b.v32 + a.w * b.v42,
		a.x* b.v13 + a.y * b.v23 + a.z * b.v33 + a.w * b.v43,
		a.x* b.v14 + a.y * b.v24 + a.z * b.v34 + a.w * b.v44,
	};

	return result;
}