#include "assops.h"

namespace assops {
    Assimp::Importer importer;
    Assimp::Exporter exporter;
    //std::vector<std::string> conversion_files;

    const unsigned int import_flags = aiProcess_CalcTangentSpace |
        aiProcess_Triangulate |
        aiProcess_JoinIdenticalVertices |
        aiProcess_SortByPType;
    
    const unsigned int export_flags = 0;

    const char* version() {
        return __DRAGO_ASS_OP;
    }
    /*
    float add_file(const char* input_file, const char* output_file) {
        //convert_obj(input_file, output_file);
        conversion_files.push_back(std::string(input_file));
        conversion_files.push_back(std::string(output_file));
    }
    */
    float convert_x(const std::string filename, const std::string output_filename, const std::string output_type) {
        const aiScene* scene = assops::importer.ReadFile(filename, import_flags);

        if (scene == nullptr) {
            return 0.0;
        }

        assops::exporter.Export(scene, output_type, output_filename);

        return 1.0;
    }
    /*
    void convert_all_x(const std::string output_type) {
        for (int i = 0; i < conversion_files.size(); i += 2) {
            std::string source = conversion_files[i];
            std::string output = conversion_files[i + 1];
            convert_x(source, output, output_type);
        }
        conversion_files.clear();
    }
    */
    float convert_obj(const std::string filename, const std::string output_filename) {
        return convert_x(filename, output_filename, "obj");
    }
    /*
    void convert_all_obj() {
        convert_all_x("obj");
    }
    */
    float convert_fbx(const std::string filename, const std::string output_filename) {
        return convert_x(filename, output_filename, "fbx");
    }

    float convert_dae(const std::string filename, const std::string output_filename) {
        return convert_x(filename, output_filename, "dae");
    }

    float convert_3ds(const std::string filename, const std::string output_filename) {
        return convert_x(filename, output_filename, "3ds");
    }

    float convert_stl(const std::string filename, const std::string output_filename) {
        return convert_x(filename, output_filename, "stl");
    }

    float convert_gltf(const std::string filename, const std::string output_filename) {
        return convert_x(filename, output_filename, "gltf");
    }

    float convert_glb(const std::string filename, const std::string output_filename) {
        return convert_x(filename, output_filename, "glb");
    }

    float convert_ply(const std::string filename, const std::string output_filename) {
        return convert_x(filename, output_filename, "ply");
    }

    float convert_plyb(const std::string filename, const std::string output_filename) {
        return convert_x(filename, output_filename, "plyb");
    }
    /*
    void convert_all_fbx() {
        convert_all_x("fbx");
    }

    void convert_all_dae() {
        convert_all_x("dae");
    }

    void convert_all_3ds() {
        convert_all_x("3ds");
    }

    void convert_all_stl() {
        convert_all_x("stl");
    }

    void convert_all_ply() {
        convert_all_x("ply");
    }

    void convert_all_plyb() {
        convert_all_x("plyb");
    }

    void convert_all_gltf() {
        convert_all_x("gltf");
    }

    void convert_all_glb() {
        convert_all_x("glb");
    }
    */
}