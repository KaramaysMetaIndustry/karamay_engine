#ifndef GL_ARRAY_BUFFER_H
#define GL_ARRAY_BUFFER_H

#include "graphics/resource/buffers/raw_buffer/gl_buffer.h"

class ArrayBuffer final
{
public:

	ArrayBuffer(Int64 BytesNum)
	{
		_Allocate(BytesNum);
	}

	ArrayBuffer(const ArrayBuffer&) = delete;
	ArrayBuffer& operator=(const ArrayBuffer&) = delete;

	~ArrayBuffer() {}

public:

	void Reallocate(Int64 BytesNum)
	{
		_Allocate(BytesNum);
	}

	void Fill(UInt32 ByteOffset, const UInt8* BytesData, UInt32 BytesNum)
	{
		if (!_Buffer) return;

		_Buffer->ExecuteMappedMemoryWriter(ByteOffset, BytesNum, 
			[=](std::uint8_t* data, std::int64_t size)
			{
				std::memcpy(data, BytesData, BytesNum);
			}
		);

		_Buffer->ExecuteMappedMemoryReader(ByteOffset, BytesNum, 
			[](const std::uint8_t* data, std::int64_t size) 
			{
				const float* _Floats = reinterpret_cast<const float*>(data);
				for (int i = 0; i < size / sizeof(float); ++i)
				{
					std::cout << _Floats[i] << std::endl;
				}
			}
		);
	}



public:

	void Bind() const noexcept
	{
		glBindBuffer(GL_ARRAY_BUFFER, _Buffer->get_handle());
	}

	void Unbind() const noexcept
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

private:

	std::unique_ptr<Buffer> _Buffer;

	void _Allocate(Int64 Size)
	{
		BufferStorageOptions _Options;
		_Options.ClientStorage = false;
		_Options.DynamicStorage = true;
		_Options.MapRead = true;
		_Options.MapWrite = true;
		_Options.MapCoherent = false;
		_Options.MapPersistent = false;
		_Buffer = std::make_unique<Buffer>(_Options, Size);
	}

};


#endif
