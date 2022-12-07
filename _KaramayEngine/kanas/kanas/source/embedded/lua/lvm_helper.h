#pragma once

#include "lvm.h"

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

template<typename ...Args, std::size_t... N>
static std::tuple<Args...> to_tuple_base(lua_State* l, std::index_sequence<N...>)
{
    std::tuple<Args...> parameters;
    ((std::get<N>(parameters) = lua_api::basic::static_to<Args, N + 1>(l).value()), ...);
    return parameters;
}

template<typename ...Args>
static std::tuple<Args...> to_tuple_from_bottom(lua_State* l)
{
    return to_tuple_base<Args...>(l, std::index_sequence_for<Args...>());
}

template<typename Func, typename... Args, std::size_t... N>
static void call_func_impl(lua_State* l, Func func, const std::tuple<Args...> parameters, std::index_sequence<N...>)
{
    if constexpr (std::is_void_v<typename Func::result_type>)
    {
        func((std::get<N>(parameters), ...));
    }
    else
    {
        lua_api::push(func((std::get<N>(parameters), ...)));
    }
}

template<typename Ret, typename... Args>
static void call_func(lua_State* l, std::function<Ret(Args...)> func)
{
    const auto parameters = to_tuple_from_bottom<Args...>(l);
    call_func_impl(func, parameters, std::index_sequence_for<Args...>());
}

template<typename Ret, typename... Args>
struct lua_function_delegate
{
    lua_function_delegate(const std::string& name, Ret(* f)(Args...))
    {
        delegate_name = name;
        callable = f;
    }
    
    std::string delegate_name;
    std::function<Ret(Args...)> callable;
};

template<typename Ret, typename Ty, typename... Args>
struct lua_member_function_delegate
{
    lua_member_function_delegate(const std::string& name, Ret(Ty::* f)(Args...))
    {
        delegate_name = name;
        callable = f;
    }

    std::string delegate_name;
    std::function<Ret(Ty*, Args...)> callable;
};

static void aa_test(std::int32_t v) {}

class oda
{
    int a = 1;
public:
    std::int32_t set(std::int32_t v)
    {
        a = v;
        return a;
    }
};

// namespace lua_set
// {
//     static lua_function_delegate ded = lua_function_delegate("__add", &aa_test);
//     
//     static int call_delegate(lua_State*)
//     {
//         call_func(ded.callable);
//         return 1;
//     }
//     
// }


#define DEFINE_LUA_FUNCTION(NAMESPACE, FUNCTION_NAME, FUNCTION_PTR)\
namespace NAMESPACE\
{\
    static lua_function_delegate ded = lua_function_delegate(FUNCTION_NAME, &FUNCTION_PTR);\
    \
    static int call_delegate(lua_State* l)\
    {\
        call_func(l, ded.callable);\
        return 1;\
    }\
    \
}

//DEFINE_LUA_FUNCTION(lua_set, "__add", aa_test)

// namespace lua_oda_set
// {
//     static lua_member_function_delegate ded = lua_member_function_delegate("__add", &oda::set);
//
//     static int call_delegate(lua_State*)
//     {
//         call_func(ded.callable);
//         return 1;
//     }
// }

#define DEFINE_LUA_MEMBER_FUNCTION(LUA_FUNCTION_NAME, CLASS_NAME, CLASS_FUNCTION_NAME)\
namespace lua_##CLASS_NAME##_##CLASS_FUNCTION_NAME\
{\
    static lua_member_function_delegate ded = lua_member_function_delegate(LUA_FUNCTION_NAME, &CLASS_NAME##::##CLASS_FUNCTION_NAME);\
\
    static int call_delegate(lua_State* l)\
    {\
        call_func(l, ded.callable);\
        return 1;\
    }\
}

//DEFINE_LUA_MEMBER_FUNCTION("__add", oda, set)