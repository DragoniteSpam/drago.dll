#define SPRITE_DATA_X 0
#define SPRITE_DATA_Y 2
#define SPRITE_DATA_W 4
#define SPRITE_DATA_H 6

#include "spriteatlas.h"
#include <cmath>

void pack_atlas(int* sprite_data, int number, int padding) {
	int maxx = 0, maxy = 0, nextx = 0, nexty = 0;

	for (int i = 0; i < number; i += 8) {
		short ww = *(sprite_data + i + SPRITE_DATA_W);
		short hh = *(sprite_data + i + SPRITE_DATA_H);
		if (maxx == 0) {
			*(sprite_data + i + SPRITE_DATA_X) = 0;
			*(sprite_data + i + SPRITE_DATA_Y) = 0;
			nextx += ww;
		}
		else {
			if (!place_sprite(sprite_data, number, i, maxx, maxy)) {
				if (nextx + ww > ((int)ceil(log2((double)maxy))) {
					nexty = maxy;
					nextx = 0;
				}
				*(sprite_data + i + SPRITE_DATA_X) = nextx;
				*(sprite_data + i + SPRITE_DATA_Y) = nexty;
				nextx += ww;
			}
		}

		maxx = (int)fmax((double)maxx, (double)(*(sprite_data + i + SPRITE_DATA_X)));
		maxy = (int)fmax((double)maxy, (double)(*(sprite_data + i + SPRITE_DATA_Y)));
	}

	maxx = 1 << ((int)ceil(log2((double)maxx));
	maxy = 1 << ((int)ceil(log2((double)maxy));
}

bool place_sprite(int* sprite_data, int number, int index, int maxx, int maxy) {
	for (int x = 0; x < maxx; x += 4) {
		for (int y = 0; y < maxy; y += 4) {
			if (!collide_sprite(sprite_data, index, x, y)) {
				*(sprite_data + index + SPRITE_DATA_X) = x;
				*(sprite_data + index + SPRITE_DATA_Y) = y;
				return true;
			}
		}
	}
	return false;
}

bool collide_sprite(int* sprite_data, int number, int index) {
	short ow = *(sprite_data + index + SPRITE_DATA_W);
	short oh = *(sprite_data + index + SPRITE_DATA_H);

	for (int i = 0; i < number; i += 8) {
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