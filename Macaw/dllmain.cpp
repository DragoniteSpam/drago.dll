#include "main/core.h"
#include "macaw.h"

ex double macaw_generate(float* buffer, double w, double h, double octaves) {
	macaw::generate(buffer, (int)w, (int)h, (int)octaves);
	return 1.0;
}