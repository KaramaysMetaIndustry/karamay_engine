#ifndef GL_ARRAY_BUFFER_H
#define GL_ARRAY_BUFFER_H

#include "graphics/resource/buffers/raw_buffer/gl_buffer.h"

class ArrayBuffer final
{
public:

	ArrayBuffer(Int64 Size)
	{
		_Allocate(Size);
	}

	~ArrayBuffer() 
	{}

public:

	void Reallocate(Int64 Size)
	{
		_Allocate(Size);
	}

	void Fill(UInt32 Offset, const UInt8* Data, UInt32 Size)
	{
		if (!_Buffer) return;

		//_Buffer->execute_mapped_memory_writer(Offset, Size, []() {})
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

	std::unique_ptr<gl_buffer> _Buffer;

	void _Allocate(Int64 Size)
	{
		gl_buffer_storage_options _options;
		_options.is_client_storage = false;
		_options.is_dynamic_storage = true;
		_options.is_map_read = true;
		_options.is_map_write = true;
		_options.is_map_coherent = false;
		_options.is_map_persistent = false;
		_Buffer = std::make_unique<gl_buffer>(_options, Size);

	}

};


#endif
