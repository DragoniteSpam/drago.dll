#include "main/core.h"
#include "assops.h"

dllex const char* version() {
	return assops::version();
}

// assimp
dllex double convert_obj(const char* filename, const char* output_name) {
	assops::convert_obj(std::string(filename), std::string(output_name));
	return 1.0;
}