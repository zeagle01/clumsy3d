
module;

#include <iostream>
#include <string>

module clumsy3d:ui_binder;

import :input_table;
import :entity_relation;
import :component;

import clumsy.ui;

import clumsy.core;

namespace clumsy
{
	struct ui_binder
	{
		template<typename entity_system>
		static void apply(ui_manager& p_ui_manager, entity_system& p_entity_system)
		{

			clumsy::for_each_type<input_table_type_list>::template apply<bind_ui>(p_ui_manager, p_entity_system);
			p_ui_manager.add_ui<ui::button>("my_button", empty_v, [](empty) { printf(" hello , i'm here!\n"); });
			//m_ui_manager.add_ui<ui::check_box>("my_check_box", m_my_bool);
			//m_ui_manager.add_ui<ui::slider_float>("my_float0", m_my_float0, 0.f, 100.f);
			//m_ui_manager.add_ui<ui::input_float>("my_float1", m_my_float1);
			//m_ui_manager.add_ui<ui::input_int>("my_int", m_my_int);

		}

	private:
		struct bind_ui
		{
			template<is_in_list<input_table_type_list> connect, typename entity_system>
			static void apply(ui_manager& p_ui_manager, entity_system& p_entity_system)
			{
				std::string name = typeid(connect).name();
				using ui_value_type = connect::ui::type;
				p_ui_manager.add_ui<connect::ui>
				(
					name.c_str(),
					connect::ui_param,
					[&](ui_value_type v)
					{
						//std::cout << " value " << v << typeid(connect::func).name() << std::endl;
						//connect::func::apply(p_entity_system.get v);
						invoke_slot<connect::out>::apply<connect::func>(v, p_entity_system);
					}
				);
				using aa = new_entity<int>;
			}
		private:

			template<typename tl>
			struct invoke_slot;

			template<is_in_list<component_list> ... cpn >
			struct invoke_slot< new_entity<cpn...> >
			{
				template<typename F, typename T, typename entity_system>
				static void apply(T v, entity_system& p_entity_system)
				{
					auto id = p_entity_system.add_entity();
					((p_entity_system.add_component<cpn>(id)), ...);

					F::apply(p_entity_system.get_component<cpn>(id)..., v);
				}
			};

			template<is_in_list<component_list> ... cpn >
			struct invoke_slot< selected_entity<cpn...> >
			{
				template<typename F, typename T, typename entity_system>
				static void apply(T v, entity_system& p_entity_system)
				{
					F::apply(p_entity_system.get_component<cpn>(0)..., v);
				}
			};

		};

	};

}