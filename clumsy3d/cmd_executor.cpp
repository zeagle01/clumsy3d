module ;


module clumsy3d:cmd_executor;

import :update_table;
import :invoke_update_function;

import clumsy.core;

namespace clumsy
{

	class cmd_executor
	{
	public:
		template<typename entity_system>
		static void apply(entity_system& p_entity_system)
		{
			for_each_type< updators >::apply< update_entry<entity_system > >(p_entity_system);
		}

	private:

		template<typename entity_system >
		struct update_entry
		{
			template<typename entry>
			static void apply(entity_system& p_entity_system)
			{
				auto alway_pass_through = []() { return true; };
				invoke_update_function<typename entry::out, typename entry::in, typename entry::output_range, typename entry::input_range, typename entry::pack_out, typename entry::pack_in, entity_system >::apply<entry::func>(p_entity_system, alway_pass_through);

			}
		};
	};

}



