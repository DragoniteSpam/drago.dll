#include "spriteatlas.h"

ex double init() {
    return 1.0;
}

ex double sprite_pack_textures(int* sprite_data, double length) {
    return sprite_atlas::pack(sprite_data, ((int)length) >> 2);
}

ex const char* sprite_pack_version() {
    return sprite_atlas::version();
}