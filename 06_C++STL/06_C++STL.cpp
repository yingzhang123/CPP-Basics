#include<iostream>
#include<vector>
#include<deque>     // 双端队列
#include<list>      // 双向循环链表
#include<stack>
#include<queue>     // queue priority_queue
//使用有序关联容器包含的头文件
#include<set>       // set multiset
#include<map>       // map multimap
//使用无序关联容器包含的头文件
#include<unordered_set>
#include<unordered_map>
#include<string>
using namespace std;


/*
一、标准容器   (C++11 还有array数组 forward_list单向链表）
1、顺序容器
vector
deque
list

2、容器适配器
stack
queue
priority_queue

3.关联容器
无序关联容器  =======> 链式哈希表           增删查O（1）
set:集合 key         map:映射表[key,value]
unordered_set : 不允许key重复
unordered_multiset ：允许key重复
unordered_map  : 不允许key重复
unordered_multimap

有序关联容器  =======> 红黑树 增删查O(log2n)   （2是底数，n是树的层数，树的高度）
set
multiset
map
multimap


二、近容器
数组，string, bitset(位容器)

三、迭代器
iterator 和 const_iterator
reverse_iterator 和const_reverse_iterator

四、函数对象 (类似C的函数指针)
greater, less

五、泛型算法
sort, find, find_if, binary_search, for_each .......
*/




//=======================================================  6.有序关联容器  ================================================
#if 0 
class Student
{
public:
	// “Student::Student” : 没有合适的默认构造函数可用    ===========> map使用[]时，必须提供默认构造函数
	Student(int id=0, string name="") :_id(id), _name(name) {}
	//Student(int id, string name) :_id(id), _name(name) {}
	
	// 没有找到接受“const _Ty”类型的左操作数的运算符(或没有可接受的转换)   
	bool operator<(const Student& stu) const
	{
		return _id < stu._id;
	}
private:
	int _id;
	string _name;

	friend ostream& operator<<(ostream& out, const Student& stu);
};
ostream& operator<<(ostream& out, const Student& stu)
{
	out << stu._id << " " << stu._name << endl;
	return out;   // 为了连续赋值
}

int main()
{
	map<int, Student> stuMap;     // map是使用key来排序的，所以不需要重载比较运算符也可以
	stuMap.insert({ 1030,Student(1000,"张伟") });
	stuMap.insert({ 1010,Student(1010, "刘雯") });
	stuMap.insert({ 1020,Student(1020, "玲子") });

	// stu
	cout << stuMap[1000] << endl;

	for (auto v : stuMap)
	{
		cout << "key:" << v.first << " values:" << v.second;
	}

#if 0 
	set<Student> set2;     //  对于自定义类型，需要重载比较运算符
	set2.insert(Student(1020, "金科"));
	set2.insert(Student(1000, "刘雯"));
	set2.insert(Student(1010, "玲子"));

	//for (auto v : set2)
	//{
	//	cout << v;
	//}

	for (auto it = set2.begin(); it != set2.end(); ++it)
	{
		cout << *it;
	}

	/*
	1000 刘雯
	1010 玲子
	1020 金科
	*/
#endif

#if 0 
	set<int> set1;
	for (int i = 0; i < 20; ++i)
	{
		set1.insert(rand() % 100 + 1);
	}
	for (auto v : set1)
	{
		cout << v << " ";
	}  
	// 1 6 25 28 35 37 42 43 46 59 62 63 65 68 70 79 82 92 96
	cout << endl; 
#endif
	return 0;
}
#endif







//=======================================================  5.无序关联容器  ================================================
/*
关联容器：
1.各个容器底层的数据结构 O(1)  O(log2n)
2.常用增删查方法
增加 insert(val)
遍历 iterator自己搜索   调用set.find成员方法
删除 erase(key)  erase(it)
*/

