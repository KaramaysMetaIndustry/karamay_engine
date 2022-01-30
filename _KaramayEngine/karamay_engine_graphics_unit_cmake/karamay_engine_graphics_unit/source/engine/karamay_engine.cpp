#include "karamay_engine.h"

std::string karamay_engine::_engine_root_dir;

bool karamay_engine::initialize() noexcept
{
	std::cout << "karamay engine starts to initialize." << std::endl;

	std::cout << "karamay engine has initialized." << std::endl;
	return true;
}

void karamay_engine::run() noexcept
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
