#ifndef __DRAGO_ASS_OP
#define __DRAGO_ASS_OP "0.0"

#include <assimp/Importer.hpp>
#include <assimp/Exporter.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace assops {
    extern Assimp::Importer importer;
    extern Assimp::Exporter exporter;

    const char* version();
    float convert_obj(const std::string, std::string);
}

#endif