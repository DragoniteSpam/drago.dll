#ifndef __DRAGO_MESH_OP_BUILDING
#define __DRAGO_MESH_OP_BUILDING

#include <algorithm>
#include "main/core.h"
#include "meshops.h"

// standard attributes
#define VFX_POSITION_2D         0x00001
#define VFX_POSITION_3D         0x00002
#define VFX_NORMAL              0x00004
#define VFX_TEXCOORD			0x00008
#define VFX_COLOUR              0x00010
#define VFX_TANGENT             0x00020
#define VFX_BITANGENT           0x00040
#define VFX_BARYCENTRIC         0x00080
// special things
#define VFX_SMALL_NORMAL        0x00100     // 4 bytes (nx ny nz 0)
#define VFX_SMALL_TANGENT       0x00200     // 4 bytes (tx ty tz 0)
#define VFX_SMALL_BITANGENT     0x00400     // 4 bytes (bx by bz 0)
#define VFX_SMALL_TEXCOORD      0x00800     // 4 bytes (u v 0 0)
#define VFX_SMALL_NORMAL_PAL    0x01000     // 4 bytes (nx ny nz and a byte representing a 256 color palette index)
#define VFX_SMALL_BARYCENTIRC   0x02000     // 4 bytes (x y z 0)

#define ADJUST(val, mn, mx, omin, omax) ((mn) + (((val) - (omin)) / ((omax) - (omin))) * ((mx) - (mn)))

namespace meshops {
	extern int chunk_size;
	extern float chunk_startx;
	extern float chunk_starty;
	extern float chunk_endx;
	extern float chunk_endy;
	extern float chunk_countx;
	extern float chunk_county;

	long vertex_formatted(float*, float*, int, int);
	void chunk_settings(int, float, float, float, float);
	void chunk_analyze(float*, long long*, int, int);
	void chunk(float*, long long*, int);

	void write_vertex(float*, long long*, float, float, float, float, float, float, float, float, unsigned int, float, float, float, float, float, float, float, float, float);
}

#endif