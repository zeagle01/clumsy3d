
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
			auto key = get_type_index<var>();
			m_commands.get_ref<cmd>()[id].insert(key);
		}

		template< is_in_list<cmd_types> cmd >
		void add_cmds(uint64_t id, const std::vector<std::type_index>& var_keys)
		{
			for (auto key : var_keys)
			{
				m_commands.get_ref<cmd>()[id].insert(key);
			}
		}

		template< is_in_list<cmd_types> cmd, is_in_list<var_list> ... var>
		auto get_entities() const
		{
			std::vector<uint64_t> ret;
			for (const auto& [id, var_indices] : m_commands.get_ref<cmd>())
			{
				bool var_exsited = (this->contains<cmd, var>(id)||...);
				if (var_exsited)
				{
					ret.push_back(id);
				}

			}
			return ret;
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

		template<typename>
		struct collection_type
		{
			using type = std::map<uint64_t, std::set<std::type_index>>;
		};

		static_var_map<cmd_types, collection_type>  m_commands;
	};
}