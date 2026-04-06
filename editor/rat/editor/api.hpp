#pragma once

#ifdef RAT_EDITOR_EXPORT
	#define RAT_EDITOR_API __declspec(dllexport)
#else
	#define RAT_EDITOR_API __declspec(dllimport)
#endif
