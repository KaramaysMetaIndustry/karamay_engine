#ifndef H_STL
#define H_STL

#include <iostream>
#include <sstream>
#include <istream>
#include <ostream>
#include <fstream>

#include <array>
#include <vector>
#include <list>
#include <forward_list>
#include <deque>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <stack>
#include <queue>
#include <bitset>
#include <memory>
#include <string>
#include <chrono>
#include <future>
#include <thread>
#include <regex>
#include <functional>


// C++ 17
#include <any >
#include <charconv>
#include <execution>
#include <filesystem>
#include <memory_resource>
#include <optional>
#include <string_view>
#include <variant>

// C++ 20
#include <concepts>
#include <coroutine>
#include <compare>
#include <version>
#include <source_location>
#include <format>
#include <span>
#include <ranges>
#include <bit>
#include <numbers>
#include <syncstream>
#include <stop_token>
#include <semaphore>
#include <latch>
#include <barrier>

using uint8 = std::uint8_t;
using uint16 = std::uint16_t;
using uint32 = std::uint32_t;
using uint64 = std::uint64_t;
using int8 = std::int8_t;
using int16 = std::int16_t;
using int32 = std::int32_t;
using int64 = std::int64_t;

template<class _Ty>
using sptr = std::shared_ptr<_Ty>;

template<class _Ty>
using wptr = std::weak_ptr<_Ty>;

template<class _Ty>
using uptr = std::unique_ptr<_Ty>;


#endif