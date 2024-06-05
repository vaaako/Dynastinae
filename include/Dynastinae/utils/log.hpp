#pragma once

#include <cstring>
#include <iostream>
#include <string>

// Macros on the end of the file
namespace Log {
	std::string get_current_time();

	// std::string
	inline void message(const std::string& level, const std::string& message) {
		std::cout << "[" << Log::get_current_time() << "] [" << level << "] " << message << std::endl;
	}

	// fmt
	inline void message(const std::string& level, const char* fmt, ...) {
		std::cout << "[" << level << "] " << fmt << std::endl;
	}

	// Avoid ambiguous
	inline void message_macro(const std::string& level, const std::string& func, const char* fmt, ...) {
		std::cout << "[" << level << "] " << "[" << func << "] " << fmt << std::endl;
	}


	/*
	 * std::string
	 */
	inline void info(const std::string& message) {
		Log::message("INFO", message);
	}

	inline void warning(const std::string& message) {
		Log::message("WARNING", message);
	}

	inline void error(const std::string& message) {
		Log::message("ERROR", message);
	}
};

// Normal macro log
#define LOG_INFO(fmt, ...) Log::message_macro("INFO", __func__, fmt, ##__VA_ARGS__)
#define LOG_WARNING(fmt, ...) Log::message_macro("WARNING", __func__, fmt, ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...) Log::message_macro("ERROR", __func__, fmt, ##__VA_ARGS__)

// No function name
#define LOG_INFO_NF(fmt, ...) Log::message("INFO", fmt, __VA_ARGS__)
#define LOG_WARNING_NF(fmt, ...) Log::message("WARNING", fmt, __VA_ARGS__)
#define LOG_ERROR_NF(fmt, ...) Log::message("ERROR", fmt, __VA_ARGS__)
