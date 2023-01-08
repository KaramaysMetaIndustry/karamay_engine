#ifndef LUA_TYPE_CONCEPTS_H
#define LUA_TYPE_CONCEPTS_H

#include <memory>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <queue>
#include <stack>

#include "lua_type_def.h"

namespace lua_api
{
	
	template<class T>
	concept lua_boolean_acceptable =
		std::is_same_v<std::remove_cvref_t<T>, bool>;

	template<class T>
	concept lua_integer_number_acceptable =
		std::_Is_any_of_v<std::remove_cvref_t<T>, std::int8_t, std::uint8_t, std::int16_t, std::uint16_t, std::int32_t, std::uint32_t, std::int64_t, std::uint64_t>;

	template<typename T>
	concept lua_real_number_acceptable = 
		std::_Is_any_of_v<std::remove_cvref_t<T>, std::float_t, std::double_t>;
	
	template<typename T>
	concept lua_number_acceptable =
		lua_integer_number_acceptable<T> or lua_real_number_acceptable<T>;

	template<typename T>
	concept lua_string_acceptable_c_style =
		std::is_same_v<T, const char*>;

	template<typename T>
	concept lua_string_acceptable_std_str =
		std::_Is_any_of_v<std::remove_cvref_t<T>, std::string>;

	template<typename T>
	concept lua_string_acceptable_std_str_view = 
		std::_Is_any_of_v<std::remove_cvref_t<T>, std::string_view>;
	
	template<typename T>
	concept lua_string_acceptable =
		lua_string_acceptable_c_style<T> or lua_string_acceptable_std_str<T> or lua_string_acceptable_std_str_view<T>;

	template<typename T>
	constexpr bool is_shared_ptr_v = false;

	template<typename T>
	constexpr bool is_shared_ptr_v<std::shared_ptr<T>> = true;
	
	
	template<typename T>
	concept lua_userdata_acceptable =
		is_shared_ptr_v<std::remove_cvref_t<T>>;

	
	template<typename T>
	constexpr bool is_c_closure_v = false;

	template<typename... Args>
	constexpr bool is_c_closure_v<c_closure<Args...>> = true;
	
	template<typename T>
	concept lua_closure_acceptable =
		is_c_closure_v<T>;

	
	template<typename T>
	concept lua_t_acceptable_non_container =
		lua_boolean_acceptable<T> or lua_number_acceptable<T> or lua_string_acceptable<T> or lua_userdata_acceptable<T>;
	

	template<typename T>
	constexpr bool is_array_v = false;

	template<typename T, std::size_t size>
	constexpr bool is_array_v<std::array<T, size>> = true;


	template<typename T>
	constexpr bool is_vector_v = false;

	template<typename T>
	constexpr bool is_vector_v<std::vector<T>> = true;

	template<typename T, typename U>
	constexpr bool is_vector_v<std::vector<T, U>> = true;


	template<typename T>
	constexpr bool is_deque_v = false;

	template<typename T>
	constexpr bool is_deque_v<std::deque<T>> = true;

	template<typename T, typename U>
	constexpr bool is_deque_v<std::deque<T, U>> = true;


	template<typename T>
	constexpr bool is_list_v = false;

	template<typename T>
	constexpr bool is_list_v<std::list<T>> = true;

	template<typename T, typename U>
	constexpr bool is_list_v<std::list<T, U>> = true;


	template<typename T>
	constexpr bool is_forward_list_v = false;

	template<typename T>
	constexpr bool is_forward_list_v<std::forward_list<T>> = true;

	template<typename T, typename U>
	constexpr bool is_forward_list_v<std::forward_list<T, U>> = true;


	template<typename T>
	constexpr bool is_stack_v = false;

	template<typename T>
	constexpr bool is_stack_v<std::stack<T>> = true;

	template<typename T, typename U>
	constexpr bool is_stack_v<std::stack<T, U>> = true;


	template<typename T>
	constexpr bool is_queue_v = false;

	template<typename T>
	constexpr bool is_queue_v<std::queue<T>> = true;

