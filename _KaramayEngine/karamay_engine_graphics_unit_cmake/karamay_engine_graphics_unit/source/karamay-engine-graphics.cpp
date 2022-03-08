#include "engine/karamay_engine.h"
#include "karamay_RHI/karamay_RHI.h"

int main()
{

    karamay_RHI::dispatcher _dispatcher{};
    _dispatcher.initialize();

    karamay_engine::set_engine_root(
        "C:\\PrivateRepos\\karamay_engine\\_KaramayEngine\\karamay_engine_graphics_unit_cmake\\karamay_engine_graphics_unit\\"
    );
    
    karamay_engine _ke;
    if (!_ke.initialize())
    {
        return 1;
    } 
    _ke.run();
    return 0;
}
