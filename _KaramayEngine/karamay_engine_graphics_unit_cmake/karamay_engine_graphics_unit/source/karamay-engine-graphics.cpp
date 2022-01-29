
#include "engine/karamay_engine.h"

int main()
{
    karamay_engine _engine;
    if (!_engine.initialize())
    {
        return 1;
    }
    _engine.run();
    return 0;
}
