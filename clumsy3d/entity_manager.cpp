
module;

#include <stdint.h>
#include <functional>

module clumsy3d:entity_manager;

import :component;
import :common_structs;

import clumsy.core;

namespace clumsy
{

	template<typename T,typename type_list>
	concept single_component = is_in_list<T, type_list> && is_in_list<typename field_tag::singleton, typename T::tag>;

	template<typename T,typename type_list>
	concept is_created_on_new_entity = is_in_list<T, type_list> && is_in_list<typename field_tag::create_on_new_entity, typename T::tag>;

	template
	<
		typename type_list,
		template <typename > typename type_getter 
	>
	class entity_manager
	{
	public:
		entity_manager()
		{

			using singleton_list = filter_list<type_list, is_singleton_wrapper>::type;

			for_each_type<singleton_list>::template apply<create_one>(*this);
		}

		uint64_t add_entity()
		{
			auto id = m_entity_system.add_entity();

			using components = filter_list<type_list, is_created_on_new_entity_wraper>::type;
			for_each_type<components>::template apply<component_adder>(id, m_entity_system, id);

			return id;
		}

		void remove_entity(uint64_t id)
		{
			m_entity_system.remove_entity(id);
		}

		template<is_in_list<type_list> component>
		void add_component(uint64_t id, const type_getter<component>::type& value)
		{
			return m_entity_system.add_component<component>(id, value);
		}

		template<is_in_list<type_list> component>
		void add_component(uint64_t id )
		{
			return m_entity_system.add_component<component>(id);
		}

		template<is_in_list<type_list> component>
		auto& get_component(uint64_t id)
		{
			return m_entity_system.get_component<component>(id);
		}

		template<is_in_list<type_list> component>
		const auto& get_component(uint64_t id) const
		{
			return m_entity_system.get_component<component>(id);
		}

		template<single_component<type_list> component>
		auto& get_singleton()
		{
			auto obj = m_entity_system.get_entities<component>();
			return m_entity_system.get_component<component>(obj.back());
		}

		template<single_component<type_list> component>
		const auto& get_singleton(uint64_t id) const
		{
			auto obj = m_entity_system.get_entities<component>();
			return m_entity_system.get_component<component>(obj.back());
		}

		template<is_in_list<type_list> component>
		void remove_component(uint64_t id)
		{
			return m_entity_system.remove_component<component>(id);
		}

	public:

		template<is_in_list<type_list> ... component>
		bool contains(uint64_t id) const
		{
			return m_entity_system.contains<component...>(id);
;
		}

		template<is_in_list<type_list> ... component>
		void for_each(std::function<void(typename type_getter<component>::type ...) > fn)
		{
			m_entity_system.for_each<component...>(fn);
		}

		template<is_in_list<type_list> ... component>
		auto get_entities() const
		{
			return m_entity_system.get_entities<component...>();
		}

	private:

		template<typename U >
		struct is_singleton_wrapper
		{
			static constexpr bool value = single_component<U, type_list>;
		};

		template<typename U >
		struct is_created_on_new_entity_wraper
		{
			static constexpr bool value = is_created_on_new_entity<U, type_list>;
		};

		struct create_one
		{
			template< is_in_list<type_list> component, typename  entity_system_t>
			static void apply(entity_system_t& p_entity_system)
			{
				auto id = p_entity_system.add_entity();
				p_entity_system.add_component<component>(id);
			}

		};

		struct component_adder
		{
			template< is_in_list<type_list> component, typename  entity_system_t, typename T >
			static void apply(uint64_t id, entity_system_t& p_entity_system, T v)
			{
				p_entity_system.add_component<component>(id, v);
			}

		};

	private:
		entity_system<type_list, type_getter> m_entity_system;
	};


}

