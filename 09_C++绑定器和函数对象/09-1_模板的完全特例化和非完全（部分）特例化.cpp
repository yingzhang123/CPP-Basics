#include<iostream>
#include<vector>
#include<algorithm>
#include<functional>
#include<typeinfo>
using namespace std;

/*
模板的完全特例化和非完全（部分）特例化
模板的实参推演   ===> 基本概念很简单
*/

#if 0 
// T包含了所有的大的类型 返回值，所有形参的类型都取出来
template<typename T>       
void func(T a)
{
	cout << typeid(T).name() << endl;
}

template<typename R,typename A1,typename A2>
void func2(R(*a)(A1,A2))
{
	//cout << "func2(R(*a)(A1,A2))" << endl;
	cout << typeid(R).name() << endl;
	cout << typeid(A1).name() << endl;
	cout << typeid(A2).name() << endl;
}

template<typename T,typename R, typename A1, typename A2>
void func3(R(T::*a)(A1, A2))
{
	cout << typeid(T).name() << endl;
	cout << typeid(R).name() << endl;
	cout << typeid(A1).name() << endl;
	cout << typeid(A2).name() << endl;
}

class Test
{
public:
	int sum(int a, int b)
	{
		return a + b;
	}
};

int sum(int a, int b) { return a + b; }

int main()
{
	func(10);        // int
	func("aaa");     // char const*
	func(sum);       // int (*)(int,int)
	func2(sum);
	func(&Test::sum);    // int (__thiscall Test::*)(int,int)
	func3(&Test::sum);   
	/*
	class Test
	int
	int
	int
	*/
	return 0;
}
#endif

#if 0       模板的完全特例化和非完全（部分）特例化
// 原模板  # 3
template<typename T>
class Vector
{
public:
	Vector()
	{
		cout << "call Vector template init" << endl;
	}
};

// 下面这个是对char*类型提供的完全特例化版本     # 1
template<>
class Vector<char*>
{
public:
	Vector()
	{
		cout << "call Vector<char*> template init" << endl;
	}
};

// 下面这个是对指针类型提供的部分特例化版本     # 2
template<typename Ty>
class Vector<Ty*>
{
public:
	Vector()
	{
		cout << "call Vector<Ty*> template init" << endl;
	}
};

// 针对函数指针（有返回值，有两个形参变量）提供的部分特例化
template<typename R,typename A1,typename A2>
class Vector<R(*)(A1,A2)>
{
public:
	Vector()
	{
		cout << "call Vector<R(*)(A1,A2)> template init" << endl;
	}
};


template<typename R, typename A1, typename A2>
class Vector<R(A1, A2)>
{
public:
	Vector()
	{
		cout << "call Vector<R(A1, A2)> template init" << endl;
	}
};


//template<typename A1, typename A2>
//class Vector<int(*)(A1, A2)>
//{
//public:
//	Vector()
//	{
//		cout << "call  Vector<int(*)(A1, A2)> template init" << endl;
//	}
//};

// 针对函数指针提供的完全特例化
template<>
class Vector<int(*)(int, int)>
{
public:
	Vector()
	{
		cout << "call Vector<int(*)(int, int)> template init" << endl;
	}
};


int sum(int a, int b) { return a + b; }
int main()
{
	Vector<int> vec1;
	Vector<char*> vec2;
	Vector<int*> vec3;
	Vector<int(*)(int, int)> vec4;    // int(*)(int, int)函数指针 
	Vector<int(int, int)> vec5;       //function，函数类型 


	// 注意区分一下函数类型和函数指针类型
	typedef int(*PFUNC)(int, int);  // 函数指针类型
	PFUNC pfunc1 = sum;
	cout << pfunc1(1, 2) << endl;

	//typedef int(FUNC)(int, int);   //函数类型
	typedef int FUNC(int, int);   //函数类型
	FUNC* pfunc2 = sum;
	cout << (*pfunc2)(1, 2) << endl;
	cout << pfunc2(1, 2) << endl;
	return 0;
	/*
	call Vector template init
	call Vector<char*> template init
	call Vector<Ty*> template init
	call Vector<int(*)(int, int)> template init
	call Vector<R(A1, A2)> template init
	3
	3
	3	
	*/
}
#endif

#if 0
template<typename T>
bool compare(T a, T b)
{
	cout << "tempalte compare" << endl;
	return a > b;
}

// 提供特例化版本
template<>
bool compare<const char*>(const char* a, const char* b)
{
	cout << "tempalte compare<const char*>(const char* a, const char* b)" << endl;
	return strcmp(a,b)>0;
}

int main()
{
	compare(10, 20);
	compare("aaaa", "bbbb");  //依赖模板的实参推演==》 T const char*  ===> 比较的是两个地址，而不是字符串的字典序  ==》 不符合实际处理的逻辑

	return 0;
}
#endif