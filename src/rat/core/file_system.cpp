#include "file_system.hpp"

#include <cassert>
#include <fstream>

#include "logger.hpp"

namespace rat {

	static std::string getPath(FileSystem::Directory directory, const char* path) {
		std::string fullPath;
		switch(directory) {
		case FileSystem::Directory::Root: fullPath = path; break;
		case FileSystem::Directory::Assets: fullPath = std::string("./assets/") + path; break;
		default:
			rat::error("Invalid directory provided ({})", int(directory));
			assert(false);
			break;
		}
		return fullPath;
	}

	std::vector<char> rat::FileSystem::loadFile(Directory directory, const char* path) {
		std::string fullPath = getPath(directory, path);
		std::ifstream file(fullPath, std::ios::ate | std::ios::binary);
		if(!file.is_open()) {
			rat::error("Cannot find file at: \"{}\"", fullPath);
			return {};
		}

		size_t fileSize = size_t(file.tellg());
		std::vector<char> data(fileSize);
		file.seekg(0);
		if(!file.read((char*)data.data(), fileSize)) return {};
		return data;
	}

	std::string FileSystem::loadTextFile(Directory directory, const char* path) {
		std::string fullPath = getPath(directory, path);
		std::ifstream file(fullPath, std::ios::ate);
		if(!file.is_open()) {
			rat::error("Cannot find file at: \"{}\"", fullPath);
			return {};
		}

		std::string data;
		data.resize(size_t(file.tellg()));
		file.seekg(0);
		if(!file.read(data.data(), data.size())) return {};
		return data;
	}

	void FileSystem::writeFile(Directory directory, const char* path, const char* data, size_t size) {
		assert(directory != Directory::Assets); // Cannot write to assets

		std::string fullPath = getPath(directory, path);
		std::ofstream file(fullPath);
		if(!file.is_open()) {
			rat::error("Cannot find file at: \"{}\"", fullPath);
			return;
		}
		file.write(data, size);
	}

	void FileSystem::writeTextFile(Directory directory, const char* path, const char* data) {
		assert(directory != Directory::Assets); // Cannot write to assets

		std::string fullPath = getPath(directory, path);
		std::ofstream file(fullPath);
		if(!file.is_open()) {
			rat::error("Cannot find file at: \"{}\"", fullPath);
			return;
		}
		file << data;
	}

	bool FileSystem::exists(Directory directory, const char* path) {
		std::string fullPath = getPath(directory, path);
		std::ifstream file(fullPath);
		return file.is_open();
	}

} // namespace rat
