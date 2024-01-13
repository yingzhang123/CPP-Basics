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
	priority_queue<int> pque;  // �ײ㣺vector   Ĭ���Ǵ����
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

	using MinHeap = priority_queue<int, vector<int>, greater<int>>;  // greater<int>��������
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

//=======================================================  8.��������  ================================================
/*
��������   ==�� ����C���Եĺ���ָ
����operator()С������������غ����Ķ��󣬳�������������߳����º�����������������������
*/
/*
1.ͨ�������������operator()������ʡ�Ժ����ĵ��ÿ�������ͨ������ָ����ú��������ܹ�inline�������ã�Ч�ʸ�

2.��Ϊ��������ʹ�������ɵģ����Կ��������صĳ�Ա������������¼��������ʹ��ʱ�������Ϣ
*/

#if 0 
// C++��������İ汾ʵ��
template<typename T>
class MyGreater
{
public:
	bool operator()(T a, T b)        // ��Ԫ��������
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


// ʹ��C�ĺ���ָ��������
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

// compare��C++�⺯��ģ��
template<typename T,typename Compare>
bool compare(T a, T b, Compare Comp)  // ����ָ��
{
	// ͨ������ָ���ӵ���mygreater��myless
	// ͨ������ָ����ú�������û�а취�����ģ�Ч�ʺܵͣ���Ϊ�к������ÿ���
	return Comp(a,b);        

}

//template<typename T>
//bool compare(T a, T b)
//{
//	return a > b;
//}

int main()
{
	// ����ָ��
	cout << compare(10, 20, mygreater<int>) << endl;
	cout << compare('b', 'y', myless<char>) << endl;

	// �������󣨷º�����
	cout << compare(10, 20, MyGreater<int>()) << endl;
	cout << compare('b', 'y', MyLess<char>()) << endl;

	return 0;
}
#endif