#pragma once

#ifndef CIRCULAR_BUFFER_H__
#define CIRCULAR_BUFFER_H__

#include <array>
#include <forward_list>
#include "RWLock.h"

namespace liuw
{
	template <typename T, int N>
	class Circular_buffer 
	{
	public:
		Circular_buffer()
			: m_pos(0) { }
		std::forward_list<T>& get();
		int set(T&&);
		linduo::RWLock& getLock() { return m_Lock; }
	private:
		std::array<std::forward_list<T>, N> m_container;
		int m_pos;		//正在访问的位置
		linduo::RWLock m_Lock;
	};

	template <typename T, int N>
	std::forward_list<T>& Circular_buffer<T, N>::get()
	{
		int oldPos = m_pos;
		m_pos = m_pos + 1 >= N ? 0 : m_pos + 1;

		return m_container[oldPos];
	}

	template <typename T, int N>
	int Circular_buffer<T, N>::set(T&& task)
	{
		linduo::WriteGuard lg(m_Lock);
		m_container[m_pos].push_front(std::forward<T>(task));

		return 0;
	}
}


#endif