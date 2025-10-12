
module;

#include "cl_core/config_define_helper.h"

#include <vector>

module clumsy3d:component;

import clumsy.matrix;
import clumsy.core;

namespace clumsy
{
	struct component
	{

		ENTRY(resolution_x,					USE(type, int);								VALUE(init_value,20);				LIST(tag));
		ENTRY(resolution_y,					USE(type, int);								VALUE(init_value,20);				LIST(tag));

		ENTRY(length_x,						USE(type, float);							VALUE(init_value,1.f);				LIST(tag));
		ENTRY(length_y,						USE(type, float);							VALUE(init_value,1.f);				LIST(tag));

		ENTRY(position_buffer,				USE(type, std::vector<vec3f>);				VALUE(init_value,nullptr);			LIST(tag));
		ENTRY(triangle_buffer,				USE(type, std::vector<vec3i>);				VALUE(init_value,nullptr);			LIST(tag));

	};

	using component_list = extract_member_type_list_t<component>;
}
