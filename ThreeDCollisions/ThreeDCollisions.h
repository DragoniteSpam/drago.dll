#ifndef __DRAGO_3DC
#define __DRAGO_3DC "0.0.1"

#include "main/core.h"
#include "main/dragomath.h"

#include <vector>

namespace collisions {
	extern float epsilon;

	const char* version();
	const void set_epsilon(float epsilon);
	const inline bool compare_epsilon(float a, float b);
}

#endif