#if 0
int main()
{
	/* map
	 [key,value]
	 struct pair
	 {
		first;    // key
		second;   // value
	 }

	 map的operator[]
	 1、查询
	 2. 如果key不存在，他会插入一对数据[key,string()]
		 相当于:
			 V& operator[](const K &key)
			 {
				insert({K,V()});
			 }
	*/

	// 处理海量数据查重复，去重复的时候
	//const int ARR_LEN = 100000;
	const int ARR_LEN = 100;
	int arr[ARR_LEN] = { 0 };
	for (int i = 0; i < ARR_LEN; ++i)
	{
		arr[i] = rand() % 20 + 1;
	}

	unordered_set<int> set;
	// 上面10万个整数中，把数字进行去重打印
	for (auto k : arr)     // O(n)
	{
		set.insert(k);     // O(1)
	}
	for (int v : set)
	{
		cout << v << " ";
	}

#endif

#if 0
	// 上面10万个整数中，统计哪些数字重复了，并且统计数字重复的次数
	unordered_map<int, int> map2;
	//for (int i = 0; i < ARR_LEN; ++i)
	//{
	//	//auto it1 = map2.find(arr[i]);
	//	//if (it1 == map2.end())     // 在哈希表中没出现过
	//	//{
	//	//	map2.insert({ arr[i], 1});
	//	//}
	//	//else
	//	//{
	//	//	map2[arr[i]]++;
	//	//}

	//	map2[arr[i]]++;

	//}

	for (auto k : arr)
	{
		//auto it1 = map2.find(k);
		//if (it1 == map2.end())
		//{
		//	map2.insert({ k, 1 });
		//}
		//else
		//{
		//	map2[k]++;
		//}

		map2[k]++;
	}


	// 第一种遍历
	for (const pair<int, int>& p : map2)
	{
		if (p.second > 1)
		{
			cout << "key:" << p.first << " count:" << p.second << endl;
		}
	}
	cout << "====================================" << endl;
	// 第二种遍历
	auto it = map2.begin();
	for (;it != map2.end();++it)
	{
		if (it->second > 1)
		{
			cout << "key:" << it->first << " count:" << it->second << endl;
		}
	}
#endif

	/*
	unordered_map<int, string> map1;
	map1.insert(make_pair(1000, "张三"));     // map表增加元素
	map1.insert({ 1010,"李四" });
	map1.insert({ 1020,"王五" });
	//map1.insert(make_pair(1000, "啊宝"));   // 键重复，会跳过插入
	map1.insert(make_pair(1030, "李李"));

	map1.erase(1020);                      // map删除元素

	auto it1 = map1.find(1030);
	if (it1 != map1.end())      // 找到了
	{
		// it1 -> pair 
		cout << "key:" << it1->first << " value:" << it1->second << endl;
	}

	//map1[2000];   // key:2000   // 查询操作     map1.insert({2000,""})
	//map1[2000] = "汪小姐";     // ===> 相当于插入操作  map1.insert({2000,"汪小姐"})
	//map1[1000] = "张三2";      // 相当于修改操作

	//cout << map1.size() << endl;   // 4
	//// map operator[](key) ==> value
	//cout << map1[1000] << endl;   // 张三
	*/
#if 0  set
	unordered_set<int> set1;   // 不会存储key值重复的元素
	for (int i = 0; i < 50; ++i)
	{
		set1.insert(rand() % 20 + 1);    // 与vector/deque/list 的insert(it,val)不同，unordered_set不用指定位置，unordered_set底层数据结构为哈希表，位置由哈希函数决定
	}

	//cout << set1.size() << endl;               // 18
	//cout << set1.count(15) << endl;            // 1

	auto it1 = set1.begin();
	for (; it1 != set1.end(); ++it1)
	{
		cout << *it1 << " ";
	}

	set1.erase(20);   //按值删除元素

	for (it1 = set1.begin();it1!=set1.end();)
	{
		if (*it1 == 20)
		{
			it1 = set1.erase(it1);   // 调用erase，it1迭代器就失效了
		}
		else 
		{
			++it1;
		}
	}

	it1 = set1.find(20);  // 如果存在，返回元素的迭代器，不存在返回end()；
	if (it1 != set1.end())
	{
		set1.erase(it1);
	}

	for (int v : set1)
	{
		cout << v << " ";
	}
	cout << endl;

	return 0;
}
#endif





//=======================================================  4.容器适配器  ================================================
/*
标准容器 - 容器适配器
怎么理解容器适配器？
1.适配器底层没有自己的数据结构，它是另外一个容器的封装，他的方法，全部由底层依赖的容器进行实现的
2.适配器没有实现自己的迭代器（不能用迭代器遍历适配器）

template<typename T,typename Container=deque<T>>
class Stack
{
public:
	void push(const T& val) { con.push(val); }
	void pop() { con.pop(); }
	void top()const { return con.back(); }
private:
	Container con;
};
*/

