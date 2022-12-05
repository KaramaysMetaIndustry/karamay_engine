// kanas.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "embedded/lua/lvm.h"

class lua_object_test
{
	int a = 1;

public:

    void set_a(std::int32_t v)
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

LUA_CLASS_MODULE_BEGIN(lua_object_test)
ADD_FUNC("new", lua_new_ATest);
LUA_CLASS_MODULE_END(lua_object_test)

static int lua_new_ATest(lua_State* l)
{
    const auto _this = std::make_shared<lua_object_test>();
    lua_api::basic::push(_this);
    
    return 1;
}

template<typename ...Args, std::size_t... N>
static std::tuple<Args...> to_tuple_base(std::index_sequence<N...>)
{
    std::tuple<Args...> parameters;

    ((std::get<N>(parameters) = lua_api::basic::static_to<Args, N + 1>().value()), ...);
    
    return parameters;
}

template<typename ...Args>
static std::tuple<Args...> to_tuple()
{
    return to_tuple_base<Args...>(std::index_sequence_for<Args...>());
}

template<typename ...Args>
static std::tuple<Args...> to_object_call_list()
{
    return to_tuple_base<Args...>(std::index_sequence_for<Args...>());
}

template<typename Func>
void call_func()
{
}


struct lua_object_test_set_a_delegate
{
    std::function<void(lua_object_test*, std::int32_t)> f = &lua_object_test::set_a;
    std::shared_ptr<lua_object_test> _this;
} _dele;

static int lua_setA(lua_State* l)
{
    // auto _this = lua_api::basic::to<std::shared_ptr<ATest>>(1);
    // auto param1 = lua_api::basic::to<std::int32_t>(2);

    auto params = to_tuple<std::shared_ptr<lua_object_test>, std::int32_t>();
    _dele.f(std::get<0>(params).get(), std::get<1>(params));
    
    // if(!params.has_value())
    // {
    //     return 0;
    // }
    //
    // std::get<0>(params.value())->setA(
    //     std::get<1>(params.value())
    //     );

    return 1;
}

int main()
{
    const auto test = std::make_shared<lua_object_test>();
    lua_api::basic::push(test);
    lua_api::basic::push(1.1);
    lua_api::basic::push("json-jcc");

    auto c =
        to_tuple<std::shared_ptr<lua_object_test>, double, std::string>();

    
    

    // if(v.has_value())
    // {
    //     std::cout<< "lua v : " << v.value() << std::endl;
    // }
    // else
    // {
    //     std::cout<<"has no value"<<std::endl;
    // }

    //lua_api::basic::push_c_closure(lua_setA, 1, "aaaa", 2.f);
    
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
