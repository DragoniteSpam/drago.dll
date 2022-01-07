#ifndef __DRAGO_MESH_OP_BUILDING
#define __DRAGO_MESH_OP_BUILDING

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

#define NORMALIZE(val, mn, mx, omin, omax) ((mn) + (((val) - (omin)) / ((omax) - (omin))) * ((mx) - (mn)))

namespace meshops {
	long vertex_formatted(float*, float*, int, int);
}

#endif