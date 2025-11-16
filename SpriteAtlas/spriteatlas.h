#ifndef __DRAGO_SPRITE_ATLAS
#define __DRAGO_SPRITE_ATLAS "1.2.0"

#include "main/core.h"

namespace sprite_atlas {
	const char* version();

	double pack(int*, int, int);
	void place_sprite(int*, int, int, int, int);
	bool collide_sprite(int*, int, int, int, int);
}

#endif