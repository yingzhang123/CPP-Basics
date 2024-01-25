#include<iostream>
#include<vector>
#include<algorithm>
#include<functional>
#include<typeinfo>
using namespace std;

/*
ģ�����ȫ�������ͷ���ȫ�����֣�������
ģ���ʵ������   ===> ��������ܼ�
*/

#if 0 
// T���������еĴ������ ����ֵ�������βε����Ͷ�ȡ����
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

#if 0       ģ�����ȫ�������ͷ���ȫ�����֣�������
// ԭģ��  # 3
template<typename T>
class Vector
{
public:
	Vector()
	{
		cout << "call Vector template init" << endl;
	}
};

// ��������Ƕ�char*�����ṩ����ȫ�������汾     # 1
template<>
class Vector<char*>
{
public:
	Vector()
	{
		cout << "call Vector<char*> template init" << endl;
	}
};

// ��������Ƕ�ָ�������ṩ�Ĳ����������汾     # 2
template<typename Ty>
class Vector<Ty*>
{
public:
	Vector()
	{
		cout << "call Vector<Ty*> template init" << endl;
	}
};

// ��Ժ���ָ�루�з���ֵ���������βα������ṩ�Ĳ���������
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

// ��Ժ���ָ���ṩ����ȫ������
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
	Vector<int(*)(int, int)> vec4;    // int(*)(int, int)����ָ�� 
	Vector<int(int, int)> vec5;       //function���������� 


	// ע������һ�º������ͺͺ���ָ������
	typedef int(*PFUNC)(int, int);  // ����ָ������
	PFUNC pfunc1 = sum;
	cout << pfunc1(1, 2) << endl;

	//typedef int(FUNC)(int, int);   //��������
	typedef int FUNC(int, int);   //��������
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

// �ṩ�������汾
template<>
bool compare<const char*>(const char* a, const char* b)
{
	cout << "tempalte compare<const char*>(const char* a, const char* b)" << endl;
	return strcmp(a,b)>0;
}

int main()
{
	compare(10, 20);
	compare("aaaa", "bbbb");  //����ģ���ʵ������==�� T const char*  ===> �Ƚϵ���������ַ���������ַ������ֵ���  ==�� ������ʵ�ʴ�����߼�

	return 0;
}
#endif