#ifndef LVM_H
#define LVM_H

#include "public/stl.h"
#include "public/_lua.h"


// 只有 userdata table lightuserdata 有权利去修改
// 

namespace lua_api
{
	//nil, boolean, number, string, function, userdata, thread, and table.
	enum class lua_t : int
	{
		NONE = LUA_TNONE,
		NIL = LUA_TNIL,
		BOOLEAN = LUA_TBOOLEAN,
		NUMBER = LUA_TNUMBER,
		STRING = LUA_TSTRING,
		
		FUNCTION = LUA_TFUNCTION,
		
		TABLE = LUA_TTABLE,
		USERDATA = LUA_TUSERDATA,
		LIGHTUSERDATA = LUA_TLIGHTUSERDATA,
		
		THREAD = LUA_TTHREAD,

		NUMTYPES = LUA_NUMTYPES
	};

	enum class lua_status : int
	{
		OK = LUA_OK, // : no errors.
		ERR_RUN = LUA_ERRRUN, // : a runtime error.
		ERR_MEM = LUA_ERRMEM, // : memory allocation error.For such errors, Lua does not call the message handler.
		ERR_ERR = LUA_ERRERR, //: error while running the message handler.
		ERR_SYNTAX = LUA_ERRSYNTAX, // : syntax error during precompilation.
		YIELD = LUA_YIELD, //: the thread(coroutine) yields.
		ERR_FILE = LUA_ERRFILE // : a file - related error; e.g., it cannot open or read the file.
	};

	enum class lua_compare_op : int
	{
		EQ = LUA_OPEQ, // ==
		LT = LUA_OPLT, // <
		LE = LUA_OPLE // <=
	};

	enum class lua_gc_option : int
	{
		GCCOLLECT = LUA_GCCOLLECT, //Performs a full garbage - collection cycle.
		GCSTOP = LUA_GCSTOP, //Stops the garbage collector.
		GCRESTART = LUA_GCRESTART, //Restarts the garbage collector.
		GCCOUNT = LUA_GCCOUNT, //Returns the current amount of memory(in Kbytes) in use by Lua.
		GCCOUNTB = LUA_GCCOUNTB, //Returns the remainder of dividing the current amount of bytes of memory in use by Lua by 1024.
		GCSTEP = LUA_GCSTEP, //Performs an incremental step of garbage collection, corresponding to the allocation of stepsize Kbytes.
		GCISRUNNING = LUA_GCISRUNNING, //Returns a boolean that tells whether the collector is running(i.e., not stopped).
		GCINC = LUA_GCINC, //Changes the collector to incremental mode with the given parameters(see §2.5.1).Returns the previous mode(LUA_GCGEN or LUA_GCINC).
		GCGEN = LUA_GCGEN //Changes the collector to generational mode with the given parameters(see §2.5.2).Returns the previous mode(LUA_GCGEN or LUA_GCINC).
	};

	namespace basic
	{
		inline bool check_stack_available_capacity(lua_State* L, int32 num)
		{
			return lua_checkstack(L, num) == 1;
		}

		inline void close(lua_State* L)
		{
			lua_close(L);
		}

		inline void compare(lua_State* L, int32 left_index, int32 right_index, lua_compare_op op)
		{
			lua_compare(L, left_index, right_index, static_cast<int>(op));
		}

		inline void concat(lua_State* L, int32 num)
		{
			lua_concat(L, num);
		}

		inline void copy(lua_State* L, int32 src_index, int32  dst_index)
		{
			lua_copy(L, src_index, dst_index);
		}

		inline void create_table(lua_State* L, int32 size, int32 capacity)
		{
			lua_createtable(L, 0, 0);
		}

		inline void create_table(lua_State* L)
		{
			lua_newtable(L);
		}

		inline int32 dump(lua_State* L)
		{
			//lua_dump(L,)
			return 0;
		}

		inline int32 error(lua_State* L)
		{
			return lua_error(L);
		}

