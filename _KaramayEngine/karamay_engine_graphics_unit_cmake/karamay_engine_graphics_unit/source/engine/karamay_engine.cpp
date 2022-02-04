#include "karamay_engine.h"

std::string karamay_engine::_engine_root_dir;

bool karamay_engine::initialize() noexcept
{
	std::cout << "karamay engine starts to initialize." << std::endl;
	_renderer_dispatcher = std::make_unique<gl_renderer_dispatcher>();
	_lvm = std::make_unique<lua_api::lua_vm>();


	if (!_renderer_dispatcher->initialize() || !_lvm->initialize()) return false;
	

	std::cout << "karamay engine has initialized." << std::endl;
	return true;
}

void karamay_engine::run() noexcept
{
	std::cout << "karamay engine is running." << std::endl;

	// run other threads
	_renderer_dispatcher_thread = std::thread(
		[&]()
		{
			_renderer_dispatcher->start();
		}

	);

	_lvm_thread = std::thread(
		[&]()
		{
			_lvm->start();
		}
	);

	uint64 _count = 0;

	while (!_should_exit)
	{
		if (_count > 20000000000) break;
		_count++;
	}

	_lvm->notify_to_exit();
	_renderer_dispatcher->notify_exit();

	_renderer_dispatcher_thread.join(); 
	_lvm_thread.join();

	std::cout << "karamay engine has exited." << std::endl;
}
