
module;


#include "cl_core/config_define_helper.h"

module clumsy3d:input_table;

import :component;
import :entity_relation;
import :update_functions;

import clumsy.ui;
import clumsy.core;


#define OUT(...)			LIST(out,__VA_ARGS__)
#define OUT_RNG(...)		USE(out_range,entity_range::__VA_ARGS__)
#define IN(...)				LIST(in,__VA_ARGS__)
#define IN_RNG(...)			USE(in_range,entity_range::__VA_ARGS__)
#define INDEX_MAP(...)		USE(index_map,index_map::__VA_ARGS__)
//#define CMD(...)			USE(command,cmd_type::__VA_ARGS__)
#define UI(x)				USE(ui,ui::x)
#define UI_PARAM(...)		VALUE(ui_param,__VA_ARGS__)
#define FUNC(...)			USE(func,__VA_ARGS__)

namespace clumsy
{
	using cpn = component;

	struct input_table
	{

		//ENTRY(add_triangle,			FUNC(build_triangle);			OUT(cpn::position_buffer,cpn::triangle_buffer);					OUT_RNG(created_one);										INDEX_MAP(none);					IN();										IN_RNG(none)											UI(button)			UI_PARAM(empty_v));
		//ENTRY(random_select,		FUNC(get_last);					OUT(cpn::selected_entities);									OUT_RNG(unconstraited);										INDEX_MAP(all_to_one);				IN(cpn::id);								IN_RNG(unconstraited)									UI(button)			UI_PARAM(empty_v));
		//ENTRY(sync_move,			FUNC(offsetting_pos);			OUT(cpn::position_buffer);										OUT_RNG(receiver_of_edge<cpn::sync_move_pairs>);			INDEX_MAP(all_to_one);				IN(cpn::position_buffer);					IN_RNG(sender_of_edge<cpn::sync_move_pairs>)			UI(button)			UI_PARAM(empty_v));
		//ENTRY(set_resolution_x,		FUNC(assign);					OUT(cpn::resolution_x);											OUT_RNG(unconstraited);										INDEX_MAP(one_to_one);				IN();										IN_RNG(value_of<cpn::selected_entities>)				UI(input_int)		UI_PARAM(empty_v));

		ENTRY(add_triangle,			FUNC(build_triangle);			OUT(cpn::position_buffer,cpn::triangle_buffer);					INDEX_MAP(create_one);								IN();											UI(button)			UI_PARAM(empty_v));
		ENTRY(random_select,		FUNC(get_last);					OUT(cpn::selected_entities);									INDEX_MAP(all_to_one);								IN(cpn::id);									UI(button)			UI_PARAM(empty_v));
		ENTRY(add_sync_pair,		FUNC(set_sync_pair);			OUT(cpn::sync_move_pairs);										INDEX_MAP(all_to_one);								IN(cpn::id);									UI(button)			UI_PARAM(empty_v));
		ENTRY(sync_move,			FUNC(offsetting_pos);			OUT(cpn::position_buffer);										INDEX_MAP(one_to_one<cpn::sync_move_pairs>);		IN(cpn::position_buffer);						UI(button)			UI_PARAM(empty_v));
		ENTRY(set_resolution_x,		FUNC(assign);					OUT(cpn::resolution_x);											INDEX_MAP(identity);								IN();											UI(input_int)		UI_PARAM(empty_v));

		//ENTRY(bind_resolution_x,		FUNC(assign);						OUT(selected_entity<cpn::resolution_x>);												IN()														UI(input_int)		UI_PARAM(empty_v));
		//ENTRY(bind_resolution_y,		FUNC(assign);						OUT(selected_entity<cpn::resolution_y>);												IN()														UI(input_int)		UI_PARAM(empty_v));
		//ENTRY(bind_length_x,			FUNC(assign);						OUT(selected_entity<cpn::length_x>);													IN()														UI(input_float)		UI_PARAM(empty_v));
		//ENTRY(bind_length_y,			FUNC(assign);						OUT(selected_entity<cpn::length_y>);													IN()														UI(input_float)		UI_PARAM(empty_v));


	};

	using input_table_type_list = extract_member_type_list_t<input_table>;
}

#undef OUT			
#undef OUT_RNG		
#undef IN			
#undef IN_RNG		
#undef INDEX_MAP	
//#undef CMD			
#undef UI			
#undef UI_PARAM	
#undef FUNC		
