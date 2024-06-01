#include "Dynastinae/utils/string.hpp"

std::string StringHelper::file_extension(const std::string& filename) {
	// Find the last position of '.' in the file name
	size_t dot_position = filename.find_last_of(".");
	if(dot_position != std::string::npos) {
		return filename.substr(dot_position + 1); // Extract and return the extension
	}

	// Return an empty string if the dot is not found
	return "";
}
