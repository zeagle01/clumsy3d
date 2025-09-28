module;

#include "GLFW/glfw3.h"
#include <iostream>

module event_driver;

namespace clumsy
{

	class event_driver::imp
	{
	public:
		void* get_window_ptr()
		{
			return m_window;
		}

		void set_update_callback(std::function<void(double, double)> fn)
		{
			m_update_fn = fn;
		}

	public:
		void run_event_loop()
		{
			while (!glfwWindowShouldClose((GLFWwindow*)m_window))
			{
				glfwPollEvents();

				double cx;
				double cy;

				glfwGetCursorPos(m_window, &cx, &cy);

				m_update_fn(cx, cy);

				glfwMakeContextCurrent(m_window); //in case for docking gui

				glfwSwapBuffers(m_window);
			}
		}

		void init(int width, int height)
		{
			auto status = glfwInit();
			if (status == GLFW_TRUE)
			{
				printf("glfw init succeed! \n");
			}
			else
			{
				printf("glfw init error! \n");
			}

			GLFWwindow* window;
			window = glfwCreateWindow(width, height, "gl window", nullptr, nullptr);

			if (window)
			{
				printf("window  is created\n" );
			}
			else
			{
				printf("window can't be created\n");
			}

			glfwMakeContextCurrent(window);

			glfwSwapInterval(1);

			m_window = window;

			//glfwSetWindowUserPointer(m_window, &m_dispatchor);

			//register_GLFW_event_callback();
		}

	private:
		GLFWwindow* m_window;
		std::function<void(double,double)> m_update_fn;
	};


	/////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////

	event_driver::event_driver()
		:m_imp(std::make_unique<imp>())
	{
	}

	event_driver::~event_driver() = default;

	void event_driver::init(int width, int height)
	{
		m_imp->init(width, height);
	}

	void event_driver::run_event_loop()
	{
		m_imp->run_event_loop();
	}

	void event_driver::set_update_callback(std::function<void(double, double)> fn)
	{
		m_imp->set_update_callback(fn);

	}

	void* event_driver::get_proc_address()
	{
		return &glfwGetProcAddress;
	}

	void* event_driver::get_window_ptr()
	{
		return m_imp->get_window_ptr();
	}

}
