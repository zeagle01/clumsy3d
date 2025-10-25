
module;

#include "cl_core/config_define_helper.h"

module clumsy3d:input_table;

import :common_structs;
import :component;
import :update_functions;

import clumsy.ui;
import clumsy.core;


#define OUT(...)			LIST(out,__VA_ARGS__)
#define IN(...)				LIST(in,__VA_ARGS__)
#define INDEX_MAP(...)		USE(index_map,entity_mapper::__VA_ARGS__)
#define UI(x)				USE(ui,ui::x)
#define UI_PARAM(...)		VALUE(ui_param,__VA_ARGS__)
#define FUNC(...)			USE(func,__VA_ARGS__)

namespace clumsy
{
	using cpn = component;

	struct input_table
	{


		ENTRY(add_triangle,			FUNC(build_triangle);			OUT(cpn::position_buffer,cpn::triangle_buffer);					INDEX_MAP(all_to_one<entity_range::create,entity_range::none>);										IN();											UI(button)			UI_PARAM(empty_v));
		ENTRY(random_select,		FUNC(get_last);					OUT(cpn::selected_entities);									INDEX_MAP(all_to_one<entity_range::all,entity_range::all>);											IN(cpn::id);									UI(button)			UI_PARAM(empty_v));
		ENTRY(remove_selected,		FUNC(empty);					OUT(empty);														INDEX_MAP(erase<entity_range::value_of<cpn::selected_entities>>);									IN();											UI(button)			UI_PARAM(empty_v));
		ENTRY(add_sync_pair,		FUNC(set_sync_pair);			OUT(cpn::sync_move_pairs);										INDEX_MAP(all_to_one<entity_range::all,entity_range::all>);											IN(cpn::id);									UI(button)			UI_PARAM(empty_v));
		ENTRY(sync_move,			FUNC(offsetting_pos);			OUT(cpn::position_buffer);										INDEX_MAP(one_to_one<index_map::directed_edge, entity_range::value_of<cpn::sync_move_pairs>>);		IN(cpn::position_buffer);						UI(button)			UI_PARAM(empty_v));
		ENTRY(set_resolution_x,		FUNC(do_nothing);				OUT(cpn::resolution_x);											INDEX_MAP(all_to_all<entity_range::value_of<cpn::selected_entities>,entity_range::none>);			IN();											UI(input_int)		UI_PARAM(empty_v));

		//ENTRY(bind_resolution_x,		FUNC(assign);						OUT(selected_entity<cpn::resolution_x>);												IN()														UI(input_int)		UI_PARAM(empty_v));
		//ENTRY(bind_resolution_y,		FUNC(assign);						OUT(selected_entity<cpn::resolution_y>);												IN()														UI(input_int)		UI_PARAM(empty_v));
		//ENTRY(bind_length_x,			FUNC(assign);						OUT(selected_entity<cpn::length_x>);													IN()														UI(input_float)		UI_PARAM(empty_v));
		//ENTRY(bind_length_y,			FUNC(assign);						OUT(selected_entity<cpn::length_y>);													IN()														UI(input_float)		UI_PARAM(empty_v));


	};

	using input_table_type_list = extract_member_type_list_t<input_table>;
}

#undef OUT			
#undef IN			
#undef INDEX_MAP	
#undef UI			
#undef UI_PARAM	
#undef FUNC		
