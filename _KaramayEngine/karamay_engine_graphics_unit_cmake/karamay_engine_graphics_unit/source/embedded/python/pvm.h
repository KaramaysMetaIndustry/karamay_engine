#ifndef PVM_H
#define PVM_H

#include "public/stl.h"

namespace python_api
{
	namespace basic
	{

	}


	class python_vm
	{
	public:

		bool initialize()  noexcept
		{
			return true;
		}

		void run() noexcept;

	public:

		void notify_to_exit() noexcept
		{
			_should_exit = true;
		}

	private:

		std::atomic_bool _should_exit = false;

	};

}


#endif