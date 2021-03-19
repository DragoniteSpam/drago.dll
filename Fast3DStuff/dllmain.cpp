#include "main/core.h"
#include "falcon.h"

ex double set_vertex_size(double floats) {
	falcon::set_vertex_size((int)floats);
	return 1.0;
}

ex double falcon_combine(float* combine_target, float* combine_positions, double count) {
	falcon::combine(combine_target, combine_positions, (int)count);
	return 1.0;
}

ex double falcon_combine_color(float* combine_target, float* combine_positions, double count) {
	falcon::combine_color(combine_target, combine_positions, (int)count);
	return 1.0;
}

ex const char* falcon_version() {
	return falcon::version();
}