#ifndef KARAMAY_ENGINE_H
#define KARAMAY_ENGINE_H

#include "commandlet/karamray_engine_commandlet.h"
#include "filesystem/karamay_engine_filesystem.h"
#include "embedded/lua/lvm.h"
#include "embedded/lua/lvm_graphics_module.h"
#include "embedded/python/pvm.h"
#include "graphics/gl_renderer_dispatcher.h"
#include "network/network_dispatcher.h"

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

	// renderer dispatcher
	std::unique_ptr<gl_renderer_dispatcher> _renderer_dispatcher;
	std::thread _renderer_dispatcher_thread;

	// network dispatcher
	std::unique_ptr<network_dispatcher> _network_dispatcher;
	std::thread _network_dispatcher_thread;

	// lua vm
	std::unique_ptr<lua_api::lua_vm> _lvm;
	std::thread _lvm_thread;

	// python vm
	std::unique_ptr<python_api::python_vm> _pvm;
	std::thread _pvm_thread;

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