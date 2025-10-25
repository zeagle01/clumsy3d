
module;

#include <string>
#include <concepts>
#include <functional>

export module clumsy.ui;

export import :ui_type_table;
export import :ui_factory;

import clumsy.core;
import :ui_components;

namespace clumsy
{

	export
	class ui_manager
	{
	public:
		void init(void* window);
		//void update();
		void clear();
		void update(std::function<void()> fn);

	public:
		template<is_in_list<ui_list> ui_cpn ,typename ui_param >
		requires std::convertible_to<std::decay_t<ui_param>, typename ui_cpn::param>
		void add_ui(const std::string& name, ui_param param, std::function<void(typename ui_cpn::type)> slot)
		{
			m_components.add_ui<ui_cpn>(name, param, slot);
		}

	private:
		ui_components m_components;
	};

}
