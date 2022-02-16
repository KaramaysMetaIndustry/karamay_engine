#include "karamay_engine.h"
#include "framework/world/world.h"
#include "framework/avatars/avatar.h"
#include "framework/prostheses/entity_prosthesis.h"
#include "framework/prostheses/singularity_prosthesis.h"

std::string karamay_engine::_engine_root_dir;

bool karamay_engine::initialize() noexcept
{
	std::cout << "karamay engine is initializing." << std::endl;

	_lvm = std::make_unique<lua_api::lua_vm>();
	_pvm = std::make_unique<python_api::python_vm>();
	_renderer_dispatcher = std::make_unique<gl_renderer_dispatcher>();
	_network_dispatcher = std::make_unique<network_dispatcher>();
	
	if (!_lvm || !_pvm || !_renderer_dispatcher || !_network_dispatcher)
	{
		std::cerr << "karamay engine initialization failed." << std::endl;
		return false;
	}

	// run sequence
	if (!_renderer_dispatcher->initialize() || 
		!_lvm->initialize() || !_pvm->initialize() || 
		!_network_dispatcher->initialize())
	{
		std::cerr << "karamay engine initialization failed." << std::endl;
		return false;
	}

	std::cout << "karamay engine has successfully initialized." << std::endl;
	return true;
}

void karamay_engine::run() noexcept
{
	std::cout << "karamay engine is running." << std::endl;

	// renderer dispatcher thread
	_renderer_dispatcher_thread = std::move(std::thread([&]() {
		_renderer_dispatcher->run(); 
		}
	));
	// network dispatcher thread
	_network_dispatcher_thread = std::move(std::thread([&]() {
		_network_dispatcher->run(); 
		}
	));
	// lvm thread
	_lvm_thread = std::move(std::thread([&]() {
		_lvm->run(); 
		}
	));
	// pvm thread
	_pvm_thread = std::move(std::thread([&]() { 
		_pvm->run(); 
		}
	));

	std::thread _commandlet([&]() {
		std::string _com;
		while (true)
		{
			std::cout << "karamay engine >> : ";
			std::cin >> _com;
			std::cout << "command {" << _com << "} done." << std::endl;
		}
		}
	);

	auto _world = std::make_unique<world>();
	
	for (uint64 _index = 0; _index < 1000000; ++_index)
	{
		_world->create<avatar>(std::format("{}", _index));
	}
	std::vector<avatar*> _avatars;
	_world->invoke_avatars_all(_avatars);

	float _delta_time = 0.0f;
	while (!_should_exit)
	{
		auto _start_point = std::chrono::steady_clock::now();
		_world->tick(_delta_time);
		auto _end_point = std::chrono::steady_clock::now();
		_delta_time = std::chrono::duration_cast<std::chrono::seconds>(_end_point - _start_point).count();
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
