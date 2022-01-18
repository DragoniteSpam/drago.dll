#include "building.h"
#include "meshops.h"

namespace meshops {
	int chunk_size = 0;
	float chunk_startx = 0;
	float chunk_starty = 0;
	float chunk_endx = 0;
	float chunk_endy = 0;
	float chunk_countx = 0;
	float chunk_county = 0;

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
		int iteration = meshops::vertex_size;

		for (int i = 0; i < len; i += iteration) {
			x = data[i];
			y = data[i + 1];
			z = data[i + 2];
			nx = data[i + 3];
			ny = data[i + 4];
			nz = data[i + 5];
			u = data[i + 6];
			v = data[i + 7];
			c = ((unsigned int*)data)[i + 8];
			tax = data[i + 9];
			tay = data[i + 10];
			taz = data[i + 11];
			bix = data[i + 12];
			biy = data[i + 13];
			biz = data[i + 14];
			barx = data[i + 15];
			bary = data[i + 16];
			barz = data[i + 17];

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
				nx = ADJUST(nx, 0.0f, 255.0f, -1.0f, 1.0f);
				ny = ADJUST(ny, 0.0f, 255.0f, -1.0f, 1.0f);
				nz = ADJUST(nz, 0.0f, 255.0f, -1.0f, 1.0f);
				value = nx + ny * 256.0 + nz * 65536.0;
				((unsigned int*)out)[byte++] = (unsigned int)value;
			}
			if (use_small_tangent) {
				tax = ADJUST(tax, 0.0f, 255.0f, -1.0f, 1.0f);
				tay = ADJUST(tay, 0.0f, 255.0f, -1.0f, 1.0f);
				taz = ADJUST(taz, 0.0f, 255.0f, -1.0f, 1.0f);
				value = tax + tay * 256.0 + taz * 65536.0;
				((unsigned int*)out)[byte++] = (unsigned int)value;
			}
			if (use_small_bitangent) {
				bix = ADJUST(bix, 0.0f, 255.0f, -1.0f, 1.0f);
				biy = ADJUST(biy, 0.0f, 255.0f, -1.0f, 1.0f);
				biz = ADJUST(biz, 0.0f, 255.0f, -1.0f, 1.0f);
				value = bix + biy * 256.0 + biz * 65536.0;
				((unsigned int*)out)[byte++] = (unsigned int)value;
			}
			if (use_small_texcoord) {
				u = floor(u * 255.0f);
				v = floor(v * 255.0f);
				value = u + v * 256.0;
				((unsigned int*)out)[byte++] = (unsigned int)value;
			}
			if (use_small_texcoord) {
				nx = ADJUST(nx, 0.0f, 255.0f, -1.0f, 1.0f);
				ny = ADJUST(ny, 0.0f, 255.0f, -1.0f, 1.0f);
				nz = ADJUST(nz, 0.0f, 255.0f, -1.0f, 1.0f);
				u = floor(u * 255.0f);
				value = nx + ny * 256.0 + nz * 65536.0 + u * 16777216.0;
				((unsigned int*)out)[byte++] = (unsigned int)value;
			}
		}

		return byte;
	}

