
module;

#include <memory>

export module clumsy.render;

namespace clumsy
{
	export class renderer
	{
	public:
		renderer();
		~renderer();
	public:
		void set_window(void* window);
		void load_glad(void* proc_addr);
		
	private:
		struct imp;
		std::unique_ptr<imp> m_imp;
	};

}
