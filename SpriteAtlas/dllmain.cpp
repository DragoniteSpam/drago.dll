#include "spriteatlas.h"

dllex double sprite_atlas_pack(int* sprite_data, double length, double stride) {
    return sprite_atlas::pack(sprite_data, (int)length, (int)stride);
}

dllex const char* sprite_atlas_version() {
    return sprite_atlas::version();
}