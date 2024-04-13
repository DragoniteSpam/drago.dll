#ifndef __DRAGO_THREEDGRIDS
#define __DRAGO_THREEDGRIDS "1.0.0"

#include "main/core.h"

#define DATA_INDEX(x, y, z, height, depth) (((z) * (height) * (depth)) + ((y) * (depth)) + (x))

#endif