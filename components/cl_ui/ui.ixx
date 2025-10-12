
module;

#include <string>
#include <concepts>

export module clumsy.ui;

export import :ui_type_table;

import clumsy.core;
import :ui_components;

namespace clumsy
{
	export
	class ui_manager
	{
	public:
		void init(void* window);
		void update();

	public:
		template<is_in_list<ui_list> ui_cpn, typename cpn_type, typename ...P>
		requires std::convertible_to<std::remove_cvref_t<cpn_type>, typename ui_cpn::type>
		void add_ui(const std::string& name, cpn_type&& value,P...p)
		{
			m_components.add_ui<ui_cpn>(name, std::forward<cpn_type>(value), p...);
		}

	private:
		ui_components m_components;
	};

}
