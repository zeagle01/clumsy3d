
module;

#include "cl_core/config_define_helper.h" 

module  clumsy3d: update_table;

import  : common_structs;
import  : component;
import  : update_functions;
import  : update_functions_meta;

import clumsy.core;

#define OUT(...)			LIST(out,__VA_ARGS__)
#define IN(...)				LIST(in,__VA_ARGS__)
#define INDEX_MAP(...)		USE(index_map,entity_mapper::__VA_ARGS__)
#define IN_RNG(...)			USE(input_range,entity_range::__VA_ARGS__)
#define OUT_RNG(...)		USE(output_range,entity_range::__VA_ARGS__)
#define PACK_IN(in)			USE(pack_in,param_pack::in) 
#define PACK_OUT(out)		USE(pack_out,param_pack::out) 
#define FUNC(...)			USE(func,__VA_ARGS__)

namespace clumsy
{
	using cpn = component;

	struct update_table
	{
		ENTRY(update_plane, FUNC(compute_plane);			PACK_OUT(as_each); PACK_IN(as_each);		OUT_RNG(same_as_input);		IN_RNG(all);	OUT(cpn::position_buffer, cpn::triangle_buffer);	IN(cpn::resolution_x, cpn::resolution_y, cpn::length_x, cpn::length_y); );
	};

	using updators = extract_member_type_list_t<update_table>;
}


#undef OUT			
#undef IN			
#undef INDEX_MAP	
#undef FUNC		
