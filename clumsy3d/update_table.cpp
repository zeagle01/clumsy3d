
module;

#include "cl_core/config_define_helper.h" 

module  clumsy3d: update_table;

import  : component;
import  : update_functions;

import clumsy.core;

#define OUT(...)			LIST(out,__VA_ARGS__)
#define IN(...)				LIST(in,__VA_ARGS__)
#define INDEX_MAP(...)		USE(index_map,entity_mapper::__VA_ARGS__)
#define FUNC(...)			USE(func,__VA_ARGS__)

namespace clumsy
{
	using cpn = component;

	struct update_table
	{
		ENTRY(update_plane,			FUNC(compute_plane);			OUT(cpn::position_buffer,cpn::triangle_buffer);					INDEX_MAP(one_to_one<index_map::identity,entity_range::all>);										IN(cpn::resolution_x,cpn::resolution_y,cpn::length_x,cpn::length_y));
	};

	using updators = extract_member_type_list_t<update_table>;
}


#undef OUT			
#undef IN			
#undef INDEX_MAP	
#undef FUNC		
