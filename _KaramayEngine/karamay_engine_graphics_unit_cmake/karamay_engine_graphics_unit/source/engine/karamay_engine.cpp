#include "karamay_engine.h"
#include "clipp/clipp.h"

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

	auto _tex_1d_array = std::make_shared<gl_texture_1d_array>();
	_tex_1d_array->build_mipmaps();
	_tex_1d_array->fetch(0, 0, 0, 1024, gl_texture_pixel_format::BGR, gl_texture_pixel_type::FLOAT, 32, nullptr);
	_tex_1d_array->fill(0, 0, 512, 512, gl_texture_pixel_format::BGR, gl_texture_pixel_type::FLOAT, nullptr);
	_tex_1d_array->set_border_color(glm::vec4(0.1f));

	// renderer dispatcher thread
	_renderer_dispatcher_thread = std::thread([&]() {
		_renderer_dispatcher->run(); 
		}
	);
	// network dispatcher thread
	_network_dispatcher_thread = std::thread([&]() { 
		_network_dispatcher->run(); 
		}
	);
	// lvm thread
	_lvm_thread = std::thread([&]() {
		_lvm->run(); 
		}
	);
	// pvm thread
	_pvm_thread = std::thread([&]() { 
		_pvm->run(); 
		}
	);

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

	uint64 _count = 0;
	while (!_should_exit)
	{
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
