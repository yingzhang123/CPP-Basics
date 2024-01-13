#include<iostream>
#include<set>
#include<queue>
#include<string>
using namespace std;


#if 0 
int main()
{
	//_EXPORT_STD template <class _Kty, class _Pr = less<_Kty>, class _Alloc = allocator<_Kty>>
	//	class set : public _Tree<_Tset_traits<_Kty, _Pr, _Alloc, false>> {
	set<int> set1;
	for (int i = 0; i < 10; ++i)
	{
		set1.insert(rand() % 100 + 1);
	}
	for (int v : set1)
	{
		cout << v << " ";
	}
	cout << endl;  // 1 25 35 42 59 63 65 68 70 79

	set<int,greater<int>> set2;
	for (int i = 0; i < 10; ++i)
	{
		set2.insert(rand() % 100 + 1);
	}
	for (int v : set2)
	{
		cout << v << " ";
	}
	cout << endl;  // 96 92 82 62 46 43 37 28 6
	return 0;
}
#endif


#if 0 
int main()
{
	// template <class _Ty, class _Container = vector<_Ty>, class _Pr = less<typename _Container::value_type>>
	priority_queue<int> pque;  // 底层：vector   默认是大根堆
	for (int i = 0; i < 10; ++i)
	{
		pque.push(rand() % 100 + 1);
	}
	
	while (!pque.empty())
	{
		cout << pque.top() << " ";
		pque.pop();
	}
	// 79 70 68 65 63 59 42 35 25 1
	cout << endl;

	using MinHeap = priority_queue<int, vector<int>, greater<int>>;  // greater<int>函数对象
	MinHeap pque2;  
	for (int i = 0; i < 10; ++i)
	{
		pque2.push(rand() % 100 + 1);
	}

	while (!pque2.empty())
	{
		cout << pque2.top() << " ";
		pque2.pop();
	}
	// 6 28 28 37 43 46 62 82 92 96

	return 0;
}
#endif

//=======================================================  8.函数对象  ================================================
/*
函数对象   ==》 类似C语言的函数指
把有operator()小括号运算符重载函数的对象，称作函数对象或者称作仿函数！！！！！！！！！！
*/
/*
1.通过函数对象调用operator()，可以省略函数的调用开销，比通过函数指针调用函数（不能够inline内联调用）效率高

2.因为函数对象使用类生成的，所以可以添加相关的成员变量，用来记录函数对象使用时更多的信息
*/

#if 0 
// C++函数对象的版本实现
template<typename T>
class MyGreater
{
public:
	bool operator()(T a, T b)        // 二元函数对象
	{
		return a > b;
	}
};

template<typename T>
class MyLess
{
public:
	bool operator()(T a, T b)
	{
		return a < b;
	}
};


// 使用C的函数指针解决方案
template<typename T>
bool mygreater(T a, T b)
{
	return a > b;
}

template<typename T>
bool myless(T a, T b)
{
	return a < b;
}

// compare是C++库函数模板
template<typename T,typename Compare>
bool compare(T a, T b, Compare Comp)  // 函数指针
{
	// 通过函数指针间接调用mygreater或myless
	// 通过函数指针调用函数。是没有办法内联的，效率很低，因为有函数调用开销
	return Comp(a,b);        

}

//template<typename T>
//bool compare(T a, T b)
//{
//	return a > b;
//}

int main()
{
	// 函数指针
	cout << compare(10, 20, mygreater<int>) << endl;
	cout << compare('b', 'y', myless<char>) << endl;

	// 函数对象（仿函数）
	cout << compare(10, 20, MyGreater<int>()) << endl;
	cout << compare('b', 'y', MyLess<char>()) << endl;

	return 0;
}
#endif