#include<iostream>
#include<vector>

#include<string>
using namespace std;




//=======================================================  7.����������  ================================================
/*
����������
const_iterator:���������������    ֻ�ܶ���������д��(����ͨ�������õ������ı�������ֵ)
iterator:��ͨ�����������         (�ɶ���д)
reverse_iterator:��ͨ�ķ��������
const_reverse_iterator:�����ķ��������
*/

#if 0
int main()
{
	vector<int> vec;
	for (int i = 0; i < 20; ++i)
	{
		vec.push_back(rand() % 100 + 1);
	}
	//vector<int>::iterator it  ����������������Ƕ�����ͣ����Զ�������Ҫ�������������� 
	// vector<int>::const_iterator it = vec.begin();
	/*
	class const_iterator
	{
	public:
		const T& operator*(){return *_ptr}
	}
	class iterator: public const_iterator       // �̳й�ϵ
	{
	public:
		T& operator*(){return *_ptr}
	}

	*/

	vector<int>::iterator it = vec.begin();         // auto it = vec.begin()
	for (; it != vec.end(); ++it)
	{
		cout << *it << " ";
		//if (*it % 2 == 0) 
		//{
		//	*it = 0;
		//}
	}
	cout << endl;
	// rbegin():���ص������һ��Ԫ�صķ����������ʾ
	// rend(): ���ص�����Ԫ��ǰ��λ�õĵ������ı�ʾ
	vector<int>::reverse_iterator rit = vec.rbegin();
	for (; rit != vec.rend(); ++rit)
	{
		cout << *rit << " ";
	}
	cout << endl;

	//for (auto v : vec)
	//{
	//	cout << v << " ";
	//}
	//cout << endl;

	return 0;
}

#endif



















