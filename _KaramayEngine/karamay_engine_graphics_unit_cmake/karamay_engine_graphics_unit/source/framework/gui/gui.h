#ifndef GUI_H
#define GUI_H
#include "public/stl.h"
#include "public/glm.h"

namespace karamay_gui
{
	struct transform_2d
	{
		glm::vec2 location;
		glm::vec2 rotation;
		glm::vec2 scale;
	};

	class widget
	{
		widget() = default;
		widget(const widget&) = delete;
		widget& operator=(const widget&) = delete;

		virtual ~widget() = default;

	public:

		glm::vec2 size;

		transform_2d transform;

	public:

		std::shared_ptr<widget> parent;
		std::list<std::shared_ptr<widget>> children;

	};

	class container : public widget
	{

	};

	class button : public widget
	{

	};

}




#endif