	template<typename T, typename U>
	constexpr bool is_queue_v<std::queue<T, U>> = true;


	template<typename T>
	constexpr bool is_priority_queue_v = false;

	template<typename T>
	constexpr bool is_priority_queue_v<std::priority_queue<T>> = true;

	template<typename T, typename U>
	constexpr bool is_priority_queue_v<std::priority_queue<T, U>> = true;

	template<typename T, typename U, typename W>
	constexpr bool is_priority_queue_v<std::priority_queue<T, U, W>> = true;


	template<typename T>
	constexpr bool is_set_v = false;

	template<typename T>
	constexpr bool is_set_v<std::set<T>> = true;

	template<typename T, typename U>
	constexpr bool is_set_v<std::set<T, U>> = true;

	template<typename T, typename U, typename W>
	constexpr bool is_set_v<std::set<T, U, W>> = true;


	template<typename T>
	constexpr bool is_unordered_set_v = false;

	template<typename T>
	constexpr bool is_unordered_set_v<std::unordered_set<T>> = true;

	template<typename T, typename U>
	constexpr bool is_unordered_set_v<std::unordered_set<T, U>> = true;

	template<typename T, typename U, typename W>
	constexpr bool is_unordered_set_v<std::unordered_set<T, U, W>> = true;

	template<typename T, typename U, typename W, typename X>
	constexpr bool is_unordered_set_v<std::unordered_set<T, U, W, X>> = true;

	
	template<typename T>
	constexpr bool is_multiset_v = false;

	template<typename T>
	constexpr bool is_multiset_v<std::multiset<T>> = true;

	template<typename T, typename U>
	constexpr bool is_multiset_v<std::multiset<T, U>> = true;

	template<typename T, typename U, typename W>
	constexpr bool is_multiset_v<std::multiset<T, U, W>> = true;


	template<typename T>
	constexpr bool is_unordered_multiset_v = false;

	template<typename T>
	constexpr bool is_unordered_multiset_v<std::unordered_multiset<T>> = true;

	template<typename T, typename U>
	constexpr bool is_unordered_multiset_v<std::unordered_multiset<T, U>> = true;

	template<typename T, typename U, typename W>
	constexpr bool is_unordered_multiset_v<std::unordered_multiset<T, U, W>> = true;

	template<typename T, typename U, typename W, typename X>
	constexpr bool is_unordered_multiset_v<std::unordered_multiset<T, U, W, X>> = true;


	template<typename T>
	constexpr bool is_map_v = false;

	template<typename T, typename U>
	constexpr bool is_map_v<std::map<T, U>> = true;

	template<typename T, typename U, typename W>
	constexpr bool is_map_v<std::map<T, U, W>> = true;

	template<typename T, typename U, typename W, typename X>
	constexpr bool is_map_v<std::map<T, U, W, X>> = true;


	template<typename T>
	constexpr bool is_multimap_v = false;

	template<typename T, typename U>
	constexpr bool is_multimap_v<std::multimap<T, U>> = true;

	template<typename T, typename U, typename W>
	constexpr bool is_multimap_v<std::multimap<T, U, W>> = true;

	template<typename T, typename U, typename W, typename X>
	constexpr bool is_multimap_v<std::multimap<T, U, W, X>> = true;


	template<typename T>
	constexpr bool is_unordered_map_v = false;

	template<typename T, typename U>
	constexpr bool is_unordered_map_v<std::unordered_map<T, U>> = true;

	template<typename T, typename U, typename W>
	constexpr bool is_unordered_map_v<std::unordered_map<T, U, W>> = true;

	template<typename T, typename U, typename W, typename X>
	constexpr bool is_unordered_map_v<std::unordered_map<T, U, W, X>> = true;


	template<typename T>
	constexpr bool is_unordered_multimap_v = false;

	template<typename T, typename U>
	constexpr bool is_unordered_multimap_v<std::unordered_multimap<T, U>> = true;

	template<typename T, typename U, typename W>
	constexpr bool is_unordered_multimap_v<std::unordered_multimap<T, U, W>> = true;

