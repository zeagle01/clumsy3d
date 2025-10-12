
module;


#include "cl_core/config_define_helper.h"

module clumsy3d:input_table;

import :component;
import :entity_relation;
import :update_functions;

import clumsy.ui;
import clumsy.core;


#define OUT(...)			USE(out,__VA_ARGS__)
#define UI(x)				USE(ui,ui::x)
#define UI_PARAM(...)		VALUE(ui_param,__VA_ARGS__)
#define FUNC(...)			USE(func,__VA_ARGS__)

namespace clumsy
{
	using cpn = component;

	struct input_table
	{
		//ENTRY(bind_plane_maker,			FUNC(created_with_default_value);	OUT(new_entity<cpn::resolution_x, cpn::resolution_y, cpn::length_x, cpn::length_y>);		UI(button)			UI_PARAM(empty_v));
		ENTRY(bind_resolution_x,		FUNC(assign);						OUT(selected_entity<cpn::resolution_x>);													UI(input_int)		UI_PARAM(empty_v));
		ENTRY(bind_resolution_y,		FUNC(assign);						OUT(selected_entity<cpn::resolution_y>);													UI(input_int)		UI_PARAM(empty_v));
		ENTRY(bind_length_x,			FUNC(assign);						OUT(selected_entity<cpn::length_x>);														UI(input_float)		UI_PARAM(empty_v));
		ENTRY(bind_length_y,			FUNC(assign);						OUT(selected_entity<cpn::length_y>);														UI(input_float)		UI_PARAM(empty_v));
		ENTRY(bind_add_triangle,		FUNC(build_triangle);				OUT(new_entity<cpn::position_buffer,cpn::triangle_buffer>);									UI(button)			UI_PARAM(empty_v));


	};

	using input_table_type_list = extract_member_type_list_t<input_table>;
}
