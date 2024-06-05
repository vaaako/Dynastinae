#include "Dynastinae/utils/log.hpp"

#include <ctime>
#include <sstream>

std::string Log::get_current_time() {
	std::time_t now = std::time(nullptr);
	std::tm* localTime = std::localtime(&now);
	std::ostringstream oss;
	oss << (localTime->tm_year + 1900) << '-'
		<< (localTime->tm_mon + 1) << '-'
		<< localTime->tm_mday << ' '
		<< localTime->tm_hour << ':'
		<< localTime->tm_min << ':'
		<< localTime->tm_sec;
	return oss.str();
}

