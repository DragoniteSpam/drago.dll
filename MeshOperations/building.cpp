#include "building.h"
#include "meshops.h"

namespace meshops {
	float chunk_size = 0;
	float chunk_startx = 0;
	float chunk_starty = 0;
	float chunk_endx = 0;
	float chunk_endy = 0;

	long vertex_formatted(float* data, float* out, int len, int format) {
		bool use_position_2d =			format & VFX_POSITION_2D;
		bool use_position_3d =			format & VFX_POSITION_3D;
		bool use_normal =				format & VFX_NORMAL;
		bool use_texcoord =				format & VFX_TEXCOORD;
		bool use_colour =				format & VFX_COLOUR;
		bool use_barycentric =			format & VFX_BARYCENTRIC;
		bool use_tangent =				format & VFX_TANGENT;
		bool use_bitangent =			format & VFX_BITANGENT;

		bool use_small_normal =			format & VFX_SMALL_NORMAL;
		bool use_small_tangent =		format & VFX_SMALL_TANGENT;
		bool use_small_bitangent =		format & VFX_SMALL_BITANGENT;
		bool use_small_texcoord =		format & VFX_SMALL_TEXCOORD;
		bool use_small_normal_pal =		format & VFX_SMALL_NORMAL_PAL;
		bool use_small_barycentric =	format & VFX_SMALL_BARYCENTIRC;

		float x, y, z, nx, ny, nz, u, v, barx, bary, barz, tax, tay, taz, bix, biy, biz;
		unsigned int c;
		double value;
		long byte = 0;

		for (int i = 0; i < len; i += meshops::vertex_size) {
			x = data[i];
			y = data[i + 1];
			z = data[i + 2];
			nx = data[i + 3];
			ny = data[i + 4];
			nz = data[i + 5];
			u = data[i + 6];
			v = data[i + 7];
			c = ((unsigned int*)data)[i + 8];
			barx = data[i + 9];
			bary = data[i + 10];
			barz = data[i + 11];
			tax = data[i + 12];
			tay = data[i + 13];
			taz = data[i + 14];
			bix = data[i + 15];
			biy = data[i + 16];
			biz = data[i + 17];

			if (use_position_2d) {
				out[byte++] = x;
				out[byte++] = y;
			}
			if (use_position_3d) {
				out[byte++] = x;
				out[byte++] = y;
				out[byte++] = z;
			}
			if (use_normal) {
				out[byte++] = nx;
				out[byte++] = ny;
				out[byte++] = nz;
			}
			if (use_texcoord) {
				out[byte++] = u;
				out[byte++] = v;
			}
			if (use_colour) {
				((unsigned int*)out)[byte++] = c;
			}
			if (use_barycentric) {
				out[byte++] = barx;
				out[byte++] = bary;
				out[byte++] = barz;
			}
			if (use_tangent) {
				out[byte++] = tax;
				out[byte++] = tay;
				out[byte++] = taz;
			}
			if (use_bitangent) {
				out[byte++] = bix;
				out[byte++] = biy;
				out[byte++] = biz;
			}
			if (use_small_normal) {
				nx = ADJUST(nx, 0.0, 255.0, -1.0, 1.0);
				ny = ADJUST(ny, 0.0, 255.0, -1.0, 1.0);
				nz = ADJUST(nz, 0.0, 255.0, -1.0, 1.0);
				value = nx + ny * 256.0 + nz * 65536.0;
				((unsigned int*)out)[byte++] = (unsigned int)value;
			}
			if (use_small_tangent) {
				tax = ADJUST(tax, 0.0, 255.0, -1.0, 1.0);
				tay = ADJUST(tay, 0.0, 255.0, -1.0, 1.0);
				taz = ADJUST(taz, 0.0, 255.0, -1.0, 1.0);
				value = tax + tay * 256.0 + taz * 65536.0;
				((unsigned int*)out)[byte++] = (unsigned int)value;
			}
			if (use_small_bitangent) {
				bix = ADJUST(bix, 0.0, 255.0, -1.0, 1.0);
				biy = ADJUST(biy, 0.0, 255.0, -1.0, 1.0);
				biz = ADJUST(biz, 0.0, 255.0, -1.0, 1.0);
				value = bix + biy * 256.0 + biz * 65536.0;
				((unsigned int*)out)[byte++] = (unsigned int)value;
			}
			if (use_small_texcoord) {
				u = floor(u * 255.0);
				v = floor(v * 255.0);
				value = u + v * 256.0;
				((unsigned int*)out)[byte++] = (unsigned int)value;
			}
			if (use_small_texcoord) {
				nx = ADJUST(nx, 0.0, 255.0, -1.0, 1.0);
				ny = ADJUST(ny, 0.0, 255.0, -1.0, 1.0);
				nz = ADJUST(nz, 0.0, 255.0, -1.0, 1.0);
				u = floor(u * 255.0);
				value = nx + ny * 256.0 + nz * 65536.0 + u * 16777216.0;
				((unsigned int*)out)[byte++] = (unsigned int)value;
			}
		}

		return byte;
	}

	void chunk_settings(float chunk_size, float startx, float starty, float endx, float endy) {
		meshops::chunk_size = chunk_size;
		float chunk_startx = startx;
		float chunk_starty = starty;
		meshops::chunk_endx = endx;
		meshops::chunk_endy = endy;
	}

	void chunk_analyze(float* data, float* meta, int data_len, int meta_len) {
		int x1, y1, z1, x2, y2, z2, x3, y3, z3;
		for (int i = 0; i < data_len; i += meshops::vertex_size * 3) {
			x1 = data[i + meshops::vertex_size * 0 + 0];
			y1 = data[i + meshops::vertex_size * 0 + 1];
			z1 = data[i + meshops::vertex_size * 0 + 2];
			x2 = data[i + meshops::vertex_size * 1 + 0];
			y2 = data[i + meshops::vertex_size * 1 + 1];
			z2 = data[i + meshops::vertex_size * 1 + 2];
			x3 = data[i + meshops::vertex_size * 2 + 0];
			y3 = data[i + meshops::vertex_size * 2 + 1];
			z3 = data[i + meshops::vertex_size * 2 + 2];
		}
	}

	long chunk(float* data, int len) {
		return 1;
	}
}