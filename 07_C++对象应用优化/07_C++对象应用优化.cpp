#include<iostream>


using namespace std;

// ----------------------------------------------------------------------------------------------------------------------
#if 0
class Test
{
public:
	// Test() Test(10)  Test(10,10)
	Test(int a= 50,int b=50)
		:ma(a)
		,mb(b)
	{
		cout << "Test(int a,int b)" << endl;
	}

	~Test()
	{
		cout << "~Test()" << endl;
	}

	Test(const Test& t)
		:ma(t.ma)
		,mb(t.ma)
	{
		cout << "Test(const Test&)" << endl;
	}

	Test& operator=(const Test& t)
	{
		cout << "operator=(const Test&)" << endl;
		if (this == &t)
		{
			return *this;
		}
		this->ma = t.ma;
		this->mb = t.mb;
		return *this;
	}

private:
	int ma;
	int mb;
};

Test t1(10, 10);   // 全局对象，在main函数之前初始化  1.Test(int a,int b)
int main()
{
	Test t2(20, 20); // 3.Test(int a,int b)
	Test t3 = t2;    // 4.Test(const Test&)
	// static Test t4(30,30);
	static Test t4 = Test(30, 30);   // 5.Test(int a,int b)【用临时对象构造新对象，临时对象会被优化掉】  局部静态变量，内存运行一开始就存在，但初始化是在运行到它才会初始化
	t2 = Test(40, 40); // 6. 临时对象   Test(int a,int b) ==》 operator=(const Test&)     ==》    ~Test()
	// (50, 50)表达式 === 50    Test(50)
	t2 = (Test)(50, 50); //7. 显式生成临时对象（类型强转）  Test(int a,int b)  == 》  operator=(const Test&)    ==》    ~Test()
	t2 = 60;             //8. 隐式生成临时对象（类型强转）  Test(int a,int b)  == 》  operator=(const Test&)    ==》    ~Test()  

	Test* p1 = new Test(70, 70);   //9 .  1、堆上开辟内存 2、构造对象  Test(int a,int b)
	Test* p2 = new Test[2];        //10.  1、堆上开辟内存 2、构造对象  Test(int a,int b)  Test(int a,int b)
	// Test* p3 = &Test(80, 80);    // vs2022 报错  【不能用指针指向临时对象】     vs2017可以       11.    Test(int a,int b)     ==》     ~Test()            
	const Test& ref = Test(90, 90);     // 12.  Test(int a,int b)
	delete p1;    // 13.  ~Test()
	delete[]p2;   // 14.  ~Test()   ~Test()

	return 0;
}
Test t4(100, 100);     // 全局对象，在main函数之前初始化  2.Test(int a,int b)

	/*
	Test(int a,int b)
	Test(int a,int b)
	Test(int a,int b)
	Test(const Test&)
	Test(int a,int b)
	Test(int a,int b)
	operator=(const Test&)
	~Test()
	Test(int a,int b)
	operator=(const Test&)
	~Test()
	Test(int a,int b)
	operator=(const Test&)
	~Test()
	Test(int a,int b)
	Test(int a,int b)
	Test(int a,int b)
	Test(int a,int b)
	~Test()
	~Test()
	~Test()
	~Test()
	~Test()
	~Test()
	~Test()
	~Test()
	~Test()
	*/
#endif

// ----------------------------------------------------------------------------------------------------------------------
#if 0

class Test
{
public:
	Test(int a = 10) 
		:ma(a) 
	{ 
		cout << "Test()" << endl;
	}
	
	~Test() 
	{
		cout << "~Test()" << endl;
	}
	
	Test(const Test& t) 
		:ma(t.ma)
	{ 
		cout << "Test(const Test& t)" << endl;
	}

	Test& operator=(const Test& t)
	{
		cout << "operator=(const Test& t)" << endl;
		if (this == &t)
		{
			return *this;
		}
		this->ma = t.ma;
		return *this;
	}
private:
	int ma;
};

int main()
{
	Test t1;      // Test()
	Test t2(t1);  // Test(const Test& t)
	Test t3 = t1;  // 和Test t2(t1);一样   // Test(const Test& t)

	// Test(20) 显示生成临时对象（临时对象没有名字，生存周期：所在的语句，语句结束，临时对象会被析构）
	// C++编译器对于对象的优化：用临时对象生成新对象的时候，临时对象就不产生了，直接构造新对象就可以了
	Test t4 = Test(20);    // Test()       这条语句和 Test t4(20);没有区别的！！

	cout << "--------------------------" << endl;

	// t4.operator(t2)
	t4 = t2;
	// t4.operator(const Test& t)
	t4 = Test(30);          // 临时对象先构造，再赋值给t4, 临时对象析构

	//显式类型强转  显式生成临时对象
	t4 = (Test)30;      // int -> Test(int)  
	// 隐式类型强转  隐式生成临时对象
	t4 = 30;        // int -> Test(int)   Test(30)

	cout << "--------------------------" << endl;
	
	// Test* p = &Test(40);    // vs2022 报错              “& ”要求左值	07_C++对象应用优化          用指针指向临时对象是不安全的
	// 出了语句，p指向的是一个已经析构的临时对象    p是一个野指针了

	const Test& ref = Test(50);   // 该临时对象在语句结束后不会析构，

	cout << "--------------------------" << endl;
	/*
	Test()
	Test(const Test& t)
	Test(const Test& t)
	Test()
	--------------------------
	operator=(const Test& t)
	Test()
	operator=(const Test& t)
	~Test()
	Test()
	operator=(const Test& t)
	~Test()
	Test()
	operator=(const Test& t)
	~Test()
	--------------------------
	~Test()
	~Test()
	~Test()
	~Test()
	*/


	return 0;
}
#endif