
module;

#include <vector>

module  clumsy3d: update_functions;

import :component;

import clumsy.matrix;
import clumsy.core;

namespace clumsy
{

	struct assign
	{
		template<typename d,typename s>  
		static void apply(d& p_d, const s& p_s)
		{
			p_d = p_s;
		}
	};

	struct get_last
	{
		static void apply(std::vector<uint64_t>& id, const std::vector<uint64_t>& all_entities, empty)
		{
			static uint64_t offset = 0;
			auto size = all_entities.size();
			id = { all_entities[offset % size] };
			offset++;
		}
	};

	struct set_sync_pair
	{
		static void apply(std::vector<directed_edge>& edges, const std::vector<uint64_t>& all_entities, empty)
		{
			if (all_entities.size() > 1)
			{
				edges = { directed_edge{ all_entities.front(),all_entities.back() } };
			}
		}
	};

	struct build_triangle
	{
		static void apply(std::vector<vec3f>& pos, std::vector<vec3i>& tri, empty )
		{
			static float offset = 0.f;
			pos =
			{
				{0 + offset,0,0},
				{1 + offset,0,0},
				{1 + offset,1,0}
			};
			offset -= 0.1f;

			tri = { { 0,1,2 } };
		}
	};

	struct offsetting_pos
	{
		static void apply(std::vector<vec3f>& pos_out, const std::vector<vec3f>& pos_in,empty)
		{
			vec3f center = {};
			for (int i = 0; i < pos_in.size(); i++)
			{
				center += pos_in[i];
			}

			vec3f center_out = {};
			for (int i = 0; i < pos_out.size(); i++)
			{
				center_out += pos_out[i];
			}
			auto offset = vec3f{ 0,0,0 };
			for (int i = 0; i < pos_out.size(); i++)
			{
				pos_out[i] += center - center_out + offset;
			}
		}
	};


}

