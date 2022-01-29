#ifndef PVM_H
#define PVM_H

#include "public/stl.h"
#include "public/python.h"

namespace python_api
{
	namespace baisc
	{
		static void initialize()
		{
			Py_Initialize();
		}

		static bool is_initialized()
		{
			return Py_IsInitialized() == 1;
		}


	}



	class pvm
	{
	public:
		pvm() = default;

		void load()
		{
			Py_Initialize();
			if (!Py_IsInitialized())
			{
				return;
			}
			PyRun_SimpleString("import sys");
			PyRun_SimpleString("sys.path.append('./')");

			PyRun_SimpleString("print('Hello World!')");


			PyObject* pModule = NULL;
			PyObject* pFunc1 = NULL;
			PyObject* pFunc2 = NULL;
			PyObject* pFunc3 = NULL;
			pModule = PyImport_ImportModule("G:\\PrivateRepos\\Karamays\\_KaramayEngine\\karamay_engine_graphics_unit_cmake\\karamay_engine_graphics_unit\\scripts\\python\\test.py");
			if (pModule == NULL)
			{
				std::cout << "not find" << std::endl;
				return;
			}

			pFunc1 = PyObject_GetAttrString(pModule, "zip_file");
			PyEval_CallObject(pFunc1, NULL);
			
			pFunc2 = PyObject_GetAttrString(pModule, "zip_file");
			std::string readpath = R"(C:\Users\admin\Desktop\TestData)";
			std::string writepath = R"(C:\Users\admin\Desktop\TestData.zip)";
			PyObject* args = Py_BuildValue("ss", readpath.c_str(), writepath.c_str());
			PyObject_CallObject(pFunc2, args);

			pFunc3 = PyObject_GetAttrString(pModule, "_getValue");
			PyObject* args2 = Py_BuildValue("ii", 28, 103);
			PyObject* pRet = PyObject_CallObject(pFunc3, args2);
			int res = 0;
			PyArg_Parse(pRet, "i", &res);
			std::cout << "res:" << res << std::endl;

			Py_Finalize();
		}

	};

};




#endif