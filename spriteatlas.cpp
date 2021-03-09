#define SPRITE_DATA_X 0
#define SPRITE_DATA_Y 4
#define SPRITE_DATA_W 8
#define SPRITE_DATA_H 12
#define PADDING 4

#include "spriteatlas.h"
#include <cmath>

namespace sprite_atlas {
	double pack(int* sprite_data, int length) {
		int maxx = 0, maxy = 0, nextx = 0, nexty = 0;

		for (int i = 0; i < length; i += 8) {
			int ww = *(sprite_data + i + SPRITE_DATA_W);
			int hh = *(sprite_data + i + SPRITE_DATA_H);
			if (maxx == 0) {
				*(sprite_data + i + SPRITE_DATA_X) = 0;
				*(sprite_data + i + SPRITE_DATA_Y) = 0;
				nextx += ww + PADDING;
			}
			else {
				if (!place_sprite(sprite_data, length, i, maxx, maxy)) {
					if (nextx + ww > maxy) {
						nexty = maxy;
						nextx = 0;
					}
					*(sprite_data + i + SPRITE_DATA_X) = nextx;
					*(sprite_data + i + SPRITE_DATA_Y) = nexty;
					nextx += ww + PADDING;
				}
			}

			maxx = (int)fmax((double)maxx, (double)(*(sprite_data + i + SPRITE_DATA_X)) + (double)ww + (double)PADDING);
			maxy = (int)fmax((double)maxy, (double)(*(sprite_data + i + SPRITE_DATA_Y)) + (double)hh + (double)PADDING);
		}

		*(sprite_data + length + SPRITE_DATA_X - 8) = 1 << ((int)ceil(log2((double)maxx)));
		*(sprite_data + length + SPRITE_DATA_X - 4) = 1 << ((int)ceil(log2((double)maxy)));
		
		// theoretically other return values might indicate some error code
		return 1.0;
	}

	bool place_sprite(int* sprite_data, int length, int index, int maxx, int maxy) {
		for (int x = 0; x < maxx; x += 4) {
			for (int y = 0; y < maxx; y += 4) {
				if (!collide_sprite(sprite_data, length, index, x, y)) {
					*(sprite_data + index + SPRITE_DATA_X) = x;
					*(sprite_data + index + SPRITE_DATA_Y) = y;
					return true;
				}
			}
		}
		return false;
	}

	bool collide_sprite(int* sprite_data, int length, int index, int x, int y) {
		int ow = *(sprite_data + index + SPRITE_DATA_W);
		int oh = *(sprite_data + index + SPRITE_DATA_H);

		for (int i = 0; i < length; i += 8) {
			if (i != index) {
				int xx = *(sprite_data + index + SPRITE_DATA_X);
				int yy = *(sprite_data + index + SPRITE_DATA_Y);
				int ww = *(sprite_data + index + SPRITE_DATA_W);
				int hh = *(sprite_data + index + SPRITE_DATA_H);
				if (!((xx + ww + 4 < x) || (xx > x + ow + 4) || (yy + hh + 4 < y) || (yy > y + oh + 4))) return true;
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