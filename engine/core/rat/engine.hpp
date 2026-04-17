#pragma once

#include <cassert>

struct GLFWwindow;

namespace rat {

	class Engine {
	private:
		Engine(GLFWwindow* window);
		~Engine();

	public:
		Engine(Engine&) = delete;
		Engine& operator=(Engine&) = delete;
		Engine(Engine&&) = delete;
		Engine& operator=(Engine&&) = delete;

	public:
		static void initialize(GLFWwindow* window);
		static void terminate();
		static Engine& getInstance() { return *s_engine; }

	public:
		void run();

	private:
		static Engine* s_engine;
	};

} // namespace rat
