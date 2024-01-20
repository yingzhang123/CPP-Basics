
/*
����ָ�����
�Լ�ʵ������ָ��
�������ü���������ָ��auto_ptr,scoped_ptr,unique_ptr
�����ü���������ָ��shared_ptr,weak_ptr
������ָ��Ľ������ã�ѭ�����ã�����
���̷߳��ʹ����������
�Զ���ɾ����
*/





#include<iostream>
#include<memory>
#include<thread>
#include<functional>
using namespace std;

//����Դ�������ü�������
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

	void addRef()   // ������Դ�����ü���
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


// ����ָ�� ��֤��������Դ���Զ��ͷţ�����
// ����ջ�ϵĶ�����������Զ���������������������Դ���Զ��ͷ�

// CSmartPtr<int> *p = new CSmartPtr<int>(new int);  ===> ����ָ���ܷ����ڶ��ϣ� 
//   ���﷨��û���κ����⣬���ǲ��ܱ�֤��Դ���Զ��ͷţ�p����ָ�룬��Ҫ�ֶ�delete p,�Ż����CSmartPtr�������������Ż��ͷ��ͷ�ָ��������Դ


//===================================== ѭ�����ã��������ã� ===================================== 
/*
shared_ptr:ǿ����ָ��   ���Ըı���Դ�����ü���
weak_ptr:������ָ��     ����ı���Դ�����ü���     ������ָ��䵱�۲��ߣ�����ʹ����Դ��������ͨ��*��->������Դ��
												   operator*   operator-> ��û���ṩ

weak_ptr ==> shared_ptr  ==> ��Դ���ڴ棩

ǿ����ָ��ѭ�����ã��������ã���ʲô���⣿ʲô�������ô���
���new�������ڴ���Դ�޷��ͷţ������� ��Դй©���⣡������
�����������������ʱ����ǿ����ָ�룻���ö���ķ�����ʹ��������ָ��
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
	T& operator*() { return *mptr; }   // Ҫ�������� ===����ΪҪ�ı�ֵ��д������
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
	T* mptr;         // ָ����Դ��ָ��
	RefCnt<T>* mpRefCnt;   // ָ�����Դ���ü��������ָ��
};

//===================================== �Զ���ɾ���� ======================================== 
/*
����ָ���ɾ���� deletor
����ָ�룺�ܹ���֤��Դ���Ե��ͷ� 
*/
// unique_ptr  shared_ptr
/*
~unique_ptr(){��һ����������ĵ��� deletor(ptr)}

template<typename T>   // Ĭ�Ϸ�ʽ
class default_deleto
{
	void operator()(T* ptr)
	{
		delete ptr;
	}
}
*/
// �Զ���ɾ����
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

	// ���򵥵�ʵ�ַ�ʽ  lambda���ʽ====���������� function
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


//===================================== ���̷߳��ʹ���������� ======================================== 
#if 0
class A
{
public:
	A() { cout << "A()" << endl; }
	~A() { cout << "~A()" << endl; }
	void testA() { cout << "�ǳ����õķ���������" << endl; }
};

// ���߳�
void handler01(weak_ptr<A> pw)
{
	// ����A�����ʱ����Ҫ���һ��A�����Ƿ���
	shared_ptr<A> sp = pw.lock();
	if (sp != nullptr)
	{
		sp->testA();
	}
	else
	{
		cout << "A�����Ѿ������������ٷ��ʣ�" << endl;
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
A�����Ѿ������������ٷ��ʣ�
-------------------------------------
A()
�ǳ����õķ���������
~A()
*/
#endif 

//===================================== ѭ�����ã��������ã� ===================================== 
#if 0
class B;
class A
{
public:
	A() { cout << "A()" << endl; }
	~A() { cout << "~A()" << endl; }
	void testA() { cout << "�ǳ����õķ���������" << endl; }
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
		//_ptra->testA();  // ��std::weak_ptr<A>������û�����س�Ա��operator->��
		if (auto ptr = _ptra.lock())   // ����Ϊǿ����ָ��      // _ptra.lock() : convert to shared_ptr
		{
			// ��Դû���ͷţ������ɹ�
			ptr->testA();
		}
		else
		{
			// ��Դ�Ѿ��ͷţ�����ʧ��

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

//=====================================  �����ü���������ָ�� ===================================== 
#if 0
int main()
{
	/*
	�����ü���������ָ��shared_ptr��weak_ptr     (������ָ�����̰߳�ȫ��)
	�����ü������������ָ����Թ���ͬһ����Դ
	�����ü�������ÿһ��������Դ��ƥ��һ�����ü�����
	����ָ�� ==��  ָ����Դ         ===�� ���ü���+1
	����ָ�� ==�� ��ʹ����Դ��ʱ��  ===�����ü���-1  ===�� !=0   0��Դ�ͷ���  
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

//=====================================  �������ü���������ָ�� =====================================  
#if 0
int main()
{

	/*
	�������ü���������ָ�룺ֻ����һ��ָ�������Դ
	auto_ptr
	scoped_ptr:
	C++11�±�׼
	unique_ptr

	��ô���ǳ�������⣿
	scoped_ptr:
	scoped_ptr<T>(const scoped_ptr<T>&) = delete;
	scoped_ptr<T>& operator=(scoped_ptr<T>&) = delete;    


	�Ƽ�ʹ�ã�
	unique_ptr��
	unique_ptr<T>(const unique_ptr<T>&) = delete;
	unique_ptr<T>& operator=(unique_ptr<T>&) = delete;

	// ֻ�ṩ����ֵ���õĿ������죬�͸�ֵ��������غ���
	unique_ptr<T>(const unique_ptr<T>&&){};
	unique_ptr<T>& operator=(unique_ptr<T>&&){};

	*/
	// 1��
	auto_ptr<int> ptr1(new int());
	auto_ptr<int> ptr2(ptr1);       // ����Ȩ�� ptr1 ת�Ƶ� ptr2������ ptr1 ����ӵ�и��ڴ� (ת�ƶ��������Ȩ) ==>���һ��ָ��ӵ����Դ

	*ptr2 = 20;
	// cout << *ptr1 << endl;  // ���� auto_ptr
	//���� C++98 �е�һ�����ԡ�Ȼ������Ҫע����ǣ�auto_ptr �� C++11 �����߰汾���ѱ����ã�ȡ����֮���Ǹ���ȫ������ָ�룬�� std::unique_ptr �� std::shared_ptr��
	
	// 2��C++11��׼������ std::unique_ptr���� scoped_ptr �Ѿ���������
	// scoped_ptr<int>    


	unique_ptr<int> ptr3(new int(67));
	unique_ptr<int> ptr4(std::move(ptr3));   // unique_ptr�ĺô��ǣ���Ҫ�ֶ�ʹ��move���ӿ��õ����߸���ȷ

	return 0;
}
#endif

//=====================================  ����ָ������ú����� =====================================  
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