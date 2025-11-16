// see: https://www.gamedev.net/forums/topic/683912-sprite-packing-algorithm-explained-with-example-code/
// see: https://jsfiddle.net/jLchftot/
constexpr auto SPRITE_DATA_X = 0;
constexpr auto SPRITE_DATA_Y = 1;
constexpr auto SPRITE_DATA_W = 2;
constexpr auto SPRITE_DATA_H = 3;
constexpr auto SPRITE_SIZE = 4;

#include "spriteatlas.h"
#include <algorithm>

namespace sprite_atlas {
	const char* version() {
		return __DRAGO_SPRITE_ATLAS;
	}

	// we just give it a pointer to a blob of sprite data and tell it how long it is
	double pack(int* sprite_data, int ints, int stride) {
		int maxx = sprite_data[ints];
		int maxy = 0;

		for (int i = 0; i < ints; i += SPRITE_SIZE) {
			place_sprite(sprite_data, ints, i, maxx, stride);
			maxy = std::max(maxy, sprite_data[i + SPRITE_DATA_Y] + sprite_data[i + SPRITE_DATA_H]);
		}
		
		// write the final size integers in the buffer (this looks worse than
		// it really is, it's it's not actually an array index out of bounds)
		//sprite_data[ints] = maxx;
		sprite_data[ints + 1] = maxy;

		// theoretically other return values might indicate some error code
		return 1.0;
	}

	inline void place_sprite(int* sprite_data, int ints, int index, int maxx, int stride) {
		int limit = maxx - sprite_data[index + SPRITE_DATA_W];
		for (int y = 0; true; y += stride) {
			for (int x = 0; x < limit; x += stride) {
				if (!collide_sprite(sprite_data, ints, index, x, y)) {
					sprite_data[index + SPRITE_DATA_X] = x;
					sprite_data[index + SPRITE_DATA_Y] = y;
					return;
				}
			}
		}
	}

	inline bool collide_sprite(int* sprite_data, int ints, int index, int x, int y) {
		int ow = sprite_data[index + SPRITE_DATA_W];
		int oh = sprite_data[index + SPRITE_DATA_H];

		for (int i = 0; i < ints; i += SPRITE_SIZE) {
			int xx = sprite_data[i + SPRITE_DATA_X];
			if (xx == -1) continue;
			int yy = sprite_data[i + SPRITE_DATA_Y];
			int ww = sprite_data[i + SPRITE_DATA_W];
			int hh = sprite_data[i + SPRITE_DATA_H];
			if (!((xx + ww < x) || (xx > x + ow) || (yy + hh < y) || (yy > y + oh))) return true;
		}
		return false;
	}
}