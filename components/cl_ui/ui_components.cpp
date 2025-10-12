
module;

#include <vector>
#include <string>

module clumsy.ui:ui_components;

import :ui_type_table;
import :ui_wrappers;

import clumsy.core;


namespace clumsy
{

	class ui_components
	{
	public:
		template<is_in_list<ui_list> ui_cpn,typename cpn_type,typename ...P >
		void add_ui(const std::string& name, cpn_type&& value, P...p)
		{
			m_slots.push_back
			(
				[&,name]()
				{
					ui_wrapper<ui_cpn>::apply(name, std::forward<cpn_type>(value), p...);
				}
			);
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

