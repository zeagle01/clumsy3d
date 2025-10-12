
module;

#include "cl_core/config_define_helper.h"

#include <functional>

export module clumsy.ui:ui_type_table;

import clumsy.core;

namespace clumsy
{
	export
	struct range
	{
		float min;
		float max;
	};

	export
	struct ui
	{
		ENTRY(button,					USE(type, empty)					USE(param,empty)						)
		ENTRY(check_box,				USE(type, bool)						USE(param,empty)						)
		ENTRY(slider_float,				USE(type, float)					USE(param,range)						)
		ENTRY(input_float,				USE(type, float)					USE(param,empty)						)
		ENTRY(input_int,				USE(type, int)						USE(param,empty)						)

		//ENTRY(combo_box,				USE(type,bool)			)

	};
	using ui_list = extract_member_type_list_t<ui>;

}

