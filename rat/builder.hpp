#pragma once

#include "engine.hpp"

Engine linkEngine(const char* projectPath);
bool generateBuildFiles(const char* projectPath);
bool buildEngine(const char* projectPath, bool editor);
