
#include "gl_interface_block.h"

class gl_uniform_block
{

public:

	gl_uniform_block(const std::string& block_name)
	{
	}


public:

    template<typename GLSL_TRANSPARENT_T>
    void update(std::int32_t instance_index, std::string& attribute_name, const GLSL_TRANSPARENT_T& value)
    {}


private:

    const std::string _block_name;

};

