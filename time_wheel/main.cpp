#include <iostream>
#include "time_wheel.h"

int main()
{
    std::cout << "Hello World!\n"; 
	liuw::Time_wheel<int, 5> buffer;

	buffer.loop();

	std::thread t([&buffer]() {
		int i = 0;
		while (1)
		{
			buffer.set(i++);

			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		}
	});

	t.join();
}
 
