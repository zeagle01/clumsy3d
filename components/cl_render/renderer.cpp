
module;

#include "glad/glad.h"

#include <iostream>

module clumsy.render;

import :shader;

namespace clumsy
{

	class renderer::imp
	{
	public:
		void set_window(void* window)
		{
			m_window = window;
		}

	private:
		void* m_window;
	private:
		shader m_shader;
	};


	renderer::renderer() : m_imp(std::make_unique<imp>()) { }
	renderer::~renderer() = default;

	void renderer::set_window(void* window)
	{
		m_imp->set_window(window);
	}

	void renderer::load_glad(void* proc_addr)
	{
		if (!gladLoadGLLoader((GLADloadproc)proc_addr))
		{
			printf("glad load failed\n");
		}
		else
		{
			printf("glad load succend\n");
		}
		printf("gl version %s\n", glGetString(GL_VERSION));

	}

}
