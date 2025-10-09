
module;

#include <concepts>
#include <array>

export module clumsy.matrix;

namespace clumsy
{

	//////////////////////////////////////////////////////

	template< typename T >
	concept  is_indexable_2d = requires (T m)
	{
		m(0, 0);

		{ m.row_num() }-> std::same_as<int>;
		{ m.column_num() }-> std::same_as<int>;

		T::row;
		T::col;

		requires  m.row_num() == T::row;
		requires  m.column_num() == T::col;
	};

	template< typename  m0t, typename m1t >
	concept  is_same_shape = m0t::row == m1t::row && m0t::col == m1t::col;

	template< typename  m0t, typename m1t >
	concept  is_mulplication_compatible = m0t::col == m1t::row;


	//////////////////////////////////////////////////////

	export
	template<typename T, int R, int C>
	class matrix 
	{
	public:
		static constexpr int row = R;
		static constexpr int col = C;
		using type = T;
		constexpr int row_num() const { return R; }
		constexpr int column_num() const { return C; }
	public:
		struct row_layout
		{
			static constexpr int apply(int ri, int ci)
			{
				return ri * C + ci;
			}
		};
	public:

		T& operator()(int ri, int ci) { return data[row_layout::apply(ri, ci)]; }
		const T& operator()(int ri, int ci) const { return data[row_layout::apply(ri, ci)]; }

		T& operator()(int i) { static_assert(R == 1 || C == 1); return data[row_layout::apply(i, 0)]; }
		const T& operator()(int i) const { static_assert(R == 1 || C == 1); return data[row_layout::apply(i, 0)]; }

		T& operator()() { static_assert(R == 1 && C == 1); return data[0]; }
		const T& operator()() const { static_assert(R == 1 && C == 1); return data[0]; }


	public:
		T data[R * C];
	};

	//////////////////////////////////////////////////////
	template<typename T, int R, int C, typename sub_t>
	struct view : public sub_t 
	{

	public:
		static constexpr int row = R;
		static constexpr int col = C;
		using type = T;
		constexpr int row_num() const { return R; }
		constexpr int column_num() const { return C; }

	public:
		template<is_indexable_2d m0t> requires is_same_shape<view<T, R, C, sub_t>, m0t>
		void operator=(const m0t& m0)
		{
			for (int ri = 0; ri < R; ri++)
			{
				for (int ci = 0; ci < C; ci++)
				{
					operator()(ri, ci) = m0(ri, ci);
				}
			}
		}

	public:
		decltype(auto) operator()(int ri, int ci) const { return sub_t::operator()(ri, ci); }
		decltype(auto) operator()(int ri, int ci) { return sub_t::operator()(ri, ci); }

		decltype(auto) operator()(int i) const { static_assert(R == 1 || C == 1); return sub_t::operator()(i); }
		decltype(auto) operator()(int i) { static_assert(R == 1 || C == 1); return sub_t::operator()(i); }

		decltype(auto) operator()() const { static_assert(R == 1 && C == 1); return sub_t::operator()(); }
		decltype(auto) operator()() { static_assert(R == 1 && C == 1); return sub_t::operator()(); }
		
	public:
		operator matrix<T, R, C>()
		{
			matrix<T, R, C> ret;
			for (int ri = 0; ri < R; ri++)
			{
				for (int ci = 0; ci < C; ci++)
				{
					ret(ri, ci) = operator()(ri, ci);
				}
			}

			return ret;
		}

	};

	//////////////////////////////////////////////////////

	template< is_indexable_2d m0t, is_indexable_2d m1t >
	struct expression_add
	{
		auto operator()(int ri, int ci) const 
		{
			return m0(ri, ci) + m1(ri, ci);
		}

		const m0t& m0;
		const m1t& m1;
	};

	template< is_indexable_2d m0t, is_indexable_2d m1t >
	struct expression_minus
	{
		auto operator()(int ri, int ci) const
		{
			return m0(ri, ci) - m1(ri, ci);
		}

		const m0t& m0;
		const m1t& m1;
	};

	template< is_indexable_2d m0t, is_indexable_2d m1t >
	struct expression_multiply
	{
		auto operator()(int ri, int ci) const
		{
			typename m0t::type ret {};
			for (int i = 0; i < m0.column_num(); i++)
			{
				ret += m0(ri, i) * m1(i, ci);
			}
			return ret;
		}

		const m0t& m0;
		const m1t& m1;
	};

	template< is_indexable_2d m0t  >
	struct expression_column
	{
		decltype(auto) operator()(int ri, int ) const
		{
			return m0(ri, ci);
		}

		decltype(auto) operator()(int ri, int )
		{
			return m0(ri, ci);
		}

		m0t& m0;
		int ci;
	};

	template< is_indexable_2d m0t  >
	struct expression_transpose
	{
		decltype(auto) operator()(int ri, int ci) const
		{
			return m0(ci, ri);
		}

		decltype(auto) operator()(int ri, int ci)
		{
			return m0(ci, ri);
		}

		m0t& m0;
	};



	//////////////////////////////////////////////////////
	export
	template< is_indexable_2d m0t, is_indexable_2d m1t >
	requires is_same_shape<m0t,m1t>
	auto operator+(const m0t& m0, const m1t& m1)
	{
		return view<m0t::type, m0t::row, m0t::col, expression_add<m0t, m1t>>{ m0, m1 };
	}

	export
	template< is_indexable_2d m0t, is_indexable_2d m1t >
	requires is_same_shape<m0t,m1t>
	auto operator-(const m0t& m0, const m1t& m1)
	{
		return view<m0t::type, m0t::row, m0t::col, expression_minus<m0t, m1t>>{ m0, m1 };
	}

	export
	template< is_indexable_2d m0t, is_indexable_2d m1t >
	requires is_mulplication_compatible<m0t,m1t>
	auto operator*(const m0t& m0, const m1t& m1)
	{
		return view<m0t::type, m0t::row, m1t::col, expression_multiply<m0t, m1t>>{ m0, m1 };
	}


	//////////////////////////////////////////////////////
	export
	template< is_indexable_2d m0t  >
	auto column(m0t& m0, int ci)
	{
		return view<m0t::type, m0t::row, 1, expression_column<m0t>>{ m0, ci };
	}

	export
	template< is_indexable_2d m0t  >
	auto transpose(m0t& m0)
	{
		return view<m0t::type, m0t::col, m0t::row, expression_transpose<m0t>>{ m0  };
	}

	//////////////////////////////////////////////////////
	export using mat2f = matrix<float, 2, 2>;
	export using mat3f = matrix<float, 3, 3>;

	export using vec2f = matrix<float, 2, 1>;
	export using vec3f = matrix<float, 3, 1>;
}
