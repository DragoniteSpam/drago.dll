#define SPRITE_DATA_X 0
#define SPRITE_DATA_Y 1
#define SPRITE_DATA_W 2
#define SPRITE_DATA_H 3
#define PADDING 4
#define SPRITE_SIZE 4

#include "spriteatlas.h"
#include <cmath>

namespace sprite_atlas {
	double pack(int* sprite_data, int ints) {
		int maxx = 0, maxy = 0, nextx = 0, nexty = 0;

		for (int i = 0; i < ints; i += SPRITE_SIZE) {
			int ww = sprite_data[i + SPRITE_DATA_W];
			int hh = sprite_data[i + SPRITE_DATA_H];
			if (maxx == 0) {
				sprite_data[i + SPRITE_DATA_X] = 0;
				sprite_data[i + SPRITE_DATA_Y] = 0;
				nextx += ww + PADDING;
			}
			else {
				if (!place_sprite(sprite_data, ints, i, maxx, maxy)) {
					if (nextx + ww > maxy) {
						nexty = maxy;
						nextx = 0;
					}
					sprite_data[i + SPRITE_DATA_X] = nextx;
					sprite_data[i + SPRITE_DATA_Y] = nexty;
					nextx += ww + PADDING;
				}
			}

			maxx = (int)fmax((double)maxx, (double)(sprite_data[i + SPRITE_DATA_X]) + (double)ww + (double)PADDING);
			maxy = (int)fmax((double)maxy, (double)(sprite_data[i + SPRITE_DATA_Y]) + (double)hh + (double)PADDING);
		}

		sprite_data[ints] = 1 << ((int)ceil(log2((double)maxx)));
		sprite_data[ints + 1] = 1 << ((int)ceil(log2((double)maxy)));

		// theoretically other return values might indicate some error code
		return 1.0;
	}

	bool place_sprite(int* sprite_data, int ints, int index, int maxx, int maxy) {
		for (int x = 0; x < maxx; x += PADDING) {
			for (int y = 0; y < maxx; y += PADDING) {
				if (!collide_sprite(sprite_data, ints, index, x, y)) {
					sprite_data[index + SPRITE_DATA_X] = x;
					sprite_data[index + SPRITE_DATA_Y] = y;
					return true;
				}
			}
		}
		return false;
	}

	bool collide_sprite(int* sprite_data, int ints, int index, int x, int y) {
		int ow = sprite_data[index + SPRITE_DATA_W];
		int oh = sprite_data[index + SPRITE_DATA_H];

		for (int i = 0; i < ints; i += SPRITE_SIZE) {
			if (i != index) {
				int xx = sprite_data[i + SPRITE_DATA_X];
				int yy = sprite_data[i + SPRITE_DATA_Y];
				int ww = sprite_data[i + SPRITE_DATA_W];
				int hh = sprite_data[i + SPRITE_DATA_H];
				if (!((xx + ww + PADDING < x) || (xx > x + ow + PADDING) || (yy + hh + PADDING < y) || (yy > y + oh + PADDING))) return true;
			}
		}
		return false;
	}
}

#undef SPRITE_DATA_X
#undef SPRITE_DATA_Y
#undef SPRITE_DATA_W
#undef SPRITE_DATA_H
#undef PADDING