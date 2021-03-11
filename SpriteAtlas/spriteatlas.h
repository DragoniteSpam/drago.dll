#include "main/core.h"

namespace sprite_atlas {
	const char* VERSION = "1.0.1";
	const char* version() {
		return VERSION;
	}

	double pack(int*, int);
	bool place_sprite(int*, int, int, int, int);
	bool collide_sprite(int*, int, int, int, int);
}