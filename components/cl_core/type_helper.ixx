
module;

#include <typeindex>

export module clumsy.core:type_helper;


namespace clumsy
{
	export
	template<typename T>
	struct type_getter
	{
		using type = T::type;

	};

	export
	template<typename T> constexpr auto get_type_index()
	{
		return std::type_index(typeid(T));
	}

}