		inline int32 gc(lua_State* L, lua_gc_option option)
		{
			//lua_gc(L, static_cast<int>(option), )
			return 0;
		}

		inline void pop(lua_State* L, int32 num)
		{
			lua_pop(L, num);
		}

		////// push*  : push value onto the stack from C

		inline void push_nil(lua_State* L) 
		{ 
			lua_pushnil(L);
		}

		inline void push_boolean(lua_State* L, bool value) 
		{
			lua_pushboolean(L, static_cast<int>(value)); 
		}

		template<typename INTEGER_T>
		inline void push_integer(lua_State* L, INTEGER_T value)
		{
			static_assert(
				std::is_same_v<uint8, INTEGER_T> ||
				std::is_same_v<uint16, INTEGER_T> ||
				std::is_same_v<uint32, INTEGER_T> ||
				std::is_same_v<uint64, INTEGER_T> ||
				std::is_same_v<int8, INTEGER_T> ||
				std::is_same_v<int16, INTEGER_T> ||
				std::is_same_v<int32, INTEGER_T> ||
				std::is_same_v<int64, INTEGER_T>,
				"integer must be std(uint8, uint16, uin32, uint64, int8, int16, int32, int64)"
				);
			lua_pushinteger(L, static_cast<lua_Integer>(value));
		}

		template<typename NUMBER_T>
		inline void push_number(lua_State* L, NUMBER_T value)
		{
			static_assert(
				std::is_same_v<float, NUMBER_T> ||
				std::is_same_v<double, NUMBER_T>,
				"number must be std(float, double)"
				);
			lua_pushnumber(L, static_cast<lua_Number>(value));
		}

		inline void push_string(lua_State* L, char* value) 
		{ 
			lua_pushstring(L, value); 
		}
		inline void push_string(lua_State* L, const char* value) 
		{ 
			lua_pushstring(L, value);
		}
		inline void push_string(lua_State* L, std::string& value) 
		{ 
			lua_pushstring(L, value.c_str()); 
		}
		inline void push_string(lua_State* L, const std::string& value) 
		{ 
			lua_pushstring(L, value.c_str());
		}
		inline void push_string(lua_State* L, std::string&& value) 
		{ 
			lua_pushstring(L, value.c_str());
		}

		/*
		* Pushes a light userdata onto the stack.
		* Userdata represent C values in Lua. A light userdata represents a pointer, a void*.
		* It is a value (like a number): you do not create it, 
		* it has no individual metatable, and it is not collected (as it was never created). 
		* A light userdata is equal to "any" light userdata with the same C address.
		*/
		inline void push_light_userdata(lua_State* L, void* userdata)
		{
			lua_pushlightuserdata(L, userdata);
		}
		
		inline void push_light_userdata(lua_State* L, const void* userdata)
		{
			lua_pushlightuserdata(L, (void*)userdata);
		}

		inline void push_thread(lua_State* L)
		{
			lua_pushthread(L);
		}

		inline void push_table(lua_State* L)
		{
			lua_pushglobaltable(L);
		}
		
		inline void push_value(lua_State* L, int32 index)
		{
			lua_pushvalue(L, index);
		}

		/*
		* Loads a Lua chunk without running it. 
		* If there are no errors, lua_load pushes the compiled chunk as a Lua function on top of the stack. 
		* Otherwise, it pushes an error message.
		* 
		* The lua_load function uses a user-supplied reader function to read the chunk (see lua_Reader). 
		* The data argument is an opaque value passed to the reader function.
		* The chunkname argument gives a name to the chunk, which is used for error messages and in debug information (see §4.7).
		* lua_load automatically detects whether the chunk is text or binary and loads it accordingly (see program luac). 
		* The string mode works as in function load, with the addition that a NULL value is equivalent to the string "bt".
		* 
		* lua_load uses the stack internally, so the reader function must always leave the stack unmodified when returning.
		* lua_load can return LUA_OK, LUA_ERRSYNTAX, or LUA_ERRMEM. The function may also return other values corresponding to errors raised by the read function (see §4.4.1).
		* If the resulting function has upvalues, its first upvalue is set to the value of the global environment stored at index LUA_RIDX_GLOBALS in the registry (see §4.3). 
		* When loading main chunks, this upvalue will be the _ENV variable (see §2.2). Other upvalues are initialized with nil.
		*/
		inline lua_status load(lua_State* L, lua_Reader reader, void* data, const char* chunk_name, const char* mode)
		{
			return static_cast<lua_status>(lua_load(L, reader, data, chunk_name, mode));
		}

