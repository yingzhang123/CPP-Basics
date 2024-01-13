#include<iostream>
#include<vector>

#include<string>
using namespace std;




//=======================================================  7.容器迭代器  ================================================
/*
容器迭代器
const_iterator:常量的正向迭代器    只能读，而不能写了(不能通过解引用迭代器改变容器的值)
iterator:普通的正向迭代器         (可读可写)
reverse_iterator:普通的反向迭代器
const_reverse_iterator:常量的反向迭代器
*/

#if 0
int main()
{
	vector<int> vec;
	for (int i = 0; i < 20; ++i)
	{
		vec.push_back(rand() % 100 + 1);
	}
	//vector<int>::iterator it  迭代器都是容器的嵌套类型，所以定义是需要加上容器作用域 
	// vector<int>::const_iterator it = vec.begin();
	/*
	class const_iterator
	{
	public:
		const T& operator*(){return *_ptr}
	}
	class iterator: public const_iterator       // 继承关系
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
	// rbegin():返回的是最后一个元素的反向迭代器表示
	// rend(): 返回的是首元素前驱位置的迭代器的表示
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



















