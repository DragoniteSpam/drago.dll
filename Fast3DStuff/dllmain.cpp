#include "main/core.h"
#include "falcon.h"

ex double falcon_combine(float* combine_target, float* combine_positions, double count) {
	falcon::combine(combine_target, combine_positions, (int)count);
	return 1.0;
}

ex const char* falcon_version() {
	return falcon::version();
}