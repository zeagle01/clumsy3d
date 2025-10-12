
module;

#include <vector>
#include <string>
#include <functional>

module clumsy.ui:ui_components;

import :ui_type_table;
import :ui_wrappers;
import :ui_object;

import clumsy.core;


namespace clumsy
{
	template<typename ui_cpn>
	concept ui_type_is_void = requires
	{
		requires is_in_list<ui_cpn, ui_list>;
		requires std::is_same_v<typename ui_cpn::type, void>;

	};

	template<typename T>
	using get_slot_t = std::conditional_t
		<ui_type_is_void<T>,
		std::function<void()>,
		std::function<void(typename T::type)>
		>;

	class ui_components
	{
	public:
		template<is_in_list<ui_list> ui_cpn ,typename ui_param >
		requires std::convertible_to<std::decay_t<ui_param>, typename ui_cpn::param>
		void add_ui(const std::string& name, ui_param param, std::function<void(typename ui_cpn::type)> slot)
		{

			ui_object<ui_cpn> l_ui_object(name, param, slot);

			m_slots.push_back(l_ui_object);

		}

		void invoke_slots()
		{
			for (auto f : m_slots)
			{
				f();
			}
		}

	private:
		std::vector<std::function<void()>> m_slots;
	};

}

