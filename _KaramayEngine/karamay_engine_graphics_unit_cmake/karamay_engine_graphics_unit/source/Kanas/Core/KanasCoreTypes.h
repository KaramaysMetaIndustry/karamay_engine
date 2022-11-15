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

_KANAS_CORE_END

#endif