		/*
		* Creates a new empty table and pushes it onto the stack. 
		* It is equivalent to createtable(L, 0, 0).
		*/
		inline void new_table(lua_State* L)
		{
			lua_newtable(L);
		}
		
		inline void new_table(lua_State* L, int32 narr, int32 nrec)
		{
			lua_createtable(L, narr, nrec);
		}

		////////// to* : fetch value form stack to C

		template<typename INTEGER_T>
		inline INTEGER_T to_integer(lua_State* L, int32 stack_index)
		{
			static_assert(
				std::is_same_v<uint8, INTEGER_T> ||
				std::is_same_v<uint16, INTEGER_T> ||
				std::is_same_v<uint32, INTEGER_T> ||
				std::is_same_v<uint64, INTEGER_T> ||
				std::is_same_v<int8, INTEGER_T> ||
				std::is_same_v<int16, INTEGER_T> ||
				std::is_same_v<int32, INTEGER_T> ||
				std::is_same_v<int64, INTEGER_T>,
				"integer must be uint8, uint16, uin32, uint64, int8, int16, int32, int64."
				);
			return static_cast<INTEGER_T>(lua_tointeger(L, stack_index));
		}

		template<typename NUMBER_T>
		inline NUMBER_T to_number(lua_State* L, int32 stack_index)
		{
			static_assert(
				std::is_same_v<float, NUMBER_T> ||
				std::is_same_v<double, NUMBER_T>,
				"number must be float or double."
				);
			return static_cast<NUMBER_T>(lua_tonumber(L, stack_index));
		}

		inline bool to_boolean(lua_State* L, int32 stack_index) 
		{ 
			return lua_toboolean(L, stack_index) == 1; 
		}

		inline std::string to_string(lua_State* L, int32 stack_index) 
		{ 
			return std::string(lua_tostring(L, stack_index));
		}

		inline void* to_userdata(lua_State* L, int32 index)
		{
			return lua_touserdata(L, index);
		}
		
		inline lua_State* to_thread(lua_State* L, int32 stack_index) 
		{ 
			return lua_tothread(L, stack_index); 
		}

		inline lua_CFunction to_cfunction(lua_State* L, int32 stack_index) 
		{ 
			return lua_tocfunction(L, stack_index);
		}

#ifdef _DEBUG
		inline const void* to_pointer(lua_State* L, int32 stack_index)
		{
			return lua_topointer(L, stack_index);
		}
#endif

		/*
		* Returns the index of the top element in the stack. 
		* Because indices start at 1, this result is equal to the number of elements in the stack; in particular, 0 means an empty stack.
		* @return stack top index (1 ~ N)
		*/
		inline int32 top_index(lua_State* l)
		{ 
			return lua_gettop(l);
		}

		/////// fetch value from lua, push onto stack

		/*
		* Pushes onto the stack the value of the global name. 
		* Returns the type of that value.
		* @return the type of value
		*/
		inline int32 get_global(lua_State* l, const char* name)
		{
			return lua_getglobal(l, name);
		}

		/*
		* Pushes onto the stack the value t[i], where t is the value at the given index. 
		* As in Lua, this function may trigger a metamethod for the "index" event (see §2.4).
		* Returns the type of the pushed value.
		* @return the type of value
		*/
		inline int32 geti(lua_State* l, int32 stack_index, int32 index)
		{
			return lua_geti(l, stack_index, index);
		}

