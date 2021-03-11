#include "spriteatlas.h"

ex double sprite_atlas_pack(int* sprite_data, double length) {
    return sprite_atlas::pack(sprite_data, ((int)length) >> 2);
}

ex const char* sprite_atlas_version() {
    return sprite_atlas::version();
}