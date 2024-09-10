#pragma once

#ifdef GK_DEBUG
	#define GK_ENABLE_ASSERTS
#endif

#ifdef GK_ENABLE_ASSERTS
	#define GK_ASSERT(x, ...) { if(!(x)) { GK_ERROR("Assertion failed. {0}", __VA_ARGS__); __debugbreak(); } }
	#define GK_CORE_ASSERT(x, ...) { if(!(x)) { GK_CORE_ERROR("Assertion failed. {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define GK_ASSERT(x, ...)
	#define GK_CORE_ASSERT(x, ...)
#endif

