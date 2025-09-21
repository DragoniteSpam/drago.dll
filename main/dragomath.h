#ifndef __DRAGO_CORE_MATH
#define __DRAGO_CORE_MATH

#include <math.h>
#include <immintrin.h>
#include <algorithm>

// helpers
constexpr float PI = 3.14159265358f;
#define DEG2RAD(angle) (angle * PI / 180.0f)
#define RAD2DEG(angle) (angle * 180.0f / PI)
#define BYTES2FLOATS(bytes) (((int)(bytes)) / 4)
#define FLOATS2BYTES(floats) (((int)(floats)) * 4)
#define BYTES2DOUBLES(bytes) (((int)(bytes)) / 8)
#define DOUBLES2BYTES(floats) (((int)(floats)) * 8)
#define CMP(a, b) (fabsf(a - b) <= 0.000000001 * fmaxf(1.0f, fmaxf(fabsf(a), fabsf(b))))

#define CLAMP(x, lower, upper) (std::max(std::min(x, upper), lower))

#define LERP(a, b, f) ((a) * 1.0f + (f) * ((b) * 1.0f - (a) * 1.0f))
#define LERP_CUBIC(a, b, f) (((float)(b) - (float)(a)) * (3.0f - (float)(f) * 2.0f) * (float)(f) * (float)(f) + (float)(a))
#define LERP_WHATEVERS_SMOOTHER_THAN_CUBIC(a, b, f) ((float)(b) - (float)(a)) * (((float)(f) * ((float)(f) * 6.0f - 15.0f) + 10.0f) * (float)(f) * (float)(f) * (float)(f)) + (float)(a)

// all of the vector macros assume that you're using at least a vector3
#define ADD(result, a, b) { (result).x = a.x + b.x; (result).y = a.y + b.y; (result).z = a.z + b.z; }
#define SUB(result, a, b) { (result).x = a.x - b.x; (result).y = a.y - b.y; (result).z = a.z - b.z; }
#define MUL(result, a, b) { (result).x = a.x * b.x; (result).y = a.y * b.y; (result).z = a.z * b.z; }
#define DIV(result, a, b) { (result).x = a.x / b.x; (result).y = a.y / b.y; (result).z = a.z / b.z; }

#define PADD(result, a, b) { (result)->x = a->x + b->x; (result)->y = a->y + b->y; (result)->z = a->z + b->z; }
#define PSUB(result, a, b) { (result)->x = a->x - b->x; (result)->y = a->y - b->y; (result)->z = a->z - b->z; }
#define PMUL(result, a, b) { (result)->x = a->x * b->x; (result)->y = a->y * b->y; (result)->z = a->z * b->z; }
#define PDIV(result, a, b) { (result)->x = a->x / b->x; (result)->y = a->y / b->y; (result)->z = a->z / b->z; }

#define DOT(a, b) (a.x * b.x + a.y * b.y + a.z * b.z)
#define CROSS(result, a, b) { (result).x = a.y * b.z - a.z * b.y; (result).y = -a.x * b.z + a.z * b.x; (result).z = a.x * b.y - a.y * b.x; }
#define MAGNITUDE(vec3) sqrtf(DOT(vec3, vec3))
#define NORMALIZE(vec3) { float mag = MAGNITUDE((vec3)); (vec3).x /= mag; (vec3).y /= mag; (vec3).z /= mag; }

