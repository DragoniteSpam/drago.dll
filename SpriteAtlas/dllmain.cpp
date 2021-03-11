#include "spriteatlas.h"

ex double init() {
    return 1.0;
}

ex double pack_textures(int* sprite_data, double length) {
    return sprite_atlas::pack(sprite_data, ((int)length) >> 2);
}

ex const char* version() {
    return sprite_atlas::version();
}