
module;

#include <functional>
#include <memory>

export module event_driver;


namespace clumsy
{
	export class event_driver
	{
	public:
		event_driver();
		~event_driver();
	public:
		void init(int width, int height);
		void run_event_loop();

	public:
		void set_update_callback(std::function<void(double, double)> fn);

	public:
		static void* get_proc_address();
		void* get_window_ptr();

	private:
		class imp;
		std::unique_ptr<imp> m_imp;
	};

}