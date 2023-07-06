#include "main/core.h"
#include "assops.h"

dllex const char* assops_version() {
	return "0.0";
}

// assimp
dllex double convert_fbx(const char* filename, const char* output_name) {
	assops::convert_fbx(std::string(filename), std::string(output_name));
	return 1.0;
}