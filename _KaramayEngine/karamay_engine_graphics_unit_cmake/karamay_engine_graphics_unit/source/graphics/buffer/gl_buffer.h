#ifndef H_GL_BUFFER_BASE
#define H_GL_BUFFER_BASE

#include "graphics/glo/gl_object.h"
#include "graphics/buffer/gl_buffer_tools.h"
#include "graphics/type/glsl.h"


struct gl_buffer_pool_element
{
    std::uint32_t handle;
    std::int64_t capacity;
    gl_buffer_storage_options storage_options;
    std::uint32_t storage_flags;

    gl_buffer_pool_element(const gl_buffer_pool_element& other)
    {
    }
};

/*
 * [You must trust clients who will use your class.]
 * gl_buffer which can only accept glsl_type and bytes
 *
 * 该类提供的 write 系列接口定义的参数是对应情形下最高效的数据组织方式，请阅读接口对应情形并严格考量写入数据的情形以保证效率。
 * */
class gl_buffer : public gl_object
{
public:

    const static std::int64_t THEORETICAL_MAX_CAPACITY;
    const static std::int64_t HARDWARE_MAX_CAPACITY;
    const static std::int64_t GPU_MAX_CAPACITY;
    const static std::int64_t BUFFER_AVAILABLE_MAX_CAPACITY;

public:

    explicit gl_buffer(std::int64_t required_capacity, gl_buffer_storage_options storage_options) :
        _required_capacity(required_capacity),
        _storage_options(storage_options),
        _capacity(0),
        _storage_flags(0)
    {
        reallocate(required_capacity, storage_options);
    }

    ~gl_buffer() override
    {
        //_buffer_pool.insert_after(_buffer_pool.end(), gl_buffer_pool_element{_handle, _storage_options, _capacity});
    }

public:

    /*
     * Description: immediately write << bytes stream >> into [offset, offset + byte_stream_size)
     * 包含安全处理的原生接口
     * 使用须知：调用该接口会产生通讯开销，频繁调用影响性能（即连续数据尽量整合一起写入，避免多次开销）
     * */
    inline void write(std::int64_t offset, const std::uint8_t* byte_stream, std::int64_t byte_stream_size)
    {
        if(!_storage_options.is_dynamic_storage || !byte_stream || offset < 0 || offset + byte_stream_size > _capacity) return;
        glNamedBufferSubData(_handle, offset, byte_stream_size, byte_stream);
    }

public:

    /*
     * 当前上下文中仅需写入[类型明确的 GLSL_TRANSPARENT_T ]的[单个数据]
     *
     * */
    template<typename GLSL_TRANSPARENT_T>
    void write(int64_t offset, const GLSL_TRANSPARENT_T& value)
    {
        if(offset < 0 || offset + sizeof(GLSL_TRANSPARENT_T) > _capacity) return;
        glNamedBufferSubData(_handle, offset, sizeof(GLSL_TRANSPARENT_T), reinterpret_cast<const void*>(&value));
    }

    /*
     * 当前上下文中需写入[类型明确的 GLSL_TRANSPARENT_T]的[离散][数据集]
     * */
    template<typename GLSL_TRANSPARENT_T>
    void write_dispersed_list(const std::vector<std::pair<std::int64_t, GLSL_TRANSPARENT_T>>& dispersed_list)
    {

        if(dispersed_list.size() < 5) for(const auto& _pair : dispersed_list) write(_pair.first, _pair.second);
        else {
            const std::int64_t _dispersed_list_covered_size = 0;
            const std::int64_t _min_offset = 0;
            if(_min_offset < 0 || _min_offset + _dispersed_list_covered_size > _capacity) return;
            execute_mutable_memory_handler(_min_offset, _dispersed_list_covered_size, [&dispersed_list](std::uint8_t* mapped_memory, std::int64_t mapped_memory_size){
                if(mapped_memory)
                {
                    for(const auto& _pair : dispersed_list)
                    {
                        //std::memcpy(mapped_memory, _pair.second, )
                    }
                }
            });
        }
    }

    /*
     * 当前上下文需写入[抽象类型的 GLSL_TRANSPARENT_T]的[离散][数据集]
     * */
    void write_dispersed_interracial_list(const std::vector<std::pair<int64_t, const glsl_transparent_class*>>& dispersed_interracial_list)
    {

    }

    /*
     * 当前上下文需写入[类型明确的 GLSL_TRANSPARENT_T]的[连续][数据集]
     * */
    template<typename GLSL_TRANSPARENT_T>
    void write_consequent_list(std::int64_t offset, const std::vector<GLSL_TRANSPARENT_T>& consequent_list)
    {
        const std::int64_t _consequent_list_size = consequent_list.size() * sizeof(GLSL_TRANSPARENT_T);
        if(offset < 0 || offset +  _consequent_list_size > _capacity) return;
        glNamedBufferSubData(_handle, offset, _consequent_list_size, reinterpret_cast<const void*>(consequent_list.data()));
    }

