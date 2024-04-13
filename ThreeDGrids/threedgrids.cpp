#include "threedgrids.h"
#include <main/dragomath.h>
#include <math.h>

namespace threedgrids {
	void set_region() {
		// grid, x1, y1, z1, x2, y2, z2, value
		for (int i = x1; i <= x2; i++) {
			for (int j = y1; j <= y2; j++) {
				for (int k = z1; k <= z2; k++) {
					grid[DATA_INDEX(i, j, k, h, d)] = value;
				}
			}
		}
	}

	void set_sphere() {
		// grid, x1, y1, z1, r, value
		int xx1 = x1 - r;
		int yy1 = y1 - r;
		int zz1 = z1 - r;
		int xx2 = x1 + r;
		int yy2 = y1 + r;
		int zz2 = z1 + r;
		for (int i = xx1; i <= xx2; i++) {
			for (int j = yy1; j <= yy2; j++) {
				for (int k = zz1; k <= zz2; k++) {
					if (distance3D(x1, y1, z1, i, j, k) <= r) {
						grid[DATA_INDEX(i, j, k, h, d)] = value;
					}
				}
			}
		}
	}

	float distance3D(float x1, float y1, float z1, float x2, float y2, float z2) {
		return sqrt(powf(x2 - x1, 2.0) + powf(y2 - y1, 2.0) + powf(z2 - z1, 2.0));
	}
}