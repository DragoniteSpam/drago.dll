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

    float convert_x(const std::string, std::string, std::string);

    // used for importing
    float convert_obj(const std::string, std::string);

    // used for exporting
    float convert_fbx(const std::string, std::string);
    float convert_dae(const std::string, std::string);
    float convert_stl(const std::string, std::string);
    float convert_gltf(const std::string, std::string);
    float convert_glb(const std::string, std::string);
    float convert_ply(const std::string, std::string);
    float convert_plyb(const std::string, std::string);
}

#endif