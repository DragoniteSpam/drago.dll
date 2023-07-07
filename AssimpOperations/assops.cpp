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

    float convert_obj(const std::string filename, std::string output_filename) {
        const aiScene* scene = assops::importer.ReadFile(filename, import_flags);

        if (scene == nullptr)
            return 0.0;

        assops::exporter.Export(scene, "obj", output_filename);

        return 1.0;
    }
}