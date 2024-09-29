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

#define BIT(x) (1 << x)

#define GK_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace Gecko {

	template<typename T>
	using Ref = std::shared_ptr<T>;

}
