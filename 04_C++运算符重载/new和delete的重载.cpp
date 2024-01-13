#include<iostream>

/*
 运算符的重载：成员方法、全局方法
 内存池      进程池     线程池       连接池       对象池
*/

// 对象池
template<typename T>
class Queue
{
public:
	Queue()
	{
		_front = _rear = new QueueItem();   // 头节点
	}
	~Queue()
	{
		QueueItem *cur = _front;
		while (cur !=nullptr)
		{
			_front = _front->_next;
			delete cur;
			cur = _front;
		}
	}

	void push(const T& val)   //入队操作
	{
		QueueItem *item = new QueueItem(val);
		_rear->_next = item;
		_rear = item;
	}

	void pop()   //出队操作
	{
		if (empty())
			return;
		QueueItem *first = _front->_next;
		_front-> _next = first->_next;
		if (_front->_next == nullptr)
		{
			_rear = _front;
		}
		delete first;
	}

	T front()const
	{
		return _front->_next->_data;
	}

	bool empty()const
	{
		return _front == _rear;
	}


private:
	struct QueueItem
	{
		QueueItem(T data = T())
			:_data(data)
			, _next(nullptr)
		{}

		void* operator new(size_t size)
		{
			// 如果还没有申请内存空间
			if (_itemPool == nullptr)
			{
				_itemPool = (QueueItem*)new char[POOL_ITEM_SIZE*sizeof(QueueItem)];   //按字节开辟内存空间
				QueueItem *p = _itemPool;
				for (;p < _itemPool + POOL_ITEM_SIZE -1 ; ++p)
				{
					p->_next = p + 1;
				}
				p->_next = nullptr;
			}
			QueueItem* p = _itemPool;
			_itemPool = _itemPool->_next;
			return p;
		}

		void operator delete(void *ptr)
		{
			QueueItem* p = (QueueItem*)ptr;
			p->_next = _itemPool;
			_itemPool = p;
		}

		T _data;
		QueueItem *_next;
		static QueueItem* _itemPool;
		static const int POOL_ITEM_SIZE = 100000;
	};

	QueueItem *_front;   //指向头节点
	QueueItem *_rear;    // 指向最后一个节点
};

template<typename T>
typename Queue<T>::QueueItem* Queue<T>::QueueItem::_itemPool = nullptr;

int main()
{
	Queue<int> que;
	for (int i = 0; i < 1000000; ++i)
	{
		//短时间内大量调用new和delete  ==> malloc/free
		que.push(i);                           
		que.pop();
	}
	std::cout << que.empty() << std::endl;

}


#if 0
//==================================================================== 深入理解new和delete运算符的原理 ======================================================================
/*
1.malloc和new的区别？
a.malloc是按字节开辟内存空间的，new开辟内存时需要指定类型,例如new int(10)
	所以malloc开辟内存返回的都是void*              operator new ->int* 

b.malloc值负责内存空间，new不仅仅有malloc的功能，可以进行数据的初始化 new int(20);    new int[20]();  
	                                      
c.malloc开辟内存失败返回nullPtr指针；new抛出的是bad_alloc类型的是异常

2.free和delete的区别
delete p:调用析构函数；再free(p);


new -> operator new（）重载函数的调用
delete -> operator delete()重载函数的调用

new和delete能混用吗？C++为什么区分单个元素和数组的内存分配和释放呢？
new delete
new[]  delete[]
对于普通的编译器内置类型（int,long,double....） new/delete[]   new[]/delete    可以混用，没问题

自定义的类类型，有析构函数，为了调用正确的析构函数，那么开辟对象数组的时候，会多开辟4个字节，记录对象的个数    所以此时new和delete不能能混用，必须配对使用

*/


// 先调用operator new开辟内存空间、然后调用对象的构造函数（初始化）
void* operator new(size_t size)
{
	void *p = malloc(size);
	if (p == nullptr)
	{
		throw std::bad_alloc();
	}
	std::cout << "operator new addr:" << p << std::endl;
	return p;
}


// delete p;   先调用p指向对象的析构函数,再调用operator delete释放内存空间   （如果p指向的是编译器内置类型，不会调用析构，直接释放内存空间）
void operator delete(void* ptr)
{
	std::cout << "operator delete addr:" << ptr << std::endl;
	free(ptr);
}

void* operator new[](size_t size)
{
	void* p = malloc(size);
	if (p == nullptr)
	{
		throw std::bad_alloc();
	}
	std::cout << "operator new[] addr:" << p << std::endl;
	return p;
}

void operator delete[](void* ptr)
{
	std::cout << "operator delete[] addr:" << ptr << std::endl;
	free(ptr);
}

class Test
{
public:
	//Test(int data = 10):ptr(new int(data)){ std::cout << "Test()" << std::endl; }
	//~Test() { delete ptr; std::cout << "~Test()" << std::endl; }
	Test(int data = 10)
	{ 
		std::cout << "Test()" << std::endl;
	}

	~Test() 
	{ 
		std::cout << "~Test()" << std::endl; 
	}
private:
	//int* ptr;
};

int main()
{
	Test* p1 = new Test();
	//delete[] p1;   // 载.exe (进程 26348)已退出，代码为 -1073741819。
	delete p1;


	Test* p2 = new Test[5];
	// delete p2;   //程序直接崩了
	delete[]p2;

#if 0
	try 
	{
		int* p = new int;  // 尝试分配内存
		// 如果成功，p指向一个动态分配的int
		delete p;  // 释放内存

		int* p1 = new int[10];
		delete[]p1;

	}
	catch (const std::bad_alloc& e) 
	{
		// 内存分配失败时捕获异常
		std::cerr << "Memory allocation failed: " << e.what() << std::endl;
	}

	//int* p1 = new int[10];
	//delete[]p1;
#endif  


	return 0;
}
#endif 