		/*
		* Pushes onto the stack the value t[k], where t is the value at the given index and k is the value on the top of the stack.
		* This function pops the key from the stack, pushing the resulting value in its place. 
		* As in Lua, this function may trigger a metamethod for the "index" event
		*/
		inline lua_t get_table(lua_State* l, int32 index)
		{
			return static_cast<lua_t>(lua_gettable(l , index));
		}

		/*
		* Does the equivalent to t[k] = v, where t is the value at the given index, v is the value on the top of the stack, and k is the value just below the top.
		* This function pops both the key and the value from the stack. 
		* As in Lua, this function may trigger a metamethod for the "__newindex" event
		*/
		inline void set_table(lua_State* l, int32 index)
		{
			lua_settable(l, index);
		}

		/*
		*
		*/
		inline lua_t raw_get(lua_State* l, int32 index)
		{
			return static_cast<lua_t>(lua_rawget(l, index));
		}
		
		/*
		* 
		*/
		inline void raw_set(lua_State* l, int32 index)
		{
			lua_rawset(l, index);
		}

		/*
		* Pushes onto the stack the value t[n], where t is the table at the given index.
		* The access is raw, that is, it does not use the __index metavalue.
		* Returns the type of the pushed value.
		*/
		inline lua_t raw_get(lua_State* l, int32 index, int64 key)
		{
			return static_cast<lua_t>(lua_rawgeti(l, index, key));
		}

		/*
		* Does the equivalent of t[i] = v, where t is the table at the given index and v is the value on the top of the stack.
		* This function pops the value from the stack. 
		* The assignment is raw, that is, it does not use the __newindex metavalue.
		*/
		inline void raw_set(lua_State* l, int32 index, int64 key)
		{
			lua_rawseti(l, index, key);
		}

		/*
		* Pushes onto the stack the value t[k], where t is the value at the given index.
		* As in Lua, this function may trigger a metamethod for the "index" event
		*/
		inline lua_t get_field(lua_State* l, int32 index, const char* key)
		{
			return static_cast<lua_t>(lua_getfield(l, index, key));
		}

		/*
		* Does the equivalent to t[k] = v, where t is the value at the given index and v is the value on the top of the stack.
		* This function pops the value from the stack. 
		* As in Lua, this function may trigger a metamethod for the "newindex" event
		*/
		inline void set_field(lua_State* l, int32 index, const char* key)
		{
			// v, ..., t 
			lua_setfield(l, index, key);
		}

		/*
		* sets top value as the new metatable for the value at the given index 
		* and Pops it( table or nil) from the stack and
		* @return type of value
		*/
		inline void set_metatable(lua_State* l, int32 index)
		{
			lua_setmetatable(l, index);
		}

		/*
		* If the value at the given index has a metatable, the function pushes that metatable onto the stack and returns 1.
		* Otherwise, the function returns 0 and pushes nothing on the stack.
		* @return 1 has metatable and push the metatable onto stack, 0 has no metatable and push nothing
		*/
		inline bool get_metatable(lua_State* l, int32 index)
		{
			return lua_getmetatable(l, index) == 1;
		}

		inline int32 getiuservalue(lua_State* L, int32 index, int32 n)
		{
			return lua_getiuservalue(L, index, n);
		}

		inline void set_top(lua_State* l, int32 index)
		{
			lua_settop(l, index);
		}

		inline void set_warnf(lua_State* L, lua_WarnFunction f, void* ud)
		{

		}

		inline void seti(lua_State* L, int32 stack_index, int64 n)
		{
			lua_seti(L, stack_index, n);
		}

		/*
		* Pops a value from the stack and sets it as the new value of global name.
		*/
		inline void set_global(lua_State* L, const char* name)
		{
			lua_setglobal(L, name);
		}

		inline void set_allocf(lua_State* L, lua_Alloc f, void* ud)
		{
			lua_setallocf(L, f, ud);
		}

		inline bool is_number(lua_State* L, int32 stack_index) 
		{ 
			return lua_isnumber(L, stack_index) == 1; 
		}
		
