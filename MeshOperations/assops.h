#ifndef __DRAGO_ASS_OP
#define __DRAGO_ASS_OP

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

namespace assops {
    float convert_fbx(const std::string);
}

#endif