#ifndef __DRAGO_CORE
#define __DRAGO_CORE "1.0.0"

#define ex extern "C" __declspec (dllexport)

// helpers
#define BYTES2FLOATS(bytes) (((int)bytes) / 4)

// data structures
struct Vector3 {
	float x, y, z;
};

struct Triangle {
	Vector3 a, b, c;
};

#endif