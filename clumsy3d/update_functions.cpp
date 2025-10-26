
module;

#include <vector>

module  clumsy3d: update_functions;

import :component;

import clumsy.matrix;
import clumsy.core;

namespace clumsy
{

	struct do_nothing
	{
		static void apply(...) 
		{
		}
	};


	struct get_last
	{
		static void apply(std::vector<uint64_t>& id, const std::vector<uint64_t>& all_entities )
		{
			static uint64_t offset = 0;
			auto size = all_entities.size();
			id = { all_entities[offset % size] };
			offset++;
		}
	};

	struct set_sync_pair
	{
		static void apply(std::vector<directed_edge>& edges, const std::vector<uint64_t>& all_entities )
		{
			if (all_entities.size() > 1)
			{
				edges = { directed_edge{ all_entities.front(),all_entities.back() } };
			}
		}
	};

	struct build_triangle
	{
		static void apply(std::vector<vec3f>& pos, std::vector<vec3i>& tri )
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
		static void apply(std::vector<vec3f>& pos_out, const std::vector<vec3f>& pos_in)
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



	struct compute_plane
	{
		static void apply(std::vector<vec3f>& pos, std::vector<vec3i>& tri, int nx, int ny, float lx, float ly)
		{
			printf(" compute plane %d %d %f %f ...\n", nx, ny, lx, ly);

			int vert_nx = nx + 1;
			int vert_ny = ny + 1;

			int v_num = vert_nx  * vert_ny;
			int t_num = nx * ny * 2;

			pos.clear();
			pos.reserve(v_num);

			tri.clear();
			tri.reserve(t_num);


			float dx = lx / nx;
			float dy = ly / ny;

			for (int i = 0; i < vert_nx; i++)
			{
				for (int j = 0; j < vert_ny; j++)
				{
					pos.push_back({ dx * i, dy * j, 0 });
				}
			}

			for (int i = 0; i < nx; i++)
			{
				for (int j = 0; j < ny; j++)
				{
					int v0 = i * vert_ny + j;
					int v1 = i * vert_ny + j + 1;
					int v2 = (i + 1) * vert_ny + j + 1;
					int v3 = (i + 1) * vert_ny + j;

					tri.push_back({ v0,v1,v2 });
					tri.push_back({ v0,v2,v3 });
				}
			}
			pos.shrink_to_fit();
			tri.shrink_to_fit();

		}

	};



}