		inline bool is_integer(lua_State* L, int32 stack_index) 
		{ 
			return lua_isinteger(L, stack_index) == 1;
		}
		
		inline bool is_string(lua_State* L, int32 stack_index) 
		{
			return lua_isstring(L, stack_index) == 1; 
		}
		
		inline bool is_cfunction(lua_State* L, int32 stack_index) 
		{ 
			return lua_iscfunction(L, stack_index) == 1; 
		}
		
		inline bool is_userdata(lua_State* L, int32 stack_index) 
		{ 
			return lua_isuserdata(L, stack_index) == 1; 
		}
		
		inline bool is_light_userdata(lua_State* L, int32 stack_index) 
		{ 
			return lua_islightuserdata(L, stack_index) == 1;
		}

		inline lua_t type(lua_State* L, int32 stack_index) 
		{ 
			return static_cast<lua_t>(lua_type(L, stack_index));
		}
	
		inline void new_userdata(lua_State* L, void* userdata)
		{
			void** p_userdata = (void**)lua_newuserdata(L, sizeof(void*)); // -1
			*p_userdata = userdata;
		}

	}

	namespace auxiliary
	{
		/*
		* If the registry already has the key name, returns 0.
		*
		* Otherwise, creates a new table to be used as a metatable for userdata, 
		* adds to this new table the pair __name = name,
		* adds to the registry the pair [name] = new table, 
		* and returns 1.
		*
		* In both cases, 
		* the function pushes onto the stack the final value associated with tname in the registry.
		*/
		inline int32 new_metatable(lua_State* L, const char* name)
		{
			return luaL_newmetatable(L, name);
		}

		/*
		* Pushes onto the stack the metatable associated with the name tname in the registry,
		* or nil if there is no metatable associated with that name. 
		* 
		* Returns the type of the pushed value.
		*/
		inline int32 get_metatable(lua_State* L, const char* name)
		{
			return luaL_getmetatable(L, name);
		}

		/*
		* Sets the metatable of the object on the top of the stack 
		* as the metatable associated with name tname in the registry (see luaL_newmetatable).
		*/
		inline void set_metatable(lua_State* L, const char* name)
		{
			luaL_setmetatable(L, name);
		}

		/*
		* Registers all functions in the array l  
		* into the table on the top of the stack (below optional upvalues, see next).
		* When nup is not zero, all functions are created with nup upvalues, 
		* initialized with copies of the nup values previously pushed on the stack on top of the library table. 
		* These values are popped from the stack after the registration.
		*/
		inline void set_funcs(lua_State* L, const luaL_Reg* funcs, int32 nup)
		{
			luaL_setfuncs(L, funcs, nup);
		}


		/*
		* Adds the byte c to the buffer B
		*/
		inline void add_char(luaL_Buffer* B, char c)
		{
			luaL_addchar(B, c);
		}

		inline void add_gsub() {}

		inline void add_lstring() {}

		inline void add_size() {}

		inline void add_string() {}

		inline void add_value() {}

		inline void arg_check() {}

		inline void arg_error() {}

		inline void arg_expected() {}

		inline char* buff_addr(luaL_Buffer* B) {}

		inline void buf_init_size(lua_State* L, luaL_Buffer* B, size_t sz) {}

		inline void buff_sub() {}

		inline void open_libs(lua_State* L)
		{
			luaL_openlibs(L);
		}

		/*
		* If package.loaded[modname] is not true, calls the function openf with the string modname as an argument and sets the call result to package.loaded[modname], 
		* as if that function has been called through require.
		* If glb is true, also stores the module into the global modname.
		* Leaves a copy of the module on the stack.
		*/
		inline void requiref(lua_State* L, const char* modname, lua_CFunction openf, int glb)
		{
			luaL_requiref(L, modname, openf, glb);
		}

		inline lua_State* new_state()
		{
			return luaL_newstate();
		}

