
module;

#include <set>
#include <array>
#include <vector>

module clumsy3d:entity_relation_functions;

import :entity_relation;

import clumsy.core;

namespace clumsy
{

	////////////////
	template<typename tag>
	struct get_range;

	template<>
	struct get_range<entity_range::none>
	{
		template<typename entity_system>
		static std::vector<uint64_t> apply(const entity_system& p_entity_system)
		{
			return {};
		}

	};

	template<typename ...T>
	struct get_range<entity_range::entity_has<T...>>
	{
		template<typename entity_system>
		static std::vector<uint64_t> apply(const entity_system& p_entity_system)
		{
			return {};
		}

	};

	template<typename T>
	struct get_range<entity_range::value_of<T>>
	{
		template<typename entity_system>
		static std::vector<uint64_t> apply(const entity_system& p_entity_system)
		{
			return {};
		}

	};

	template<int N>
	struct get_range<entity_range::crated<N>>
	{
		template<typename entity_system>
		static std::vector<uint64_t> apply(entity_system& p_entity_system)
		{
			return {};
		}

	};

	template<typename  T>
	struct get_range<entity_range::sender_of_edge<T>>
	{
		template<typename entity_system>
		static std::vector<uint64_t> apply(const entity_system& p_entity_system)
		{
			return {};
		}
	};

	template<typename  T>
	struct get_range<entity_range::receiver_of_edge<T>>
	{
		template<typename entity_system>
		static std::vector<uint64_t> apply(const entity_system& p_entity_system)
		{
			return {};
		}

	};
	


//	////////////////
//	template<typename tag> 
//	struct get_index_map;
//
//	template<>
//	struct get_index_map<index_map::create_one>
//	{
//
//		template<typename entity_system>
//		static uint64_t apply(const entity_system& p_entity_system)
//		{
//			return ids[slot];
//		}
//	};

//	template<>
//	struct get_index_map<index_map::one_to_one>
//	{
//		static uint64_t apply(int slot, const std::vector<uint64_t>& ids)
//		{
//			return ids[slot];
//		}
//	};
//
//	template<>
//	struct get_index_map<index_map::all_to_one>
//	{
//		static const std::vector<uint64_t>& apply(int slot, std::vector<uint64_t>& ids)
//		{
//			return ids;
//		}
//	};

}




