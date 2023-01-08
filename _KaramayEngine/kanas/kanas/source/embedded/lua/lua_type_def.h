#ifndef LUA_TYPE_DEF_H
#define LUA_TYPE_DEF_H

#include <iostream>

/*
* cpp data <=> lua data
* 
* bool <=> boolean
* uint8, uint16, uint32, uint64, int8, int16, int32, int64 <=> integer
* float, double <=> number
* c-style string, std::string <=> string
* void*, const void* <=> userdata
* lua_CFuntion <=> function
* std::containers <=> tables
*
*/
namespace lua_api
{
    enum class lua_t : int
	{
		none = LUA_TNONE,
		nil = LUA_TNIL, //nil
		boolean = LUA_TBOOLEAN, // boolean
		number = LUA_TNUMBER, // number
		string = LUA_TSTRING, // string
		function = LUA_TFUNCTION, // function
		table = LUA_TTABLE, // table
		userdata = LUA_TUSERDATA, // userdata
		light_userdata = LUA_TLIGHTUSERDATA, // userdata
		thread = LUA_TTHREAD, // thread
		num_types = LUA_NUMTYPES
	};

	enum class lua_status : int
	{
		ok = LUA_OK, // no errors.
		err_run = LUA_ERRRUN, // a runtime error.
		err_mem = LUA_ERRMEM, // memory allocation error.For such errors, Lua does not call the message handler.
		err_err = LUA_ERRERR, // error while running the message handler.
		err_syntax = LUA_ERRSYNTAX, // syntax error during precompilation.
		yield = LUA_YIELD, // the thread(coroutine) yields.
		err_file = LUA_ERRFILE // a file - related error; e.g., it cannot open or read the file.
	};

	enum class lua_compare_op : int
	{
		eq = LUA_OPEQ, // ==
		lt = LUA_OPLT, // <
		le = LUA_OPLE // <=
	};

	enum class lua_gc_option : int
	{
		gc_collect = LUA_GCCOLLECT, //Performs a full garbage - collection cycle.
		gc_stop = LUA_GCSTOP, //Stops the garbage collector.
		gc_restart = LUA_GCRESTART, //Restarts the garbage collector.
		gc_count = LUA_GCCOUNT, //Returns the current amount of memory(in Kbytes) in use by Lua.
		gc_count_b = LUA_GCCOUNTB, //Returns the remainder of dividing the current amount of bytes of memory in use by Lua by 1024.
		gc_step = LUA_GCSTEP, //Performs an incremental step of garbage collection, corresponding to the allocation of stepsize Kbytes.
		gc_is_running = LUA_GCISRUNNING, //Returns a boolean that tells whether the collector is running(i.e., not stopped).
		gc_inc = LUA_GCINC, //Changes the collector to incremental mode with the given parameters(see ��2.5.1).Returns the previous mode(LUA_GCGEN or LUA_GCINC).
		gc_gen = LUA_GCGEN //Changes the collector to generational mode with the given parameters(see ��2.5.2).Returns the previous mode(LUA_GCGEN or LUA_GCINC).
	};

	static lua_t type(lua_State* l, std::int32_t idx)
	{
		return static_cast<lua_t>(lua_type(l, idx));
	}
}

template<typename ...Args>
struct c_closure
{
	lua_CFunction f;
	std::tuple<Args...> args;
};


template<typename Ty>
struct lua_userdata_meta_info
{
    const char* get_type_name()
    {
        return "nullptr";
    }

    static lua_userdata_meta_info ref;
};
#endif