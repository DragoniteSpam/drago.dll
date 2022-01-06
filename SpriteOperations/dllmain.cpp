#include "main/core.h"
#include "spriteops.h"

ex const char* spriteops_version() {
	return spriteops::version();
}

ex double spriteops_set_dimensions_output(int* out) {
	spriteops::set_cropped_dimensions_output(out);
	return 1.0;
}

ex double spriteops_get_cropped_dimensions(int* data, double w, double h, double cutoff) {
	spriteops::get_cropped_dimensions(data, (int)w, (int)h, (int)(cutoff * 255));
	return 1.0;
}

ex double spriteops_remove_transparent_colour(int* data, double length, double colour) {
	spriteops::spriteops_remove_transparent_colour(data, BYTES2FLOATS(length), (int)colour);
	return 1.0;
}