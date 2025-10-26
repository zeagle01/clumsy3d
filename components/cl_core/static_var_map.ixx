module;

#include <memory>

export module clumsy.core:static_var_map;

import :type_list;
import :type_helper;

namespace clumsy
{

	export
	template<typename tl, template<typename> typename t_getter = type_getter>
	class static_var_map
	{
	public:

		static_var_map()
		{
			for_each_type<tl>::apply<make_shared>(this);
		}

		template<is_in_list<tl> var_name>
		auto& get_ref() 
		{
			constexpr int i = get_index_v< tl, var_name>;
			auto ptr = std::static_pointer_cast<typename t_getter<var_name>::type>(m_datas[i]);
			return *ptr;
		}

		template<is_in_list<tl> var_name>
		const auto& get_ref() const 
		{
			constexpr int i = get_index_v< tl, var_name>;
			auto ptr = std::static_pointer_cast<typename t_getter<var_name>::type>(m_datas[i]);
			return *ptr;
		}

		constexpr int size() const
		{
			return  std::size(m_datas);
		}

	private:
		struct make_shared
		{
			template<typename var_name>
			static void apply(static_var_map* obj)
			{
				constexpr int i = get_index_v< tl, var_name>;
				obj->m_datas[i] = std::make_shared<typename t_getter<var_name>::type>();
			}

		};

	private:
		static constexpr inline int  N = get_size_v<tl>;
		std::shared_ptr<void> m_datas[N];
	};
}