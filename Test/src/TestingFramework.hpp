#pragma once

#include "Engine/Core/Debug/Logger.hpp"

#define TEST_INIT() int main() { Core::Logger::Init(); APP_INFO("Running tests...\n");
#define TEST_END() APP_INFO("Tests finished.\n"); Core::Logger::Shutdown(); return 0; }

#define TEST_CASE(name) APP_WARN("Running test case: {}", name);
#define TEST_CASE_END() APP_WARN("Test case finished.\n");

#define SUCCESS(message) APP_INFO("Check passed: {}  {}", __FUNCTION__, message)
#define FAIL(message) APP_ERROR("Test failed: {}  {}", __FUNCTION__, message)

#define ASSERT_EQUALS(a, b) if ((a) != (b)) { FAIL(#a " != " #b); } else { SUCCESS(#a " == " #b); }
#define ASSERT_NOT_EQUALS(a, b) if ((a) == (b)) { FAIL(#a " == " #b); } else { SUCCESS(#a " != " #b); }

#define ASSERT_LESS_OR_EQUAL(a, b) if ((a) > (b)) { FAIL(#a " > " #b); } else { SUCCESS(#a " <= " #b); }
#define ASSERT_LESS(a, b) if ((a) > (b)) { FAIL(#a " > " #b); } else { SUCCESS(#a " < " #b); }

#define ASSERT_GREATER_OR_EQUAL(a, b) if ((a) <= (b)) { FAIL(#a " <= " #b); } else { SUCCESS(#a " >= " #b); }
#define ASSERT_GREATER(a, b) if ((a) < (b)) { FAIL(#a " < " #b); } else { SUCCESS(#a " > " #b); }

#define ASSERT_TRUE(expr) if (!(expr)) { FAIL(#expr); } else { SUCCESS("true == " #expr); }
#define ASSERT_FALSE(expr) if ((expr)) { FAIL(#expr); } else { SUCCESS("false == " #expr); }

#define ASSERT_NULL(expr) if ((expr) != nullptr) { FAIL(#expr " != nullptr"); } else { SUCCESS(#expr " == nullptr"); }
#define ASSERT_NOT_NULL(expr) if ((expr) == nullptr) { FAIL(#expr " == nullptr"); } else { SUCCESS(#expr " != nullptr"); } 
