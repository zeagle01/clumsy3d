
module;

#include <vector>

module  clumsy3d: update_functions;

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

	struct created_with_default_value
	{
		static void apply()
		{

		}
	};

}

