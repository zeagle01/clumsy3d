module;

#include <stdint.h>

module clumsy3d:common_structs;

namespace clumsy
{
	struct directed_edge
	{
		uint64_t sender;
		uint64_t receiver;
	};

	struct field_tag
	{
		struct read_only {};
		struct singleton {};
		struct create_on_new_entity {};
	};

	////////////////
	struct cmd_type
	{
		struct create {};
		struct erase {};
		struct modify {};
	};


	//////
	struct entity_range
	{
		struct all {};

		template<typename cpn>
		struct value_of {};

		struct create {};

		struct none {};
	};


	//////
	struct index_map
	{
		struct identity {};
		struct directed_edge {};
	};

	struct entity_mapper
	{
		template<typename out_range, typename input_range>
		struct all_to_one {};

		template<typename id_map, typename input_range>
		struct one_to_one {};

		template< typename input_range>
		struct erase {};
	};

}