/*
stack : push入栈  pop出栈  top查看栈顶元素  empty判断栈空  size返回元素个数

queue : push入队  pop出队  front查看队头元素  back查看队尾元素  empty判断队空  size返回元素个数
stack ==> deque 为什么不依赖vector呢？
queue ==> deque 为什么不依赖vector呢？
1.vector的初始内存使用效率太低了！！没有deque好    
	queue<int>,stack<int>    vector初始内部扩容问题比较多（0-1-2-4-8-16）【但是可以通过reserve()函数接口预留内存空间，减少内存扩容次数】    deque 4096/sizeof(int)=1024
2.对于queue来说，需要支持尾部插入，头部删除操作最好是O(1)，所以选用deque比较好（如果queue依赖vector，其出队效率非常低）
3.vector需要大片的连续的内存，而deque只需要分段的内存，当存储大量数据时，显然deque对内存利用率更好一些

priority_queue: ppush入队  pop出队  top查看队顶元素  empty判断队空  size返回元素个数   【默认是大根堆】
priority_queue  ==> vector  为什么依赖vector呢？
                   底层默认把数据组成一个大根堆结构，在一个内存连续的数组上构建一个大根堆或者小根堆【下标关系】
*/

#if 0 

int main()
{
	priority_queue<int> pque;
	for (int i = 0; i < 20; ++i)
	{
		pque.push(rand() % 100 + 1);
	}

	cout << pque.size() << endl;

	while (!pque.empty())
	{
		cout << pque.top() << " ";
		pque.pop();
	}

	cout << endl;
	cout << "---------------------------------------------------------";
	cout << endl;

	queue<int> que;
	for (int i = 0; i < 20; ++i)
	{
		que.push(rand() % 100 + 1);
	}

	cout << que.size() << endl;

	while (!que.empty())
	{
		cout << que.front() << " ";
		que.pop();
	}

	cout << endl;
	cout << "---------------------------------------------------------";
	cout << endl;

	stack<int> s1;
	for (int i = 0; i < 20; ++i)
	{
		s1.push(rand() % 100 + 1);
	}
	
	cout << s1.size() << endl;

	while (!s1.empty())
	{
		cout << s1.top() << " ";
		s1.pop();
	}

	return 0;
}

#endif

//======================================================= 2.deque 和 list    ================================================
/*
#inclide<deque>
deque:双端队列容器
底层数据结构：动态开辟的二维数组，一维数组从2开始，以2倍的方式进行扩容，每次扩容后，原来第二维的数组，
从新的第一维数组的下标oldsize/2开始存放，上下都预留相同的空行，方便支持deque的首尾元素添加

deque<int> deq;
增加：
deq.push_back(20):从末尾添加元素 O(1)
deq.push_front(20):从首部添加元素 O(1)
deq.insert(it,20): it指向位置添加元素  O(n)

删除：
deq.pop_back(): 从末尾删除元素 O(1)
deq.pop_front(): 从首部删除元素 O(1)
deq.erase(it):  it指向位置删除元素  O(n)

查询搜索：
iterator(连续的insert和erase一定要考虑迭代器失效的问题)
//////////////////////////////////////////////////////// 
std::deque 提供了一种兼具随机访问和双端操作高效性的数据结构。在涉及频繁的两端操作时<※※>，std::deque 可能比 std::vector 更为适用。
需要注意的是，虽然 std::deque 在两端操作上高效，但在中间插入或删除元素的操作相对较慢，因为可能涉及到块的移动
///////////////////////////////////////////////////////

list:链表容器     底层数据结构：双向循环链表   pre data next
#include<list>
list<int> mylist;
增加：
mylist.push_back(20):从末尾添加元素 O(1)
mylist.push_front(20):从首部添加元素 O(1)
mylist.insert(it,20): it指向位置添加元素   （就插入这个动作而言，本身尾O(1)）O(1)  
										//链表中进行insert的时候，先要进行一个query查询操作，对链表来说，查询操作效率就比较慢了     

删除：
deq.pop_back(): 从末尾删除元素 O(1)
deq.pop_front(): 从首部删除元素 O(1)
deq.erase(it):  it指向位置删除元素  O(1)

查询搜索：
iterator(连续的insert和erase一定要考虑迭代器失效的问题)
/////////////////////////////////////////////////////////////
std::list 在许多场景中都是一个强大的工具，特别是在需要频繁插入和删除元素的情况下。
////////////////////////////////////////////////////////////

deque和list，比vector容器多出来的增加删除接口：
push_front和pop_front

*/

