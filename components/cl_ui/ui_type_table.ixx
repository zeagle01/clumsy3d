
module;

#include "cl_core/config_define_helper.h"

#include <functional>

export module clumsy.ui:ui_type_table;

import clumsy.core;

namespace clumsy
{
	using fn = std::function<void()>;

	export
	struct ui
	{
		ENTRY(button,					USE(type, fn))
		ENTRY(check_box,				USE(type, bool))
		ENTRY(slider_float,				USE(type, float))
		ENTRY(input_float,				USE(type, float))
		ENTRY(input_int,				USE(type, int))
		//ENTRY(combo_box,				USE(type,bool)							)

	};
	using ui_list = extract_member_type_list_t<ui>;

}

