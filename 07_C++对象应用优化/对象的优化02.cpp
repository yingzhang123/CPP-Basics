#include<iostream>

using namespace std;



class Test
{
public:
	// Test()   Test(20)
	Test(int data = 10) 
		:ma(data)
	{
		cout << "Test(int)" << endl;
	}
	~Test()
	{
		cout << "~Test()" << endl;
	}
	Test(const Test& t)
	{
		cout << "Test(const Test& t)" << endl;
	}
	Test& operator=(const Test& t)
	{
		cout << "operator=(const Test& t)" << endl;
		ma = t.ma;
		return* this;
	}
	int getData()const { return ma; }
private:
	int ma;
};


// 不能返回局部的或者临时对象的指针或引用
/*
1.函数参数传递过程中，对象优先按引用传递，不要按值传递
2.函数返回对象的时候，应该优先返回一个临时对象，而不要返回一个定义过的对象
3.接收返回值是对象的函数调用的时候，优先按初始化的方式接收，不要按赋值的方式接收
*/
Test GetObject(Test& t)   // 3.Test(const Test& t)  实参到形参调用拷贝构造函数           
{
	int val = t.getData();
	//Test tmp(val);       // 4.Test(int)
	//return tmp;

	// 返回临时对象    =====》 用临时对象构造一个新对象  Test t = Test(val);  ====》 编译器都会做一个优化，临时对象都不产生了   ===》 Test(val)
	return Test(val);
}

int main()
{
	//Test t1;  // 1.Test(int)
	//Test t2;  // 2.Test(int)
	//t2 = GetObject(t1);
	//// 函数调用，实参 ==》 形参      是初始化？还是赋值？  ===》是初始化！！！！的过程

	Test t1;  
	Test t2 = GetObject(t1);
	return 0;
}

/*  vs2022
Test(int)
Test(int)
Test(const Test& t)
Test(int)
~Test()
operator=(const Test& t)
~Test()
~Test()
~Test()
*/

/*  vs2017
Test(int)
Test(int)
Test(const Test& t)
Test(int)
Test(const Test& t)      ==》 tmp在main函数栈帧上拷贝构造临时返回值对象
~Test()
~Test()
operator=(const Test& t)
~Test()
~Test()
~Test()
*/


/*                      1，2 优化后 
Test(int)
Test(int)
Test(int)
operator=(const Test& t)
~Test()
~Test()
~Test()
*/

/*                        1，2，3优化后
Test(int)
Test(int)
~Test()
~Test()
*/