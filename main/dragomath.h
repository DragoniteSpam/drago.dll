#ifndef __DRAGO_CORE_MATH
#define __DRAGO_CORE_MATH

#include <math.h>

// helpers
constexpr float PI = 3.14159265358f;
#define DEG2RAD(angle) (angle * PI / 180.0f)
#define RAD2DEG(angle) (angle * 180.0f / PI)
#define BYTES2FLOATS(bytes) (((int)(bytes)) / 4)
#define FLOATS2BYTES(floats) (((int)(floats)) * 4)
#define BYTES2DOUBLES(bytes) (((int)(bytes)) / 8)
#define DOUBLES2BYTES(floats) (((int)(floats)) * 8)
#define CMP(a, b) (fabsf(a - b) <= 0.000000001 * fmaxf(1.0f, fmaxf(fabsf(a), fabsf(b))))

#define LERP(a, b, f) ((a) * 1.0f + (f) * ((b) * 1.0f - (a) * 1.0f))
#define LERP_CUBIC(a, b, f) (((float)(b) - (float)(a)) * (3.0f - (float)(f) * 2.0f) * (float)(f) * (float)(f) + (float)(a))
#define LERP_WHATEVERS_SMOOTHER_THAN_CUBIC(a, b, f) ((float)(b) - (float)(a)) * (((float)(f) * ((float)(f) * 6.0f - 15.0f) + 10.0f) * (float)(f) * (float)(f) * (float)(f)) + (float)(a)

// all of the vector macros assume that you're using at least a vector3
#define ADD(result, a, b) { (result).x = a.x + b.x; (result).y = a.y + b.y; (result).z = a.z + b.z; }
#define SUB(result, a, b) { (result).x = a.x - b.x; (result).y = a.y - b.y; (result).z = a.z - b.z; }
#define MUL(result, a, b) { (result).x = a.x * b.x; (result).y = a.y * b.y; (result).z = a.z * b.z; }
#define DIV(result, a, b) { (result).x = a.x / b.x; (result).y = a.y / b.y; (result).z = a.z / b.z; }

#define DOT(a, b) (a.x * b.x + a.y * b.y + a.z * b.z)
#define CROSS(result, a, b) { (result).x = a.y * b.z - a.z * b.y; (result).y = -a.x * b.z + a.z * b.x; (result).z = a.x * b.y - a.y * b.x; }
#define MAGNITUDE(vec3) sqrtf(DOT(vec3, vec3))
#define NORMALIZE(vec3) { float mag = MAGNITUDE((vec3)); (vec3).x /= mag; (vec3).y /= mag; (vec3).z /= mag; }

#define SWAPYZ(vec3) { float t = vec3.y; vec3.y = vec3.z; vec3.z = -t; }
#define SWAPCELLYZ(cell) {												\
	SWAPYZ(cell.nw); SWAPYZ(cell.ne); SWAPYZ(cell.se); SWAPYZ(cell.sw);	\
}

// data structures
struct Vector4;
struct Vector3;
struct Vector2;
struct Matrix4x4;

struct Vector4 {
	union {
		float x;
		float r;
	};
	union {
		float y;
		float g;
	};
	union {
		float z;
		float b;
	};
	union {
		float w;
		float a;
	};

	// some methods that act on the struct itself
	void Transform(Matrix4x4*);

	inline float Dot(Vector4* other) {
		return this->x * other->x * this->y + other->y + this->z * other->z;
	}

	inline void Normalize() {
		float mag = sqrtf(this->Dot(this));
		if (CMP(mag, 0)) return;
		this->x /= mag;
		this->y /= mag;
		this->z /= mag;
	}
};

struct Vector3 {
	union {
		float x;
		int a;
	};
	union {
		float y;
		int b;
	};
	union {
		float z;
		int c;
	};
};

struct Vector2 {
	union {
		float x;
		int a;
	};
	union {
		float y;
		int b;
	};
};

struct Triangle {
	Vector3 a, b, c;
};

struct TerrainCell {
	union {
		struct {
			Vector3 nw, ne, se, sw;
		};
		Vector3 asArray[4];
	};
};

struct TerrainCellVector2 {
	union {
		struct {
			Vector2 nw, ne, se, sw;
		};
		Vector2 asArray[4];
	};
};

struct TerrainCellUInt {
	union {
		struct {
			unsigned int nw, ne, se, sw;
		};
		unsigned int asArray[4];
	};
};

