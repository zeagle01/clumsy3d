
module;

#include <iostream>
#include <string>
#include <vector>

module clumsy3d:ui_binder;

import :input_table;
import :invoke_update_function;

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

		}

	private:
		struct bind_ui
		{
			template<is_in_list<input_table_type_list> connect, typename entity_system>
			static void apply(ui_manager& p_ui_manager, entity_system& p_entity_system)
			{

			//	auto out_entities = invoke_slot<connect::out, connect::in>::get_output_entities<connect::index_map >(p_entity_system);

			//	if (!out_entities)
			//	{
			//		return;
			//	}

				std::string name = get_type_name<connect>();
				using ui_value_type = connect::ui::type;
				p_ui_manager.add_ui<connect::ui>
				(
					name.c_str(),
					connect::ui_param,
					[&](ui_value_type v)
					{
						invoke_update_function<typename connect::out, typename connect::in, typename connect::index_map, entity_system>::apply<connect::func>(p_entity_system, v);

					}
				);
			}

		};

	};

}