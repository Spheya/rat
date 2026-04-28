#ifdef RAT_DEV_TOOLS

	#include "logger.hpp"

	#include <iostream>

namespace rat {

	void message(const char* message, LogLevel level) {
		const char* prefix;
		switch(level) {
		case LogLevel::Warn: prefix = "\033[1;33mWarn > \033[0m"; break;
		case LogLevel::Error: prefix = "\033[1;31mError > \033[0m"; break;
		default: prefix = "> "; break;
		}

		std::cout << prefix << message << "\n";
	}

} // namespace rat

#endif
