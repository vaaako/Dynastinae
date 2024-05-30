#pragma once

#include <string>

namespace String {
	inline std::string file_extension(const std::string& file) {
		// Find the last position of '.' in the file name
		size_t dot_position = file.find_last_of(".");
		if(dot_position != std::string::npos) {
			// Extract and return the extension
			return file.substr(dot_position + 1);
		}

		// Return an empty string if the dot is not found
		return "";
	}
}
