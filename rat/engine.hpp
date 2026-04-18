#pragma once

#include "sharedlib.hpp"

namespace rat {
	struct EditorContext;
}

class Engine {
public:
	explicit Engine(SharedLib lib) :
	    m_library(lib),
	    m_ratEngineInit(lib == nullptr ? nullptr : GetSymbol<void(rat::EditorContext*)>(lib, "ratEngineInit")),
	    m_ratEngineTick(lib == nullptr ? nullptr : GetSymbol<void()>(lib, "ratEngineTick")),
	    m_ratEngineClose(lib == nullptr ? nullptr : GetSymbol<void()>(lib, "ratEngineClose")) {}

	Engine(Engine&& other) noexcept :
	    m_library(other.m_library),
	    m_ratEngineInit(other.m_ratEngineInit),
	    m_ratEngineTick(other.m_ratEngineTick),
	    m_ratEngineClose(other.m_ratEngineClose) {
		other.m_library = nullptr;
	}

	Engine& operator=(Engine&& other) noexcept {
		if(m_library) CloseLibrary(m_library);
		m_ratEngineInit = other.m_ratEngineInit;
		m_ratEngineTick = other.m_ratEngineTick;
		m_ratEngineClose = other.m_ratEngineClose;
		other.m_library = nullptr;
		return *this;
	}

	~Engine() {
		if(m_library) CloseLibrary(m_library);
	}

	Engine(Engine&) = delete;
	Engine& operator=(Engine&) = delete;

	bool isValid() { return m_ratEngineInit != nullptr && m_ratEngineTick != nullptr && m_ratEngineClose != nullptr; }

	void init(rat::EditorContext* editorContext) { m_ratEngineInit(editorContext); }
	void tick() { m_ratEngineTick(); }
	void close() { m_ratEngineClose(); }

private:
	SharedLib m_library;
	void (*m_ratEngineInit)(rat::EditorContext*);
	void (*m_ratEngineTick)();
	void (*m_ratEngineClose)();
};
