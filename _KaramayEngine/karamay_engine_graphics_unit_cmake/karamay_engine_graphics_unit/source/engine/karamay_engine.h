#ifndef KARAMAY_ENGINE_H
#define KARAMAY_ENGINE_H

#include "embedded/lua/lvm.h"
#include "embedded/lua/lvm_graphics_class.h"
#include "graphics/gl_renderer_dispatcher.h"

class karamay_engine final
{
public:

	karamay_engine() = default;
	karamay_engine(const karamay_engine&) = delete;
	karamay_engine& operator=(const karamay_engine&) = delete;

	~karamay_engine() = default;

public:

	bool initialize() noexcept
	{
		std::cout << "karamay engine starts to initialize." << std::endl;

		std::cout << "karamay engine has initialized." << std::endl;
		return true;
	}

	void run() noexcept
	{
		std::cout << "karamay engine is running." << std::endl;

		// run other threads
		_renderer_dispathcer_thread = std::thread(
			[this]()
			{
				_renderer_dispatcher.initialize();
				_renderer_dispatcher.start();
			}
		);

		_lvm_thread = std::thread(
			[this]()
			{
				_lvm.initialize();
				_lvm.start();
			}
		);

		_renderer_dispathcer_thread.detach();
		_lvm_thread.detach();

		while (!_should_exit)
		{

		}

		_lvm.notify_to_exit();
		_renderer_dispatcher.notify_exit();
		std::cout << "karamay engine has exited." << std::endl;
	}

private:

	bool _should_exit = false;

	gl_renderer_dispatcher _renderer_dispatcher;
	std::thread _renderer_dispathcer_thread;

	lua_api::lua_vm _lvm;
	std::thread _lvm_thread;

};

#endif