	template<typename T, typename U, typename W, typename X>
	constexpr bool is_unordered_multimap_v<std::unordered_multimap<T, U, W, X>> = true;


	template<typename T>
	concept lua_table_acceptable_std_array =
		is_array_v<T> && 
		lua_t_acceptable_non_container<typename T::value_type>;

	template<typename T>
	concept lua_table_acceptable_std_vector =
		is_vector_v<T> &&
		lua_t_acceptable_non_container<typename T::value_type>;

	template<typename T>
	concept lua_table_acceptable_std_stack =
		is_stack_v<T> &&
		lua_t_acceptable_non_container<typename T::value_type>;

	template<typename T>
	concept lua_table_acceptable_std_queue =
		is_queue_v<T> &&
		lua_t_acceptable_non_container<typename T::value_type>;

	template<typename T>
	concept lua_table_acceptable_std_priority_queue =
		is_priority_queue_v<T> &&
		lua_t_acceptable_non_container<typename T::value_type>;

	template<typename T>
	concept lua_table_acceptable_std_deque =
		is_deque_v<T> &&
		lua_t_acceptable_non_container<typename T::value_type>;

	template<typename T>
	concept lua_table_acceptable_std_list =
		is_list_v<T> &&
		lua_t_acceptable_non_container<typename T::value_type>;

	template<typename T>
	concept lua_table_acceptable_std_forward_list =
		is_forward_list_v<T> &&
		lua_t_acceptable_non_container<typename T::value_type>;

	template<typename T>
	concept lua_table_acceptable_std_set =
		is_set_v<T> && 
		lua_t_acceptable_non_container<typename T::value_type>;

	template<typename T>
	concept lua_table_acceptable_std_unordered_set =
		is_unordered_set_v<T> &&
		lua_t_acceptable_non_container<typename T::value_type>;

	template<typename T>
	concept lua_table_acceptable_std_multiset =
		is_multiset_v<T> &&
		lua_t_acceptable_non_container<typename T::value_type>;

	template<typename T>
	concept lua_table_acceptable_std_unordered_multiset =
		is_unordered_multiset_v<T> &&
		lua_t_acceptable_non_container<typename T::value_type>;

	template<typename T>
	concept lua_table_acceptable_std_map = 
		is_map_v<T> &&
		lua_t_acceptable_non_container<typename T::key_type> &&
		lua_t_acceptable_non_container<typename T::mapped_type>;

	template<typename T>
	concept lua_table_acceptable_std_unordered_map =
		is_unordered_map_v<T> &&
		lua_t_acceptable_non_container<typename T::key_type> &&
		lua_t_acceptable_non_container<typename T::mapped_type>;

	template<typename T>
	concept lua_table_acceptable_std_multimap = 
		is_multimap_v<T> &&
		lua_t_acceptable_non_container<typename T::key_type> &&
		lua_t_acceptable_non_container<typename T::mapped_type>;

	template<typename T>
	concept lua_table_acceptable_std_unordered_multimap =
		is_unordered_multimap_v<T> &&
		lua_t_acceptable_non_container<typename T::key_type> &&
		lua_t_acceptable_non_container<typename T::mapped_type>;


	template<typename T>
	concept lua_t_acceptable = 
		lua_t_acceptable_non_container<T> or 
		lua_table_acceptable_std_array<T> or
		lua_table_acceptable_std_vector<T> or
		lua_table_acceptable_std_stack<T> or
		lua_table_acceptable_std_queue<T> or
		lua_table_acceptable_std_priority_queue<T> or
		lua_table_acceptable_std_deque<T> or
		lua_table_acceptable_std_list<T> or
		lua_table_acceptable_std_forward_list<T> or
		lua_table_acceptable_std_set<T> or
		lua_table_acceptable_std_unordered_set<T> or
		lua_table_acceptable_std_multiset<T> or
		lua_table_acceptable_std_unordered_multiset<T> or
		lua_table_acceptable_std_map<T> or
		lua_table_acceptable_std_unordered_map<T> or
		lua_table_acceptable_std_multimap<T> or
		lua_table_acceptable_std_unordered_multimap<T>;
}

#endif