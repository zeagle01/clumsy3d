
module;

#include "cl_core/config_define_helper.h"

#include <vector>
#include <set>

module clumsy3d:component;

import :common_structs;

import clumsy.matrix;
import clumsy.core;

namespace clumsy
{

	struct component
	{

		ENTRY(id,							USE(type, uint64_t);						VALUE(init_value,empty_v);			LIST(tag,field_tag::read_only,field_tag::create_on_new_entity));
		ENTRY(selected_entities,			USE(type, std::vector<uint64_t>);			VALUE(init_value,empty_v);			LIST(tag,field_tag::singleton));
		ENTRY(sync_move_pairs,				USE(type, std::vector<directed_edge>);		VALUE(init_value,empty_v);			LIST(tag,field_tag::singleton));

		ENTRY(resolution_x,					USE(type, int);								VALUE(init_value,20);				LIST(tag));
		ENTRY(resolution_y,					USE(type, int);								VALUE(init_value,20);				LIST(tag));

		ENTRY(length_x,						USE(type, float);							VALUE(init_value,1.f);				LIST(tag));
		ENTRY(length_y,						USE(type, float);							VALUE(init_value,1.f);				LIST(tag));

		ENTRY(position_buffer,				USE(type, std::vector<vec3f>);				VALUE(init_value,empty_v);			LIST(tag));
		ENTRY(triangle_buffer,				USE(type, std::vector<vec3i>);				VALUE(init_value,empty_v);			LIST(tag));

	};

	using component_list = extract_member_type_list_t<component>;
}
