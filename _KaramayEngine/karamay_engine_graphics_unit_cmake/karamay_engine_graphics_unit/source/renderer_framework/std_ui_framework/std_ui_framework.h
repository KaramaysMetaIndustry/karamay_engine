#ifndef STD_UI_FRAMEWORK
#define STD_UI_FRAMEWORK
#include "graphics/gl_renderer_framework.h"

namespace std_ui_framework
{
	class widget
	{

	};

	class framework final : public gl_renderer_framework
	{
	public:
		framework() = default;

	public:

		bool initialize() noexcept override;

		void tick(float delta_time) noexcept override;

		bool set_state(bool active) noexcept override;

		bool is_active() const noexcept override;

	private:

		std::vector<gl_renderer*> _renderers;

	public:

		void add(widget* wd) {}

	};
}



#endif