#include <iostream>
#include <functional>
#include <vector>
#include <map>
#include <memory>
#include <queue>
#include <algorithm>
using namespace std;



/*
lambda���ʽֻ��ʹ������䵱�У����������ʹ��֮ǰ����õ�lambda���ʽ��
��ô�죿��ʲô��������ʾlambda���ʽ��
==============>��Ȼʱ��function��������ʾ��������������                         bind1st/bind2nd   bind����===�����صĶ��Ǻ�������

lambda���ʽ  ====�� ��������  =====��function

*/
class Data
{
public:
	Data(int val1 = 10, int val2 = 10) : ma(val1), mb(val2) {}
	/*bool operator>(const Data& data) const { return ma > data.ma; }     // �����̫��
	bool operator<(const Data& data) const { return ma < data.ma; }*/
	int mb;
	int ma;
};

int main()
{
	// ����ָ���Զ���ɾ����     
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

	cout << "ѡ��:";
	int choice;
	cin >> choice;
	cout << "10 + 15 = " << caculateMap[choice](10, 15) << endl;

	return 0;
}
#endif


//=================================================================================================
/*
lambda���ʽ���﷨
[�����ⲿ����](�β��б�)->����ֵ{��������}

���lambda���ʽ�ķ���ֵ����Ҫ����ô"->����ֵ"����ʡ�Ե�
*/

/*
lambda���ʽ���﷨��
[�����ⲿ����]���β��б�)->����ֵ{��������};

���lambda���ʽ�ķ���ֵ����Ҫ����ô"->����ֵ"����ʡ��

[�����ⲿ����]
[]: ��ʾ�������κ��ⲿ����
[=]: �Դ�ֵ�ķ�ʽ�����ⲿ�����б���
[&]: �Դ����õķ�ʽ�����ⲿ�����б���
[this]: �����ⲿ��thisָ��   ��һ�����ڲ���ǰ�����thisָ�룩
[=, &a]: �Դ�ֵ�ķ�ʽ�����ⲿ�����б���������a�����Դ����õķ�ʽ����
[a, b]: ��ֵ���ݵķ�ʽ�����ⲿ����a��b
[a, &b]: a��ֵ���ݲ���b�Դ����õķ�ʽ����
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
		// ������û���޸���ı����������ݣ�ֻ�Ǹı�ma,mb���õ��ڴ棡������(���õײ�Ҳ��ָ�룡����)
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
	cout << t2(20, 30) << endl;      // ��lambdaһģһ��������lambda���ʽ�ǳ�����




	int a = 10;
	int b = 20;
	//auto func3 = [a, b]() mutable 
	//	{
	//		int tmp = a;          // ��lambda���ʽ���޷�ֱ��ʹ��a,b,��Ҫ�����ⲿ��a,b���ܷ���
	//		a = b;
	//		b = tmp;
	//	};
	//func3();
	//TestLambda03 t3(a, b);
	//t3();
	//cout << "a:" << a << " b:" << b << endl;             <=================== �޷��޸��ⲿa,b��ֵ


	//auto func4 = [&a, &b]()  // �����ô��ݣ�mutable���ü���
	//{
	//	int tmp = a;
	//	a = b;
	//	b = tmp;
	//};
	//func4();                                            //��============  �ɹ������ⲿ��a,b��ֵ
	//cout << "a:" << a << " b:" << b << endl;

	TestLambda04 t4(a, b);
	t4();
	cout << "a:" << a << " b:" << b << endl;               //��============  �ɹ������ⲿ��a,b��ֵ
#endif

	// lambda���ʽ��Ӧ��
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

	// 65�����������  Ҫ�ҵ�һ��С��65������
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