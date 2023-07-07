#include "assops.h"

#include <iostream>

namespace assops {
    Assimp::Importer importer;
    Assimp::Exporter exporter;

    const unsigned int import_flags = aiProcess_CalcTangentSpace |
        aiProcess_Triangulate |
        aiProcess_JoinIdenticalVertices |
        aiProcess_SortByPType;
    
    const unsigned int export_flags = 0;

    const char* version() {
        return __DRAGO_ASS_OP;
    }

    float convert_x(const std::string filename, std::string output_filename, std::string output_type) {
        const aiScene* scene = assops::importer.ReadFile(filename, import_flags);

        if (scene == nullptr)
            return 0.0;

        assops::exporter.Export(scene, output_type, output_filename);

        return 1.0;
    }

    float convert_obj(const std::string filename, std::string output_filename) {
        return convert_x(filename, output_filename, "obj");
    }

    float convert_fbx(const std::string filename, std::string output_filename) {
        return convert_x(filename, output_filename, "fbx");
    }

    float convert_dae(const std::string filename, std::string output_filename) {
        return convert_x(filename, output_filename, "dae");
    }

    float convert_stl(const std::string filename, std::string output_filename) {
        return convert_x(filename, output_filename, "stl");
    }

    float convert_gltf(const std::string filename, std::string output_filename) {
        return convert_x(filename, output_filename, "gltf");
    }

    float convert_glb(const std::string filename, std::string output_filename) {
        return convert_x(filename, output_filename, "glb");
    }

    float convert_ply(const std::string filename, std::string output_filename) {
        return convert_x(filename, output_filename, "ply");
    }

    float convert_plyb(const std::string filename, std::string output_filename) {
        return convert_x(filename, output_filename, "plyb");
    }
}