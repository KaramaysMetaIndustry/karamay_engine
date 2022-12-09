#pragma once

#include <memory>
#include <string>
#include <iostream>

struct widget_lib
{
	static std::shared_ptr<class widget> create_widget();

	static void kanas_log(const std::string& msg)
	{
		std::cout << "[kanas - lua] : " << msg << std::endl;
	}

};

namespace kanas
{
	static void log(const std::string& msg)
	{
		std::cout << "[kanas - lua] : " << msg << std::endl;
	}
}