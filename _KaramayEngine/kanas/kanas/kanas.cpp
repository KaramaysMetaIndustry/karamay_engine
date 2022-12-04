// kanas.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "embedded/lua/lvm.h"

class ATest
{
	int a = 1;

public:

    void setA(std::int32_t v)
    {
        a = v;
    }
    
};

static int lua_new_ATest(lua_State* l);

#define LUA_CLASS_MODULE_BEGIN(CLASS_NAME)\
lua_api::basic::function_registry lua_api::basic::lua_exporter<CLASS_NAME>::registry ={};\
std::function<void(lua_api::basic::function_registry&)> lua_api::basic::lua_exporter<CLASS_NAME>::registry_delegate =  [](function_registry& fr)\
{\

#define LUA_CLASS_MODULE_END(CLASS_NAME)\
};\
lua_api::basic::lua_exporter<CLASS_NAME> lua_api::basic::lua_exporter<CLASS_NAME>::exporter = {};\
template<>\
constexpr bool lua_api::basic::is_lua_exporter_registered<CLASS_NAME> = true;

#define ADD_FUNC(NAME, FUNC)\
fr.set(NAME, FUNC)

LUA_CLASS_MODULE_BEGIN(ATest)
ADD_FUNC("new", lua_new_ATest);
LUA_CLASS_MODULE_END(ATest)

static int lua_new_ATest(lua_State* l)
{
    std::shared_ptr<ATest> _this = std::make_shared<ATest>();
    lua_api::basic::push(_this);
    return 1;
}

static int lua_setA(lua_State* l)
{
    
    auto _this = lua_api::basic::to<std::shared_ptr<ATest>>(1);
    auto param1 = lua_api::basic::to<std::int32_t>(2);
    
    _this.value()->setA(param1.value());

    return 1;
}

int main()
{
    const auto test = std::make_shared<ATest>();
    lua_api::basic::push(test);
    const auto v = lua_api::basic::to<std::shared_ptr<ATest>>(-1);
    
    if(v.has_value())
    {
        std::cout<< "lua v : " << v.value() << std::endl;
    }
    else
    {
        std::cout<<"has no value"<<std::endl;
    }
    
    std::cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
