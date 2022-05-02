#pragma once
#include<cassert>
#include<string>
#include <iostream>
using namespace std;

template<class T>
class Stack
{
public:
	Stack()
		:_a(NULL)
		, _size(0)
		, _capacity(0)
	{}

	~Stack()
	{
		if (_a)
		{
			delete[] _a;
			_a = NULL;
		}
	}
	void Push(const T& x)//压栈
	{
		_Checkcapacity();
		_a[_size] = x;
		_size++;
	}

	void Pop()//出栈
	{
		assert(_size > 0);
		--_size;
	}
	size_t Size()
	{
		return _size;
	}
	bool Empty()//判断栈是否为空
	{
		return _size == 0;
	}
	T& Top()//显示栈顶元素
	{
		assert(_size > 0);
		return _a[_size-1];
	}
	void _Checkcapacity()
	{
		if (_size >= _capacity)
		{
			size_t newCapacity = _capacity == 0 ? 3 : _capacity * 2;
			T* tmp = new T[newCapacity];
			for (size_t i = 0; i < _size; ++i)
			{
				tmp[i] = _a[i];
			}

			delete[] _a;
			_a = tmp;
			_capacity = newCapacity;
		}
	}
protected:
	T* _a;
	size_t _size;
	size_t _capacity;
};
