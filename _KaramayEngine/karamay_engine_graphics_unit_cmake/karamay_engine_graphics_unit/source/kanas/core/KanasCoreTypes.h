#ifndef _KANAS_CORE_TYPES_H_
#define _KANAS_CORE_TYPES_H_

#include "Core/CoreLibrary.h"
#include "KanasCoreMacros.h"
#include "KanasFlagBits.h"

_KANAS_CORE_BEGIN

struct FConcurrentGuide
{
	void GetConcurrentFamilyIndices(std::vector<std::uint32_t>& OutFamilyIndices) const
	{
	}

	bool DoesSupportConcurrency() const
	{
		return false;
	}

	FConcurrentGuide(const std::vector<std::shared_ptr<class queue>>& InQueues) :
		ConcurrentQueues(InQueues)
	{
	}

private:

	std::vector<std::shared_ptr<class queue>> ConcurrentQueues;

	static const FConcurrentGuide& StaticConstRef;

};

const FConcurrentGuide& FConcurrentGuide::StaticConstRef = FConcurrentGuide({});

template<typename device_object_T, typename Handle_T = device_object_T::Handle_T>
static void Collectdevice_objectHandles(const std::vector<std::shared_ptr<device_object_T>>& Objects, std::vector<Handle_T>& OutHandles)
{
	OutHandles.reserve(Objects.size());

	for (const auto& Object : Objects)
	{
		OutHandles.emplace_back(Object->get_handle());
	}
}


_KANAS_CORE_END

#endif