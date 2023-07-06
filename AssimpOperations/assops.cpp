#include "assops.h"

#include <iostream>

const char* assops::version() {
    return __DRAGO_ASS_OP;
}

float assops::convert_fbx(const std::string filename, std::string output_filename) {
    // Create an instance of the Importer class
    Assimp::Importer importer;
    Assimp::Exporter exporter;
    
    // And have it read the given file with some example postprocessing
    // Usually - if speed is not the most important aspect for you - you'll
    // probably to request more postprocessing than we do in this example.
    const aiScene* scene = importer.ReadFile(filename,
        aiProcess_CalcTangentSpace |
        aiProcess_Triangulate |
        aiProcess_JoinIdenticalVertices |
        aiProcess_SortByPType);

    // If the import failed, report it
    if (nullptr == scene) {
        std::cout << "oh no!" << std::endl;
        return 0.0;
    }

    // Now we can access the file's contents.
    std::cout << "imported the file" << std::endl;

    exporter.Export(scene, "obj", output_filename);
    std::cout << "exported the converted file" << std::endl;
    
    return 1.0;
}