#define SWAPYZ(vec3) {						\
	float t = vec3.y;						\
	vec3.y = vec3.z;						\
	vec3.z = -t;							\
}
#define SWAPCELLYZ(cell) {					\
	SWAPYZ(cell.nw);						\
	SWAPYZ(cell.ne);						\
	SWAPYZ(cell.se);						\
	SWAPYZ(cell.sw);						\
}
// this will swap and rotate the handedness
#define SWAPYZ_HANDEDNESS(vec3) {			\
	float ox = vec3.x;						\
	float oy = vec3.y;						\
	float oz = vec3.z;						\
	vec3.x = oy;							\
	vec3.z = ox;							\
	vec3.y = -oz;							\
}
#define SWAPCELLYZ_HANDEDNESS(cell) {		\
	SWAPYZ_HANDEDNESS(cell.nw);				\
	SWAPYZ_HANDEDNESS(cell.ne);				\
	SWAPYZ_HANDEDNESS(cell.se);				\
	SWAPYZ_HANDEDNESS(cell.sw);				\
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

	inline Vector4() {
		this->x = 0;
		this->y = 0;
		this->z = 0;
		this->w = 0;
	}

	inline Vector4(float x, float y, float z, float w) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	inline Vector4(const Vector4* source) {
		this->x = source->x;
		this->y = source->y;
		this->z = source->z;
		this->w = source->w;
	}

	inline void Set(const Vector4* source) {
		this->x = source->x;
		this->y = source->y;
		this->z = source->z;
		this->w = source->w;
	}

	inline bool Equals(const Vector4* a) const {
		return (fabsf(this->x - a->x) <= 0.000000001) && (fabsf(this->y - a->y) <= 0.000000001) && (fabsf(this->z - a->z) <= 0.000000001) && (fabsf(this->z - a->z) <= 0.000000001);
	}

	inline float Dot(const Vector4* other) const {
		return this->x * other->x + this->y * other->y + this->z * other->z + this->w * other->w;
	}

	inline Vector4 Normalize() const {
		float mag = sqrtf(this->Dot(this));
		return Vector4{ this->x / mag, this->y / mag, this->z / mag, this->w / mag };
	}

	inline float Magnitude() const {
		return sqrtf(this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w);
	}

	inline float Distance(const Vector4* other) const {
		float a = this->x - other->x;
		float b = this->y - other->y;
		float c = this->z - other->z;
		float d = this->w - other->w;
		return sqrtf(a * a + b * b + c * c + d * d);
	}

	inline Vector4 Abs() const {
		return Vector4{ (float)fabs(this->x), (float)fabs(this->y), (float)fabs(this->z), (float)fabs(this->w) };
	}

	inline Vector4 Floor() const {
		return Vector4{ (float)floor(this->x), (float)floor(this->y), (float)floor(this->z), (float)floor(this->w) };
	}

	inline Vector4 Ceil() const {
		return Vector4{ (float)ceil(this->x), (float)ceil(this->y), (float)ceil(this->z), (float)ceil(this->w) };
	}

	inline Vector4 Frac() const {
		return Vector4{ (float)fmod(this->x, 1.0), (float)fmod(this->y, 1.0), (float)fmod(this->z, 1.0), (float)fmod(this->w, 1.0) };
	}

	inline Vector4 Min(const Vector4* other) const {
		return Vector4{ (float)fmin(this->x, other->x), (float)fmin(this->y, other->y), (float)fmin(this->z, other->z), (float)fmin(this->w, other->w) };
	}

	inline Vector4 Max(const Vector4* other) const {
		return Vector4{ (float)fmax(this->x, other->x), (float)fmax(this->y, other->y), (float)fmax(this->z, other->z), (float)fmax(this->w, other->w) };
	}

	inline Vector4 Clamp(const Vector4* a, const Vector4* b) const {
		return Vector4{ (float)fmin(fmax(this->x, a->x), b->x), (float)fmin(fmax(this->y, a->y), b->y), (float)fmin(fmax(this->z, a->z), b->z), (float)fmin(fmax(this->w, a->w), b->w) };
	}

	inline Vector4 Project(const Vector4* direction) const {
		float f = this->Dot(direction) / direction->Dot(direction);
		return Vector4{ direction->x * f, direction->y * f, direction->z * f, direction->w * f };
	}

	inline Vector4 Lerp(const Vector4* target, const Vector4* amount) const {
		return Vector4{ LERP(this->x, target->x, amount->x), LERP(this->y, target->y, amount->y), LERP(this->z, target->z, amount->z), LERP(this->w, target->w, amount->w) };
	}

	inline Vector4 Lerp(const Vector4* target, float amount) const {
		return Vector4{ LERP(this->x, target->x, x), LERP(this->y, target->y, y), LERP(this->z, target->z, z), LERP(this->w, target->w, w) };
	}

	inline Vector4 Approach(const Vector4* target, float amount) const {
		float f = (float)fmax(this->Distance(target) - amount, 0) / amount;
		return this->Lerp(target, f);
	}

	// some methods that act on the struct itself
	void TransformInPlace(Matrix4x4*);

	inline void NormalizeInPlace() {
		float mag = sqrtf(this->Dot(this));
		if (CMP(mag, 0)) return;
		this->x /= mag;
		this->y /= mag;
		this->z /= mag;
		this->w /= mag;
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

	inline Vector3() {
		this->x = 0;
		this->y = 0;
		this->z = 0;
	}

	inline Vector3(const Vector3* source) {
		this->x = source->x;
		this->y = source->y;
		this->z = source->z;
	}

	inline Vector3(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	inline void Set(const Vector3* source) {
		this->x = source->x;
		this->y = source->y;
		this->z = source->z;
	}

	inline bool Equals(const Vector3* a) const {
		return (fabsf(this->x - a->x) <= 0.000000001) && (fabsf(this->y - a->y) <= 0.000000001) && (fabsf(this->z - a->z) <= 0.000000001);
	}

	inline float Dot(const Vector3* other) const {
		return this->x * other->x + this->y * other->y + this->z * other->z;
	}

	inline Vector3 Cross(const Vector3* other) const {
		return Vector3{
			this->y * other->z - other->y * this->z,
			this->z * other->x - other->z * this->x,
			this->x * other->y - other->x * this->y
		};
	}

	inline Vector3 Normalize() const {
		float mag = sqrtf(this->Dot(this));
		return Vector3{ this->x / mag, this->y / mag, this->z / mag };
	}

	inline float Magnitude() const {
		return sqrtf(this->x * this->x + this->y * this->y + this->z * this->z);
	}

	inline float Distance(const Vector3* other) const {
		float a = this->x - other->x;
		float b = this->y - other->y;
		float c = this->z - other->z;
		return sqrtf(a * a + b * b + c * c);
	}

	inline Vector3 Abs() const {
		return Vector3{ (float)fabs(this->x), (float)fabs(this->y), (float)fabs(this->z) };
	}

	inline Vector3 Floor() const {
		return Vector3{ (float)floor(this->x), (float)floor(this->y), (float)floor(this->z) };
	}

	inline Vector3 Ceil() const {
		return Vector3{ (float)ceil(this->x), (float)ceil(this->y), (float)ceil(this->z) };
	}

	inline Vector3 Frac() const {
		return Vector3{ (float)fmod(this->x, 1.0), (float)fmod(this->y, 1.0), (float)fmod(this->z, 1.0) };
	}

	inline Vector3 Min(const Vector3* other) const {
		return Vector3{ (float)fmin(this->x, other->x), (float)fmin(this->y, other->y), (float)fmin(this->z, other->z) };
	}

	inline Vector3 Max(const Vector3* other) const {
		return Vector3{ (float)fmax(this->x, other->x), (float)fmax(this->y, other->y), (float)fmax(this->z, other->z) };
	}

	inline Vector3 Clamp(const Vector3* a, const Vector3* b) const {
		return Vector3{ (float)fmin(fmax(this->x, a->x), b->x), (float)fmin(fmax(this->y, a->y), b->y), (float)fmin(fmax(this->z, a->z), b->z) };
	}

	inline Vector3 Project(const Vector3* direction) const {
		float f = this->Dot(direction) / direction->Dot(direction);
		return Vector3{ direction->x * f, direction->y * f, direction->z * f };
	}

	inline Vector3 Lerp(const Vector3* target, const Vector3* amount) const {
		return Vector3{ LERP(this->x, target->x, amount->x), LERP(this->y, target->y, amount->y), LERP(this->z, target->z, amount->z) };
	}

	inline Vector3 Lerp(const Vector3* target, float amount) const {
		return Vector3{ LERP(this->x, target->x, x), LERP(this->y, target->y, y), LERP(this->z, target->z, z) };
	}

	inline Vector3 Approach(const Vector3* target, float amount) const {
		float f = (float)fmax(this->Distance(target) - amount, 0) / amount;
		return this->Lerp(target, f);
	}

	inline void NormalizeInPlace() {
		float mag = sqrtf(this->Dot(this));
		if (CMP(mag, 0)) return;
		this->x /= mag;
		this->y /= mag;
		this->z /= mag;
	}
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

	inline Vector2() {
		this->x = 0;
		this->y = 0;
	}

	inline Vector2(const Vector2* source) {
		this->x = source->x;
		this->y = source->y;
	}

	inline Vector2(float x, float y) {
		this->x = x;
		this->y = y;
	}

	inline void Set(const Vector2* source) {
		this->x = source->x;
		this->y = source->y;
	}

	inline bool Equals(const Vector2* a) const {
		return (fabsf(this->x - a->x) <= 0.000000001) && (fabsf(this->y - a->y) <= 0.000000001);
	}

	inline float Dot(const Vector2* other) const {
		return this->x * other->x + this->y * other->y;
	}

	inline Vector2 Normalize() const {
		float mag = sqrtf(this->Dot(this));
		return Vector2{ this->x / mag, this->y / mag };
	}

	inline float Magnitude() const {
		return sqrtf(this->x * this->x + this->y * this->y);
	}

	inline float Distance(const Vector2* other) const {
		float a = this->x - other->x;
		float b = this->y - other->y;
		return sqrtf(a * a + b * b);
	}

	inline Vector2 Abs() const {
		return Vector2{ (float)fabs(this->x), (float)fabs(this->y) };
	}

	inline Vector2 Floor() const {
		return Vector2{ (float)floor(this->x), (float)floor(this->y) };
	}

	inline Vector2 Ceil() const {
		return Vector2{ (float)ceil(this->x), (float)ceil(this->y) };
	}

	inline Vector2 Frac() const {
		return Vector2{ (float)fmod(this->x, 1.0), (float)fmod(this->y, 1.0) };
	}

	inline Vector2 Min(const Vector2* other) const {
		return Vector2{ (float)fmin(this->x, other->x), (float)fmin(this->y, other->y) };
	}

	inline Vector2 Max(const Vector2* other) const {
		return Vector2{ (float)fmax(this->x, other->x), (float)fmax(this->y, other->y) };
	}

	inline Vector2 Clamp(const Vector2* a, const Vector2* b) const {
		return Vector2{ (float)fmin(fmax(this->x, a->x), b->x), (float)fmin(fmax(this->y, a->y), b->y) };
	}

	inline Vector2 Project(const Vector2* direction) const {
		float f = this->Dot(direction) / direction->Dot(direction);
		return Vector2{ direction->x * f, direction->y * f };
	}

	inline Vector2 Lerp(const Vector2* target, const Vector2* amount) const {
		return Vector2{ LERP(this->x, target->x, amount->x), LERP(this->y, target->y, amount->y) };
	}

	inline Vector2 Lerp(const Vector2* target, float amount) const {
		return Vector2{ LERP(this->x, target->x, x), LERP(this->y, target->y, y) };
	}

	inline Vector2 Approach(const Vector2* target, float amount) const {
		float f = (float)fmax(this->Distance(target) - amount, 0) / amount;
		return this->Lerp(target, f);
	}

	inline void Remap(Vector2* start1, Vector2* start2, Vector2* end1, Vector2* end2) {
		this->x = end1->x + (this->x - start1->x) * (end2->x - end1->x) / (start2->x - start1->x);
		this->y = end1->y + (this->y - start1->y) * (end2->y - end1->y) / (start2->y - start1->y);
	}

	inline void NormalizeInPlace() {
		float mag = sqrtf(this->Dot(this));
		if (CMP(mag, 0)) return;
		this->x /= mag;
		this->y /= mag;
	}
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

	inline void Set(const Matrix4x4* source) {
		for (int i = 0; i < 16; i++) {
			this[i] = source[i];
		}
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

Vector4 operator+(const Vector4&, const Vector4&);
Vector4 operator-(const Vector4&, const Vector4&);
Vector4 operator*(const Vector4&, const Vector4&);
Vector4 operator/(const Vector4&, const Vector4&);
Vector4 operator+(const Vector4&, float);
Vector4 operator-(const Vector4&, float);
Vector4 operator*(const Vector4&, float);
Vector4 operator/(const Vector4&, float);
Vector4 operator+(float, const Vector4&);
Vector4 operator-(float, const Vector4&);
Vector4 operator*(float, const Vector4&);
Vector4 operator/(float, const Vector4&);

Vector3 operator+(const Vector3&, const Vector3&);
Vector3 operator-(const Vector3&, const Vector3&);
Vector3 operator*(const Vector3&, const Vector3&);
Vector3 operator/(const Vector3&, const Vector3&);
Vector3 operator+(const Vector3&, float);
Vector3 operator-(const Vector3&, float);
Vector3 operator*(const Vector3&, float);
Vector3 operator/(const Vector3&, float);
Vector3 operator+(float, const Vector3&);
Vector3 operator-(float, const Vector3&);
Vector3 operator*(float, const Vector3&);
Vector3 operator/(float, const Vector3&);

Vector2 operator+(const Vector2&, const Vector2&);
Vector2 operator-(const Vector2&, const Vector2&);
Vector2 operator*(const Vector2&, const Vector2&);
Vector2 operator/(const Vector2&, const Vector2&);
Vector2 operator+(const Vector2&, float);
Vector2 operator-(const Vector2&, float);
Vector2 operator*(const Vector2&, float);
Vector2 operator/(const Vector2&, float);
Vector2 operator+(float, const Vector2&);
Vector2 operator-(float, const Vector2&);
Vector2 operator*(float, const Vector2&);
Vector2 operator/(float, const Vector2&);

#endif