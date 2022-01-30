#ifndef KARAMAY_ENGINE_H
#define KARAMAY_ENGINE_H

#include "embedded/lua/lvm.h"
#include "embedded/lua/lvm_graphics_module.h"
#include "embedded/python/pvm.h"
#include "graphics/gl_renderer_dispatcher.h"

class karamay_engine final
{
public:

	karamay_engine() = default;
	karamay_engine(const karamay_engine&) = delete;
	karamay_engine& operator=(const karamay_engine&) = delete;

	~karamay_engine() = default;

public:

	bool initialize() noexcept;

	void run() noexcept;

private:

	bool _should_exit = false;

	gl_renderer_dispatcher _renderer_dispatcher;
	std::thread _renderer_dispathcer_thread;

	lua_api::lua_vm _lvm;
	std::thread _lvm_thread;

public:

	static void set_engine_root(const std::string& engine_root)
	{
		_engine_root_dir = engine_root;
	}

	static const std::string& get_engine_root() { return _engine_root_dir; }

private:

	static std::string _engine_root_dir;

};



#endif