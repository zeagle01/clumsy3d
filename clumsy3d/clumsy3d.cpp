module ;

#include <iostream>
#include <vector>

module clumsy3d;

import :component;
import :ui_binder;
import :entity_manager;
import :commands;
import :cmd_executor;
import :command_manager;

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

			//m_ui_manager.clear();
			command_manager<cm_access::full, component_list, type_getter> full_entities(m_entity_system, m_commands);

			m_ui_manager.update(
				[&]()
				{
					ui_binder::apply(m_ui_manager, full_entities );
				}
			);

			command_manager<cm_access::cmd_only, component_list, type_getter> cmd_entities(m_entity_system, m_commands);
			cmd_executor::apply(cmd_entities );

			m_commands.clear();

			//ui_binder::apply(m_ui_manager, m_entity_system);
			//m_ui_manager.update();

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
		entity_manager<component_list, type_getter> m_entity_system;
		commands<component_list,type_getter>		 m_commands;
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
