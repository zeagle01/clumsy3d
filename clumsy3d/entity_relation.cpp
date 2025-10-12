
module;

module clumsy3d:entity_relation;

import clumsy.core;

namespace clumsy
{
	template<typename ...T>
	struct new_entity
	{
		using type = type_list<T...>;
	};

	template<typename ...T>
	struct selected_entity
	{
		using type = type_list<T...>;
	};



}




