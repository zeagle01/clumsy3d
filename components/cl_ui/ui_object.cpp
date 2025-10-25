module;

#include <string>
#include <functional>

module clumsy.ui:ui_object;

import :ui_type_table;
import :ui_wrappers;

namespace clumsy
{
	template<is_in_list<ui_list> cpn >
	struct ui_object
	{
		static_assert(is_in_list<cpn, ui_list>);

		using fn_t = std::function<void(typename cpn::type)>;
		using param_t = typename cpn::param;
		using type = typename cpn::type;

		ui_object(const std::string& name, param_t p, fn_t fn)
			:m_name(name), m_param(p), m_fn(fn)
		{
		}

		void operator()()
		{
			if (ui_wrapper < cpn >::apply(m_name.c_str(), m_value, m_param))
			{
				m_fn(m_value);
			}
		}

	private:
		std::string		m_name;
		fn_t			m_fn;
		param_t			m_param;
		type			m_value;
	};

	template<is_in_list<ui_list> cpn >
	struct ui_object_2
	{
		using param_t = typename cpn::param;
		using type = typename cpn::type;

		ui_object_2(const std::string& name, param_t p,type& value)
			:m_name(name), m_param(p), m_value(value)
		{
		}

		bool operator()()
		{
			return ui_wrapper < cpn >::apply(m_name.c_str(), m_value, m_param);

		}

	private:
		std::string		m_name;
		param_t			m_param;
		type&			m_value;
	};

}