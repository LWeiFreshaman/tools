#pragma once
#ifndef TIME_WHEEL_H__
#define TIME_WHEEL_H__

#include "circular_buffer.h"
#include <thread>
#include <iostream>
#include <chrono>

namespace liuw
{
	template <typename T, int N>
	class Time_wheel
	{
	public:
		Time_wheel(int loopTime = 5 * 60)
			: m_loopTime(loopTime), b_stop(false) { }

		std::forward_list<T> get()
		{
			std::forward_list<T> result;
			
			linduo::ReadGuard rg(m_buffer.getLock());
			result.swap(m_buffer.get());

			return result;
		}

		int set(T&& task)
		{
			return m_buffer.set(std::forward<T>(task));
		}

		void loop()
		{
			std::thread t([this]() { 
				while (!b_stop)
				{
					auto taskList = get();
					for (auto i : taskList)
					{
						std::cout << i << " ";
					}
					std::cout << std::endl;

					std::this_thread::sleep_for(std::chrono::seconds(5));
				}
			});

			t.detach();
		}

	private:
		Circular_buffer<T, N> m_buffer;
		int m_loopTime;		//µ•Œª √Î
		int b_stop;
	};
}

#endif