
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
		ENTRY(position_buffer,				USE(type, std::vector<vec3f>);				VALUE(init_value,nullptr);			LIST(tag));
		ENTRY(triangle_buffer,				USE(type, std::vector<vec3i>);				VALUE(init_value,nullptr);			LIST(tag));

	};
}
