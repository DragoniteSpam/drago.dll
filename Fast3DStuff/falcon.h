#ifndef __DRAGO_FALCON
#define __DRAGO_FALCON "1.0.0"

#define FALCON_BATCH_DATA_SIZE 7

#include "falcon.h"

namespace falcon {
	const char* version();
	void combine(float*, float*, double);
}

#endif