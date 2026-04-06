#pragma once

#ifdef _WIN32
	#ifdef RAT_EDITOR_EXPORT
		#define RAT_EDITOR_API __declspec(dllexport)
	#else
		#define RAT_EDITOR_API __declspec(dllimport)
	#endif
#else
	#if defined(__GNUC__) && __GNUC__ >= 4
		#define RAT_EDITOR_API __attribute__((visibility("default")))
	#else
		#define RAT_EDITOR_API
	#endif
#endif
