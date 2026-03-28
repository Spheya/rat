#include "logger.hpp"

#include <iostream>

namespace rat {

	void message(std::string_view message, LogLevel level) {
		switch(level) {
		case LogLevel::Info: std::cout << "\033[1;32mInfo > \033[0m"; break;
		case LogLevel::Warn: std::cout << "\033[1;33mWarn > \033[0m"; break;
		case LogLevel::Error: std::cout << "\033[1;31mError > \033[0m"; break;
		default: std::cout << "> "; break;
		}
		std::cout << message << '\n';
	}

} // namespace rat
