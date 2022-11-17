#ifndef _KANAS_CORE_TYPES_H_
#define _KANAS_CORE_TYPES_H_

#include "Core/CoreLibrary.h"
#include "KanasCoreMacros.h"
#include "KanasFlagBits.h"

_KANAS_CORE_BEGIN

struct FConcurrentGuide
{
	void GetConcurrentFamilyIndices(TVector<uint32>& OutFamilyIndices) const
	{
	}

	bool DoesSupportConcurrency() const
	{
		return false;
	}

	FConcurrentGuide(const TVector<TSharedPtr<class FQueue>>& InQueues) :
		ConcurrentQueues(InQueues)
	{
	}

private:

	TVector<TSharedPtr<class FQueue>> ConcurrentQueues;

	static const FConcurrentGuide& StaticConstRef;

};

const FConcurrentGuide& FConcurrentGuide::StaticConstRef = FConcurrentGuide({});

template<typename DeviceObject_T, typename Handle_T = DeviceObject_T::Handle_T>
static void CollectDeviceObjectHandles(const TVector<TSharedPtr<DeviceObject_T>>& Objects, TVector<Handle_T>& OutHandles)
{
	OutHandles.reserve(Objects.size());

	for (const auto& Object : Objects)
	{
		OutHandles.emplace_back(Object->GetHandle());
	}
}


_KANAS_CORE_END

#endif