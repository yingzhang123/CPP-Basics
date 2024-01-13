#include<iostream>

//======================================================= 3.C++ 类模板 实现vector  空间配置器allocator  继续添加迭代器功能  迭代器失效问题  =====================================

// 自定义空间配置器  定义容器的空间配置器，和C++标准库的allocator实现一样
template<typename T>
class Allocator
{
public:
	T* allocate(size_t size)  // 负责内存开辟
	{
		return (T*)malloc(sizeof(T) * size);
	}

	void deallocate(void* p)  // 负责内存释放
	{
		free(p);
	}

	void construct(T* p, const T& val)  //负责对象构造
	{
		new (p) T(val);   // 定位new，在指定的内存上去构造一个值为val的对象
	}

	void destroy(T* p)         // 负责对象析构
	{
		p->~T();             // ~T() 代表了T类型的析构函数
	}
};

/*
容器底层内存开辟，内存释放，对象构造和析构，都通过allocator空间配置器实现
*/
template<typename T = int, typename Alloc = Allocator<T>>
class vector
{
public:
	//vector(int size=10,const Alloc& alloc = Allocator<T>())    // 也可以让用户传进来,不传使用默认的Allocator<T>
	//	:_allocator(alloc)

	vector(int size = 10)      // 
	{
		// 需要把内存开辟和对象构造分开处理  [new运算符把这两步一起做了，会自动构造数组大小个数的对象，尽管这些对象不是我，我们想要的]
		//_first = new T[size];
		_first = _allocator.allocate(size);  // 10个元素对象  开辟内存空间
		_last = _first;
		_end = _first + size;
	}

	~vector()
	{
		// 析构容器有效的元素，然后释放_first指针直线的堆内存  [delete]
		//delete[]_first;

		for (T* p = _first; p != _last; ++p)   // 把_first指针指向的数组的有效元素进行析构操作
		{
			_allocator.destroy(p);
		}
		_allocator.deallocate(_first);   //释放堆上的数组内存
		_first = _last = _end = nullptr;
	}

	vector(const vector<T>& other)
	{
		int size = other._end - other._first;
		//_first = new T[size];
		_first = _allocator.allocate(size);
		int len = other._last - other._first;
		for (int i = 0; i < len; ++i)
		{
			//	_first[i] = other._first[i];
			_allocator.construct(_first + i, other._first[i]);
		}
		_last = _first + len;
		_end = _first + size;
	}

	vector<T>& operator=(const vector<T>& other)
	{
		if (this == &other)
			return *this;

		//delete[]_first;
		for (T* p = _first; p != _last; ++p)   // 把_first指针指向的数组的有效元素进行析构操作
		{
			_allocator.destroy(p);
		}
		_allocator.deallocate(_first);         //释放堆上的数组内存

		int size = other._end - other._first;
		//_first = new T[size];
		_first = _allocator.allocate(size);
		int len = other._last - other._first;
		for (int i = 0; i < len; ++i)
		{
			//	_first[i] = other._first[i];
			_allocator.construct(_first + i, other._first[i]);
		}
		_last = _first + len;
		_end = _first + size;

		return *this;
	}


	void push_back(const T& val)   // 向容器末尾添加元素
	{
		if (full())
		{
			expand();
		}
		//*_last++ = val;   // 先赋值 指针加1
		_allocator.construct(_last, val);   // _last指针指向的内存构造一个值为val的对象
		_last++;
	}

	void pop_back()      // 从容器末尾删除容器
	{
		if (empty())
		{
			return;
		}
		// erase(it);   ===>  verify(it._ptr,_last);
		// insert(it,val)    ===> verify(it._ptr,_last)
		verify(_last - 1, _last);
		//--_last;
		--_last;         // 不仅要把_last指针--，还要析构删除的元素
		_allocator.destroy(_last);
	}

	T back()const   //返回容器末尾得元素的值
	{
		if (empty())
		{
			// 返回一个默认值或抛出异常，以表示容器为空
			throw std::out_of_range("Vector is empty");
		}
		return *(_last - 1);
	}


	bool full() const { return _last == _end; }
	bool empty() const { return _first == _last; }
	int size() const { return _last - _first; }

	T& operator[](int index)  // 重载下标运算符 vec[2]
	{
		if (index < 0 || index >= size())
		{
			throw "OutOfRangeException";
		}
		return _first[index];
	}

	// 1.迭代器一般实现为容器的嵌套类型    （迭代器一般是用来遍历容器的）  
	class iterator
	{
	public:
		friend class vector<T, Alloc>;  //友元类
		iterator(vector<T,Alloc> *pvec = nullptr,T* ptr=nullptr)          //新生成当前容器某一个位置元素的迭代器
			:_ptr(ptr)
			,_pVec(pvec)
		{
			Iterator_Base* itb = new Iterator_Base(this, _pVec->_head._next);       // 相当于头插法！！！
			_pVec->_head._next = itb;
		}
		
		bool operator!=(const iterator& it) const
		{
			//检查迭代器的有效性
			if (_pVec == nullptr || _pVec != it._pVec)
			{
				throw "iterator incompatable!";
				return false;
			}
			return _ptr != it._ptr;
		}

		void operator++()
		{
			// 检查迭代器的有效性
			if (_pVec == nullptr)
			{
				throw "iterator invalid！";
			}
			_ptr++;   // 指针++
		} 

