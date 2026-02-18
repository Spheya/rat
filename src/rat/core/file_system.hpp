#pragma once

#include <span>
#include <string>
#include <vector>

namespace rat {

	class FileSystem {
	public:
		enum class Directory { Root, Assets, Engine };

		std::vector<char> loadFile(Directory directory, const char* path);
		std::string loadTextFile(Directory directory, const char* path);

		void writeFile(Directory directory, const char* path, std::span<char> data);
		void writeTextFile(Directory directory, const char* path, const char* data);

		bool exists(Directory directory, const char* path);
	};

} // namespace rat
