module;

#include <stdint.h>
#include <vector>

module clumsy3d:update_functions_meta;

import :common_structs;
import :entity_manager;
import :command_manager;

namespace clumsy
{

	struct entity_range
	{
		struct all
		{
			template< typename ...cpn, typename entity_system>
			static std::vector<uint64_t> apply(entity_system& p_entity_system)
			{
				return p_entity_system.get_entities<cpn...>();
			}

		};

		template<typename cpn>
		struct edge_from
		{
			template< typename ... in_cpn, typename entity_system>
			static std::vector<uint64_t> apply(entity_system& p_entity_system)
			{
				auto obj = p_entity_system.template get_entities<cpn>();
				auto id = obj.back(); //TODO: assume singleton , make this safer !
				auto edges = p_entity_system.template get_component<cpn>(id);
				std::vector<uint64_t> ret;
				for (auto edge : edges)
				{
					auto id = edge.sender;
					if (p_entity_system.contains<in_cpn...>(id))
					{
						ret.push_back(id);
					}
				}
				return ret;
			}
		};

		template<typename cpn>
		struct edge_to
		{
			template< typename ... in_cpn, typename entity_system>
			static std::vector<uint64_t> apply(entity_system& p_entity_system)
			{
				auto obj = p_entity_system.template get_entities<cpn>();
				auto id = obj.back(); //TODO: assume singleton , make this safer !
				auto edges = p_entity_system.template get_component<cpn>(id);
				std::vector<uint64_t> ret;
				for (auto edge : edges)
				{
					auto id = edge.receiver;
					if (p_entity_system.contains<in_cpn...>(id))
					{
						ret.push_back(id);
					}
				}
				return ret;
			}
		};

		template<typename cpn>
		struct value_of
		{
			template< typename ... in_cpn, typename entity_system>
			static std::vector<uint64_t> apply(entity_system& p_entity_system)
			{
				auto obj = p_entity_system.template get_entities<cpn>();
				auto id = obj.back(); //TODO: assume singleton , make this safer !
				auto entity_range = p_entity_system.template get_component<cpn>(id);
				std::vector<uint64_t> ret;
				for (auto id : entity_range)
				{
					if (p_entity_system.contains<in_cpn...>(id))
					{
						ret.push_back(id);
					}
				}
				return ret;
			}
		};

		struct create_entity
		{

			template< typename ... in_cpn, typename entity_system>
			static std::vector<uint64_t> apply(const entity_system& p_entity_system)
			{
				return  { p_entity_system.next_entity() };
			}

		};

		struct none
		{
			template< typename ... in_cpn, typename entity_system>
			static std::vector<uint64_t> apply(const entity_system& p_entity_system)
			{
				return  {  };
			}
		};

		struct same_as_input
		{
			template< typename ... in_cpn, typename entity_system>
			static const std::vector<uint64_t>& apply(const entity_system& p_entity_system, const std::vector<uint64_t>& input_range)
			{
				return input_range;
			}

		};
	};


	struct erase_entity
	{
		template<typename entity_system>
		//static void apply(entity_system& p_entity_system,uint64_t ids)
		static void apply(entity_system& p_entity_system,uint64_t id)
		{
			//for (auto id : ids)
			{
				p_entity_system.remove_entity(id);
			}
		}

	};


	//struct create_component
	//{
	//	template<typename entity_system>
	//	static void apply(entity_system& p_entity_system)
	//	{

	//	}

	//};



}