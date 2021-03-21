#pragma once

// TODO: Ficure out how to start debugging nicely
#ifdef FS_DEBUG
#define FS_ENABLE_ASSERTS
#endif

#if defined(FS_ENABLE_ASSERTS)
#if defined(FS_WIN64)
#define FS_ASSERT_NO_MESSAGE(condition) { if(!(condition)) { FS_ERROR("Assertion Failed"); __debugbreak(); } }
#define FS_ASSERT_MESSAGE(condition, ...) { if(!(condition)) { FS_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }

#define FS_ASSERT_RESOLVE(arg1, arg2, macro, ...) macro
#define FS_GET_ASSERT_MACRO(...) FS_EXPAND_VARGS(FS_ASSERT_RESOLVE(__VA_ARGS__, FS_ASSERT_MESSAGE, FS_ASSERT_NO_MESSAGE))

#define FS_ASSERT(...) FS_EXPAND_VARGS( FS_GET_ASSERT_MACRO(__VA_ARGS__)(__VA_ARGS__) )
#define FS_CORE_ASSERT(...) FS_EXPAND_VARGS( FS_GET_ASSERT_MACRO(__VA_ARGS__)(__VA_ARGS__) )
#elif defined(FS_APPLE)
#define FS_ASSERT(x, ...) //{ if(!(x)) {FS_ERROR("Assertion failed! {0}", __VA_ARGS__); __asm__("int $3"); } }
#define FS_CORE_ASSERT(x, ...) //{FS_CORE_ERROR("Assertion failed! {0}", __VA_ARGS__); __asm__("int $3"); } }
#endif
#endif