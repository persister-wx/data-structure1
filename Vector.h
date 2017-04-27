#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;

//vector的插入和删除都存在迭代器失效的问题，解决方法将插入和删除的函数
//的参数给成引用，可以达到如下结果：当上述两个函数内部迭代器失效，也会使得
//外部的迭代器也同样失效，那么就要在函数内部将其重置
//-------------------------------------------------------------
//类型萃取
struct __TrueType
{
	bool Get()
	{
		return true;
	}
};

struct __FalseType
{
	bool Get()
	{
		return false;
	}
};

template<class T>
struct TypeTraits
{
	typedef __FalseType __IsPODType;
};

template<>
struct TypeTraits<int>
{
	typedef __TrueType __IsPODType;
};

template<>
struct TypeTraits <char>
{
	typedef __TrueType __IsPODType;
};

template<>
struct TypeTraits<float>
{
	typedef __TrueType __IsPODType;
};

template<>
struct TypeTraits<double>
{
	typedef __TrueType __IsPODType;
};

template<>
struct  TypeTraits <long>
{
	typedef __TrueType __IsPODType;
};


template<class T>
void __Copy(T*& dst, T* const & src, size_t size)
{
	if (TypeTraits<T>::__IsPODType().Get())
	{
		memcpy(dst, src, size* sizeof(T));
	}
	else               
	{
		for (size_t i = 0; i < size; ++i)
		{
			dst[i] = src[i];
		}
	}
}
//-----------------------------------------------------------------------


template<class T>
class Vector
{
public :
	typedef T* Iterator;
	typedef const T* ConstIterator;

	//构造函数
	Vector()
		:_start(NULL)
		, _finish(NULL)
		, _endOfStorage(NULL)
	{}

	Vector(int n, const T& data = T())
		:_start(NULL)
		, _finish(NULL)
		, _endOfStorage(NULL)
	{
		_start = new T[n];
		for (size_t i = 0; i < n; ++i)
		{
			_start[i] = data;
		}
		_finish = _start + n;
		_endOfStorage = _finish;
	}

	//拷贝构造函数
	Vector(const Vector<T>& v)
		:_start(0)
		, _finish(0)
		, _endOfStorage(0)
	{
		//可以分为两种情况：①容量等于size(stl)  ②容量大于size
		size_t size = v.Size();
		_start = new T[size];
 
		/*for (size_t i = 0; i < size; ++i)
		 {
			_start[i] = v._start[i];
		}*/
		__Copy<T>(_start, v._start, size);
		_finish = _start + v.Size();
		_endOfStorage = _finish;	
	}

	size_t Size()const 
	{
		return _finish - _start;
	}

	size_t Capacity()const
	{
		return _endOfStorage - _start;
	}

	void PopBack()
	{
		if (_start)
		{
			--finish;
		}
	}

	Iterator Begin()
	{
		return _start;
	}
	
	ConstIterator Begin()const
	{
		return _start;
	}

	Iterator End()
	{
		return _finish;
	}


	ConstIterator End()const
	{
		return _finish;
	}

	//增容
	void CheckEndOfStorage()
	{
		size_t size = Size();
		if (_finish == _endOfStorage)
		{
			//1.开空间 2.赋值 3.释放旧空间 4.赋值
			Iterator tmp = new T[2 * size + 3];
			for (size_t i = 0; i < size; ++i)
			{
				tmp[i] = _start[i];
			}
			delete[] _start;
			_start = tmp;
			_finish = _start + size;
			_endOfStorage = _start + 2 * size + 3;
		}
	}

	//插入（存在迭代器失效问题）
	void Insert(Iterator& pos,const T& value)
	{
		size_t size = pos - _start;
		size_t oldSize = Size();
		if (pos == End() && _finish < _endOfStorage)//容量足够且尾插
		{
			_start[oldSize] = value;
			++_finish;
		}
		else//不是尾插
		{
			CheckEndOfStorage();
			Iterator it = _finish;
			pos = _start + size;//重置pos
			while (pos != it)
			{
				*it = *(it - 1);
				it--;
			}
			*pos = value;
			++_finish;
		}
	}

	//将参数给成引用可以解决迭代器失效问题
	Iterator Erase(Iterator& pos)
	{
		Iterator end = End();
		Iterator cur = pos;
		while (cur != end)
		{
			*cur = *(cur + 1);
			cur++;
		}
		--_finish;
		pos--;
		return pos;
	}

	T& operator[](size_t index)
	{
		return *(_start + index)
	}

	const T& operator[](size_t index)const
	{
		return *(_start + index)
	}

	//capacity的值在vector中是以1/2来增长的
	void Expand(size_t size)
	{
		size_t capacity = Capacity();
		if (size == capacity)
		{
			capacity = capacity + capacity / 2;
			if (capacity < Size() + 1)
			{
				capacity = Size() + 1;
			}
		}
		_start = new T[capacity];
		_finish = _start + size;
		_endOfStorage = _start + capacity;
	}

	bool Empty()
	{
		return _start == _finish;
	}

	void Print()
	{
		size_t size = Size();
		for (size_t i = 0; i < size; ++i)
		{
			cout << _start[i] << " ";
		}
		cout << endl;
	}

	//析构函数
	~Vector()
	{
		if (_start)
		{
			delete[] _start;
			_start = NULL;
			_finish = NULL;
			_endOfStorage = NULL;
		}
	}

protected :
	Iterator _start;
	Iterator _finish;
	Iterator _endOfStorage;
};



