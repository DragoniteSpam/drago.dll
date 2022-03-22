#ifndef __DRAGO_CORE_MATH
#define __DRAGO_CORE_MATH

// helpers
#define BYTES2FLOATS(bytes) (((int)(bytes)) / 4)
#define FLOATS2BYTES(floats) (((int)(floats)) * 4)
#define BYTES2DOUBLES(bytes) (((int)(bytes)) / 8)
#define DOUBLES2BYTES(floats) (((int)(floats)) * 8)

#define LERP(a, b, f) ((a) * 1.0f + (f) * ((b) * 1.0f - (a) * 1.0f))
#define LERP_CUBIC(a, b, f) (((float)(b) - (float)(a)) * (3.0f - (float)(f) * 2.0f) * (float)(f) * (float)(f) + (float)(a))
#define LERP_WHATEVERS_SMOOTHER_THAN_CUBIC(a, b, f) ((float)(b) - (float)(a)) * (((float)(f) * ((float)(f) * 6.0f - 15.0f) + 10.0f) * (float)(f) * (float)(f) * (float)(f)) + (float)(a)

// all of the vector macros assume that you're using a vector3
#define ADD(result, a, b) { (result).x = a.x + b.x; (result).y = a.y + b.y; (result).z = a.z + b.z; }
#define SUB(result, a, b) { (result).x = a.x - b.x; (result).y = a.y - b.y; (result).z = a.z - b.z; }
#define MUL(result, a, b) { (result).x = a.x * b.x; (result).y = a.y * b.y; (result).z = a.z * b.z; }
#define DIV(result, a, b) { (result).x = a.x / b.x; (result).y = a.y / b.y; (result).z = a.z / b.z; }

#define DOT(a, b) (a.x * b.x + a.y * b.y + a.z * b.z)
#define CROSS(result, a, b) { (result).x = a.y * b.z - a.z * b.y; (result).y = -a.x * b.z + a.z * b.x; (result).z = a.x * b.y - a.y * b.x; }
#define MAGNITUDE(vec3) sqrtf(DOT(vec3, vec3))
#define NORMALIZE(vec3) { float mag = MAGNITUDE((vec3)); (vec3).x /= mag; (vec3).y /= mag; (vec3).z /= mag; }

// data structures
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
};

Matrix4x4 operator*(const Matrix4x4&, const Matrix4x4&);
Vector4 operator*(const Matrix4x4&, const Vector4&);
Vector4 operator*(const Vector4&, const Matrix4x4&);

#endif