		T& operator*()    // 可读可修改   非 const 对象  
		{ 
			// 检查迭代器的有效性
			if (_pVec == nullptr)
			{
				throw "iterator invalid！";
			}
			return *_ptr;
		}            
		const T& operator*() const    // 返回值也被const（可读，但是不能修改） * it = 20;    报错！！！     const 对象
		{ 
			// 检查迭代器的有效性
			if (_pVec == nullptr)
			{
				throw "iterator invalid！";
			}
			return *_ptr; 
		}  
		// T& operator*() const { return *_ptr; }  //  这个声明实际上是不合法的，因为它试图在 const 限定的成员函数内部具有非常量运算符。这看起来像一个拼写错误或者是一个不太明显的错误。编译器可能会报错。
	private:
		T* _ptr;    // 迭代器指向容器的某个元素，其实是迭代器的指针指向容器这个底层数组的某一个位置
		// 当前迭代器迭代的是哪个容器
		vector<T, Alloc>* _pVec;
	};

	// 2.需要给容器提供begin和end方法
	iterator begin() { return iterator(this,_first); }
	iterator end() {return iterator(this,_last); }

	// 检查迭代器失效       迭代器失效方法
	void verify(T* first, T* last)
	{
		Iterator_Base* pre = &this->_head;
		Iterator_Base* it = this->_head._next;
		while (it != nullptr)
		{
			if (it->_cur->_ptr > first && it->_cur->_ptr <= last)
			{
				// 迭代器失效，把iterator持有的容器指针置为nullptr
				it->_cur->_pVec = nullptr;
				// 删除当前结点，继续判断后面的迭代器节点是否失效
				pre->_next = it->_next;
				delete it;
				it = pre->_next;
			}
			else
			{
				pre = it;
				it = it->_next;
			}
		}
	}

	// 自定义vector容器insert方法的实现
	iterator insert(iterator it, const T& val)
	{
		/*  
		1.不考虑扩容      verify(_first, _last);
		2.不考虑it._ptr的指针合法性     《===== 为了简单
		*/
		verify(it._ptr - 1, _last);
		T* p = _last;
		while (p > it._ptr)
		{
			_allocator.construct(p, *(p - 1));
			_allocator.destroy(p - 1);
			p--;
		}
		_allocator.construct(p, val);
		_last++;
		return iterator(this, p);
	}

	iterator erase(iterator it)
	{
		verify(it._ptr - 1, _last);
		T* p = it._ptr;
		while (p < _last-1)
		{
			_allocator.destroy(p);
			_allocator.construct(p, *(p + 1));
			p++;
		}
		_allocator.destroy(p);
		_last--;
		return iterator(this, it._ptr);
	}

private:
	T* _first;      // 指向数组起始的位置
	T* _last;       // 指向数组中有效元素的后继位置
	T* _end;        // 指向数组空间的后继位置

	Alloc _allocator;     //定义容器的空间配置器对象

	// 容器迭代器失效增加代码
	struct Iterator_Base
	{
		Iterator_Base(iterator* c = nullptr, Iterator_Base* n = nullptr)
			:_cur(c)
			,_next(n)
		{

		}

		iterator* _cur;         // 维护某个迭代器的指针
		Iterator_Base* _next;   // 链表：保存容器哪个元素的迭代器
	};
	Iterator_Base _head;

	void expand()   // 容器的二倍扩容
	{
		int size = _end - _first;   //原来容器大小
		//T* ptmp = new T[size * 2];
		T* ptmp = _allocator.allocate(size * 2);

		for (int i = 0; i < size; i++)
		{
			//ptmp[i] = _first[i];
			_allocator.construct(ptmp + i, _first[i]);
		}
		// delete[]_first;
		for (T* p = _first; p != _last; ++p)
		{
			_allocator.destroy(p);
		}
		_allocator.deallocate(_first);

		_first = ptmp;
		_last = _first + size;
		_end = _first + (size * 2);
	}
};


// 在C++中，指针的 + 1 操作并不是简单的将指针的值加 1，而是基于指针指向的类型进行增加。具体而言， + 1 操作会使指针向前移动一个存储单元的大小，即增加一个偏移，这个偏移是由指针的类型确定的

int main04()
{
	vector<int> vec(200);
	for (int i = 0; i < 20; i++)
	{
		vec.push_back(rand() % 100);
	}
	for (int ch : vec)
	{
		std::cout << ch << " ";
	}
	std::cout << std::endl;

	auto it = vec.begin();
	while (it != vec.end())
	{
		if (*it % 2 == 0)
		{
			it = vec.erase(it);
		}
		else
		{
			++it;
		}
	}


	for (int ch : vec)
	{
		std::cout << ch << " ";
	}
	std::cout << std::endl;
#if 0
	auto it = vec.begin();
	for (; it != vec.end(); ++it)
	{
		if (*it % 2 == 0)
		{
			it = vec.insert(it, (*it - 1));
			++it;      // 更新2次
		}
	}

	for (int ch : vec)
	{
		std::cout << ch << " ";
	}
	std::cout << std::endl;
#endif



#if 0
	//使用[]遍历       // 针对vector数组有用
	int size = vec.size();
	for (int i = 0; i < size; i++)
	{
		std::cout << vec[i] << " ";
	}
	std::cout << std::endl;

	// 使用迭代器遍历
	vector<int>::iterator it = vec.begin();   // auto it = vec.begin();
	for (; it != vec.end(); ++it)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;


	for (int ch : vec)  // 其底层原理，就是通过容器的迭代器来实现容器遍历的
	{
		std::cout << ch << " ";
	}
	std::cout << std::endl;
#endif
	return 0;
}