namespace sprite_atlas {
#define SPRITE_DATA_X 0
#define SPRITE_DATA_Y 2
#define SPRITE_DATA_W 4
#define SPRITE_DATA_H 6
#define PADDING 4

#include "spriteatlas.h"
#include <cmath>

	void pack_atlas(short* sprite_data, int length, short padding) {
		short maxx = 0, maxy = 0, nextx = 0, nexty = 0;

		for (int i = 0; i < length; i += 8) {
			short ww = *(sprite_data + i + SPRITE_DATA_W);
			short hh = *(sprite_data + i + SPRITE_DATA_H);
			if (maxx == 0) {
				*(sprite_data + i + SPRITE_DATA_X) = (short)0;
				*(sprite_data + i + SPRITE_DATA_Y) = (short)0;
				nextx += ww + PADDING;
			}
			else {
				if (!place_sprite(sprite_data, length, i, maxx, maxy)) {
					if (nextx + ww > maxy) {
						nexty = maxy;
						nextx = 0;
					}
					*(sprite_data + i + SPRITE_DATA_X) = (short)nextx;
					*(sprite_data + i + SPRITE_DATA_Y) = (short)nexty;
					nextx += ww + PADDING;
				}
			}

			maxx = (int)fmax((double)maxx, (double)(*(sprite_data + i + SPRITE_DATA_X) + ww + PADDING));
			maxy = (int)fmax((double)maxy, (double)(*(sprite_data + i + SPRITE_DATA_Y) + hh + PADDING));
		}

		maxx = 1 << ((int)ceil(log2((double)maxx));
		maxy = 1 << ((int)ceil(log2((double)maxy));
	}

	bool place_sprite(short* sprite_data, int length, int index, int maxx, int maxy) {
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

	bool collide_sprite(short* sprite_data, int length, int index, int x, int y) {
		short ow = *(sprite_data + index + SPRITE_DATA_W);
		short oh = *(sprite_data + index + SPRITE_DATA_H);

		for (int i = 0; i < length; i += 8) {
			if (i != index) {
				short xx = *(sprite_data + index + SPRITE_DATA_X);
				short yy = *(sprite_data + index + SPRITE_DATA_Y);
				short ww = *(sprite_data + index + SPRITE_DATA_W);
				short hh = *(sprite_data + index + SPRITE_DATA_H);
				if (!((xx + ww + 4 < x) || (xx > x + ow + 4) || (yy + hh + 4 < y) || (yy > y + oh + 4))) return true;
			}
		}
		return false;
	}
}