
#include<iostream>
#include<vector>
#include<algorithm>
#include<functional>
using namespace std;

/*
绑定器和函数对象operator()
1、C++ STL中得绑定器
bind1st：operator()的第一个变量绑定一个确定的值
bind2nd：operator()的第二个变量绑定一个确定的值

2、C++11从Boost库中引入了bind和function机制

3、lambda表达式：底层依赖函数对象的机制实现的

*/

template<typename Container>
void showContainer(Container &con)
{
	typename Container::iterator it = con.begin();
	for (; it != con.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;
}

// 自定义my_find_if
template<typename Iterator,typename Compare>
Iterator my_find_if(Iterator first, Iterator last, Compare comp)
{
	for (; first != last; ++first)
	{
		if (comp(*first))     // comp.operator()(*first)
		{
			return first; 
		}
	}
	return last;
}

//===================================================================================
template<typename Compare, typename T>
class _mybind1st            // 帮顶起是函数对象的一个应用
{
public:
	_mybind1st(Compare comp, T val)
		:_comp(comp)
		, _val(val)
	{

	}
	bool operator()(const T& second)   // 一元函数对象
	{
		return _comp(_val, second);
	}
private:
	Compare _comp;
	T _val;
};


template<typename Compare,typename T>
_mybind1st<Compare, T> mybind1st(Compare comp, const T& val)
{
	// 直接使用函数模板，好处是，可以进行类型的推演
	return _mybind1st<Compare, T>(comp, val);
}
//===================================================================================
template<typename Compare, typename T>
class _mybind2nd            // 帮顶起是函数对象的一个应用
{
public:
	_mybind2nd(Compare comp, T val)
		:_comp(comp)
		, _val(val)
	{

	}
	bool operator()(const T& second)   // 一元函数对象
	{
		return _comp(second, _val);
	}
private:
	Compare _comp;
	T _val;
};


template<typename Compare, typename T>
_mybind2nd<Compare, T> mybind2nd(Compare comp, const T& val)
{
	// 直接使用函数模板，好处是，可以进行类型的推演
	return _mybind2nd<Compare, T>(comp, val);
}
//===================================================================================
#if 0
int main()
{
	vector<int> vec;
	srand(time(nullptr));
	for (int i = 0; i < 20; ++i)
	{
		vec.push_back(rand() % 100 + 1);
	}
	showContainer(vec);
	std::sort(vec.begin(), vec.end());        //    _STD sort(_First, _Last, less<>{});
	showContainer(vec);


	std::sort(vec.begin(), vec.end(),greater<int>());
	showContainer(vec);

	// find_if 按条件查找
	// 把48按顺序插入到vector容器当中  === > 找第一个小于48的数字
	// find_if需要的是一个一元函数对象
	// greater a(48)>b     less a<b(48)
	/*
	绑定器 + 二元函数对象 ===》 一元函数对象
	bind1st + greater bool oprator()(48,_ty& _Right)
	bind2nd + less bool oprator()(_ty& _Left,48)
	*/
	auto it2 = my_find_if(vec.begin(), vec.end(),
		// bind1st(greater<int>(), 48));
		// mybind1st(greater<int>(), 48)
		// bind2nd(less<int>(), 48))
		mybind2nd(less<int>(), 48)
		// [](int val)->bool {return val < 48; }
	);
	if (it2 != vec.end())
	{
		vec.insert(it2, 48);
	}
	showContainer(vec);

	return 0;
}
#endif