		/*
		* Loads a string as a Lua chunk. This function uses lua_load to load the chunk in the zero-terminated string s.
		* This function returns the same results as lua_load.
		* Also as lua_load, this function only loads the chunk; it does not run it.
		*/
		inline lua_status load_string(lua_State* L, const char* str)
		{
			return static_cast<lua_status>(luaL_loadstring(L, str));
		}

		inline lua_status do_string(lua_State* L, const char* str)
		{
			return static_cast<lua_status>(luaL_dostring(L, str));
		}

		inline lua_status load_file(lua_State* L, const char* file_name)
		{
			return static_cast<lua_status>(luaL_loadfile(L, file_name));
		}

		inline lua_status load_file(lua_State* L, const char* file_name, const char* mode)
		{
			return static_cast<lua_status>(luaL_loadfilex(L, file_name, mode));
		}

		inline lua_status do_file(lua_State* L, const char* file_name)
		{
			return static_cast<lua_status>(luaL_dofile(L, file_name));
		}

		inline lua_status load_buffer(lua_State* L, const char* buff, size_t sz, const char* name, const char* mode)
		{
			return static_cast<lua_status>(luaL_loadbufferx(L, buff, sz, name, mode));
		}

		inline lua_status load_buffer(lua_State* L, const char* buff, size_t sz, const char* name)
		{
			return static_cast<lua_status>(luaL_loadbuffer(L, buff, sz, name));
		}

	}

	/*struct lua_index
	{
		explicit lua_index(int32 _Index);

		int32 GetIndex() const { return Index; }

	protected:
		int32 Index;
	};

	struct lua_value : public lua_index
	{
		explicit lua_value(int32 _Index);
		explicit lua_value(int32 _Index, int32 _Type);

		int32 GetType() const { return Type; }

		template <typename T>
		T Value() const;

		template <typename T>
		operator T() const;

		template <typename T, typename Allocator>
		operator std::vector<T, Allocator>& () const;

		template <typename T, typename KeyFunc, typename Allocator>
		operator std::set<T, KeyFunc, Allocator>& () const;

		template <typename KeyType, typename ValueType, typename Allocator, typename KeyFunc>
		operator std::map<KeyType, ValueType, Allocator, KeyFunc>& () const;

	private:
		int32 Type;
	};

	struct lua_ret_values
	{
		explicit lua_ret_values(int32 NumResults);
		lua_ret_values(lua_ret_values&& Src);
		~lua_ret_values();

		void Pop();
		bool IsValid() const { return bValid; }
		int32 Num() const { return values.size(); }

		const lua_value& operator[](int32 i) const;

	private:
		lua_ret_values(const lua_ret_values& Src);

		std::vector<lua_value> values;
		bool bValid;
	};

	struct lua_table : public lua_index
	{
		explicit lua_table(int32 index);
		explicit lua_table(lua_value value);
		~lua_table();

		void Reset();
		int32 Length() const;

		lua_value operator[](int32 i) const;
		lua_value operator[](int64 i) const;
		lua_value operator[](double d) const;
		lua_value operator[](const char* s) const;
		lua_value operator[](const void* p) const;
		lua_value operator[](lua_index stack_index) const;
		lua_value operator[](lua_value key) const;

		template <typename... T>
		lua_ret_values Call(const char* FuncName, T&&... Args) const;

	private:
		mutable int32 PushedValues;
	};*/ 

	inline void* to_userdata_fast(lua_State* L, int32 stack_index, bool two_level_ptr)
	{
		bool _two_level_ptr = false;
		void* _userdata = nullptr;



	}

