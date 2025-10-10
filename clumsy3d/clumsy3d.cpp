module ;

#include <iostream>
#include <vector>

module clumsy3d;

import :component;

import clumsy.core;
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

			m_entity_system.for_each<component::position_buffer, component::triangle_buffer>
				(
					[&,this](const auto& pos, const auto& tri)
					{
						m_renderer.add_triangles(&pos[0](0), &tri[0](0), pos.size(), tri.size(), id);
					}
				);

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

			auto my_triangle = m_entity_system.add_entity();

			m_entity_system.add_component<component::position_buffer>
			(
				my_triangle,
				{
					{0,0,0},
					{1,0,0},
					{1,1,0},
				}
			);

			m_entity_system.add_component<component::triangle_buffer>
			(
				my_triangle,
				{
					{0,1,2},
				}
			);
		}

	private:
		event_driver m_event_driver;
		renderer m_renderer;

	private:
		template<typename T>
		struct get_type { using type = T::type; };

		using component_list = extract_member_type_list_t<component>;

		entity_system<component_list, get_type> m_entity_system;
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
