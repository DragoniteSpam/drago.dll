#ifndef __DRAGO_CORE_MATH
#define __DRAGO_CORE_MATH

// helpers
#define BYTES2FLOATS(bytes) (((int)(bytes)) / 4)
#define FLOATS2BYTES(floats) (((int)(floats)) * 4)
#define BYTES2DOUBLES(bytes) (((int)(bytes)) / 8)
#define DOUBLES2BYTES(floats) (((int)(floats)) * 8)

#define DOT(a, b) (a.x * b.x + a.y * b.y + a.z * b.z)
#define MAGNITUDE(vec3) sqrtf(DOT(vec3, vec3))
#define NORMALIZE(vec3) { float mag = MAGNITUDE(vec3); vec3.x /= mag; vec3.y /= mag; vec3.z /= mag; }

// data structures
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