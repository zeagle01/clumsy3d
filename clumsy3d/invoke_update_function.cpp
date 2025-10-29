module;

#include <utility>
#include <concepts>
#include <vector>
#include <functional>
#include <stdint.h>

module clumsy3d:invoke_update_function;

import :common_structs;

import clumsy.core;

namespace clumsy
{



	//////////////////////
	struct functor_forward
	{
		template<typename F, typename entity_system, typename ...P>
		static void apply(entity_system& p_entity_system, P&& ...p)
		{
			if constexpr (requires { F::apply(p_entity_system, std::forward<P>(p)...); })
			{
				F::apply(p_entity_system, std::forward<P>(p)...);
			}
			else
			{
				F::apply(std::forward<P>(p)...);
			}

		}
	};



	//////////////////////
	using triggerer = std::function<bool()>;

	template<typename out_list, typename in_list, typename out_rng, typename in_rng, typename param_pack_out, typename param_pack_in, typename entity_system >
	struct invoke_update_function;

	template< typename in_list, typename out_rng, typename in_rng, typename param_pack_out, typename param_pack_in, typename entity_system, typename ...out_cpn>
	struct invoke_update_function<type_list<out_cpn...>, in_list, out_rng, in_rng, param_pack_out, param_pack_in, entity_system >
	{
		using out_list = type_list<out_cpn...>;

		template<typename F, typename ...P >
		static void apply(entity_system& p_entity_system,  triggerer trig, P&&...p)
		{
			with_in_out_list < in_list > ::template apply<F>(p_entity_system, trig, std::forward<P>(p)...);
		}
	private:
		template<typename in_list_t>
		struct with_in_out_list;

		template< typename ...in_cpn>
		struct with_in_out_list<type_list<in_cpn...>>
		{
			template<typename F, typename ...P >
			static void apply(entity_system& p_entity_system,  triggerer& trig, P&&...p)
			{
				imp2<param_pack_out, param_pack_in>::template apply<F>(p_entity_system, trig, std::forward<P>(p)...);
			}

		private:

			template<typename param_pack_t>
			struct create_or_get_value;

			template< >
			struct create_or_get_value<param_pack::as_each>
			{

				template<typename cpn >
				static auto& apply(int sloti, const std::vector<uint64_t>& ids, entity_system& p_entity_system)
				{
					auto id = ids[sloti];
					if (!p_entity_system.contains<cpn>(id))
					{

						if (!p_entity_system.contains(id))
						{
							auto new_id = p_entity_system.add_entity();
							if (new_id != id)
							{
								printf("wrong !\n");
							}
						}

						if constexpr (std::is_same_v<std::decay_t<decltype(cpn::init_value)>, empty>)
						{
							p_entity_system.add_component<cpn>(id);
						}
						else
						{
							p_entity_system.add_component<cpn>(id, cpn::init_value);
						}
					}
					return p_entity_system.get_component_to_modify<cpn>(id);

				}

			};

			template< >
			struct create_or_get_value<param_pack::as_whole>
			{

				template<typename cpn >
				static auto apply(int sloti, const std::vector<uint64_t>& ids, entity_system& p_entity_system)
				{
					std::vector<typename cpn::type*>  ret;
					for (int i = 0; i < ids.size(); i++)
					{
						auto& v = create_or_get_value<param_pack::as_each>::template apply<cpn>(i, ids, p_entity_system);
						ret.push_back(&v);
					}

					return ret;
				}
			};

			template<typename param_pack_t>
			struct get_values;

			template<>
			struct get_values<param_pack::as_whole>
			{
				template<typename cpn, typename entity_system>
				static auto apply(int sloti, const std::vector<uint64_t>& ids, entity_system& p_entity_system)
				{
					std::vector<cpn::type>  ret;
					for (auto id : ids)
					{
						ret.push_back(p_entity_system.get_component<cpn>(id));
					}
					return ret;
				}
			};

			template<>
			struct get_values<param_pack::as_each>
			{
				template<typename cpn, typename entity_system>
				static const auto& apply(int sloti, const std::vector<uint64_t>& ids, entity_system& p_entity_system)
				{
					auto id = ids[sloti];
					return p_entity_system.get_component<cpn>(id);
				}
			};


			template<typename param_pack_t>
			struct loop_out_put_param;

			template<>
			struct loop_out_put_param<param_pack::as_whole>
			{

				template< typename entity_system >
				static void apply(entity_system& p_entity_system, int id_num, std::function<void(int sloti)> fn)
				{
					fn(0);
				}
			};

			template<>
			struct loop_out_put_param<param_pack::as_each>
			{

				template< typename entity_system >
				static void apply(entity_system& p_entity_system, int id_num, std::function<void(int sloti)> fn)
				{
					for (int i = 0; i < id_num; i++)
					{
						fn(i);
					}
				}

			};
			



		private:

			template<typename para_pack_out, typename para_pack_in>
			struct imp2
			{

				template<typename F, typename ...P >
				static void apply(entity_system& p_entity_system, triggerer& trig, P&&...p)
				{
					auto in_entities = in_rng::template apply<in_cpn...>(p_entity_system);
					std::vector<uint64_t> out_entities;

					if constexpr (requires { out_rng::template apply<out_cpn...>(p_entity_system,in_entities); })
					{
						out_entities = out_rng::template apply<out_cpn...>(p_entity_system, in_entities);
					}
					else
					{
						out_entities = out_rng::template apply<out_cpn...>(p_entity_system);
					}

					if (out_entities.empty())
					{
						return;
					}

					if (trig())
					{
						auto fn = [&](int i)
						{
							functor_forward::apply<F>(p_entity_system, create_or_get_value<para_pack_out>::template apply<out_cpn>(i, out_entities, p_entity_system)..., get_values<param_pack_in>::template apply<in_cpn>(i, in_entities, p_entity_system)..., std::forward<P>(p)...);
						};
						loop_out_put_param<param_pack_out>::template apply(p_entity_system, out_entities.size(), fn);
					}

				}

			};
			


		};

	};


}