
module;

#include "cl_core/config_define_helper.h"
#include <set>
#include <array>
#include <vector>

module clumsy3d:entity_relation;

import clumsy.core;

namespace clumsy
{

	////////////////
	struct cmd_type
	{
		struct create {};
		struct erase {};
		struct modify {};
	};

	////////////////
	struct entity_range
	{
		template<typename ...T>
		struct entity_has {};
		using unconstraited = entity_has<>;

		template<typename T>
		struct sender_of_edge {};

		template<typename T>
		struct receiver_of_edge {};

		template<typename T>
		struct value_of {};

		template<int N>
		struct crated {};
		using created_one = crated<1>;

		struct none {};
	};


	////////////////

	struct index_map
	{
		template<int N> struct create {};
		using create_one = create<1>;

		struct none {};

		struct all_to_one {};

		template<typename edge>
		struct one_to_one {};
		using identity = one_to_one<empty>;
	};



}




