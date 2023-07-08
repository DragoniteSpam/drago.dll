#include "main/core.h"
#include "assops.h"

dllex const char* version() {
	return assops::version();
}

dllex float add_file(const char* input_file, const char* output_file) {
	assops::add_file(input_file, output_file);
	return 1.0;
}

dllex double convert_obj(const char* filename, const char* output_name) {
	assops::convert_obj(std::string(filename), std::string(output_name));
	return 1.0;
}

dllex double convert_fbx(const char* filename, const char* output_name) {
	assops::convert_fbx(std::string(filename), std::string(output_name));
	return 1.0;
}

dllex double convert_dae(const char* filename, const char* output_name) {
	assops::convert_dae(std::string(filename), std::string(output_name));
	return 1.0;
}

dllex double convert_stl(const char* filename, const char* output_name) {
	assops::convert_stl(std::string(filename), std::string(output_name));
	return 1.0;
}

dllex double convert_gltf(const char* filename, const char* output_name) {
	assops::convert_gltf(std::string(filename), std::string(output_name));
	return 1.0;
}

dllex double convert_glb(const char* filename, const char* output_name) {
	assops::convert_glb(std::string(filename), std::string(output_name));
	return 1.0;
}

dllex double convert_ply(const char* filename, const char* output_name) {
	assops::convert_ply(std::string(filename), std::string(output_name));
	return 1.0;
}

dllex double convert_plyb(const char* filename, const char* output_name) {
	assops::convert_plyb(std::string(filename), std::string(output_name));
	return 1.0;
}