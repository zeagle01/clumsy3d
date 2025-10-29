
module;

#include "cl_core/config_define_helper.h"

module clumsy3d:input_table;

import :common_structs;
import :component;
import :update_functions;
import :update_functions_meta;

import clumsy.ui;
import clumsy.core;


#define OUT(...)			LIST(out,__VA_ARGS__)
#define IN(...)				LIST(in,__VA_ARGS__)
#define INDEX_MAP(...)		USE(index_map,entity_mapper::__VA_ARGS__)
#define PACK_IN(in)			USE(pack_in,param_pack::in) 
#define PACK_OUT(out)		USE(pack_out,param_pack::out) 
#define IN_RNG(...)			USE(input_range,entity_range::__VA_ARGS__)
#define OUT_RNG(...)		USE(output_range,entity_range::__VA_ARGS__)
#define UI(x)				USE(ui,ui::x)
#define UI_PARAM(...)		VALUE(ui_param,__VA_ARGS__)
#define FUNC(...)			USE(func,__VA_ARGS__)

namespace clumsy
{
	using cpn = component;

	struct input_table
	{

		ENTRY(add_triangle,				FUNC(build_triangle);		PACK_OUT(as_each);	PACK_IN(as_whole);				OUT_RNG(create_entity);									IN_RNG(none);								OUT(cpn::position_buffer, cpn::triangle_buffer);																			IN();											UI(button)			UI_PARAM(empty_v));
		ENTRY(add_plane,				FUNC(do_nothing);			PACK_OUT(as_each);	PACK_IN(as_whole);				OUT_RNG(create_entity);									IN_RNG(none);								OUT(cpn::resolution_x, cpn::resolution_y, cpn::length_x, cpn::length_y);													IN();											UI(button)			UI_PARAM(empty_v));
		ENTRY(random_select,			FUNC(get_last);				PACK_OUT(as_each);	PACK_IN(as_whole);				OUT_RNG(all);											IN_RNG(all);								OUT(cpn::selected_entities);																								IN(cpn::id);									UI(button)			UI_PARAM(empty_v));
		ENTRY(remove_selected,			FUNC(erase_entity);			PACK_OUT(as_each);	PACK_IN(as_whole);				OUT_RNG(value_of<cpn::selected_entities>);				IN_RNG(none);								OUT(cpn::id);																												IN();											UI(button)			UI_PARAM(empty_v));
		ENTRY(add_sync_pair,			FUNC(set_sync_pair);		PACK_OUT(as_each);	PACK_IN(as_whole);				OUT_RNG(all);											IN_RNG(value_of<cpn::selected_entities>);	OUT(cpn::sync_move_pairs);																									IN(cpn::id);									UI(button)			UI_PARAM(empty_v));
		ENTRY(sync_move,				FUNC(offsetting_pos);		PACK_OUT(as_each);	PACK_IN(as_each);				OUT_RNG(edge_to<cpn::sync_move_pairs>);					IN_RNG(edge_from<cpn::sync_move_pairs>);	OUT(cpn::position_buffer);																									IN(cpn::position_buffer);						UI(button)			UI_PARAM(empty_v));

		ENTRY(bind_resolution_x,		FUNC(broad_cast_by_first);	PACK_OUT(as_whole); PACK_IN(as_whole);				OUT_RNG(value_of<cpn::selected_entities>);				IN_RNG(none);								OUT(cpn::resolution_x);																										IN();											UI(input_int)		UI_PARAM(empty_v));
		ENTRY(bind_resolution_y,		FUNC(broad_cast_by_first);	PACK_OUT(as_whole); PACK_IN(as_whole);				OUT_RNG(value_of<cpn::selected_entities>);				IN_RNG(none);								OUT(cpn::resolution_y);																										IN();											UI(input_int)		UI_PARAM(empty_v));
		ENTRY(bind_length_x,			FUNC(broad_cast_by_first);	PACK_OUT(as_whole); PACK_IN(as_whole);				OUT_RNG(value_of<cpn::selected_entities>);				IN_RNG(none);								OUT(cpn::length_x);																											IN();											UI(input_float)		UI_PARAM(empty_v));
		ENTRY(bind_length_y,			FUNC(broad_cast_by_first);	PACK_OUT(as_whole); PACK_IN(as_whole);				OUT_RNG(value_of<cpn::selected_entities>);				IN_RNG(none);								OUT(cpn::length_y);																											IN();											UI(input_float)		UI_PARAM(empty_v));

	};

	using input_table_type_list = extract_member_type_list_t<input_table>;
}

#undef OUT			
#undef IN			
#undef INDEX_MAP	
#undef UI			
#undef UI_PARAM	
#undef FUNC		
