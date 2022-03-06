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

	const char** glfwExtensions;
	uint32 extension_count = 0;
	glfwExtensions = glfwGetRequiredInstanceExtensions(&extension_count);

	std::vector<const char*> layers;
#if defined(_DEBUG)
	layers.push_back("VK_LAYER_KHRONOS_validation");
#endif

	VkApplicationInfo _app_info{};
	_app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	_app_info.pApplicationName = "Hello Triangle";
	_app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	_app_info.pEngineName = "No Engine";
	_app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	_app_info.apiVersion = VK_API_VERSION_1_0; //VK_API_VERSION_1_2

	VkInstanceCreateInfo _create_info{};
	_create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	_create_info.pApplicationInfo = &_app_info;
	_create_info.enabledExtensionCount = extension_count;
	_create_info.ppEnabledExtensionNames = glfwExtensions;
	_create_info.enabledLayerCount = layers.size();
	_create_info.ppEnabledLayerNames = layers.data();

	VkResult _ret = vkCreateInstance(&_create_info, nullptr, &_handle);
	if (_ret != VkResult::VK_SUCCESS)
	{
		return false;
	}
	return true;
}

void instance::deallocate() noexcept
{
	vkDestroyInstance(_handle, nullptr);
}

uint32 instance::enumerate_version() noexcept
{
	uint32 _version = 0;
	vkEnumerateInstanceVersion(&_version);
	return _version;
}

void instance::enumerate_physical_devices(std::vector<physical_device*>& physical_devices) noexcept
{
	uint32 _count = 0;
	vkEnumeratePhysicalDevices(_handle, &_count, nullptr);
	std::vector<VkPhysicalDevice> _pds(_count);
	physical_devices.reserve(_count);
	vkEnumeratePhysicalDevices(_handle, &_count, _pds.data());

	for (auto _pd : _pds)
	{
		physical_devices.push_back(new physical_device(_pd));
	}
}

void instance::enumerate_physical_device_groups(std::vector<VkPhysicalDeviceGroupProperties>& properties) noexcept
{
	uint32 _count = 0;
	vkEnumeratePhysicalDeviceGroups(_handle, &_count, nullptr);
	if (_count == 0) return;
	properties.resize(_count);
	vkEnumeratePhysicalDeviceGroups(_handle, &_count, properties.data());
}

void instance::enumerate_extension_properties(const std::string& player_name, std::vector<VkExtensionProperties>& properties) noexcept
{
	uint32 _count = 0;
	vkEnumerateInstanceExtensionProperties(player_name.c_str(), &_count, nullptr);
	if (_count == 0) return;
	properties.resize(_count);
	vkEnumerateInstanceExtensionProperties(player_name.c_str(), &_count, properties.data());
}

void instance::enumerate_layer_properties(std::vector<VkLayerProperties>& properties) noexcept
{
	uint32 _count = 0;
	vkEnumerateInstanceLayerProperties(&_count, nullptr);
	if (_count == 0) return;
	properties.resize(_count);
	vkEnumerateInstanceLayerProperties(&_count, properties.data());
}
