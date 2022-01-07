#include "main/core.h"
#include "macaw.h"

ex const char* macaw_version() {
	return __DRAGO_MACAW;
}

ex double macaw_set_octaves(double octaves) {
	macaw::set_octaves((int)octaves);
	return 1.0;
}

ex double macaw_set_height(double height) {
	macaw::set_height((float)height);
	return 1.0;
}

ex double macaw_generate(float* buffer, double w, double h) {
	macaw::generate(buffer, (int)w, (int)h);
	return 1.0;
}

ex double macaw_set_seed(double seed) {
	macaw::seed_set((unsigned int)seed);
	return 1.0;
}

ex double macaw_to_sprite(float* in, int* out, double len) {
	macaw::to_sprite(in, out, (int)len);
	return 1.0;
}

ex double macaw_to_vbuff(float* in, float* out, double w, double h) {
	macaw::to_vbuff(in, out, (int)w, (int)h);
	return 1.0;
}