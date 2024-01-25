#include<iostream>
#include<vector>
#include<map>
#include<functional>
#include<algorithm>
#include<string>
using namespace std;

/*
C++11�ṩ�İ����ͺ�������
				bind   function
				C++ STL   bind1st��bind2nd===>������һ����������

function:��������������lambda���ʽ      ��������ʹ����һ�������
*/


#if 0
void doShowAllBooks() { cout << "�鿴�����鼮��Ϣ" << endl; }
void doBorrow() { cout << "����" << endl; }
void doBack() { cout << "����" << endl; }
void doQueryBooks() { cout << "��ѯ�鼮" << endl; }
void doLoginOut() { cout << "ע��" << endl; }

int main()
{
	int choice = 0;
	// ������ָ����ȣ�Ӧ�ø��㷺�����Խ���lambda���ʽ������
	map<int, function<void()>> actionMap;
	actionMap.insert({ 1, doShowAllBooks });
	actionMap.insert({ 2, doBorrow });
	actionMap.insert({ 3, doBack });
	actionMap.insert({ 4, doQueryBooks });
	actionMap.insert({ 5, doLoginOut });
	for (; ;)
	{
		cout << "-----------------" << endl;
		cout << "1.�鿴�����鼮��Ϣ" << endl;
		cout << "2.����" << endl;
		cout << "3.����" << endl;
		cout << "4.��ѯ�鼮" << endl;
		cout << "5.ע��" << endl;
		cout << "-----------------" << endl;
		cout << "��ѡ��:";
		cin >> choice;


		auto it = actionMap.find(choice);
		if (it == actionMap.end())
		{
			cout << "����������Ч������ѡ��" << endl;
		}
		else
		{
			it->second();
		}

	}
	/*
	switch (choice) // ���ã���Ϊ�������޷��պ�  �޷���������-�ա�ԭ�� ������ɾ�Ĺ���
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

//================================================== 1��function ===========================================
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
	// ��Ա�����ĵ��ã���������һ������  
	void hello(string str)       // void (Test::*pfunc)(string)
	{
		cout << str << endl;
	}
};

int main()
{
	/*
	1���ú�������ʵ����function
	2��ͨ��function����operator()������ʱ����Ҫ���ݺ������ʹ�����Ӧ�Ĳ���
	*/

	// ��function����ģ�嶨�崦������ϣ����һ����������ʵ����function
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




