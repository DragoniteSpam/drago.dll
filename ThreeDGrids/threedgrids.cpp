#include "threedgrids.h"
#include <main/dragomath.h>
#include <math.h>
#include <limits>

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

	void set_grid_region() {
		// grid, x1, y1, z1, x2, y2, z2, other, other_x, other_y, other_z
		int dx = other_x - x1;
		int dy = other_y - y1;
		int dz = other_z - z1;
		for (int i = x1; i <= x2; i++) {
			for (int j = y1; j <= y2; j++) {
				for (int k = z1; k <= z2; k++) {
					grid[DATA_INDEX(i, j, k, h, d)] = other[DATA_INDEX(i + dx, j + dy, k + dz, other_h, other_d)];
				}
			}
		}
	}

	void set_grid_sphere() {
		// grid, x1, y1, z1, r, other, other_x, other_y, other_z
		int xx1 = x1 - r;
		int yy1 = y1 - r;
		int zz1 = z1 - r;
		int xx2 = x1 + r;
		int yy2 = y1 + r;
		int zz2 = z1 + r;
		int dx = other_x - x1;
		int dy = other_y - y1;
		int dz = other_z - z1;
		for (int i = xx1; i <= xx2; i++) {
			for (int j = yy1; j <= yy2; j++) {
				for (int k = zz1; k <= zz2; k++) {
					if (distance3D(x1, y1, z1, i, j, k) <= r) {
						grid[DATA_INDEX(i, j, k, h, d)] = other[DATA_INDEX(i + dx, j + dy, k + dz, other_h, other_d)];
					}
				}
			}
		}
	}

	double get_region_mean() {
		double total = 0;
		int n = (x2 - x1 + 1) * (y2 - y1 + 1) * (z2 - z1 + 1);
		// grid, x1, y1, z1, x2, y2, z2
		for (int i = x1; i <= x2; i++) {
			for (int j = y1; j <= y2; j++) {
				for (int k = z1; k <= z2; k++) {
					total += grid[DATA_INDEX(i, j, k, h, d)];
				}
			}
		}
		return total / n;
	}

	double get_region_min() {
		double lowest = std::numeric_limits<double>::infinity();
		// grid, x1, y1, z1, x2, y2, z2
		for (int i = x1; i <= x2; i++) {
			for (int j = y1; j <= y2; j++) {
				for (int k = z1; k <= z2; k++) {
					lowest = fmin(grid[DATA_INDEX(i, j, k, h, d)], lowest);
				}
			}
		}
		return lowest;
	}

	double get_region_max() {
		double highest = -std::numeric_limits<double>::infinity();
		// grid, x1, y1, z1, x2, y2, z2
		for (int i = x1; i <= x2; i++) {
			for (int j = y1; j <= y2; j++) {
				for (int k = z1; k <= z2; k++) {
					highest = fmax(grid[DATA_INDEX(i, j, k, h, d)], highest);
				}
			}
		}
		return highest;
	}

	double get_region_sum() {
		double total = 0;
		// grid, x1, y1, z1, x2, y2, z2
		for (int i = x1; i <= x2; i++) {
			for (int j = y1; j <= y2; j++) {
				for (int k = z1; k <= z2; k++) {
					total += grid[DATA_INDEX(i, j, k, h, d)];
				}
			}
		}
		return total;
	}

	double get_region_standard_deviation() {
		// grid, x1, y1, z1, x2, y2, z2
		double mean = get_region_mean();
		int n = (x2 - x1 + 1) * (y2 - y1 + 1) * (z2 - z1 + 1);
		double squares = 0;
		for (int i = x1; i <= x2; i++) {
			for (int j = y1; j <= y2; j++) {
				for (int k = z1; k <= z2; k++) {
					squares += pow(grid[DATA_INDEX(i, j, k, h, d)] - mean, 2.0);
				}
			}
		}
		return sqrt(mean / n);
	}

	double get_sphere_mean() {
		double total = 0;
		int n = 0;
		// grid, x1, y1, z1, r
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
						total += grid[DATA_INDEX(i, j, k, h, d)];
						n++;
					}
				}
			}
		}
		return total / n;
	}

	double get_sphere_min() {
		double lowest = std::numeric_limits<double>::infinity();
		// grid, x1, y1, z1, r
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
						lowest = fmin(grid[DATA_INDEX(i, j, k, h, d)], lowest);
					}
				}
			}
		}
		return lowest;
	}

	double get_sphere_max() {
		double highest = -std::numeric_limits<double>::infinity();
		// grid, x1, y1, z1, r
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
						highest = fmax(grid[DATA_INDEX(i, j, k, h, d)], highest);
					}
				}
			}
		}
		return highest;
	}

	double get_sphere_sum() {
		double total = 0;
		// grid, x1, y1, z1, r
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
						total += grid[DATA_INDEX(i, j, k, h, d)];
					}
				}
			}
		}
		return total;
	}

	double get_sphere_standard_deviation() {
		// grid, x1, y1, z1, r
		double mean = get_sphere_mean();
		double squares = 0;
		int n = 0;
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
						squares += pow(grid[DATA_INDEX(i, j, k, h, d)] - mean, 2.0);
						n++;
					}
				}
			}
		}
		return sqrt(mean / n);
	}

	void add_region() {
		// grid, x1, y1, z1, x2, y2, z2, value
		for (int i = x1; i <= x2; i++) {
			for (int j = y1; j <= y2; j++) {
				for (int k = z1; k <= z2; k++) {
					grid[DATA_INDEX(i, j, k, h, d)] += value;
				}
			}
		}
	}

	void add_sphere() {
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
						grid[DATA_INDEX(i, j, k, h, d)] += value;
					}
				}
			}
		}
	}

	void add_grid_region() {
		// grid, x1, y1, z1, x2, y2, z2, other, other_x, other_y, other_z
		int dx = other_x - x1;
		int dy = other_y - y1;
		int dz = other_z - z1;
		for (int i = x1; i <= x2; i++) {
			for (int j = y1; j <= y2; j++) {
				for (int k = z1; k <= z2; k++) {
					grid[DATA_INDEX(i, j, k, h, d)] += other[DATA_INDEX(i + dx, j + dy, k + dz, other_h, other_d)];
				}
			}
		}
	}

	void add_grid_sphere() {
		// grid, x1, y1, z1, r, other, other_x, other_y, other_z
		int xx1 = x1 - r;
		int yy1 = y1 - r;
		int zz1 = z1 - r;
		int xx2 = x1 + r;
		int yy2 = y1 + r;
		int zz2 = z1 + r;
		int dx = other_x - x1;
		int dy = other_y - y1;
		int dz = other_z - z1;
		for (int i = xx1; i <= xx2; i++) {
			for (int j = yy1; j <= yy2; j++) {
				for (int k = zz1; k <= zz2; k++) {
					if (distance3D(x1, y1, z1, i, j, k) <= r) {
						grid[DATA_INDEX(i, j, k, h, d)] += other[DATA_INDEX(i + dx, j + dy, k + dz, other_h, other_d)];
					}
				}
			}
		}
	}

	void multiply_region() {
		// grid, x1, y1, z1, x2, y2, z2, value
		for (int i = x1; i <= x2; i++) {
			for (int j = y1; j <= y2; j++) {
				for (int k = z1; k <= z2; k++) {
					grid[DATA_INDEX(i, j, k, h, d)] *= value;
				}
			}
		}
	}

	void multiply_sphere() {
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
						grid[DATA_INDEX(i, j, k, h, d)] *= value;
					}
				}
			}
		}
	}

	void multiply_grid_region() {
		// grid, x1, y1, z1, x2, y2, z2, other, other_x, other_y, other_z
		int dx = other_x - x1;
		int dy = other_y - y1;
		int dz = other_z - z1;
		for (int i = x1; i <= x2; i++) {
			for (int j = y1; j <= y2; j++) {
				for (int k = z1; k <= z2; k++) {
					grid[DATA_INDEX(i, j, k, h, d)] *= other[DATA_INDEX(i + dx, j + dy, k + dz, other_h, other_d)];
				}
			}
		}
	}

	void multiply_grid_sphere() {
		// grid, x1, y1, z1, r, other, other_x, other_y, other_z
		int xx1 = x1 - r;
		int yy1 = y1 - r;
		int zz1 = z1 - r;
		int xx2 = x1 + r;
		int yy2 = y1 + r;
		int zz2 = z1 + r;
		int dx = other_x - x1;
		int dy = other_y - y1;
		int dz = other_z - z1;
		for (int i = xx1; i <= xx2; i++) {
			for (int j = yy1; j <= yy2; j++) {
				for (int k = zz1; k <= zz2; k++) {
					if (distance3D(x1, y1, z1, i, j, k) <= r) {
						grid[DATA_INDEX(i, j, k, h, d)] *= other[DATA_INDEX(i + dx, j + dy, k + dz, other_h, other_d)];
					}
				}
			}
		}
	}

	void lerp_region() {
		// grid, x1, y1, z1, x2, y2, z2, value, f
		for (int i = x1; i <= x2; i++) {
			for (int j = y1; j <= y2; j++) {
				for (int k = z1; k <= z2; k++) {
					double current = grid[DATA_INDEX(i, j, k, h, d)];
					grid[DATA_INDEX(i, j, k, h, d)] = LERP(current, value, f);
				}
			}
		}
	}

	void lerp_sphere() {
		// grid, x1, y1, z1, r, value, f
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
						double current = grid[DATA_INDEX(i, j, k, h, d)];
						grid[DATA_INDEX(i, j, k, h, d)] = LERP(current, value, f);
					}
				}
			}
		}
	}

	void lerp_grid_region() {
		// grid, x1, y1, z1, x2, y2, z2, other, other_x, other_y, other_z
		int dx = other_x - x1;
		int dy = other_y - y1;
		int dz = other_z - z1;
		for (int i = x1; i <= x2; i++) {
			for (int j = y1; j <= y2; j++) {
				for (int k = z1; k <= z2; k++) {
					double current = grid[DATA_INDEX(i, j, k, h, d)];
					double value = other[DATA_INDEX(i + dx, j + dy, k + dz, other_h, other_d)];
					grid[DATA_INDEX(i, j, k, h, d)] = LERP(current, value, f);
				}
			}
		}
	}

	void lerp_grid_sphere() {
		// grid, x1, y1, z1, r, other, other_x, other_y, other_z
		int xx1 = x1 - r;
		int yy1 = y1 - r;
		int zz1 = z1 - r;
		int xx2 = x1 + r;
		int yy2 = y1 + r;
		int zz2 = z1 + r;
		int dx = other_x - x1;
		int dy = other_y - y1;
		int dz = other_z - z1;
		for (int i = xx1; i <= xx2; i++) {
			for (int j = yy1; j <= yy2; j++) {
				for (int k = zz1; k <= zz2; k++) {
					if (distance3D(x1, y1, z1, i, j, k) <= r) {
						double current = grid[DATA_INDEX(i, j, k, h, d)];
						double value = other[DATA_INDEX(i + dx, j + dy, k + dz, other_h, other_d)];
						grid[DATA_INDEX(i, j, k, h, d)] = LERP(current, value, f);
					}
				}
			}
		}
	}

	float distance3D(float x1, float y1, float z1, float x2, float y2, float z2) {
		return sqrt(powf(x2 - x1, 2.0) + powf(y2 - y1, 2.0) + powf(z2 - z1, 2.0));
	}
}