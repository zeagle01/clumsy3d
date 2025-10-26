
module;

#include <map>
#include <memory>
#include <typeindex>
#include <functional>

export module clumsy.core:entity_system;

import :type_list;
import :type_helper;

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
		using components = type_list;

	public:
		uint64_t add_entity()
		{
			m_entities[m_id] = {};
			return m_id++;
		}

		void remove_entity(uint64_t id)
		{
			m_entities.erase(id);
		}

		template<is_in_list<type_list> component>
		void add_component(uint64_t id, const type_getter<component>::type& value)
		{
			auto key = get_type_index<component>();

			m_entities[id][key] = std::make_shared<typename type_getter<component>::type>(value);
		}

		template<is_in_list<type_list> component>
		void add_component(uint64_t id )
		{
			auto key = get_type_index<component>();

			m_entities[id][key] = std::make_shared<typename type_getter<component>::type>();
		}

		template<is_in_list<type_list> component>
		auto& get_component(uint64_t id)
		{
			auto key = get_type_index<component>();

			return *std::static_pointer_cast<typename type_getter<component>::type>(m_entities[id][key]);
		}

		template<is_in_list<type_list> component>
		const auto& get_component(uint64_t id) const
		{
			auto key = get_type_index<component>();

			return *std::static_pointer_cast<typename type_getter<component>::type>(m_entities.at(id).at(key));
		}

		std::vector<std::type_index> get_component_keys(uint64_t id)
		{
			std::vector<std::type_index> ret; 
			ret.reserve(m_entities[id].size());
			for (auto [key, _] : m_entities[id])
			{
				ret.push_back(key);
			}
			ret.shrink_to_fit();

			return ret;
		}

		template<is_in_list<type_list> component>
		void remove_component(uint64_t id)
		{
			auto key = get_type_index<component>();
			m_entities[id].erase(key);
		}

	public:

		template<is_in_list<type_list> ... component>
		bool contains(uint64_t id) const
		{
			return  m_entities.contains(id) && (m_entities.at(id).contains(typeid(component))&&...);
		}

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
								m_entities[id][get_type_index<component>()]
							)
						)
						...
					);
				}
			}
		}

		template<is_in_list<type_list> ... component>
		auto get_entities() const
		{
			std::vector<uint64_t> ret;
			for (auto& [id, components] : m_entities)
			{
				bool has_components = (m_entities.at(id).contains(typeid(component))&&...);

				if (has_components)
				{
					ret.emplace_back(id);
				}
			}
			return ret;
		}

	private:
		using key_t = std::type_index;

	private:
		std::map<uint64_t, std::map<key_t, std::shared_ptr<void>>> m_entities;
		uint64_t m_id = 0;
	};
}