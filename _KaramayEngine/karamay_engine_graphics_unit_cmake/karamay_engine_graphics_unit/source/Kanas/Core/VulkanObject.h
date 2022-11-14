#ifndef _VULKAN_OBJECT_H_
#define _VULKAN_OBJECT_H_

#include "KanasCoreTypes.h"
#include "KanasCoreMacros.h"

_KANAS_CORE_BEGIN

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

template<typename VkHandleT>
class VulkanObject
{
public:
	VulkanObject() = default;

	virtual ~VulkanObject() {}

protected:

	VkHandleT _Handle{ VK_NULL_HANDLE };

	inline void ResetHandle() { _Handle = VK_NULL_HANDLE; }

	bool IsValid() const { return _Handle != VK_NULL_HANDLE; }

public:

	VkHandleT GetHandle() const { return _Handle; }

};





_KANAS_CORE_END

#endif