	inline void* to_userdata(lua_State* L, int32 stack_index, bool* two_level_ptr)
	{
		if (stack_index < 0 && stack_index > LUA_REGISTRYINDEX)
		{
			int32 _top = basic::top_index(L);
			stack_index += _top + 1;
		}

		void* _userdata = nullptr;
		bool _two_level_ptr = false, _class_metatable = false;

		lua_t _type = basic::type(L, stack_index);
		switch (_type)
		{
		case lua_t::TABLE:
		{
			basic::push_string(L, "Object");
			_type = basic::raw_get(L, stack_index);
			if (_type == lua_t::USERDATA)
			{
				_userdata = basic::to_userdata(L, -1);
			}
			else {
				basic::pop(L, 1);
				basic::push_string(L, "ClassDesc");
				_type = basic::raw_get(L, stack_index);
				if (_type == lua_t::LIGHTUSERDATA)
				{
					_userdata = basic::to_userdata(L, -1);
					_class_metatable = true;
				}
			}
			_two_level_ptr = true;
			basic::pop(L, 1);
		}
		break;
		case lua_t::USERDATA: 
		{
		}
		break;
		default:
			break;
		}

		void** _instance_ptr = (void**)lua_touserdata(L, stack_index);
		if (!_instance_ptr || !(*_instance_ptr))
		{
			luaL_argcheck(L, false, stack_index, "input val test, invalid user data");
			return nullptr;
		}
		return (void*)*_instance_ptr;
	}

	inline void* to_cpp_instance(lua_State* L, int32 stack_index)
	{
		bool _two_level_ptr = false;
		void* _userdata = to_userdata(L, stack_index, &_two_level_ptr);
		if (_userdata)
		{
			return _two_level_ptr ? *((void**)_userdata) : _userdata;
		}
		return nullptr;
	}

	inline void* to_cpp_instance(lua_State* L, int32 stack_index, const char* metatable_name)
	{
		//void** pp_userdata = (void**)luaL_checkudata(L, stack_index, metatable_name);
		//return (void*)*pp_userdata;
		void* pp_userdata = (void*)luaL_checkudata(L, stack_index, metatable_name);
		return pp_userdata;
	}

	struct lua_class
	{
		std::string name;
		const luaL_Reg* funcs;
	};

	class lua_vm
	{
	public:

		lua_vm() = default;

		static void register_class(const char* name, const luaL_Reg* funcs)
		{
			std::cout << "register class : " << name << std::endl;
			auto _class = new lua_class();
			_class->name = name;
			_class->funcs = funcs;
			_classes.push_back(_class);
		}

		static void register_functions(const luaL_Reg* funcs)
		{

		}

	private:

		lua_State* _state = nullptr;

		std::unique_ptr<std::thread> _vm_thread = {};

		bool _should_exit = false;

		static std::vector<lua_class*> _classes;

	private:

		void _load_class(const std::string& class_name, const luaL_Reg* funcs)
		{
			const auto _clazz_name = class_name + "_clazz";

			// stack : null
			lua_api::auxiliary::new_metatable(_state, _clazz_name.c_str());
			// stack : metatable
			lua_api::basic::push_value(_state, -1);
			// stack : metatable, metatable
			lua_api::basic::set_field(_state, -2, "__index");
			// stack : metable
			lua_api::auxiliary::set_funcs(_state, funcs, 0);
			lua_api::basic::pop(_state, 1);
			// stack : null

			lua_api::basic::new_table(_state);
			// stack : table
			lua_api::auxiliary::set_metatable(_state, _clazz_name.c_str());
			lua_api::basic::set_global(_state, class_name.c_str());
			// stack : null

			std::cout << "load class : " << class_name << std::endl;
		}

		void _load_libs()
		{
			lua_api::auxiliary::open_libs(_state); // std

			//luaL_requiref(_state, "karamay_RHI", testModelOpen, 0);

			for (auto _class : _classes)
			{
				_load_class(_class->name, _class->funcs);
			}
		}

	public:

		bool start()
		{
			_state = lua_api::auxiliary::new_state();
			if (!_state) return false;
			_load_libs();

			// start dispatcher thread
			/*_vm_thread = std::make_unique<std::thread>(
				[this](int i)
				{
					while (!_should_exit)
					{
						std::cout << "lvm tick" << std::endl;

						int ret = luaL_dofile(_state, "G:\\PrivateRepos\\Karamays\\_KaramayEngine\\karamay_engine_graphics_unit_cmake\\karamay_engine_graphics_unit\\scripts\\blue_freckle\\Test.lua");
						if (ret != 0)
						{
							printf("%s", lua_tostring(_state, -1));
						}

						std::this_thread::sleep_for(std::chrono::milliseconds(100));
					}

					lua_close(_state);
					std::cout << "Lua virtual machine exit." << std::endl;
					_should_exit = false;
				}, 1
			);*/

			std::cout << "Lua virtual machine has been initialized, now is running." << std::endl;
			//_vm_thread->detach();
		}

