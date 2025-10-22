module;

#include <string>

export module clumsy.core:get_type_name;

namespace clumsy
{

	export
	template<typename T>
	constexpr std::string get_type_name()
	{
		std::string ret = typeid(T).name();

		auto pos = ret.find_last_of(":");

		return  ret.substr(pos + 1, std::string::npos);

	}


}