//======================================================= 3.vector deque 和 list 对比    ================================================
/*
vector特点：动态数组，内存时连续的，2倍的方式进行扩容
deque特点：动态开辟的二维数组空间，第二维时固定长度的数组空间；扩容的时候（第一维的数组进行2倍扩容）
			面经问题：deque底层是内存连续的？  并不是，每一个第二维是连续的


容器的纵向考察：容器掌握的深度
容器的横向考察：各个相似容器之间的对比
vector和deque之间的区别？
1.底层数据结构
2.前中后插入删除元素的时间复杂度：中间0(n),末尾O(1)    前：deque O(1)  vector 0(n)
3.对于内存使用效率： vector需要的内存空间必须是连续的   deque可以分块进行数据存储，不需要内存空间必须是一片连续的、
4.在中间进行insert或者erase，vector和deque它们的效率谁能好一点（vector√）？  谁更差一点（deque）?       虽然时间复杂度都是O（1），但是deque元素移动更复杂一些


vector和list之间堵塞区别？   数组：增加/删除0(n)  查询0(n)  下标访问O(1)      链表：(不考虑搜索的时间0(n))增加删除0(1)
1.底层数据结构：   数组         双向循环链表


*/

// 
//======================================================= 1.vector  ================================================
/*
vector:向量容器
底层数据结构：动态开辟的数组，每次以原来空间大小的2倍进行扩容的

vector<int> vec;
增加：
vec.push_back(20);  末尾添加元素 O(1)             可能会导致元素扩容
vec.insert(it,20);   it迭代器指向堵塞位置添加一个元素20    0(n)              导致元素扩容
删除：
vec.pop();    末尾删除元素
vec.erase(it);    删除it迭代器指向的元素  0(n)
查询：
operator[]  下标随机访问  O(1)
iterator迭代器进行遍历
find,for_each
foreach（基于范围的for语句） => 通过iterator来实现的

注意：对容器进行连续插入或者删除操作(insert/erase),一定要更新迭代器，否则第一次insert或者erase完成后,循环的迭代器就失效了

常用方法介绍：
size()
empty()
reserve(20):vector预留空间的    只给容器底层开辟指定大小的内存空间，并不会添加新的元素
resize():   容器扩容用的        不仅给容器底层开辟指定大小的内存空间，还添加新的元素
swap():     两个容器进行元素交换
*/

#if 0 

int main()
{
	
	vector<int> vec;   // 0 1 2 4 8 16 32 64 128 256
	vec.resize(20);    // 叫做给vector容器预留空间

	cout << vec.empty() << endl;
	cout << vec.size() << endl;
	for (int i = 0; i < 20; ++i)
	{
		vec.push_back(rand() % 100 + 1);
	}
	cout << vec.empty() << endl;
	cout << vec.size() << endl;
	/*
0
20
0
40
	*/

	//vector<int> vec;   // 0 1 2 4 8 16 32 64 128 256
	//vec.reserve(20);    // 叫做给vector容器预留空间

	//cout << vec.empty() << endl;
	//cout << vec.size() << endl;
	//for (int i = 0; i < 20; ++i)
	//{
	//	vec.push_back(rand() % 100 + 1);
	//}
	//cout << vec.empty() << endl;
	//cout << vec.size() << endl;
	/*
1
0
0
20
	*/

#if 0 
	vector<int> vec;
	for (int i = 0; i < 20; ++i)
	{
		vec.push_back(rand() % 100 + 1);
	}

	int size = vec.size();
	for (int i = 0; i < size; ++i)
	{
		cout << vec[i] << " ";   // vector的operator[]运算符重载函数
	}
	cout << endl;

	// 把vec容器中的所有偶数删除掉
	auto it2 = vec.begin();
	for (; it2 != vec.end();)
	{
		if ((*it2 % 2) == 0)
		{
			it2 = vec.erase(it2);        // 更新信息it2迭代器
		}
		else
		{
			++it2;
		}
	}

	size = vec.size();
	for (int i = 0; i < size; ++i)
	{
		cout << vec[i] << " ";   // vector的operator[]运算符重载函数
	}
	cout << endl;

	 // 把vec容器中的所有奇数前面都添加一个小于奇数一个1的偶数
	auto it3 = vec.begin();
	for (; it3 != vec.end(); it3+=2)
	{
		if ((*it3 % 2) != 0)
		{
			it3 = vec.insert(it3, *it3 - 1);
			//++it3;
		}
	}


	// 通过迭代器遍历vector容器
	auto it1 = vec.begin();
	for (; it1 != vec.end(); ++it1)
	{
		cout << *it1 << " ";
	}
	cout << endl;

#endif

	return 0;
}
#endif
