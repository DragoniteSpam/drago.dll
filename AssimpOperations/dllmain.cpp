#include "main/core.h"
#include "assops.h"

dllex const char* version() {
	return assops::version();
}
/*
dllex float add_file(const char* input_file, const char* output_file) {
	assops::add_file(input_file, output_file);
	return 1.0;
}

dllex float convert_all_obj() {
	assops::convert_all_obj();
	return 1.0;
}
*/
dllex double convert_obj(const char* filename, const char* output_name) {
	return assops::convert_obj(std::string(filename), std::string(output_name));
}

dllex double convert_fbx(const char* filename, const char* output_name) {
	return assops::convert_fbx(std::string(filename), std::string(output_name));
}

dllex double convert_dae(const char* filename, const char* output_name) {
	return assops::convert_dae(std::string(filename), std::string(output_name));
}

dllex double convert_3ds(const char* filename, const char* output_name) {
	return assops::convert_3ds(std::string(filename), std::string(output_name));
}

dllex double convert_stl(const char* filename, const char* output_name) {
	return assops::convert_stl(std::string(filename), std::string(output_name));
}

dllex double convert_gltf(const char* filename, const char* output_name) {
	return assops::convert_gltf(std::string(filename), std::string(output_name));
}

dllex double convert_glb(const char* filename, const char* output_name) {
	return assops::convert_glb(std::string(filename), std::string(output_name));
}

dllex double convert_ply(const char* filename, const char* output_name) {
	return assops::convert_ply(std::string(filename), std::string(output_name));
}

dllex double convert_plyb(const char* filename, const char* output_name) {
	return assops::convert_plyb(std::string(filename), std::string(output_name));
}
/*
dllex float convert_all_fbx() {
	return assops::convert_all_fbx();
}

dllex float convert_all_dae() {
	return assops::convert_all_dae();
}

dllex float convert_all_3ds() {
	return assops::convert_all_3ds();
}

dllex float convert_all_stl() {
	return assops::convert_all_stl();
}

dllex float convert_all_ply() {
	return assops::convert_all_ply();
}

dllex float convert_all_plyb() {
	return assops::convert_all_plyb();
}

dllex float convert_all_gltf() {
	return assops::convert_all_gltf();
}

dllex float convert_all_glb() {
	return assops::convert_all_glb();
}
*/