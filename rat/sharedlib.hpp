// from https://gist.github.com/RoseApollo/6456cdec457c6ede4426b8c5359bc416
#pragma once

#include <filesystem>

#ifdef __APPLE__
	#define LIBWRAP_NIX
#endif
#ifdef __linux__
	#define LIBWRAP_NIX
#endif
#ifdef unix
	#define LIBWRAP_NIX
#endif

#ifdef __WIN32__
	#define LIBWRAP_NT
#endif
#ifdef __MINGW32__
	#define LIBWRAP_NT
#endif

#ifdef LIBWRAP_NIX
	#include <dlfcn.h>

using SharedLib = void*;
#else
	#include <Windows.h>

using SharedLib = HINSTANCE;
#endif

inline SharedLib OpenLibrary(const std::filesystem::path& path) {
#ifdef LIBWRAP_NIX
	return dlopen(path.c_str(), RTLD_LAZY);
#else
	return LoadLibrary(path.c_str());
#endif
}

template<typename T>
inline T* GetSymbol(SharedLib lib, const char* symb) {
#ifdef LIBWRAP_NIX
	return reinterpret_cast<T*>(dlsym(lib, symb));
#else
	return reinterpret_cast<T*>(GetProcAddress(lib, symb));
#endif
}

inline void CloseLibrary(SharedLib lib) {
#ifdef LIBWRAP_NIX
	dlclose(lib);
#else
	if(lib != nullptr) FreeLibrary(lib);
#endif
}