#define VERTEX_CHUNK_ADDRESS(x, y, h, alignment) ((int)((alignment) * (((x) * (h)) + (y))))

	void chunk_settings(int chunk_size, float startx, float starty, float endx, float endy) {
		meshops::chunk_size = chunk_size;
		meshops::chunk_startx = startx;
		meshops::chunk_starty = starty;
		meshops::chunk_endx = endx;
		meshops::chunk_endy = endy;
		meshops::chunk_countx = (endx - startx) / chunk_size;
		meshops::chunk_county = (endy - starty) / chunk_size;
	}

	void chunk_analyze(float* data, long long* meta, int data_len, int meta_len) {
		float x1, y1, x2, y2, x3, y3;
		int address1, address2, address3;
		int iteration = meshops::vertex_size * 3;
		int vsize = meshops::vertex_size;
		int csize = meshops::chunk_size;
		float startx = meshops::chunk_startx;
		float starty = meshops::chunk_starty;
		float county = meshops::chunk_county;

		for (int i = 0; i < data_len; i += iteration) {
			x1 = (data[i + vsize * 0 + 0] - startx) / csize;
			y1 = (data[i + vsize * 0 + 1] - starty) / csize;
			x2 = (data[i + vsize * 1 + 0] - startx) / csize;
			y2 = (data[i + vsize * 1 + 1] - starty) / csize;
			x3 = (data[i + vsize * 2 + 0] - startx) / csize;
			y3 = (data[i + vsize * 2 + 1] - starty) / csize;

			address1 = VERTEX_CHUNK_ADDRESS(floor(x1), floor(y1), county, 2);
			address2 = VERTEX_CHUNK_ADDRESS(floor(x2), floor(y2), county, 2);
			address3 = VERTEX_CHUNK_ADDRESS(floor(x3), floor(y3), county, 2);

			meta[address1]++;
			if (address1 != address2)
				meta[address2]++;
			if (address1 != address3 && address2 != address3)
				meta[address3]++;
		}
	}

	void chunk(float* data, long long* meta, int length) {
		float x1, y1, z1, x2, y2, z2, x3, y3, z3;
		float nx1, ny1, nz1, nx2, ny2, nz2, nx3, ny3, nz3;
		float u1, v1, u2, v2, u3, v3;
		unsigned int c1, c2, c3;
		float tx1, ty1, tz1, tx2, ty2, tz2, tx3, ty3, tz3;
		float bx1, by1, bz1, bx2, by2, bz2, bx3, by3, bz3;
		float barx1, bary1, barz1, barx2, bary2, barz2, barx3, bary3, barz3;

		int address1, address2, address3;
		int iteration = meshops::vertex_size * 3;
		int vsize = meshops::vertex_size;
		int csize = meshops::chunk_size;
		float startx = meshops::chunk_startx;
		float starty = meshops::chunk_starty;
		float county = meshops::chunk_county;

		for (int i = 0; i < length; i += iteration) {
			x1 = (data[i + vsize * 0 + 0] - startx) / csize;
			y1 = (data[i + vsize * 0 + 1] - starty) / csize;
			z1 = (data[i + vsize * 0 + 2]);
			nx1 = (data[i + vsize * 0 + 3]);
			ny1 = (data[i + vsize * 0 + 4]);
			nz1 = (data[i + vsize * 0 + 5]);
			u1 = (data[i + vsize * 0 + 6]);
			v1 = (data[i + vsize * 0 + 7]);
			c1 = ((unsigned int*)data)[i + vsize * 0 + 8];
			barx1 = (data[i + vsize * 0 + 9]);
			bary1 = (data[i + vsize * 0 + 10]);
			barz1 = (data[i + vsize * 0 + 11]);
			tx1 = (data[i + vsize * 0 + 12]);
			ty1 = (data[i + vsize * 0 + 13]);
			tz1 = (data[i + vsize * 0 + 14]);
			bx1 = (data[i + vsize * 0 + 15]);
			by1 = (data[i + vsize * 0 + 16]);
			bz1 = (data[i + vsize * 0 + 17]);

			x2 = (data[i + vsize * 1 + 0] - startx) / csize;
			y2 = (data[i + vsize * 1 + 1] - starty) / csize;
			z2 = (data[i + vsize * 1 + 2]);
			nx2 = (data[i + vsize * 1 + 3]);
			ny2 = (data[i + vsize * 1 + 4]);
			nz2 = (data[i + vsize * 1 + 5]);
			u2 = (data[i + vsize * 1 + 6]);
			v2 = (data[i + vsize * 1 + 7]);
			c2 = ((unsigned int*)data)[i + vsize * 1 + 8];
			barx2 = (data[i + vsize * 1 + 9]);
			bary2 = (data[i + vsize * 1 + 10]);
			barz2 = (data[i + vsize * 1 + 11]);
			tx2 = (data[i + vsize * 1 + 12]);
			ty2 = (data[i + vsize * 1 + 13]);
			tz2 = (data[i + vsize * 1 + 14]);
			bx2 = (data[i + vsize * 1 + 15]);
			by2 = (data[i + vsize * 1 + 16]);
			bz2 = (data[i + vsize * 1 + 17]);

			x3 = (data[i + vsize * 2 + 0] - startx) / csize;
			y3 = (data[i + vsize * 2 + 1] - starty) / csize;
			z3 = (data[i + vsize * 2 + 2]);
			nx3 = (data[i + vsize * 2 + 3]);
			ny3 = (data[i + vsize * 2 + 4]);
			nz3 = (data[i + vsize * 2 + 5]);
			u3 = (data[i + vsize * 2 + 6]);
			v3 = (data[i + vsize * 2 + 7]);
			c3 = ((unsigned int*)data)[i + vsize * 2 + 8];
			barx3 = (data[i + vsize * 2 + 9]);
			bary3 = (data[i + vsize * 2 + 10]);
			barz3 = (data[i + vsize * 2 + 11]);
			tx3 = (data[i + vsize * 2 + 12]);
			ty3 = (data[i + vsize * 2 + 13]);
			tz3 = (data[i + vsize * 2 + 14]);
			bx3 = (data[i + vsize * 2 + 15]);
			by3 = (data[i + vsize * 2 + 16]);
			bz3 = (data[i + vsize * 2 + 17]);

			address1 = VERTEX_CHUNK_ADDRESS(floor((x1 - startx) / csize), floor((y1 - starty) / csize), county, 2);
			address2 = VERTEX_CHUNK_ADDRESS(floor((x2 - startx) / csize), floor((y2 - starty) / csize), county, 2);
			address3 = VERTEX_CHUNK_ADDRESS(floor((x3 - startx) / csize), floor((y3 - starty) / csize), county, 2);

			long long* count1 = &meta[address1];
			long long* count2 = &meta[address2];
			long long* count3 = &meta[address3];
			float* chunk1 = ((float**)meta)[address1 + 1];
			float* chunk2 = ((float**)meta)[address2 + 1];
			float* chunk3 = ((float**)meta)[address3 + 1];

			write_vertex(chunk1, count1, x1, y1, z1, nx1, ny1, nz1, u1, v1, c1, tx1, ty1, tz1, bx1, by1, bz1, barx1, bary1, barz1);
			write_vertex(chunk1, count1, x2, y2, z2, nx2, ny2, nz2, u2, v2, c2, tx2, ty2, tz2, bx2, by2, bz2, barx2, bary2, barz2);
			write_vertex(chunk1, count1, x3, y3, z3, nx3, ny3, nz3, u3, v3, c3, tx3, ty3, tz3, bx3, by3, bz3, barx3, bary3, barz3);

			if (address1 != address2) {
				write_vertex(chunk1, count1, x1, y1, z1, nx1, ny1, nz1, u1, v1, c1, tx1, ty1, tz1, bx1, by1, bz1, barx1, bary1, barz1);
				write_vertex(chunk1, count1, x2, y2, z2, nx2, ny2, nz2, u2, v2, c2, tx2, ty2, tz2, bx2, by2, bz2, barx2, bary2, barz2);
				write_vertex(chunk1, count1, x3, y3, z3, nx3, ny3, nz3, u3, v3, c3, tx3, ty3, tz3, bx3, by3, bz3, barx3, bary3, barz3);
			}
			if (address1 != address3 && address2 != address3) {
				write_vertex(chunk1, count1, x1, y1, z1, nx1, ny1, nz1, u1, v1, c1, tx1, ty1, tz1, bx1, by1, bz1, barx1, bary1, barz1);
				write_vertex(chunk1, count1, x2, y2, z2, nx2, ny2, nz2, u2, v2, c2, tx2, ty2, tz2, bx2, by2, bz2, barx2, bary2, barz2);
				write_vertex(chunk1, count1, x3, y3, z3, nx3, ny3, nz3, u3, v3, c3, tx3, ty3, tz3, bx3, by3, bz3, barx3, bary3, barz3);
			}
		}
	}

	inline void write_vertex(
			float* out, long long* address,
			float x, float y, float z,
			float nx, float ny, float nz,
			float u, float v,
			unsigned int c, 
			float tx, float ty, float tz,
			float bx, float by, float bz,
			float bc1, float bc2, float bc3) {
		// position
		out[(*address)++] = x;
		out[(*address)++] = y;
		out[(*address)++] = z;
		// normals oughta be calculated later anyway
		out[(*address)++] = nx;
		out[(*address)++] = ny;
		out[(*address)++] = nz;
		// texture and color
		out[(*address)++] = u;
		out[(*address)++] = v;
		((unsigned int*)out)[(*address)++] = c;
		// tangent and bitangent, we calculate these later
		out[(*address)++] = tx;
		out[(*address)++] = ty;
		out[(*address)++] = tz;
		out[(*address)++] = bx;
		out[(*address)++] = by;
		out[(*address)++] = bz;
		// barycentrics
		out[(*address)++] = bc1;
		out[(*address)++] = bc2;
		out[(*address)++] = bc3;
	}

#undef VERTEX_CHUNK_ADDRESS
}