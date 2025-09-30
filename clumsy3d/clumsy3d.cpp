module ;

#include <iostream>
#include <vector>

module clumsy3d;

import clumsy.event_driver;

import clumsy.render;

namespace clumsy
{

	class app::imp
	{
	public:

		void init()
		{
			set_window_size(m_event_driver, 1920, 1080);

			set_update_fn(m_event_driver, &app::imp::update);

			init_renderer(m_event_driver.get_window_ptr(), m_event_driver.get_proc_address());

			create_triangles();
				
		}

		void run()
		{
			m_event_driver.run_event_loop();
		}

	private:
		void update(double x, double y)
		{
			m_renderer.clear_screen();

			float id[]
			{
				1,0,0,0,
				0,1,0,0,
				0,0,1,0,
				0,0,0,1,
			};

			m_renderer.add_triangles(m_pos.data(), m_tris.data(), 3, 1, id);
		}

	private:
		void set_window_size(event_driver& event_driver, int width, int height)
		{
			event_driver.init(width, height);
		}

		void set_update_fn(event_driver& event_driver, auto f)
		{
			event_driver.set_update_callback
			(
				[this,f](auto x, auto y)
				{
					(this->*f)( x, y);
				}
			);

		}

		void init_renderer(void* window, void* proc_address)
		{
			m_renderer.init(window, proc_address);
		}
	private:
		void create_triangles()
		{
			m_pos = 
			{
				0,0,0,
				1,0,0,
				1,1,0,
			};

			m_tris =
			{
				0,1,2
			};
		}

	private:
		event_driver m_event_driver;
		renderer m_renderer;

	private:
		std::vector<float>	m_pos;
		std::vector<int>	m_tris;

	};

	/////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////

	app::app() : m_imp(std::make_unique<imp>()) { }
	app::~app() = default;

	void app::run()
	{
		m_imp->init();
		m_imp->run();

	}
}
