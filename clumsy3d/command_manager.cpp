module;

#include "cl_core/config_define_helper.h"
#include <stdint.h>
#include <utility>

module clumsy3d:command_manager;

import clumsy.core;

import :commands;
import :entity_manager;


namespace clumsy
{

	struct cm_access
	{
		ENTRY(full);
		ENTRY(cmd_only);
	};

	using cm_access_polocy = extract_member_type_list_t<cm_access>;

	template
	<
		is_in_list<cm_access_polocy> acess_polocy,
		typename var_list,
		template <typename > typename type_getter 
	>
	class command_manager
	{
	public:
		using cmd_t = commands<var_list, type_getter>;
		using entity_system_t = entity_manager<var_list, type_getter>;
	public:
		command_manager(entity_system_t& es, cmd_t& cmd) :
			m_entity_system(es), m_commands(cmd)
		{
		}

		uint64_t add_entity()
		{
			return m_entity_system.add_entity();
		}

		void remove_entity(uint64_t id)
		{

			auto components_index = m_entity_system.get_component_keys(id);

			m_commands.add_cmds<cmd_type::erase>(id, components_index);

			return m_entity_system.remove_entity(id);
		}

		template<is_in_list<var_list> cpn>
		void add_component(uint64_t id, const type_getter<cpn>::type& value)
		{
			m_commands.add_cmd<cmd_type::modify, cpn>(id);
			return m_entity_system.add_component<cpn>(id, value);
		}

		template<is_in_list<var_list> cpn>
		void add_component(uint64_t id )
		{
			m_commands.add_cmd<cmd_type::modify, cpn>(id);
			return m_entity_system.add_component<cpn>(id);
		}


		template<is_in_list<var_list> cpn>
		auto& get_component_to_modify(uint64_t id)
		{
			m_commands.add_cmd<cmd_type::modify, cpn>(id);
			return m_entity_system.get_component<cpn>(id);
		}

	public:
		template<is_in_list<var_list> cpn>
		auto& get_component(uint64_t id)
		{
			return acessor<acess_polocy>::template get_component<cpn>(id, m_entity_system, m_commands);
		}

		template<is_in_list<var_list> cpn>
		const auto& get_component(uint64_t id) const
		{
			return acessor<acess_polocy>::template get_component<cpn>(id, m_entity_system, m_commands);
		}

		template<is_in_list<var_list> ... cpn>
		auto get_entities() const
		{
			return acessor<acess_polocy>::template get_entities<cpn...>(m_entity_system, m_commands);
		}

		template<is_in_list<var_list> ... cpn>
		bool contains(uint64_t id) const
		{
			return acessor<acess_polocy>::template contains<cpn...>(id, m_entity_system, m_commands);
;
		}

	private:
		template<typename polocy>
		struct  acessor;

		template<>
		struct  acessor<cm_access::full>
		{

			template<is_in_list<var_list> ...cpn, typename es_t, typename cmd_t>
			static auto get_entities(es_t&& es, cmd_t&& cmds)
			{
				return std::forward<es_t>(es).template get_entities<cpn...>();
			}

			template<is_in_list<var_list> ...cpn, typename es_t, typename cmd_t>
			static bool contains(uint64_t id, es_t& es, cmd_t& cmds)
			{
				return std::forward<es_t>(es).template contains<cpn...>(id);
			}

			template<is_in_list<var_list> cpn, typename es_t, typename cmd_t>
			static decltype(auto) get_component(uint64_t id, es_t& es, cmd_t& cmds)
			{
				return std::forward<es_t>(es).get_component<cpn>(id);
			}

		};

		template<>
		struct  acessor<cm_access::cmd_only>
		{

			template<is_in_list<var_list> ...cpn, typename es_t, typename cmd_t>
			static auto get_entities(es_t&& es, cmd_t&& cmds)
			{
				return std::forward<cmd_t>(cmds).template get_entities<cmd_type::modify, cpn...>();
			}

			template<is_in_list<var_list> ...cpn, typename es_t, typename cmd_t>
			static bool contains(uint64_t id, es_t& es, cmd_t& cmds)
			{
				return (std::forward<cmd_t>(cmds).template contains<cmd_type::modify, cpn>(id)&&...);
			}

			template<is_in_list<var_list> cpn, typename es_t, typename cmd_t>
			static decltype(auto) get_component(uint64_t id, es_t& es, cmd_t& cmds)
			{
				return std::forward<es_t>(es).get_component<cpn>(id);
			}

		};

	private:
		cmd_t&					m_commands;
		entity_system_t&		m_entity_system;
	};

}
