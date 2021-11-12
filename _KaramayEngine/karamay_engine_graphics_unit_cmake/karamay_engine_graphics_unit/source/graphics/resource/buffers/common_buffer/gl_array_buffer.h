#ifndef GL_ARRAY_BUFFER_H
#define GL_ARRAY_BUFFER_H

#include "graphics/resource/buffers/raw_buffer/gl_buffer.h"

class ArrayBuffer final
{
public:

	ArrayBuffer(Int64 BytesNum)
	{
		_Allocate(BytesNum, nullptr);
	}

	ArrayBuffer(Int64 BytesNum, const UInt8* InitializationBytes)
	{
		_Allocate(BytesNum, InitializationBytes);
	}

	ArrayBuffer(const ArrayBuffer&) = delete;
	ArrayBuffer& operator=(const ArrayBuffer&) = delete;

	~ArrayBuffer() {}

public:

	void Reallocate(Int64 BytesNum, const UInt8* InitializationBytes = nullptr)
	{
		_Allocate(BytesNum, InitializationBytes);
	}

	void Fill(UInt32 ByteOffset, const UInt8* Bytes, UInt32 BytesNum)
	{
		if (!_Buffer) return;

		_Buffer->ExecuteMappedMemoryWriter(ByteOffset, BytesNum, 
			[=](std::uint8_t* data, std::int64_t size)
			{
				std::memcpy(data, Bytes, BytesNum);
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

	UniquePtr<Buffer> _Buffer;

	void _Allocate(Int64 Size, const UInt8* InitializationBytes)
	{
		BufferStorageOptions _Options;
		_Options.ClientStorage = false;
		_Options.DynamicStorage = true;
		_Options.MapRead = true;
		_Options.MapWrite = true;
		_Options.MapCoherent = false;
		_Options.MapPersistent = false;
		if (InitializationBytes)
		{
			_Buffer = std::make_unique<Buffer>(_Options, Size, InitializationBytes);
		}
		else {
			_Buffer = std::make_unique<Buffer>(_Options, Size);
		}
	}

};


#endif
