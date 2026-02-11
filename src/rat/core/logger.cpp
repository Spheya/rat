#include "logger.hpp"

#include <iostream>

namespace rat {
	static std::function<void(std::string_view, std::source_location, LogLevel)> s_MessageCallback; // NOLINT

	void setMessageCallback(std::function<void(std::string_view, std::source_location, LogLevel)> callback) {
		s_MessageCallback = callback;
	}

	void message(std::string_view message, std::source_location location, LogLevel level) {
		if(s_MessageCallback) {
			s_MessageCallback(message, location, level);
		} else {
			std::string_view fileName = location.file_name();
			size_t lastSlash = fileName.find_last_of("\\/");
			if(lastSlash != std::string_view::npos && lastSlash != fileName.size() - 1) fileName = fileName.substr(lastSlash + 1);

			std::string msg;
			size_t len = message.length();
			switch(level) {
			case LogLevel::Warn:
				msg = "\033[1;33mWarn > \033[0m" + std::string(message);
				len += 7;
				break;
			case LogLevel::Error:
				msg = "\033[1;31mError > \033[0m" + std::string(message);
				len += 8;
				break;
			default:
				msg = "> " + std::string(message);
				len += 2;
				break;
			}

			if(len < 96) { msg.resize(80 + (msg.length() - len), ' '); }

			if(level == LogLevel::Error) {
				std::cerr << msg << "\033[1;30m (" << fileName << ":" << location.line() << ")\033[0m" << std::endl;
			} else {
				std::cout << msg << "\033[1;30m (" << fileName << ":" << location.line() << ")\033[0m" << std::endl;
			}
		}
	}

} // namespace rat
