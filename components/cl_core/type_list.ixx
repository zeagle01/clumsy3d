
module;

#include <type_traits>
#include <utility>

export module clumsy.core:type_list;

namespace clumsy
{
	export
	template<typename ...P>
	struct type_list {};

	template<typename tl>
	struct is_type_list_imp :public std::false_type {};

	template<typename ...P>
	struct is_type_list_imp<type_list<P...>> :public std::true_type {};

	export
	template<typename tl>
	constexpr  bool is_type_list = is_type_list_imp<tl>::value;


	//front
	template<typename tl>
	struct front_imp;

	template<typename H, typename ...P>
	struct front_imp < type_list<H, P...>>
	{
		using type = H;
	};

	export
	template<typename tl>
	using front_t = typename front_imp<tl>::type;


	//pop front
	template<typename tl>
	struct pop_front_imp;

	template<typename H, typename ...P>
	struct pop_front_imp<type_list<H, P...>>
	{
		using type = type_list<P...>;
	};

	export
	template<typename T>
	using pop_front_t = typename pop_front_imp<T>::type;


	//push front
	template<typename tl, typename H>
	struct push_front_imp;

	template<typename H, typename ...P>
	struct push_front_imp< type_list<P...>, H>
	{
		using type = type_list<H, P...>;
	};

	export
	template<typename tl, typename H>
	using push_front_t = typename push_front_imp<tl, H>::type;


	//get nth element
	template<typename tl, int N>
	struct get_nth_element_imp
	{
		using poped_list = typename pop_front_t<tl>;
		using type = typename get_nth_element_imp<poped_list, N - 1>::type;
	};

	template<typename tl >
	struct get_nth_element_imp<tl, 0>
	{
		using type = typename front_t<tl>;
	};

	export
	template<typename tl, int N>
	using get_nth_element_t = typename get_nth_element_imp<tl, N>::type;

	//get size
	template<typename tl>
	struct	get_size_imp;

	template<typename...Ts>
	struct	get_size_imp<type_list<Ts...>>
	{
		static constexpr int value = sizeof...(Ts);
	};

	export
	template<typename tl>
	constexpr int get_size_v = get_size_imp<tl>::value;

	//get index 
	template<typename tl, typename T, int N>
	struct get_index_imp
	{
		static constexpr int get_value() { return -1; }
	};

	template<typename T, int N, typename H, typename... Ts>
	struct get_index_imp<type_list<H, Ts...>, T, N>
	{

		static constexpr int get_value()
		{
			if constexpr (std::is_same_v<T, H>)
			{
				return N - sizeof...(Ts) - 1;
			}
			else
			{
				return get_index_imp<type_list<Ts...>, T, N>::get_value();
			}
		}
	};

	export
	template<typename tl, typename T>
	constexpr int get_index_v = get_index_imp<tl, T, get_size_v<tl>>::get_value();

	//is empty
	template<typename tl>
	struct is_empty_imp
	{
		static constexpr bool value = false;
	};

	template<>
	struct is_empty_imp<type_list<> >
	{
		static constexpr bool value = true;
	};

	export
	template<typename tl>
	constexpr bool is_empty_v = is_empty_imp<tl>::value;

	//is_in
	template<typename T, typename L>
	struct is_in_imp
	{
		static inline constexpr bool value = false;
	};

	template<typename T>
	struct is_in_imp<T, type_list<>>
	{
		static inline constexpr bool value = false;
	};

	template<typename T, typename H, typename ...P>
	struct is_in_imp<T, type_list<H, P...>>
	{
		static inline constexpr bool value = std::conditional_t<
			std::is_same_v<T, H>,
			std::true_type,
			is_in_imp<T, type_list<P...>>
		>::value;
	};

	export
	template<typename T, typename L>
	concept is_in_list = is_in_imp<T, L>::value;



	//merge_list
	template<typename ...P, typename ...Q>
	static type_list<P..., Q...> operator+(type_list<P...> l0, type_list<Q...> l1);

	//// merge_list_t TODO: should use this, bug some how vs2022 doesn't work 
	//
	//	template<typename ...tl>
	//	struct merge_list_imp
	//	{
	//		static_assert((is_type_list<tl>&&...), " shbould be type list");
	//
	//		using type = decltype(( std::declval<type_list<>>() + ... + std::declval<tl>()));
	//	};
	//	template<typename ...tl>
	//	using merge_list_t = merge_list_imp<tl...>::type;
	//// merge_list_t end

	template<typename tls>
	struct merge_list_imp;

	template<>
	struct merge_list_imp<type_list<>>
	{
		using type = type_list<>;
	};

	template<typename tl>
	struct merge_list_imp<type_list<tl>>
	{
		using type = tl;
	};

	template<typename tl0, typename tl1, typename ...tl  >
	struct merge_list_imp<type_list<tl0, tl1, tl...>>
	{
		using head = decltype((tl0{} + tl1{})); //just can't do it with one line , bug?
		using type = decltype((head{} + ... + tl{}));
	};


	export
	template<typename ...tl>
	using merge_list_t = merge_list_imp<type_list<tl...>>::type;


	export
	using empty_type_list = type_list<>;

}


namespace clumsy
{
	/////////////////////For_Each_Type///////////////////////
	template<typename type_holder>
	struct for_each_type;

	export
	template< template <typename ...> typename type_holder, typename ...u>
	struct for_each_type<type_holder<u...>>
	{
		template< typename F, typename ...P>
		static void apply(P&&...p)
		{
			(F::template apply<u>(std::forward<P>(p)...), ...);
		}
	};


	/////////////////////For_Each_In_Range///////////////////////
	template<typename seq >
	struct for_each_index_imp;

	template<size_t ... N>
	struct for_each_index_imp<std::index_sequence< N...>>
	{
		template<typename F, typename ...P>
		static void apply(P&&...p)
		{
			((F:: template apply<N>(std::forward<P>(p)...)), ...);
		}
	};

	export
	template<size_t N>
	using  for_each_index = for_each_index_imp<std::make_index_sequence<N>>;



	/////////////////////For_Each_Type_Enumerate///////////////////////
	template<typename tl, typename sq>
	struct for_each_type_enumerate;

	export
	template<typename ...Ts, template <typename ... > typename type_holder, size_t... Is>
	struct for_each_type_enumerate< type_holder<Ts...>, std::index_sequence<Is... >>
	{
		template<typename F, typename...P>
		static void apply(P&&...p)
		{
			(F::template apply<Is, Ts>(std::forward<P>(p)...), ...); //Is number and Ts nubmer must match!
		}
	};

}
