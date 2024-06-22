#pragma once

#include <filesystem>

// Needs to be a macro because of __FILE__
#define SOURCE_DIR std::filesystem::path(__FILE__).parent_path().string()


namespace FileHelper {
	// Remember to delete correcly. e.g. delete []content;
	char* get_file_content(const std::string& path);

	inline std::filesystem::path current_path() {
		return std::filesystem::current_path();
	}
};
