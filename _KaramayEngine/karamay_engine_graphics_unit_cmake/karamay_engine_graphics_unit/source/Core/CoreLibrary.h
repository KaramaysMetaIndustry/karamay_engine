#ifndef _CORE_LIBRARY_H_
#define _CORE_LIBRARY_H_

#include "public/stl.h"

template<typename T>
using TUniquePtr = std::unique_ptr<T>;

template<typename T>
using TSharedPtr = std::shared_ptr<T>;

template<typename T>
using TWeakPtr = std::weak_ptr<T>;

template<typename T, size_t Num>
using TArray = std::array<T, Num>;

template<typename T>
using TVector = std::vector<T>;

template<typename K, typename V>
using TMap = std::map<K, V>;

template<typename K, typename V>
using TUnorderedMap = std::unordered_map<K, V>;

template<typename T>
using TSet = std::set<T>;

template<typename T>
using TUnorderedSet = std::unordered_set<T>;

template<typename K, typename V>
using TMultimap = std::multimap<K, V>;

template<typename K, typename V>
using TUnorderedMultimap = std::unordered_multimap<K, V>;


template <class _Ty, class... _Types>
TSharedPtr<_Ty> MakeShared(_Types&&... _Args) {
	return std::make_shared<_Ty, _Types>;
}

template <class _Ty, class... _Types>
TUniquePtr<_Ty> MakeUnique(_Types&&... _Args)
{
	std::make_unique<_Ty>(_Args);
}

template<typename T>
std::remove_reference_t<T>&& MoveTemp(T&& _Arg)
{
	return std::move(_Arg);
}


#endif