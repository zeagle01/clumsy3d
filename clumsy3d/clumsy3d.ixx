
module ;

#include <memory>

export module clumsy3d;

namespace clumsy
{
	export class app
	{
	public:
		app();
		~app();
	public:

		void run();
	private:
		class imp;
		std::unique_ptr<imp> m_imp;
	};
}
