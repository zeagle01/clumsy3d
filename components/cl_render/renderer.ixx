
module;

#include <memory>
#include <array>

export module clumsy.render;

namespace clumsy
{
	export class renderer
	{
	public:
		renderer();
		~renderer();
	public:
		void init(void* window, void* proc_addr);

	public:
		void clear_screen();
		void add_triangles(const float* x, const int* triangles, int vNum, int tNum, float* vp);
		void add_triangles(const float* x, const int* triangles, int vNum, int tNum, float* vp, const std::array<float, 3>& color);
		
	private:
		struct imp;
		std::unique_ptr<imp> m_imp;
	};

}
