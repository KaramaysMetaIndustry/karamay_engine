#ifndef _UNIFORM_BUFFER_H_
#define _UNIFORM_BUFFER_H_

#include "Buffer.h"

_KANAS_CORE_BEGIN

class UniformBuffer : public Buffer
{
public:

	UniformBuffer();

	virtual ~UniformBuffer() override;

};

_KANAS_CORE_END

#endif