		void notify_to_exit()
		{
			_should_exit = true;

			while (_should_exit) {}
		}

	public:

		bool do_file(const std::string& path)
		{
			int _result = luaL_dofile(_state, path.c_str());
			switch (_result)
			{
			case LUA_OK(0): std::cout << "no errors." << std::endl; break;
			case LUA_ERRRUN: std::cout << "a runtime error." << std::endl; break;
			case LUA_ERRMEM: std::cout << "memory allocation error.For such errors, Lua does not call the message handler." << std::endl; break;
			case LUA_ERRERR: std::cout << "error while running the message handler." << std::endl; break;
			case LUA_ERRSYNTAX: std::cout << "syntax error during precompilation." << std::endl; break;
			case LUA_YIELD: std::cout << "the thread(coroutine) yields." << std::endl; break;
			case LUA_ERRFILE: std::cout << "a file - related error; e.g., it cannot open or read the file." << std::endl; break;
			default:
				break;
			}
			if (_result != 0)
			{
				printf("%s", lua_tostring(_state, -1));
				return false;
			}

			return true;
		}

	};

}


#define LUA_LIBS_B()\
static const luaL_Reg libs[] =\
{\

#define LUA_LIBS_E()\
{nullptr}, {nullptr}\
};\


#define LUA_FUNCS_B() \
static const luaL_Reg functions[] =\
{\

#define LUA_FUNCS_E()\
{nullptr}, {nullptr}\
};\

/////////// metatable functions helper

// +
#define __ADD()\
{"__add", __add},\

// -
#define __SUB()\
{"__sub", __sub},\

// *
#define __MUL()\
{"__mul", __mul},\

// /
#define __DIV()\
{"__div", __div},\

// %
#define __MOD()\
{"__mod", __mod},\

// ^
#define __POW()\
{"__pow", __pow},\

// 
#define __UNM()\
{"__unm", __unm},\

// //
#define __IDIV()\
{"__idiv", __idiv},\

// &
#define __BAND()\
{"__band", __band},\

// |
#define __BOR()\
{"__bor", __bor},\

#define __BXOR()\
{"__bxor", __bxor},\

#define __BNOT()\
{"__bnot", __bnot},\

// <<
#define __SHL()\
{"__shl", __shl},\

// >>
#define __SHR()\
{"__shr", __shr},\

// ..
#define __CONCAT()\
{"__concat", __concat},\

// #
#define __LEN()\
{"__len", __len},\

// ==
#define __EQ()\
{"__eq", __eq},\

// <
#define __LT()\
{"__lt", __lt},\

// <=
#define __LE()\
{"__le", __le},\


#define __INDEX()\
{"__index", __index},\

#define __NEWINDEX()\
{"__newindex", __newindex},\

#define __CALL()\
{"__call", __call},\


#define __GC()\
{"__gc", __gc},\

#define __CLOSE()\
{"__close", __close},\

#define __NAME()\
{"__name", __name},\

#define __MODE()\
{"__mode", __mode},\

#define __PAIRS()\
{"__pairs", __pairs}\

#define FUNC(FUNC_PTR)\
{#FUNC_PTR, FUNC_PTR},\

#define IMPLEMENT_EXPORTER(NAME)\
struct NAME##_exporter\
{\
	static NAME##_exporter instance;\
	NAME##_exporter()\
	{\
		lua_api::lua_vm::register_class(#NAME, functions);\
	}\
	~NAME##_exporter() = default;\
};\
NAME##_exporter NAME##_exporter::instance;\


#endif