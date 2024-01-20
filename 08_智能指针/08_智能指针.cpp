
/*
智能指针介绍
自己实现智能指针
不带引用计数的智能指针auto_ptr,scoped_ptr,unique_ptr
带引用计数的智能指针shared_ptr,weak_ptr
带智能指针的交叉引用（循环引用）问题
多线程访问共享对象问题
自定义删除器
*/





#include<iostream>
#include<memory>
#include<thread>
#include<functional>
using namespace std;

//对资源进行引用计数的类
template<typename T>
class RefCnt
{
public:
	RefCnt(T* ptr = nullptr)
		:_mptr(ptr)
	{
		if (ptr != nullptr)
		{
			mcount = 1;
		}
	}

	void addRef()   // 增加资源的引用计数
	{
		mcount++;
	}

	int delRef()
	{
		return --mcount;
	}

private:
	T* _mptr;
	int mcount;
};


// 智能指针 保证能做到资源的自动释放！！！
// 利用栈上的对象出作用域自动析构的特征，来做到资源的自动释放

// CSmartPtr<int> *p = new CSmartPtr<int>(new int);  ===> 智能指针能否定义在堆上？ 
//   在语法上没有任何问题，但是不能保证资源的自动释放，p是裸指针，需要手动delete p,才会调用CSmartPtr的析构函数，才会释放释放指针管理的资源


//===================================== 循环引用（交叉引用） ===================================== 
/*
shared_ptr:强智能指针   可以改变资源的引用计数
weak_ptr:弱智能指针     不会改变资源的引用计数     弱智能指针充当观察者，不能使用资源（即不能通过*，->访问资源）
												   operator*   operator-> 都没有提供

weak_ptr ==> shared_ptr  ==> 资源（内存）

强智能指针循环引用（交叉引用）是什么问题？什么结果？怎么解决
造成new出来的内存资源无法释放！！！！ 资源泄漏问题！！！！
解决方法：定义对象的时候，用强智能指针；引用对象的方法，使用弱智能指针
*/


template<typename T>
class CSmartPtr
{
public:
	CSmartPtr(T* ptr = nullptr)
		:mptr(ptr)
	{
		mpRefCnt = new RefCnt<T>(mptr);
	}
	~CSmartPtr() { 
		if (0 == mpRefCnt->delRef())
		{
			delete mptr;
			mptr = nullptr;
		}
	}
	T& operator*() { return *mptr; }   // 要返回引用 ===》因为要改变值（写操作）
	T* operator->() { return mptr; }

	CSmartPtr(const CSmartPtr<T>& src)
		:mptr(src.mptr)
		,mpRefCnt(src.mpRefCnt)
	{
		if (mptr != nullptr)
		{
			mpRefCnt->addRef();
		}

	}
	CSmartPtr<T>& operator=(const CSmartPtr<T>&src)
	{
		if (this != &src)
		{
			return *this;
		}

		if(0 == mpRefCnt->delRef())
		{
			delete mptr;
			mptr = nullptr;
		}
		mptr = src.mptr;
		mpRefCnt = src.mpRefCnt;
		mpRefCnt->addRef();
		return *this;
	}

private:
	T* mptr;         // 指向资源的指针
	RefCnt<T>* mpRefCnt;   // 指向该资源引用计数对象的指针
};

//===================================== 自定义删除器 ======================================== 
/*
智能指针的删除器 deletor
智能指针：能够保证资源绝对的释放 
*/
// unique_ptr  shared_ptr
/*
~unique_ptr(){是一个函数对象的调用 deletor(ptr)}

template<typename T>   // 默认方式
class default_deleto
{
	void operator()(T* ptr)
	{
		delete ptr;
	}
}
*/
// 自定义删除器
template<typename T>
class MyDeletor
{
public:
	void operator()(T* ptr)const
	{
		cout << "call MyDeletor operator()~" << endl;
		delete[]ptr;
	}
};

template<typename T>
class MyFILEDeletor
{
public:
	void operator()(T* ptr)const
	{
		cout << "call MyFILEDeletor operator()~" << endl;
		fclose(ptr);
	}
};

int main()
{
	unique_ptr<int,MyDeletor<int>> ptr(new int[100]);
	unique_ptr<FILE, MyFILEDeletor<FILE>> ptr2(fopen("abc.txt", "w"));

	// 更简单的实现方式  lambda表达式====》函数对象 function
	unique_ptr<int, function<void(int*)>> ptr3(new int[100],
		[](int* ptr) {
			cout << "call lambda release new int[100]" << endl;
			delete[]ptr;
		});

	unique_ptr<FILE, function<void(FILE*)>> ptr4(fopen("abc.txt", "w"),
		[](FILE* ptr) {
			cout << "call lambda release new fopen" << endl;
			fclose(ptr);
		});

	return 0;
}


//===================================== 多线程访问共享对象问题 ======================================== 
#if 0
class A
{
public:
	A() { cout << "A()" << endl; }
	~A() { cout << "~A()" << endl; }
	void testA() { cout << "非常好用的方法！！！" << endl; }
};

