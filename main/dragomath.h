#ifndef __DRAGO_CORE_MATH
#define __DRAGO_CORE_MATH

// helpers
#define BYTES2FLOATS(bytes) (((int)(bytes)) / 4)
#define FLOATS2BYTES(floats) (((int)(floats)) * 4)
#define BYTES2DOUBLES(bytes) (((int)(bytes)) / 8)
#define DOUBLES2BYTES(floats) (((int)(floats)) * 8)

#define LERP(a, b, f) ((a) * 1.0f + (f) * ((b) * 1.0f - (a) * 1.0f))
#define LERP_CUBIC(a, b, f) (((float)(b) - (float)(a)) * (3.0 - (float)(f) * 2.0) * (float)(f) * (float)(f) + (float)(a))
#define LERP_WHATEVERS_SMOOTHER_THAN_CUBIC(a, b, f) ((float)(b) - (float)(a)) * (((float)(f) * ((float)(f) * 6.0 - 15.0) + 10.0) * (float)(f) * (float)(f) * (float)(f)) + (float)(a);

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

#endif