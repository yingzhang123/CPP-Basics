#include <iostream>
#include <functional>
#include <vector>
#include <map>
#include <memory>
#include <queue>
#include <algorithm>
using namespace std;



/*
lambda表达式只能使用在语句当中，如果想跨语句使用之前定义好的lambda表达式，
怎么办？用什么类型来表示lambda表达式？
==============>当然时用function类型来表示函数对象类型了                         bind1st/bind2nd   bind绑定器===》返回的都是函数对象

lambda表达式  ====》 函数对象  =====》function

*/
class Data
{
public:
	Data(int val1 = 10, int val2 = 10) : ma(val1), mb(val2) {}
	/*bool operator>(const Data& data) const { return ma > data.ma; }     // 灵活性太差
	bool operator<(const Data& data) const { return ma < data.ma; }*/
	int mb;
	int ma;
};

int main()
{
	// 智能指针自定义删除器     
	//unique_ptr<FILE, function<void(FILE*)>>
	//	ptr1(fopen("data.txt", "w"), [](FILE* pf) {fclose(pf); });

	using FUNC = function<bool(Data&, Data&)>;
	priority_queue<Data, vector<Data>, FUNC> maxHeap([](Data& d1, Data& d2)->bool
		{
			return d1.ma > d2.ma;
		});
	maxHeap.push(Data(10, 20));
	maxHeap.push(Data(15, 15));
	maxHeap.push(Data(20, 15));

	return 0;
}

#if 0
int main()
{
	map<int, function<int(int, int)>> caculateMap;
	caculateMap[1] = [](int a, int b)->int {return a + b; };
	caculateMap[2] = [](int a, int b)->int {return a - b; };
	caculateMap[3] = [](int a, int b)->int {return a * b; };
	caculateMap[4] = [](int a, int b)->int {return a / b; };

	cout << "选择:";
	int choice;
	cin >> choice;
	cout << "10 + 15 = " << caculateMap[choice](10, 15) << endl;

	return 0;
}
#endif


//=================================================================================================
/*
lambda表达式的语法
[捕获外部变量](形参列表)->返回值{操作代码}

如果lambda表达式的返回值不需要，那么"->返回值"可以省略的
*/

/*
lambda表达式的语法：
[捕获外部变量]（形参列表)->返回值{操作代码};

如果lambda表达式的返回值不需要，那么"->返回值"可以省略

[捕获外部变量]
[]: 表示不捕获任何外部变量
[=]: 以传值的方式捕获外部的所有变量
[&]: 以传引用的方式捕获外部的所有变量
[this]: 捕获外部的this指针   （一般用于捕获当前对象的this指针）
[=, &a]: 以传值的方式捕获外部的所有变量，但是a变量以传引用的方式捕获
[a, b]: 以值传递的方式捕获外部变量a和b
[a, &b]: a以值传递捕获，b以传引用的方式捕获
*/


template<typename T=void>
class TestLambda01
{
public:
	void operator() () const
	{
		cout << "hello world!!!" << endl;
	}
private:
};

template<typename T = void>
class TestLambda02
{
public:
	int operator() (int a,int b) const
	{
		return a + b;
	}
private:

};

class TestLambda03
{
public:
	TestLambda03(int a, int b) : ma(a), mb(b) {}
	void operator() () const
	{
		int tmp = ma;
		ma = mb;
		mb = tmp;
	}
private:
	mutable int ma;
	mutable int mb;
};

class TestLambda04
{
public:
	TestLambda04(int &a, int &b) : ma(a), mb(b) {}
	void operator() () const
	{
		int tmp = ma;
		ma = mb;
		mb = tmp;
		// 这里面没有修改类的变量本身内容，只是改变ma,mb引用的内存！！！！(引用底层也是指针！！！)
	}
private:
	int& ma;        
	int& mb;
};

#if 0
int main()
{
#if 0
	auto func1 = []() {cout << "hello world!" << endl; };
	func1();


	auto func2 = [](int a, int b)->int {return a + b; };
	cout << func2(20, 30) << endl;          // 50

	TestLambda01<> t1;
	t1();

	TestLambda02<> t2;
	cout << t2(20, 30) << endl;      // 和lambda一模一样，但是lambda表达式非常方便




	int a = 10;
	int b = 20;
	//auto func3 = [a, b]() mutable 
	//	{
	//		int tmp = a;          // 在lambda表达式中无法直接使用a,b,需要捕获外部的a,b才能访问
	//		a = b;
	//		b = tmp;
	//	};
	//func3();
	//TestLambda03 t3(a, b);
	//t3();
	//cout << "a:" << a << " b:" << b << endl;             <=================== 无法修改外部a,b的值


	//auto func4 = [&a, &b]()  // 按引用传递，mutable不用加上
	//{
	//	int tmp = a;
	//	a = b;
	//	b = tmp;
	//};
	//func4();                                            //《============  成功交换外部的a,b的值
	//cout << "a:" << a << " b:" << b << endl;

	TestLambda04 t4(a, b);
	t4();
	cout << "a:" << a << " b:" << b << endl;               //《============  成功交换外部的a,b的值
#endif

	// lambda表达式的应用
	vector<int> vec;
	for (int i = 0; i < 20; ++i)
	{
		vec.push_back(rand() % 100 + 1);
	}
	sort(vec.begin(), vec.end(), [](int a, int b)-> bool
		{
			return a > b;
		});

	for (int val : vec)
	{
		cout << val << " ";
	}
	cout << endl;

	// 65按序插入序列  要找第一个小于65的数字
	auto it = find_if(vec.begin(), vec.end(),
		[](int a)->bool
		{
			return a < 65;
		});
	if (it != vec.end())
	{
		vec.insert(it, 65);
	}
	for (int val : vec)
	{
		cout << val << " ";
	}
	cout << endl;

	for_each(vec.begin(), vec.end(),
		[](int a)
		{
			if (a % 2 == 0) { cout << a << " "; }
		});

	return 0;
}

#endif