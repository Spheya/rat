#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "rat/application_info.hpp"
#include "rat/logger.hpp"

namespace rat::glfw {

	inline const char* getErrString(int errCode) {
		switch(errCode) {
		case GLFW_NO_ERROR: return "GLFW_NO_ERROR";
		case GLFW_NOT_INITIALIZED: return "GLFW_NOT_INITIALIZED";
		case GLFW_NO_CURRENT_CONTEXT: return "GLFW_NO_CURRENT_CONTEXT";
		case GLFW_INVALID_ENUM: return "GLFW_INVALID_ENUM";
		case GLFW_INVALID_VALUE: return "GLFW_INVALID_VALUE";
		case GLFW_OUT_OF_MEMORY: return "GLFW_OUT_OF_MEMORY";
		case GLFW_API_UNAVAILABLE: return "GLFW_API_UNAVAILABLE";
		case GLFW_VERSION_UNAVAILABLE: return "GLFW_VERSION_UNAVAILABLE";
		case GLFW_PLATFORM_ERROR: return "GLFW_PLATFORM_ERROR";
		case GLFW_FORMAT_UNAVAILABLE: return "GLFW_FORMAT_UNAVAILABLE";
		case GLFW_NO_WINDOW_CONTEXT: return "GLFW_NO_WINDOW_CONTEXT";
		case GLFW_CURSOR_UNAVAILABLE: return "GLFW_CURSOR_UNAVAILABLE";
		case GLFW_FEATURE_UNAVAILABLE: return "GLFW_FEATURE_UNAVAILABLE";
		case GLFW_FEATURE_UNIMPLEMENTED: return "GLFW_FEATURE_UNIMPLEMENTED";
		case GLFW_PLATFORM_UNAVAILABLE: return "GLFW_PLATFORM_UNAVAILABLE";
		default: return "GLFW_ERROR";
		}
	}

	inline void errorHandler(int errCode, const char* description) {
		rat::error("{}({}): {}", getErrString(errCode), errCode, description);
	}

	inline void setupErrorHandler() {
		static bool firstCall = true;
		if(firstCall) {
			firstCall = false;
			glfwSetErrorCallback(errorHandler);
		}
	}

	inline GLFWwindow* createWindow(const ApplicationInfo& info) {
		return glfwCreateWindow(info.requestedResolution.x, info.requestedResolution.y, info.name, nullptr, nullptr);
	}

} // namespace rat::glfw
