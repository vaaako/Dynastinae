#pragma once

#include <iostream>

namespace Log {
	inline void info(const std::string& message) {
		std::cout << "INFO: " + message << std::endl;
	}

	inline void warning(const std::string& message) {
		std::cout << "WARNING: " + message << std::endl;
	}

	inline void error(const std::string& message) {
		std::cout << "ERROR: " + message << std::endl;
	}
};
