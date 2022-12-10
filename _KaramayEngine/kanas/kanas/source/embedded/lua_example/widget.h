#pragma once

#include <iostream>

#define LUA_EX_ENABLED 1

class widget
{

    std::float_t w = 0.5f;

    std::shared_ptr<widget> xx;
    
public:
    widget();

    ~widget();

    static std::shared_ptr<widget> new_lua()
    {
        return std::make_shared<widget>();
    }

    static void wrap_collector(std::shared_ptr<widget>& w)
    {
        w.reset();
    }

    static std::int32_t calc(std::int32_t& a, const std::int32_t& b)
    {
        return a * b;
    }

    [[nodiscard]] const std::shared_ptr<widget>& get_v()
    {
        return xx;
    }

    std::float_t replace(const std::shared_ptr<widget>& other)
    {
        //w = other->get_v() + 8.77f;
        return w;
    }

#if LUA_EX_ENABLED

#endif
    
};
