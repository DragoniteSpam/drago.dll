#ifndef __DRAGO_FILE_DROPPER
#define __DRAGO_FILE_DROPPER "1.0.1"

#include "main/core.h"

namespace file_dropper {
	const char* version();

	double file_drop_count();
	char* file_drop_get(double n);
	double file_drop_flush();
}

#endif