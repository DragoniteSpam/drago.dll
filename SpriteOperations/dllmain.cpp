#include "main/core.h"
#include "spriteops.h"

ex const char* spriteops_version() {
	return spriteops::version();
}

ex double spriteops_set_dimensions_output(float* out) {
	spriteops::set_cropped_dimensions_output(out);
}

ex double spriteops_get_cropped_dimensions(float* data, double length, double w, double h) {
	spriteops::get_cropped_dimensions(data, BYTES2FLOATS(length), (int)w, (int)h);
	return 1.0;
}

ex double spriteops_remove_transparent_colour(float* data, double length, double colour) {
	spriteops::spriteops_remove_transparent_colour(data, BYTES2FLOATS(length), (int)colour);
	return 1.0;
}