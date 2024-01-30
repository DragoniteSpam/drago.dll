#include "spriteatlas.h"

dllex double sprite_atlas_pack(int* sprite_data, double length, double stride, double force_po2) {
    return sprite_atlas::pack(sprite_data, ((int)length) >> 2, (int)stride, (bool)force_po2);
}

dllex const char* sprite_atlas_version() {
    return sprite_atlas::version();
}