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

Test t1(10, 10);   // ȫ�ֶ�����main����֮ǰ��ʼ��  1.Test(int a,int b)
int main()
{
	Test t2(20, 20); // 3.Test(int a,int b)
	Test t3 = t2;    // 4.Test(const Test&)
	// static Test t4(30,30);
	static Test t4 = Test(30, 30);   // 5.Test(int a,int b)������ʱ�������¶�����ʱ����ᱻ�Ż�����  �ֲ���̬�������ڴ�����һ��ʼ�ʹ��ڣ�����ʼ���������е����Ż��ʼ��
	t2 = Test(40, 40); // 6. ��ʱ����   Test(int a,int b) ==�� operator=(const Test&)     ==��    ~Test()
	// (50, 50)���ʽ === 50    Test(50)
	t2 = (Test)(50, 50); //7. ��ʽ������ʱ��������ǿת��  Test(int a,int b)  == ��  operator=(const Test&)    ==��    ~Test()
	t2 = 60;             //8. ��ʽ������ʱ��������ǿת��  Test(int a,int b)  == ��  operator=(const Test&)    ==��    ~Test()  

	Test* p1 = new Test(70, 70);   //9 .  1�����Ͽ����ڴ� 2���������  Test(int a,int b)
	Test* p2 = new Test[2];        //10.  1�����Ͽ����ڴ� 2���������  Test(int a,int b)  Test(int a,int b)
	// Test* p3 = &Test(80, 80);    // vs2022 ����  ��������ָ��ָ����ʱ����     vs2017����       11.    Test(int a,int b)     ==��     ~Test()            
	const Test& ref = Test(90, 90);     // 12.  Test(int a,int b)
	delete p1;    // 13.  ~Test()
	delete[]p2;   // 14.  ~Test()   ~Test()

	return 0;
}
Test t4(100, 100);     // ȫ�ֶ�����main����֮ǰ��ʼ��  2.Test(int a,int b)

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
	Test t3 = t1;  // ��Test t2(t1);һ��   // Test(const Test& t)

	// Test(20) ��ʾ������ʱ������ʱ����û�����֣��������ڣ����ڵ���䣬����������ʱ����ᱻ������
	// C++���������ڶ�����Ż�������ʱ���������¶����ʱ����ʱ����Ͳ������ˣ�ֱ�ӹ����¶���Ϳ�����
	Test t4 = Test(20);    // Test()       �������� Test t4(20);û������ģ���

	cout << "--------------------------" << endl;

	// t4.operator(t2)
	t4 = t2;
	// t4.operator(const Test& t)
	t4 = Test(30);          // ��ʱ�����ȹ��죬�ٸ�ֵ��t4, ��ʱ��������

	//��ʽ����ǿת  ��ʽ������ʱ����
	t4 = (Test)30;      // int -> Test(int)  
	// ��ʽ����ǿת  ��ʽ������ʱ����
	t4 = 30;        // int -> Test(int)   Test(30)

	cout << "--------------------------" << endl;
	
	// Test* p = &Test(40);    // vs2022 ����              ��& ��Ҫ����ֵ	07_C++����Ӧ���Ż�          ��ָ��ָ����ʱ�����ǲ���ȫ��
	// ������䣬pָ�����һ���Ѿ���������ʱ����    p��һ��Ұָ����

	const Test& ref = Test(50);   // ����ʱ�������������󲻻�������

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