    /*
     * 当前上下文需写入[抽象类型的 GLSL_TRANSPARENT_T]的[离散][数据集]
     * */
    void write_consequent_interracial_list(std::int64_t offset, const std::vector<const glsl_transparent_class*>& consequent_interracial_list)
    {
        std::int64_t _consequent_interracial_list_size = 0;
        for(const auto& _value : consequent_interracial_list) if(_value) _consequent_interracial_list_size += _value->clazz()->class_size;

        if(offset < 0 || _consequent_interracial_list_size < 0 || offset + _consequent_interracial_list_size > _capacity) return;
        {
            auto* _tmp_data = (std::uint8_t*)malloc(_consequent_interracial_list_size);
            std::int64_t _tmp_data_offset = 0;
            for(const auto* _value : consequent_interracial_list)
            {
                if(_tmp_data && _value)
                {
                    std::memcpy(_tmp_data + _tmp_data_offset, _value->stream(), _value->clazz()->class_size);
                    _tmp_data_offset += _value->clazz()->class_size;
                }
            }
            glNamedBufferSubData(_handle, offset, _consequent_interracial_list_size, _tmp_data);
        }

        //
//        {
//            execute_mutable_memory_handler(offset, _consequent_interracial_list_size, [&consequent_interracial_list](std::uint8_t* mapped_memory, std::int64_t mapped_memory_size){
//                if(mapped_memory)
//                {
//                    std::int64_t _offset = 0;
//                    for(const auto& _pair : consequent_interracial_list)
//                    {
//                        std::memcpy(mapped_memory + _offset, _pair.first, _pair.second);
//                        _offset += _pair.second;
//                    }
//                }
//            });
//        }
    }

private:

    static std::forward_list<gl_buffer_pool_element> _buffer_pool;

public:

    void reallocate(std::int64_t capacity, gl_buffer_storage_options storage_options);

    void reallocate(std::int64_t capacity)
    {
        reallocate(capacity, _storage_options);
    }

private:

    bool _check_buffer_validation(std::int64_t required_capacity, gl_buffer_storage_options storage_options) {return false;}

    void _release_isolated_buffers(){}

    void _release_all_pool_buffers() {
        for(const auto& _buffer_element : _buffer_pool)
        {
            glDeleteBuffers(1, &_buffer_element.handle);
        }

        std::istringstream a("12.223232");
        std::int32_t x;
        a >> x;
    }

public:

    /*
     * Mostly [Server -> Server]
     * You must sacrifice some flexibility to get rapid filling.
     * capacity % sizeof (data_mask) == 0
     * */
    void overwrite_by_byte(std::int64_t offset, std::int64_t size);

    template<typename GLSL_T>
    inline void overwrite_by_unit(std::int64_t offset, std::int64_t size, const GLSL_T& unit)
    {
        glClearNamedBufferSubData(_handle, 0, offset, size, 0, 0, reinterpret_cast<const std::uint8_t*>(&unit));
    }

public:

    /*
     * Invalidate the whole buffer, data in buffer will become undefined.
     * */
    void invalidate()
    {
        glInvalidateBufferData(_handle);
    }

    /*
     * grab another same buffer storage as new one
     * */
    void invalidate(std::int64_t offset, std::int64_t size)
    {
        if(offset < 0 || size < 0 || offset + size > _capacity) return; // VALUE_INVALID
        glInvalidateBufferSubData(_handle, offset, size);
    }

public:
    /*
     * Pure [Server -> Server]
     * */
    void output_data_to_buffer(std::int64_t self_offset, int64_t output_size, gl_buffer& target, std::int64_t target_offset);

    /*
     * Pure [Server -> Server]
     * */
    void output_data_to_buffer(gl_buffer& target_buffer);

public:

    /*
     * map a block of immutable memory
     * then execute a handler you specified (can not do any modification)
     * @ task void(mapped_memory_block, mapped_memory_block_size)
     * */
    void execute_immutable_memory_handler(std::int64_t offset, std::int64_t size, const std::function<void(const std::uint8_t*, std::int64_t)>& handler);

    /*
     * map a block of mutable memory
     * then execute a handler you specified
     * @ task void(mapped_memory_block, mapped_memory_block_size)
     * */
    void execute_mutable_memory_handler(std::int64_t offset, std::int64_t size, const std::function<void(std::uint8_t*, std::int64_t)>& handler);

public:

    [[nodiscard]] std::int64_t get_capacity() const { return _required_capacity; }

    [[nodiscard]] std::uint32_t get_storage_flags() const { return _storage_flags; }

    [[nodiscard]] std::int64_t query_buffer_size() const
    {
        std::int64_t _buffer_size = 0;
        glGetNamedBufferParameteri64v(_handle, GL_BUFFER_SIZE, &_buffer_size);
        return _buffer_size;
    }

    [[nodiscard]] std::uint8_t query_buffer_mapped() const
    {
        std::int32_t _is_mapped = 0;
        glGetNamedBufferParameteriv(_handle, GL_BUFFER_MAPPED, &_is_mapped);
        return _is_mapped == GL_TRUE;
    }

    [[nodiscard]] std::int32_t query_buffer_access() const
    {
        std::int32_t _buffer_access = 0;
        glGetNamedBufferParameteriv(_handle, GL_BUFFER_ACCESS, &_buffer_access);
        return _buffer_access;
    }

    [[nodiscard]] std::int32_t query_buffer_usage() const
    {
        std::int32_t _buffer_usage = 0;
        glGetNamedBufferParameteriv(_handle, GL_BUFFER_USAGE, &_buffer_usage);
        return _buffer_usage;
    }

private:

    [[nodiscard]] inline bool _check_capacity(std::int64_t capacity) const
    {
        return capacity != _capacity && capacity < BUFFER_AVAILABLE_MAX_CAPACITY;
    }

public:

    template<typename T>
    void print()
    {
        execute_immutable_memory_handler(0, _required_capacity, [](const std::uint8_t* data, std::int64_t size){
            const auto _data = reinterpret_cast<const T*>(data);
            if(_data)
            {
                for(std::int32_t _index = 0; _index < size/ sizeof(T); ++_index)
                {
                    std::cout<<": "<<_data[_index] <<std::endl;

                }
            }
        });
    }

private:

    void _reallocate(std::int64_t new_capacity);

private:

    std::int64_t _capacity, _required_capacity;

    std::uint32_t _storage_flags;

    gl_buffer_storage_options _storage_options;


};

#endif
