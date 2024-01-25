#include<iostream>
#include<vector>
#include<map>
#include<functional>
#include<algorithm>
#include<string>
using namespace std;

/*
C++11提供的绑定器和函数对象
				bind   function
				C++ STL   bind1st和bind2nd===>本身还是一个函数对象

function:绑定器，函数对象，lambda表达式      他们智能使用在一条语句上
*/


#if 0
void doShowAllBooks() { cout << "查看所有书籍信息" << endl; }
void doBorrow() { cout << "借书" << endl; }
void doBack() { cout << "还书" << endl; }
void doQueryBooks() { cout << "查询书籍" << endl; }
void doLoginOut() { cout << "注销" << endl; }

int main()
{
	int choice = 0;
	// 跟函数指针相比，应用更广泛，可以接收lambda表达式，绑定器
	map<int, function<void()>> actionMap;
	actionMap.insert({ 1, doShowAllBooks });
	actionMap.insert({ 2, doBorrow });
	actionMap.insert({ 3, doBack });
	actionMap.insert({ 4, doQueryBooks });
	actionMap.insert({ 5, doLoginOut });
	for (; ;)
	{
		cout << "-----------------" << endl;
		cout << "1.查看所有书籍信息" << endl;
		cout << "2.借书" << endl;
		cout << "3.还书" << endl;
		cout << "4.查询书籍" << endl;
		cout << "5.注销" << endl;
		cout << "-----------------" << endl;
		cout << "请选择:";
		cin >> choice;


		auto it = actionMap.find(choice);
		if (it == actionMap.end())
		{
			cout << "输入数字无效，重新选择！" << endl;
		}
		else
		{
			it->second();
		}

	}
	/*
	switch (choice) // 不好，因为这块代码无法闭合  无法做到“开-闭”原则 不好增删改功能
	{
	case1:
		break;
	case2:
		break;
	case3:
		break;
	case4:
		break;
	case5:
		break;
	default:
		break;
	}
	*/

	return 0;
}
#endif

//================================================== 1、function ===========================================
#if 0
void hello1()
{
	cout << "hello world!" << endl;
}

void hello2(string str)   // void (*pfunc)(string)
{
	cout << str << endl;
}

int sum(int a, int b)
{
	return a + b;
}

class Test
{
public:
	// 成员方法的调用，必须依赖一个对象  
	void hello(string str)       // void (Test::*pfunc)(string)
	{
		cout << str << endl;
	}
};

int main()
{
	/*
	1、用函数类型实例化function
	2、通过function调用operator()函数的时候，需要根据函数类型传入相应的参数
	*/

	// 从function的类模板定义处，看到希望用一个函数类型实例化function
	function<void()> func1 = hello1;
	func1();      // func1.operator()  ==> hello1()

	function<void(string)> func2 = hello2;
	func2("hello hello2!!!!");   // func2.operator(string str)  ===> hello2(str)

	function<int(int, int)> func3 = sum;
	cout << func3(30,20) << endl;

	function<int(int, int)> func4 = [](int a, int b)->int {return a + b; };
	cout << func4(30, 20) << endl;

	function<void(Test*, string)> func5 = &Test::hello;
	Test testObj;
	func5(&testObj, "call Test::hello!!!");    // 

	return 0;
}
#endif




