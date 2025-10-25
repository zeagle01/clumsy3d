module;


#include <string>

export module clumsy.ui:ui_factory;

import :ui_type_table;
import :ui_object;

namespace clumsy
{

	export
	class ui_factory
	{
	public:
		template<is_in_list<ui_list> ui> 
		static auto create(const std::string& name, ui::param p, ui::type& value)
		{
			return ui_object_2<ui>(name, p, value);
		}
	};

}
