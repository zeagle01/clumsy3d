module;

#include <utility>
#include <concepts>
#include <vector>

module clumsy3d:invoke_update_function;

import :common_structs;

import clumsy.core;

namespace clumsy
{

	template<typename index_map, typename in_list>
	struct get_entity_range;

	template<template<typename> typename tl, typename ...in_cpn>
	struct get_entity_range<typename entity_range::all, tl<in_cpn...>>
	{
		template<typename entity_system>
		static std::vector<uint64_t> apply(entity_system& p_entity_system)
		{
			return p_entity_system.template get_entities<in_cpn...>();
		}
	};

	template<typename in_list>
	struct get_entity_range<typename entity_range::none, in_list>
	{
		template<typename entity_system>
		static std::vector<uint64_t> apply(entity_system& p_entity_system)
		{
			return {};
		}
	};

	template<typename in_list>
	struct get_entity_range<typename entity_range::create, in_list>
	{
		template<typename entity_system>
		static std::vector<uint64_t> apply(entity_system& p_entity_system)
		{
			return {p_entity_system.add_entity()};
		}
	};

	template<typename cpn, typename ...in_cpn>
	struct get_entity_range<typename entity_range::value_of<cpn>, type_list<in_cpn...>>
	{
		template<typename entity_system>
		static auto apply(entity_system& p_entity_system)
		{
			auto obj = p_entity_system.template get_entities<cpn>();
			auto id = obj.back(); //assume singleton
			auto entity_range = p_entity_system.template get_component<cpn>(id);
			return entity_range;
		}
	};

	//////////////////////

	template<typename id_map>
	struct index_mapper;

	template<>
	struct index_mapper<index_map::identity>
	{
		static directed_edge apply(int i, const std::vector<uint64_t>& ids)
		{
			return { ids[i], ids[i] };
		}
	};

	template<>
	struct index_mapper<index_map::directed_edge>
	{
		static directed_edge apply(int i, const std::vector<directed_edge>& ids)
		{
			return ids[i];
		}
	};

	//////////////////////


	template<typename out_list, typename in_list, typename index_map, typename entity_system>
	struct invoke_update_function;

	template< typename in_list,  typename entity_system, typename index_map, typename ...out_cpn>
	struct invoke_update_function<type_list<out_cpn...>, in_list, index_map, entity_system>
	{
		using out_list = type_list<out_cpn...>;

		template<typename F, typename ...P >
		static void apply(entity_system& p_entity_system, P&&...p)
		{
			with_in_out_list < in_list > ::template apply<F>(p_entity_system, std::forward<P>(p)...);
		}
	private:
		template<typename in_list_t>
		struct with_in_out_list;

		template< typename ...in_cpn>
		struct with_in_out_list<type_list<in_cpn...>>
		{
			template<typename F, typename ...P >
			static void apply(entity_system& p_entity_system, P&&...p)
			{
				imp<index_map>::template apply<F>(p_entity_system, std::forward<P>(p)...);
			}

		private:
			template<typename cpn>
			static auto& create_or_get_value(uint64_t id, entity_system& p_entity_system)
			{
				if (!p_entity_system.contains<cpn>(id))
				{
					p_entity_system.add_component<cpn>(id);
				}
				return p_entity_system.get_component<cpn>(id);
			}

		private:
			template<typename index_map_t>
			struct imp;

			template<typename out_range, typename in_range>
			struct imp<entity_mapper::all_to_one<out_range,in_range>>
			{
				template<typename F, typename ...P >
				static void apply(entity_system& p_entity_system, P&&...p)
				{
					auto in_entities = get_entity_range<in_range, in_list>::apply(p_entity_system);
					auto out_entities = get_entity_range<out_range, out_list>::apply(p_entity_system);

					for (auto out_id : out_entities)
					{
						F::apply(   create_or_get_value<out_cpn>(out_id, p_entity_system)... , get_values<in_cpn>(in_entities, p_entity_system)..., std::forward<P>(p)...);
					}

				}
			private:
				template<typename cpn>
				static auto get_values(const std::vector<uint64_t >& ids, entity_system& p_entity_system)
				{
					std::vector<cpn::type>  ret;
					for (auto id : ids)
					{
						ret.push_back(p_entity_system.get_component<cpn>(id));
					}
					return ret;
				}


			};

			template< typename id_map, typename in_range>
			struct imp<entity_mapper::one_to_one<id_map, in_range>>
			{
				template<typename F, typename ...P >
				static void apply(entity_system& p_entity_system, P&&...p)
				{
					auto in_entities = get_entity_range<in_range, in_list>::apply(p_entity_system);

					for (int i = 0; i < in_entities.size(); i++)
					{
						auto d_edge = index_mapper<id_map>::apply(i, in_entities);
						auto in_id = d_edge.sender;
						auto out_id = d_edge.receiver;

						F::apply( create_or_get_value<out_cpn>(out_id, p_entity_system)..., p_entity_system.get_component<in_cpn>(in_id)...,std::forward<P>(p)...);
					}
				}

			};

			template<  typename in_range>
			struct imp<entity_mapper::erase< in_range>>
			{
				template<typename F, typename ...P >
				static void apply(entity_system& p_entity_system, P&&...p)
				{
					auto in_entities = get_entity_range<in_range, in_list>::apply(p_entity_system);

					for (auto id : in_entities)
					{
						p_entity_system.remove_entity(id);
					}
				}

			};
		};

	};


}