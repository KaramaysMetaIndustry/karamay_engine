#ifndef LUA_TYPE_IS_H
#define LUA_TYPE_IS_H

#include "public/lua.h"
#include "lua_type_concepts.h"

namespace lua_api
{
    template<lua_t_acceptable T>
    static bool is(lua_State* l, std::int32_t idx) noexcept
    {
        if constexpr (lua_boolean_acceptable<T>)
        {
            return lua_isboolean(l, idx);
        }
        else if constexpr (lua_integer_number_acceptable<T>)
        {
            return lua_isinteger(l, idx);
        }
        else if constexpr (lua_real_number_acceptable<T>)
        {
            return lua_isnumber(l, idx);
        }
        else if constexpr (lua_string_acceptable<T>)
        {
            return lua_isstring(l, idx) && !lua_isnumber(l, idx);
        }
        else if constexpr (lua_userdata_acceptable<T>)
        {
            return lua_isuserdata(l, idx);
        }
        else if constexpr (lua_table_acceptable_std_array<T>)
        {
            return lua_istable(l, idx);
        }
        else if constexpr (lua_table_acceptable_std_vector<T>)
        {
            return lua_istable(l, idx);
        }
        else if constexpr (lua_table_acceptable_std_deque<T>)
        {
            return lua_istable(l, idx);
        }
        else if constexpr (lua_table_acceptable_std_list<T>)
        {
            return lua_istable(l, idx);
        }
        else if constexpr (lua_table_acceptable_std_forward_list<T>)
        {
            return lua_istable(l, idx);
        }
        else if constexpr (lua_table_acceptable_std_set<T>)
        {
            return lua_istable(l, idx);
        }
        else if constexpr (lua_table_acceptable_std_unordered_set<T>)
        {
            return lua_istable(l, idx);
        }
        else if constexpr (lua_table_acceptable_std_unordered_multiset<T>)
        {
            return lua_istable(l, idx);
        }
        else if constexpr (lua_table_acceptable_std_map<T>)
        {
            return lua_istable(l, idx);
        }
        else if constexpr (lua_table_acceptable_std_unordered_map<T>)
        {
            return lua_istable(l, idx);
        }
        else if constexpr (lua_table_acceptable_std_multimap<T>)
        {
            return lua_istable(l, idx);
        }
        else if constexpr (lua_table_acceptable_std_unordered_multimap<T>)
        {
            return lua_istable(l, idx);
        }
        else
        {
            return false;
        }
    }
}


#endif