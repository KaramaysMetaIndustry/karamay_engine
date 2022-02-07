#include "karamay_engine.h"

std::string karamay_engine::_engine_root_dir;

bool karamay_engine::initialize() noexcept
{
	std::cout << "karamay engine starts to initialize." << std::endl;

	_lvm = std::make_unique<lua_api::lua_vm>();
	_pvm = std::make_unique<python_api::python_vm>();
	_renderer_dispatcher = std::make_unique<gl_renderer_dispatcher>();
	_network_dispatcher = std::make_unique<network_dispatcher>();
	
	if (!_lvm || !_pvm || !_renderer_dispatcher || !_network_dispatcher)
	{
		return false;
	}

	// run sequence
	if (!_renderer_dispatcher->initialize() || !_lvm->initialize() || !_pvm->initialize() || !_network_dispatcher->initialize())
	{
		return false;
	}

	std::cout << "karamay engine has initialized." << std::endl;
	return true;
}

void karamay_engine::run() noexcept
{
	std::cout << "karamay engine is running." << std::endl;

	// renderer dispatcher thread
	_renderer_dispatcher_thread = std::thread([&]() { _renderer_dispatcher->run(); });
	// network dispatcher thread
	_network_dispatcher_thread = std::thread([&]() {_network_dispatcher->run(); });
	// lvm thread
	_lvm_thread = std::thread([&]() { _lvm->run(); });
	// pvm thread
	_pvm_thread = std::thread([&]() { _pvm->run(); });

	uint64 _count = 0;
	while (!_should_exit)
	{
		if (_count > 20000000000) break;
		_count++;
	}

	// notify to exit
	_lvm->notify_to_exit();
	_pvm->notify_to_exit();
	_network_dispatcher->notify_to_exit();
	_renderer_dispatcher->notify_to_exit();

	// wait threads
	_lvm_thread.join();
	_pvm_thread.join();
	_network_dispatcher_thread.join();
	_renderer_dispatcher_thread.join();

	std::cout << "karamay engine has exited." << std::endl;
}
