
module;

#include <map>
#include <set>
#include <typeindex>
#include <functional>

module clumsy3d:commands;

import :common_structs;

import clumsy.core;

namespace clumsy
{
	template
		<
		typename var_list,
		template <typename > typename get_var_type
		>
	class commands
	{
	public:

		template< is_in_list<cmd_types> cmd, is_in_list<var_list> var>
		void add_cmd(uint64_t id)
		{
			constexpr auto key = std::type_index(typeid(var));
			m_commands.get_ref<var>()[id].insert(key);

		}

		template< is_in_list<cmd_types> cmd, is_in_list<var_list> var>
		constexpr bool contains(uint64_t id) const
		{
			return m_commands.get_ref<cmd>().at(id).contains(std::type_index(typeid(var)));

		}

		void clear()
		{
			for_each_type<cmd_types>::apply<clear_cmd>(m_commands);
		}

	private:
		using var_key = std::type_index;
	private:

		template<is_in_list<cmd_types> cmd>
		struct command_collection
		{
			std::map<uint64_t, std::set<var_key>> data;
		};
	private:
		struct clear_cmd
		{
			template<typename var>
			static void apply(auto& commands)
			{
				commands.get_ref<var>().clear();
			}
		};

	private:
		static_var_map<cmd_types>  m_commands;
	};
}