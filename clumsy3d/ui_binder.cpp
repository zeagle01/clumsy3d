
module;

#include <iostream>
#include <string>
#include <vector>

module clumsy3d:ui_binder;

import :input_table;
import :entity_relation;
import :entity_relation_functions;
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
			auto obj = p_entity_system.add_entity();
			p_entity_system.add_component<component::selected_entities>(obj, std::vector<uint64_t>());

			obj = p_entity_system.add_entity();
			p_entity_system.add_component<component::sync_move_pairs>(obj, std::vector<directed_edge>());

			clumsy::for_each_type<input_table_type_list>::template apply<bind_ui>(p_ui_manager, p_entity_system);
			//p_ui_manager.add_ui<ui::button>("my_button", empty_v, [](empty) { printf(" hello , i'm here!\n"); });
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

				auto out_entities = invoke_slot<connect::out, connect::in>::get_output_entities<connect::index_map >(p_entity_system);

				if (!out_entities)
				{
					return;
				}

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
						invoke_slot<connect::out, connect::in>::apply<connect::func, connect::index_map >(v, p_entity_system);
					}
				);
			}
		private:

			template<typename out_list ,typename in_list>
			struct invoke_slot;

			template<
				template <typename ...> typename out_list, typename in_list, typename ...out_cpn
			>
			struct invoke_slot<out_list<out_cpn...>, in_list>
			{
				template<typename F, typename index_map, typename T, typename entity_system>
				static void apply(T v, entity_system& p_entity_system)
				{
					imp<in_list>::apply<F >(index_map{}, v, p_entity_system);
				}

				template<typename index_map, typename entity_system>
				static bool get_output_entities(entity_system& p_entity_system)
				{
					return imp<in_list>::get_output_entities(index_map{}, p_entity_system);
				}

			private:
				template<typename tl>
				struct imp;

				template< template <typename ...> typename in_list, typename ...in_cpn >
				struct imp<in_list<in_cpn...>>
				{
					/////////////////// create one ////////////////////
					template< typename entity_system>
					static bool get_output_entities(index_map::create_one, entity_system& p_entity_system)
					{
						return true;
					}
					template<typename F, typename T, typename entity_system>
					static void apply(index_map::create_one, T v, entity_system& p_entity_system)
					{
						auto new_entity = p_entity_system.add_entity();

						p_entity_system.add_component<cpn::id>(new_entity, new_entity);

						((p_entity_system.add_component<out_cpn>(new_entity)), ...);

						auto in_entities = p_entity_system.template get_entities<in_cpn...>();

						F::apply(p_entity_system.get_component<out_cpn>(new_entity)..., get_value<in_cpn>::apply(in_entities, p_entity_system)..., v);

					}

					/////////////////// all to one ////////////////////
					template< typename entity_system>
					static bool get_output_entities(index_map::all_to_one, entity_system& p_entity_system)
					{
						auto out_entities = p_entity_system.template get_entities<out_cpn...>();
						return out_entities.size() > 0;
					}
					template<typename F, typename T, typename entity_system>
					static void apply(index_map::all_to_one, T v, entity_system& p_entity_system)
					{

						auto in_entities = p_entity_system.template get_entities<in_cpn...>();
						auto out_entities = p_entity_system.template get_entities<out_cpn...>();

						for (auto out_id : out_entities)
						{
							F::apply(p_entity_system.get_component<out_cpn>(out_id)..., get_value<in_cpn>::apply(in_entities, p_entity_system)..., v);
						}
					}

					/////////////////// identity ////////////////////
					template< typename entity_system>
					static bool get_output_entities(index_map::identity, entity_system& p_entity_system)
					{
						auto out_entities = p_entity_system.template get_entities<out_cpn...>();
						return out_entities.size() > 0;
					}
					template<typename F, typename T, typename entity_system>
					static void apply(index_map::identity, T v, entity_system& p_entity_system)
					{
						auto out_entities = p_entity_system.template get_entities<out_cpn...>();

						for (auto id : out_entities)
						{
							F::apply(p_entity_system.get_component<out_cpn>(id)..., p_entity_system.get_component<in_cpn>(id)..., v);
						}
					}

					/////////////////// directed edges ////////////////////
					template< typename edge, typename entity_system>
					static bool get_output_entities(index_map::one_to_one<edge>, entity_system& p_entity_system)
					{
						auto objs = p_entity_system.template get_entities<edge>();
						auto edges = p_entity_system.template get_component<edge>(objs.back());
						return edges.size() > 0;
					}
					template<typename F, typename edge, typename T, typename entity_system>
					static void apply(index_map::one_to_one<edge>, T v, entity_system& p_entity_system)
					{
						auto objs = p_entity_system.template get_entities<edge>();
						auto edges = p_entity_system.template get_component<edge>(objs.back());

						for (auto e : edges)
						{
							F::apply(p_entity_system.get_component<out_cpn>(e.receiver)..., p_entity_system.get_component<in_cpn>(e.sender)..., v);
						}
					}

				};


				template<typename cpn>
				struct get_value
				{
					template<typename entity_system>
					static auto apply(const std::vector<uint64_t >& ids, entity_system& p_entity_system)
					{
						std::vector<cpn::type>  ret;
						for (auto id : ids)
						{
							ret.push_back(p_entity_system.get_component<cpn>(id));
						}
						return ret;
					}
				};

			};

			//template<is_in_list<component_list> ... cpn >
			//struct invoke_slot< new_entity<cpn...> >
			//{
			//	template<typename F, typename T, typename entity_system>
			//	static void apply(T v, entity_system& p_entity_system)
			//	{
			//		auto id = p_entity_system.add_entity();
			//		((p_entity_system.add_component<cpn>(id)), ...);

			//		F::apply(p_entity_system.get_component<cpn>(id)..., v);
			//	}
			//};

			//template<is_in_list<component_list> ... cpn >
			//struct invoke_slot< selected_entity<cpn...> >
			//{
			//	template<typename F, typename T, typename entity_system>
			//	static void apply(T v, entity_system& p_entity_system)
			//	{
			//		//auto out_entities=
			//		F::apply(p_entity_system.get_component<cpn>(0)..., v);
			//	}
			//};

		};

	};

}