// 子线程
void handler01(weak_ptr<A> pw)
{
	// 访问A对象的时候，需要侦察一下A对像是否存活
	shared_ptr<A> sp = pw.lock();
	if (sp != nullptr)
	{
		sp->testA();
	}
	else
	{
		cout << "A对象已经析构，不能再访问！" << endl;
	}
}
int main()
{
	{
		shared_ptr<A> ptr(new A());
		thread t1(handler01, weak_ptr<A>(ptr));
		t1.detach();
		std::this_thread::sleep_for(std::chrono::seconds(2));
	}
	
	std::this_thread::sleep_for(std::chrono::seconds(20));

	return 0;
}
/*
A()
~A()
A对象已经析构，不能再访问！
-------------------------------------
A()
非常好用的方法！！！
~A()
*/
#endif 

//===================================== 循环引用（交叉引用） ===================================== 
#if 0
class B;
class A
{
public:
	A() { cout << "A()" << endl; }
	~A() { cout << "~A()" << endl; }
	void testA() { cout << "非常好用的方法！！！" << endl; }
	// shared_ptr<B> _ptrb;   
	weak_ptr<B> _ptrb;
};

class B
{
public:
	B() { cout << "B()" << endl; }
	~B() { cout << "~B()" << endl; }
	//shared_ptr<A> _ptra;
	void func()
	{
		//_ptra->testA();  // “std::weak_ptr<A>”类型没有重载成员“operator->”
		if (auto ptr = _ptra.lock())   // 提升为强智能指针      // _ptra.lock() : convert to shared_ptr
		{
			// 资源没有释放，提升成功
			ptr->testA();
		}
		else
		{
			// 资源已经释放，提升失败

		}

	}
	weak_ptr<A> _ptra;
};



int main()
{
	shared_ptr<A> pa(new A());
	shared_ptr<B> pb(new B());

	pa->_ptrb = pb;
	pb->_ptra = pa;
	pb->func();
	cout << pa.use_count() << endl;
	cout << pb.use_count() << endl;
	return 0;
}
/* 
A()
B()
2
2
*/ 

/*   weak_ptr
A()
B()
1
1
~B()
~A()
*/
#endif 

//=====================================  带引用计数的智能指针 ===================================== 
#if 0
int main()
{
	/*
	带引用计数的智能指针shared_ptr和weak_ptr     (这两个指针是线程安全的)
	带引用计数：多个智能指针可以管理同一个资源
	带引用计数：给每一个对象资源，匹配一个引用计数；
	智能指针 ==》  指向资源         ===》 引用计数+1
	智能指针 ==》 不使用资源的时候  ===》引用计数-1  ===》 !=0   0资源释放了  
	*/
	CSmartPtr<int> p1(new int(89));
	CSmartPtr<int> p2(p1);
	CSmartPtr<int> p3(p1);
	*p1 = 99;
	cout << *p2 << endl;
	cout << *p3 << endl;
	return 0;
}
#endif

//=====================================  不带引用计数的智能指针 =====================================  
#if 0
int main()
{

	/*
	不带引用计数的智能指针：只能让一个指针管理资源
	auto_ptr
	scoped_ptr:
	C++11新标准
	unique_ptr

	怎么解决浅拷贝问题？
	scoped_ptr:
	scoped_ptr<T>(const scoped_ptr<T>&) = delete;
	scoped_ptr<T>& operator=(scoped_ptr<T>&) = delete;    


	推荐使用：
	unique_ptr：
	unique_ptr<T>(const unique_ptr<T>&) = delete;
	unique_ptr<T>& operator=(unique_ptr<T>&) = delete;

	// 只提供带右值引用的拷贝构造，和赋值运算符重载函数
	unique_ptr<T>(const unique_ptr<T>&&){};
	unique_ptr<T>& operator=(unique_ptr<T>&&){};

	*/
	// 1、
	auto_ptr<int> ptr1(new int());
	auto_ptr<int> ptr2(ptr1);       // 所有权从 ptr1 转移到 ptr2，现在 ptr1 不再拥有该内存 (转移对象的所有权) ==>最后一个指针拥有资源

	*ptr2 = 20;
	// cout << *ptr1 << endl;  // 报错 auto_ptr
	//这是 C++98 中的一个特性。然而，需要注意的是，auto_ptr 在 C++11 及更高版本中已被弃用，取而代之的是更安全的智能指针，如 std::unique_ptr 和 std::shared_ptr。
	
	// 2、C++11标准引入了 std::unique_ptr，而 scoped_ptr 已经被废弃。
	// scoped_ptr<int>    


	unique_ptr<int> ptr3(new int(67));
	unique_ptr<int> ptr4(std::move(ptr3));   // unique_ptr的好处是，需要手动使用move，接口让调用者更明确

	return 0;
}
#endif

//=====================================  智能指针的作用和意义 =====================================  
#if 0 
int main()
{
	CSmartPtr<int> ptr(new int);
	*ptr = 30;

	class Test {
	public:
		void test() { cout << "call Test::test" << endl; }
	};

	CSmartPtr<Test> ptr2(new Test());
	// (ptr2.operator->())->test()
	ptr2->test();

	return 0;
}
#endif