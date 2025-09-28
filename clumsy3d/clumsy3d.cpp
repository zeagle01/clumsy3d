module ;

#include <iostream>

module clumsy3d;

import event_driver;

namespace clumsy
{
	void app::run()
	{
		event_driver event_driver;

		event_driver.init(800, 600);
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
