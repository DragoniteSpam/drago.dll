#ifndef __DRAGO_ASS_OP
#define __DRAGO_ASS_OP "0.0"

#include <assimp/Importer.hpp>
#include <assimp/Exporter.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vector>

namespace assops {
    extern Assimp::Importer importer;
    extern Assimp::Exporter exporter;
    extern std::vector<std::string> conversion_files;

    const char* version();
    
    float add_file(const char*, const char*);

    float convert_x(const std::string, const std::string, const std::string);
    void convert_all_x(const std::string);

    // used for importing
    float convert_obj(const std::string, std::string);
    void convert_all_obj();

    // used for exporting
    float convert_fbx(const std::string, const std::string);
    float convert_dae(const std::string, const std::string);
    float convert_stl(const std::string, const std::string);
    float convert_gltf(const std::string, const std::string);
    float convert_glb(const std::string, const std::string);
    float convert_ply(const std::string, const std::string);
    float convert_plyb(const std::string, const std::string);
    void convert_all_fbx();
    void convert_all_dae();
    void convert_all_stl();
    void convert_all_ply();
    void convert_all_plyb();
    void convert_all_gltf();
    void convert_all_glb();
}

#endif