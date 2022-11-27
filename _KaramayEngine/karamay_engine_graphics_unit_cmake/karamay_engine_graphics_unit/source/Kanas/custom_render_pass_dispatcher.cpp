#include "custom_render_pass_dispatcher.h"

void kanas::custom_render_pass_dispatcher::create_render_pass(const nlohmann::json& rpd)
{
	if (!rpd.is_object())
	{
		return;
	}

	auto _it = rpd.find("name");

	if (_it == rpd.cend())
	{
		return;
	}

	const std::string _render_pass_name = _it->value("name", "null");

	_it = rpd.find("subpasses");

	if (_it == rpd.cend())
	{
		return;
	}

	


	if (const auto _new_render_pass = device.create_render_pass())
	{

	}
}
