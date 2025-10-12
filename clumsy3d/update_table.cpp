
module;

#include "cl_core/config_define_helper.h" 

module  clumsy3d: update_table;

import  : component;
import  : update_functions;

#define INPUT(...)		LIST(input, __VA_ARGS__)
#define OUTPUT(...)		LIST(output, __VA_ARGS__)
#define TAG(...)		LIST(tag, __VA_ARGS__)
#define FUNC(...)		USE(func, __VA_ARGS__)

namespace clumsy
{
	using cpn = component;

	struct update_table
	{
		ENTRY(add_triangle,			FUNC(build_triangle)		OUTPUT( cpn::position_buffer, cpn::triangle_buffer)							INPUT()																TAG());
		//ENTRY(remove_triangle,		FUNC(build_triangle)		OUTPUT()																	INPUT( cpn::position_buffer, cpn::triangle_buffer)					TAG());
	};
}

#undef INPUT		
#undef OUTPUT		
#undef TAG		
