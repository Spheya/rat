#pragma once

#include <filesystem>
#include <type_traits>

#ifdef _WIN32
	#define WIN32_LEAN_AND_MEAN
	#define NOMINMAX
	#include <Windows.h>
#else
	#include <dlfcn.h>
#endif

class SharedLib {
public:
#ifdef _WIN32
	SharedLib(const std::filesystem::path& path) : m_library(LoadLibrary(path.c_str())) {}
	SharedLib(SharedLib&& other) noexcept : m_library(other.m_library) { other.m_library = nullptr; }
	SharedLib& operator=(SharedLib&& other) noexcept {
		if(m_library) FreeLibrary(m_library);
		m_library = other.m_library;
		other.m_library = nullptr;
		return *this;
	}
	~SharedLib() {
		if(m_library) FreeLibrary(m_library);
	}
#else
	SharedLib(const std::filesystem::path& path) : m_library(dlopen(path.c_str(), RTLD_LAZY)) {
		if(dlerror()) {
			dlclose(m_library);
			m_library = nullptr;
		}
	}
	SharedLib(SharedLib&& other) noexcept : m_library(other.m_library) { other.m_library = nullptr; }
	SharedLib& operator=(SharedLib&& other) noexcept {
		if(m_library) dlclose(m_library);
		m_library = other.m_library;
		other.m_library = nullptr;
		return *this;
	}
	~SharedLib() {
		if(m_library) dlclose(m_library);
	}
#endif
	SharedLib(SharedLib&) = delete;
	SharedLib& operator=(SharedLib&) = delete;

public:
#ifdef _WIN32
	template<typename T>
	    requires std::is_function_v<T>
	T* getFunction(const char* name) const {
		return reinterpret_cast<T*>(GetProcAddress(m_library, name));
	}
#else
	template<typename T>
	    requires std::is_function_v<T>
	T* getFunction(const char* name) const {
		auto f = reinterpret_cast<T*>(dlsym(m_library, name));
		if(dlerror()) return nullptr;
		return f;
	}
#endif

	operator bool() const { return m_library; }

private:
#ifdef _WIN32
	HMODULE m_library;
#else
	void* m_library;
#endif
};
