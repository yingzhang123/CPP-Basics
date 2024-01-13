#include<iostream>
#include<vector>
#include<algorithm>   // ������C++ STL����ķ����㷨
//#include<functional>
using namespace std;

/*
�塢�����㷨 = template + ������ + ��������
sort, find, find_if, binary_search, for_each .......

�ص�һ�������㷨�Ĳ������յĶ��ǵ�����
�ص���������㷨�Ĳ��������Խ��պ�������



���� + ��Ԫ�������� ===�� һԪ��������
bind1st:�Ѷ�Ԫ������operator()(a,b)�ĵ�һ���βΰ�����
bind2nd:�Ѷ�Ԫ������operator()(a,b)�ĵ�һ���βΰ�����
*/

int main()
{
	int arr[] = { 9,78,67,83,24,45,32,72,19,20 };
	vector<int> vec(arr, arr + sizeof(arr) / sizeof(arr[0]));
	
	for (int v : vec)
	{
		cout << v << " ";
	}
	cout << endl;   // 9 78 67 83 24 45 32 72 19 20

	// Ĭ��С���������
	sort(vec.begin(), vec.end());

	for (int v : vec)
	{
		cout << v << " ";
	}
	cout << endl;   // 9 19 20 24 32 45 67 72 78 83

	// ���������ж��ֲ���
	if (binary_search(vec.begin(), vec.end(), 78))
	{
		cout << "binary_search 78����" << endl;
	}

	auto it = find(vec.begin(), vec.end(), 78);
	if (it != vec.end())
	{
		cout << "find 78����" << endl;
	}


	// ���뺯������greater���ı�����Ԫ������ʱ�ıȽϷ�ʽ
	sort(vec.begin(), vec.end(),greater<int>());
	for (int v : vec)
	{
		cout << v << " ";
	}
	cout << endl;  // 83 78 72 67 45 32 24 20 19 9

	// find_if ����������
	// ��48��˳����뵽vector�������У��ҵ�һ��С��48������
	// find_if��Ҫ����һ��һԪ��������
	// greater a(48)>b     less a<b(48)
	auto it2 = find_if(vec.begin(), vec.end(),
		//bind1st(greater<int>(), 48));
		//bind2nd(less<int>(), 48));
		[](int val)->bool {return val < 48; });

	vec.insert(it2, 48);
	for (int v : vec)
	{
		cout << v << " ";
	}
	cout << endl;  // 83 78 72 67 48 45 32 24 20 19 9


	//for_each���Ա�������������Ԫ�أ�����������Ӻ��ʵĺ��������������Ԫ�ؽ��й���
	for_each(vec.begin(), vec.end(),
		[](int val)->void
		{
			if (val % 2 == 0)
			{
				cout << val << " ";
			}
		});
	cout << endl;    // 78 72 48 32 24 20

	return 0;
}























