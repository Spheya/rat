#pragma once

#include <cassert>

namespace rat {

	class Engine {
	private:
		Engine();
		~Engine();

	public:
		Engine(Engine&) = delete;
		Engine& operator=(Engine&) = delete;
		Engine(Engine&&) = delete;
		Engine& operator=(Engine&&) = delete;

	public:
		static void initialize();
		static void terminate();
		static Engine& getInstance() { return *s_engine; }

	public:
		void run();

	private:
		static Engine* s_engine;
	};

} // namespace rat
