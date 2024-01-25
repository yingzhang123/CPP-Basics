
#include<iostream>
#include<vector>
#include<algorithm>
#include<functional>
using namespace std;

/*
�����ͺ�������operator()
1��C++ STL�еð���
bind1st��operator()�ĵ�һ��������һ��ȷ����ֵ
bind2nd��operator()�ĵڶ���������һ��ȷ����ֵ

2��C++11��Boost����������bind��function����

3��lambda���ʽ���ײ�������������Ļ���ʵ�ֵ�

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

// �Զ���my_find_if
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
class _mybind1st            // �ﶥ���Ǻ��������һ��Ӧ��
{
public:
	_mybind1st(Compare comp, T val)
		:_comp(comp)
		, _val(val)
	{

	}
	bool operator()(const T& second)   // һԪ��������
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
	// ֱ��ʹ�ú���ģ�壬�ô��ǣ����Խ������͵�����
	return _mybind1st<Compare, T>(comp, val);
}
//===================================================================================
template<typename Compare, typename T>
class _mybind2nd            // �ﶥ���Ǻ��������һ��Ӧ��
{
public:
	_mybind2nd(Compare comp, T val)
		:_comp(comp)
		, _val(val)
	{

	}
	bool operator()(const T& second)   // һԪ��������
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
	// ֱ��ʹ�ú���ģ�壬�ô��ǣ����Խ������͵�����
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

	// find_if ����������
	// ��48��˳����뵽vector��������  === > �ҵ�һ��С��48������
	// find_if��Ҫ����һ��һԪ��������
	// greater a(48)>b     less a<b(48)
	/*
	���� + ��Ԫ�������� ===�� һԪ��������
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