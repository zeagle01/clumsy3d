
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


	template<typename T>
	struct implecte_sss;

	struct ui_binder
	{
		template<typename entity_system >
		static void apply(ui_manager& p_ui_manager, entity_system& p_entity_system )
		{

			clumsy::for_each_type<input_table_type_list>::template apply<bind_ui>(p_ui_manager, p_entity_system );

		}

	private:
		struct bind_ui
		{
			template<is_in_list<input_table_type_list> connect, typename entity_system >
			static void apply(ui_manager& p_ui_manager, entity_system& p_entity_system )
			{

				std::string name = get_type_name<connect>();
				using ui_value_type = connect::ui::type;
				if constexpr (std::is_same_v<ui_value_type, empty>)
				{
					auto dummy = empty{};
					auto ui = ui_factory::create<connect::ui>(name, connect::ui_param, dummy);
					invoke_update_function<typename connect::out, typename connect::in, typename connect::index_map, entity_system >::apply<connect::func>(p_entity_system, ui);
				}
				else
				{

					auto rng = get_ui_bind_variable<typename connect::index_map, typename connect::out>::get_out_range(p_entity_system);
					if (rng.empty())
					{
						return;
					}

					auto* v = get_ui_bind_variable<typename connect::index_map, typename connect::out>::apply(p_entity_system, rng);
					if (!v)
					{
						return;
					}

					auto ui = ui_factory::create<connect::ui>(name, connect::ui_param, *v);
					invoke_update_function<typename connect::out, typename connect::in, typename connect::index_map, entity_system >::template apply<connect::func>(p_entity_system, ui);
				}
			}

		private:
			template<typename cpn_range, typename in_list>
			struct get_ui_bind_variable;

			template<typename out_rng, typename in_rng, typename first_cpn,typename ...cpn>
			struct get_ui_bind_variable<entity_mapper::all_to_all<out_rng, in_rng>, type_list<first_cpn,cpn...>>
			{
				using out_list = type_list<cpn...>;
				template<typename entity_system>
				static typename first_cpn::type* apply(entity_system& p_entity_system, const auto& rng)
				{
					auto id = rng.back();
					if (p_entity_system.contains<first_cpn>(id))
					{
						return &p_entity_system.get_component<first_cpn>(id);
					}
					else
					{
						return nullptr;
					}
				}

				template<typename entity_system>
				static auto get_out_range(entity_system& p_entity_system)
				{
					return clumsy::get_entity_range<out_rng, out_list>::apply(p_entity_system);
				}
			};

		};

	};

}