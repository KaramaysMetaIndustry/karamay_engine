#include "engine/karamay_engine.h"

int main()
{
    std::cout << "size: " << sizeof(std::string) << std::endl;

    karamay_engine::set_engine_root(
        "G:\\PrivateRepos\\karamay_engine\\_KaramayEngine\\karamay_engine_graphics_unit_cmake\\karamay_engine_graphics_unit\\"
    );
    
    karamay_engine _ke;
    if (!_ke.initialize())
    {
        return 1;
    } 
    _ke.run();
    return 0;
}
