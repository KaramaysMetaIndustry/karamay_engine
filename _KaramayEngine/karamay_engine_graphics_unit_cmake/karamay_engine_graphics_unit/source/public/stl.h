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

#include <filesystem>
#include <optional>

using UInt8 = std::uint8_t;
using UInt16 = std::uint16_t;
using UInt32 = std::uint32_t;
using UInt64 = std::uint64_t;
using Int8 = std::int8_t;
using Int16 = std::int16_t;
using Int32 = std::int32_t;
using Int64 = std::int64_t;

template<class _Ty>
using SharedPtr = std::shared_ptr<_Ty>;

template<class _Ty>
using WeakPtr = std::weak_ptr<_Ty>;

template<class _Ty>
using UniquePtr = std::unique_ptr<_Ty>;


#endif