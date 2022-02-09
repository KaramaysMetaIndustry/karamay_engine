
#include "engine/karamay_engine.h"
#include "embedded/lua/lvm.h"
#include "embedded/lua/lvm_graphics_module.h"

int main()
{

    //std::cout << "size: " << sizeof(std::stringstream) << std::endl;

    karamay_engine::set_engine_root(
        "C:\\PrivateRepos\\karamay_engine\\_KaramayEngine\\karamay_engine_graphics_unit_cmake\\karamay_engine_graphics_unit\\"
    );

    karamay_engine _engine;
    if (!_engine.initialize())
    {
        return 1;
    } 
    _engine.run();

    return 0;
}
