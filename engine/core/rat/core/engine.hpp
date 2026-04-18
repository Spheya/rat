#pragma once

#include <memory>

#include "rat/rendering/graphics.hpp"

namespace rat {

	struct EditorContext;

	class Engine {
	private:
		Engine(EditorContext* editorContext);
		~Engine();

	public:
		Engine(Engine&) = delete;
		Engine& operator=(Engine&) = delete;
		Engine(Engine&&) = delete;
		Engine& operator=(Engine&&) = delete;

	public:
		static void initialize(EditorContext* editorContext);
		static void terminate();
		static Engine& getInstance() { return *s_engine; }

	public:
		void tick();
		[[nodiscard]] bool isCloseRequested() const;
		[[nodiscard]] EditorContext* getEditorContext() { return m_editorContext; }
		[[nodiscard]] GraphicsContext& getGraphicsContext() { return *m_graphicsContext; }

	private:
		static Engine* s_engine;

	private:
		EditorContext* m_editorContext;
		std::unique_ptr<GraphicsContext> m_graphicsContext;
	};

} // namespace rat
