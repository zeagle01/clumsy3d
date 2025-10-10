
module;

#include <map>
#include <memory>
#include <typeindex>
#include <functional>

export module clumsy.core:entity_system;

import :type_list;

namespace clumsy
{
	export
	template
	<
		typename type_list,
		template <typename > typename type_getter 
	>
	class entity_system
	{
	public:

		uint64_t add_entity()
		{
			m_entities[m_id] = {};
			return m_id++;
		}

		template<is_in_list<type_list> component>
		void add_component(uint64_t id, const type_getter<component>::type& value)
		{
			auto key = get_key<component>();

			m_entities[id][key] = std::make_shared<typename type_getter<component>::type>(value);
		}

		template<is_in_list<type_list> component>
		void remove_component(uint64_t id)
		{
			auto key = get_key<component>();
			m_entities[id].erase(key);
		}

	public:
		template<is_in_list<type_list> ... component>
		void for_each(std::function<void(typename type_getter<component>::type ...) > fn)
		{
			for (auto& [id, components] : m_entities)
			{
				bool has_components = (m_entities[id].contains(typeid(component))&&...);

				if (has_components)
				{
					fn
					(
						(
							*std::static_pointer_cast<typename type_getter<component>::type>
							(
								m_entities[id][get_key<component>()]
							)
						)
						...
					);
				}
			}
		}
	private:
		using key_t = std::type_index;

		template<typename var> static constexpr key_t get_key() 
		{
			return std::type_index(typeid(var));
		}

	private:
		std::map<uint64_t, std::map<key_t, std::shared_ptr<void>>> m_entities;
		uint64_t m_id = 0;
	};
}