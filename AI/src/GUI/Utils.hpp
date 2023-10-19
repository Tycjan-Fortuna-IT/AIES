#pragma once

#include "ConsolePanel.hpp"

#define CONSOLE_TRACE(...) AI::ConsolePanel::GetInstance()->AddMessage(fmt::format(__VA_ARGS__), Core::Trace)
#define CONSOLE_INFO(...) AI::ConsolePanel::GetInstance()->AddMessage(fmt::format(__VA_ARGS__), Core::Info)
#define CONSOLE_WARN(...) AI::ConsolePanel::GetInstance()->AddMessage(fmt::format(__VA_ARGS__), Core::Warn)
#define CONSOLE_ERROR(...) AI::ConsolePanel::GetInstance()->AddMessage(fmt::format(__VA_ARGS__), Core::Error)
#define CONSOLE_CRITICAL(...) AI::ConsolePanel::GetInstance()->AddMessage(fmt::format(__VA_ARGS__), Core::Critical)
#define CONSOLE_BUG(...) AI::ConsolePanel::GetInstance()->AddMessage(fmt::format(__VA_ARGS__), Core::Bug)
