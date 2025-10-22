module ;

#include <iostream>
#include <vector>

module clumsy3d;

import :component;
import :ui_binder;
import :entity_manager;

import clumsy.core;
import clumsy.event_driver;
import clumsy.render;
import clumsy.ui;

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

			m_ui_manager.init(m_event_driver.get_window_ptr());
				
		}

		void run()
		{
			m_event_driver.run_event_loop();
		}

	private:
		void update(double x, double y)
		{

			m_renderer.clear_screen();

			m_ui_manager.clear();
			ui_binder::apply(m_ui_manager, m_entity_system);
			m_ui_manager.update();

			float identity[]
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
						m_renderer.add_triangles(&pos[0](0), &tri[0](0), pos.size(), tri.size(), identity);
					}
				);

			auto obj = m_entity_system.get_entities<component::selected_entities>();
			auto selected = m_entity_system.get_component<component::selected_entities>(obj.back());
			for (auto id : selected)
			{
				if (m_entity_system.contains<component::position_buffer, component::triangle_buffer>(id))
				{
					const auto& pos = m_entity_system.get_component<component::position_buffer>(id);
					const auto& tri = m_entity_system.get_component<component::triangle_buffer>(id);
					m_renderer.add_triangles(&pos[0](0), &tri[0](0), pos.size(), tri.size(), identity, { 0,0,1 });
				}
			}

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
		event_driver m_event_driver;
		renderer m_renderer;
		ui_manager m_ui_manager;

	private:
		template<typename T> struct get_type { using type = T::type; };
		using component_list = extract_member_type_list_t<component>;
		entity_manager<component_list, get_type> m_entity_system;
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
