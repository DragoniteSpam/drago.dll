#ifndef __DRAGO_CORE
#define __DRAGO_CORE "1.0.0"

#define ex extern "C" __declspec (dllexport)

// helpers
#define BYTES2FLOATS(bytes) (((int)(bytes)) / 4)
#define FLOATS2BYTES(floats) (((int)(floats)) * 4)

#define DOT(vec3) (vec3.x * vec3.x + vec3.y * vec3.y + vec3.z * vec3.z)
#define MAGNITUDE(vec3) sqrtf(DOT(vec3))
#define NORMALIZE(vec3) { float mag = MAGNITUDE(vec3); vec3.x /= mag; vec3.y /= mag; vec3.z /= mag; }

// data structures
struct Vector3 {
	float x, y, z;
};

struct Triangle {
	Vector3 a, b, c;
};

#endif