// See here: https://github.com/gszauer/GamePhysicsCookbook/blob/master/Code/matrices.h
struct Matrix4x4 {
	union {
		struct {
			float v11, v12, v13, v14,
				v21, v22, v23, v24,
				v31, v32, v33, v34,
				v41, v42, v43, v44;
		};
		float asArray[16];
	};

	inline Matrix4x4() {
		v11 = v22 = v33 = v44 = 1.0f;
		v12 = v13 = v14 = v21 = 0.0f;
		v23 = v24 = v31 = v32 = 0.0f;
		v34 = v41 = v42 = v43 = 0.0f;
	};

	inline Matrix4x4(float f11, float f12, float f13, float f14,
		float f21, float f22, float f23, float f24,
		float f31, float f32, float f33, float f34,
		float f41, float f42, float f43, float f44) {
		v11 = f11; v12 = f12; v13 = f13; v14 = f14;
		v21 = f21; v22 = f22; v23 = f23; v24 = f24;
		v31 = f31; v32 = f32; v33 = f33; v34 = f34;
		v41 = f41; v42 = f42; v43 = f43; v44 = f44;
	}

	inline float* operator[](int i) {
		return &(asArray[i * 4]);
	}

	static inline Matrix4x4 Translation(float x, float y, float z) {
		return Matrix4x4(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			x, y, z, 1
		);
	}

	static inline Matrix4x4 Translation(Vector3 position) {
		return Matrix4x4(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			position.x, position.y, position.z, 1
		);
	}
	
	static inline Matrix4x4 RotationX(float angle) {
		angle = DEG2RAD(angle);
		return Matrix4x4(
			1, 0, 0, 0,
			0, cosf(angle), sinf(angle), 0,
			0, -sinf(angle), cosf(angle), 0,
			0, 0, 0, 1
		);
	}

	static inline Matrix4x4 RotationY(float angle) {
		angle = DEG2RAD(angle);
		return Matrix4x4(
			cosf(angle), 0, -sinf(angle), 0,
			0, 1, 0, 0,
			sinf(angle), 0, cosf(angle), 0,
			0, 0, 0, 1
		);
	}

	static inline Matrix4x4 RotationZ(float angle) {
		angle = DEG2RAD(angle);
		return Matrix4x4(
			cosf(angle), sinf(angle), 0, 0,
			-sinf(angle), cosf(angle), 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		);
	}

	static inline Matrix4x4 YawPitchRoll(float yaw, float pitch, float roll) {
		yaw = DEG2RAD(yaw);
		pitch = DEG2RAD(pitch);
		roll = DEG2RAD(roll);

		Matrix4x4 result; // z * x * y
		result.v11 = (cosf(roll) * cosf(yaw)) + (sinf(roll) * sinf(pitch) * sinf(yaw));
		result.v12 = (sinf(roll) * cosf(pitch));
		result.v13 = (cosf(roll) * -sinf(yaw)) + (sinf(roll) * sinf(pitch) * cosf(yaw));
		result.v21 = (-sinf(roll) * cosf(yaw)) + (cosf(roll) * sinf(pitch) * sinf(yaw));
		result.v22 = (cosf(roll) * cosf(pitch));
		result.v23 = (sinf(roll) * sinf(yaw)) + (cosf(roll) * sinf(pitch) * cosf(yaw));
		result.v31 = (cosf(pitch) * sinf(yaw));
		result.v32 = -sinf(pitch);
		result.v33 = (cosf(pitch) * cosf(yaw));
		result.v44 = 1;
		return result;
	}
	
	static inline Matrix4x4 Scale(float x, float y, float z) {
		return Matrix4x4(
			x, 0, 0, 0,
			0, y, 0, 0,
			0, 0, z, 0,
			0, 0, 0, 1
		);
	}

	static inline Matrix4x4 Scale(Vector3 scale) {
		return Matrix4x4(
			scale.x, 0, 0, 0,
			0, scale.y, 0, 0,
			0, 0, scale.z, 0,
			0, 0, 0, 1
		);
	}

	static Matrix4x4 Rotation(float, float, float);
	static Matrix4x4 Rotation(Vector3);
	static Matrix4x4 Transform(float, float, float, float, float, float, float, float, float);
	static Matrix4x4 Transform(Vector3, Vector3, Vector3);
};

Matrix4x4 operator*(const Matrix4x4&, const Matrix4x4&);
Vector4 operator*(const Matrix4x4&, const Vector4&);
Vector4 operator*(const Vector4&, const Matrix4x4&);

#endif