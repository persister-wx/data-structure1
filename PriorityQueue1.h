#pragma once
#include"Heap1.h"

template<class T>
class PriorityQueue
{
public:
	PriorityQueue()
	{}

	void Push(const T& data)
	{
		hp.Push(data);
	}

	void Pop()
	{
		hp.Pop();
	}

	bool Empty()
	{
		return hp.Empty();
	}

	T& Top()
	{
		return hp.Top();
	}

	size_t Size()
	{
		return hp.Size();
	}

private:
	Heap<T> hp;
};
