#include<iostream>
#include<vector>
#include<algorithm>   // 包含了C++ STL里面的泛型算法
//#include<functional>
using namespace std;

/*
五、泛型算法 = template + 迭代器 + 函数对象
sort, find, find_if, binary_search, for_each .......

特点一：泛型算法的参数接收的都是迭代器
特点二：泛型算法的参数还可以接收函数对象



绑定器 + 二元函数对象 ===》 一元函数对象
bind1st:把二元函数的operator()(a,b)的第一个形参绑定起来
bind2nd:把二元函数的operator()(a,b)的第一个形参绑定起来
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

	// 默认小到大的排序
	sort(vec.begin(), vec.end());

	for (int v : vec)
	{
		cout << v << " ";
	}
	cout << endl;   // 9 19 20 24 32 45 67 72 78 83

	// 有序容器中二分查找
	if (binary_search(vec.begin(), vec.end(), 78))
	{
		cout << "binary_search 78存在" << endl;
	}

	auto it = find(vec.begin(), vec.end(), 78);
	if (it != vec.end())
	{
		cout << "find 78存在" << endl;
	}


	// 传入函数对象greater，改变容器元素排序时的比较方式
	sort(vec.begin(), vec.end(),greater<int>());
	for (int v : vec)
	{
		cout << v << " ";
	}
	cout << endl;  // 83 78 72 67 45 32 24 20 19 9

	// find_if 按条件查找
	// 把48按顺序插入到vector容器当中，找第一个小于48的数字
	// find_if需要的是一个一元函数对象
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


	//for_each可以遍历容器的所有元素，可以自行添加合适的函数对象对容器的元素进行过滤
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























