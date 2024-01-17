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


// ���ܷ��ؾֲ��Ļ�����ʱ�����ָ�������
/*
1.�����������ݹ����У��������Ȱ����ô��ݣ���Ҫ��ֵ����
2.�������ض����ʱ��Ӧ�����ȷ���һ����ʱ���󣬶���Ҫ����һ��������Ķ���
3.���շ���ֵ�Ƕ���ĺ������õ�ʱ�����Ȱ���ʼ���ķ�ʽ���գ���Ҫ����ֵ�ķ�ʽ����
*/
Test GetObject(Test& t)   // 3.Test(const Test& t)  ʵ�ε��βε��ÿ������캯��           
{
	int val = t.getData();
	//Test tmp(val);       // 4.Test(int)
	//return tmp;

	// ������ʱ����    =====�� ����ʱ������һ���¶���  Test t = Test(val);  ====�� ������������һ���Ż�����ʱ���󶼲�������   ===�� Test(val)
	return Test(val);
}

int main()
{
	//Test t1;  // 1.Test(int)
	//Test t2;  // 2.Test(int)
	//t2 = GetObject(t1);
	//// �������ã�ʵ�� ==�� �β�      �ǳ�ʼ�������Ǹ�ֵ��  ===���ǳ�ʼ�����������Ĺ���

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
Test(const Test& t)      ==�� tmp��main����ջ֡�Ͽ���������ʱ����ֵ����
~Test()
~Test()
operator=(const Test& t)
~Test()
~Test()
~Test()
*/


/*                      1��2 �Ż��� 
Test(int)
Test(int)
Test(int)
operator=(const Test& t)
~Test()
~Test()
~Test()
*/

/*                        1��2��3�Ż���
Test(int)
Test(int)
~Test()
~Test()
*/