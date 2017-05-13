#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include <assert.h>
using namespace std;
#include<vector>

template<class T>
struct Less
{
	bool operator()(T& left,T& right)
	{
		return left < right;
	}
};

template<class T>
struct Greater
{
	bool operator()(T& left, T& right)
	{
		return left > right;
	}
};

template<class T, class Compare = Greater<T> >
class Heap
{
public:
	Heap()
	{}

	Heap(const T* a, size_t n)
	{
		_v.reserve(n);//可以提高效率
		for (size_t i = 0; i < n; ++i)
		{
			_v.push_back(a[i]);
		}

		//建堆
		for (int i = ((int)_v.size() - 2) >> 1; i >= 0; --i)
		{
			AjustDown(i);
		}
	}
	
	void Push(const T& data)
	{
		_v.push_back(data);
		AdjustUp(_v.size() - 1);
	}

	void Pop()
	{
		//1。先将堆顶元素与堆的最后一个元素交换
		swap(_v[0], _v[_v.size() - 1]);
		//2.删除掉最后一个节点
		_v.pop_back();
		//3.向下调整
		AjustDown(0);
	}

	bool Empty()
	{
		return _v.empty();
	}

	size_t Size()
	{
		return _v.size();
	}

	bool IsMaxHeap()
	{
		int len = (_v.size() - 2) / 2;

		for (int parent = 0; parent < len; ++parent)
		{
			int left = parent * 2 + 1;
			int right = parent * 2 + 2;
			if (left < len && _v[left] > _v[parent])
			{
				return false;
			}
			if (right < len && _v[right] > _v[parent])
			{
				return false;
			}
		}
		return true;
	}

	T& Top()
	{
		assert(_v.size() > 0);
		return _v[0];
	}

	void Sort()
	{
		size_t len = _v.size();
		int i = 0;
		for (int j = len - 1 - i; j >= 0;)
			{
				i++;
				swap(_v[0], _v[j]);
				j--;
				AjustDown(0,j);
			}
	}

protected:
	//向上调整算法
	void AdjustUp(int index)
	{
		int child = index;
		int parent = (child - 1) >> 1;
		while (child > 0)
		{
			if (Compare()(_v[parent],_v[child]))
			{
				break;
			}
			else
			{
				swap(_v[child], _v[parent]);
				child = parent;
				parent = (child - 1) >> 1;
			}
		}

	}

	//向下调整
	void AjustDown(int root)
	{
		int parent = root;
		int child = parent * 2 + 1;//默认是左孩子
		while (child < _v.size())
		{
			if (child + 1 < _v.size() && Compare()(_v[child + 1], _v[child]))
			{
				child++;//保证child是最大的孩子节点
			}
			if (Compare()(_v[child],_v[parent]))
			{
				swap(_v[child], _v[parent]);//交换父节点和孩子节点
				parent = child;
				child = parent * 2 + 1;
			}
			else//不用交换：说明已经是最大的堆了
			{
				break;
			}
		}
	}


	//向下调整
	void AjustDown(int root,int dest)
	{
		int parent = root;
		int child = parent * 2 + 1;//默认是左孩子
		while (child <= dest)
		{
			if (child + 1 < dest && Compare()(_v[child + 1], _v[child]))
			{
				child++;//保证child是最大的孩子节点
			}
			if (Compare()(_v[child], _v[parent]))
			{
				swap(_v[child], _v[parent]);//交换父节点和孩子节点
				parent = child;
				child = parent * 2 + 1;
			}
			else//不用交换：说明已经是最大的堆了
			{
				break;
			}
		}
	}

private:
	vector<T> _v;
};

#define N 1000
#define k 10

void AdjustDown(int* arr, int len ,int i)
{
	int parent = i;
	int child = 2 * parent + 1;
	while (child < len)
	{
		if (child + 1 < len && arr[child + 1] < arr[child])
		{
			++child;
		}
		if (arr[child] < arr[parent])
		{
			swap(arr[child], arr[parent]);
			parent = child;
			child = 2 * parent + 1;
		}
		else
		{
			break;
		}
	}
}


void Topk()
{
	int arr[N];
	int res[k];
	for (size_t i = 0; i < N; ++i)
	{
		arr[i] = rand() % N;
	}

	//验证topk问题
	/*arr[999] = N + 10;
	arr[898] = N + 23;
	arr[766] = N + 46;
	arr[3] = N + 59;
	arr[310] = N + 29;
	arr[19] = N + 58;
	arr[20] = N + 40;
	arr[209] = N + 12;
	arr[58] = N + 60;
	arr[334] = N + 14;*/

	//1.建一个小堆
	Heap<int, Less<int> > hp;
	for (size_t index = 0; index < k; ++index)
	{
		res[index] = arr[index];
	}

	//向下调整
	for (int i = (k - 2) / 2; i >= 0; --i)
	{
		AdjustDown(res, k, i);
	}

	//找出k个最大的数据
	for (size_t j = k; j < N; ++j)
	{
		if (res[0] < arr[j])
		{
			res[0] = arr[j];
			AdjustDown(res, k, 0);
		}
	}

	for (int j = 0; j < k; ++j)
	{
		cout << res[j] << " ";
	}
	cout << endl;
}


