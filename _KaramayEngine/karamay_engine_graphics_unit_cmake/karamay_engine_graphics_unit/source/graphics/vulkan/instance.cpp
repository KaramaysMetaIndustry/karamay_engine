#include "instance.h"

instance::instance() : vulkan_object()
{
}

instance::~instance()
{
	deallocate();
}

bool instance::allocate() noexcept
{
	auto _window = new glfw_window();
	_window->load_context();

	const char** _glfw_extensions = nullptr;
	uint32 _extension_count = 0;
	_glfw_extensions = glfwGetRequiredInstanceExtensions(&_extension_count);

	std::vector<const char*> layers;
#if defined(_DEBUG)
	layers.push_back("VK_LAYER_KHRONOS_validation");
#endif

	VkApplicationInfo _app_info{};
	_app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	_app_info.pApplicationName = "karamay engine vulkan graphics";
	_app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	_app_info.pEngineName = "karamay engine";
	_app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	_app_info.apiVersion = VK_API_VERSION_1_0; //VK_API_VERSION_1_2

	VkInstanceCreateInfo _create_info{};
	_create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	_create_info.pApplicationInfo = &_app_info;
	_create_info.enabledExtensionCount = _extension_count;
	_create_info.ppEnabledExtensionNames = _glfw_extensions;
	_create_info.enabledLayerCount = static_cast<uint32>(layers.size());
	_create_info.ppEnabledLayerNames = layers.data();

	VkResult _ret = vkCreateInstance(&_create_info, nullptr, &_handle);
	if (_ret != VkResult::VK_SUCCESS)
	{
		return false;
	}

	// enumerate version
	vkEnumerateInstanceVersion(&_version);

	// enumerate physical devices
	uint32 _count = 0;
	vkEnumeratePhysicalDevices(_handle, &_count, nullptr);
	if (_count == 0) return false;
	std::vector<VkPhysicalDevice> _physical_device_handles;
	_physical_device_handles.resize(_count);
	vkEnumeratePhysicalDevices(_handle, &_count, _physical_device_handles.data());
	_physical_devices.reserve(_count);
	for (const auto _physical_device_handle : _physical_device_handles)
	{
		_physical_devices.push_back(std::make_unique<physical_device>(_physical_device_handle));
	}

	// enumerate extensions
	vkEnumerateInstanceExtensionProperties("", &_count, nullptr);
	//vkEnumerateInstanceExtensionProperties("", &_count, properties.data());

	// enumerate layers
	vkEnumerateInstanceLayerProperties(&_count, nullptr);
	_layers.resize(_count);
	vkEnumerateInstanceLayerProperties(&_count, _layers.data());

	return true;
}

void instance::deallocate() noexcept
{
	if (_handle)
	{
		vkDestroyInstance(_handle, nullptr);
		_handle = nullptr;
	}
}
