module ;

#include <iostream>

module clumsy3d;

import event_driver;

import clumsy.render;

namespace clumsy
{
	void app::run()
	{
		event_driver event_driver;


		event_driver.init(800, 600);

		renderer renderer;

		renderer.set_window(event_driver.get_window_ptr());
		renderer.load_glad(event_driver.get_proc_address());

		event_driver.set_update_callback
		(
			[](auto x, auto y)
			{
				printf("mouse at: %f %f \n", x, y);
			}
		);

		event_driver.run_event_loop();
	}
}
