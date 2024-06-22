#include "Dynastinae/utils/file.hpp"
#include "Dynastinae/types.hpp"
#include "Dynastinae/utils/log.hpp"
#include <fstream>
#include <ios>

char* FileHelper::get_file_content(const std::string& path) {
	std::ifstream file = std::ifstream(path);

	if(!file.is_open()) {
		LOG_ERROR("Could not open file %s", path.c_str());
		throw;
	}

	file.seekg(0, std::ios::end);

	// Allocate memory for reading file
	const int64 size = file.tellg(); // Get file size
	char* buffer = new char[static_cast<uint64>(size+ 1)]; // +1 for terminator character

	// Read file
	file.seekg(0, std::ios::beg);
	file.read(buffer, size); // Append to buffer
	buffer[size] = '\0'; // Append terminator character
	file.close();

	// delete []buffer;
	return buffer;
}
