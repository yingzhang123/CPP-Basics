#include<iostream>
#include<vector>
#include<deque>   // ˫�˶���
#include<list>    // ˫��ѭ������
#include<stack>
#include<queue>     // queue priority_queue
//ʹ�������������������ͷ�ļ�
#include<set>    // set multiset
#include<map>    // map multimap
//ʹ�������������������ͷ�ļ�
#include<unordered_set>
#include<unordered_map>
#include<string>
using namespace std;


/*
һ����׼����   (C++11 ����array���� forward_list��������
1��˳������
vector
deque
list

2������������
stack
queue
priority_queue

3.��������
�����������  =======> ��ʽ��ϣ��           ��ɾ��O��1��
set:���� key         map:ӳ���[key,value]
unordered_set : ������key�ظ�
unordered_multiset ������key�ظ�
unordered_map  : ������key�ظ�
unordered_multimap

�����������  =======> ����� ��ɾ��O(log2n)   ��2�ǵ�����n�����Ĳ��������ĸ߶ȣ�
set
multiset
map
multimap


����������
���飬string, bitset(λ����)

����������
iterator �� const_iterator
reverse_iterator ��const_reverse_iterator

�ġ��������� (����C�ĺ���ָ��)
greater, less

�塢�����㷨
sort, find, find_if, binary_search, for_each .......
*/




//=======================================================  6.�����������  ================================================
#if 0 
class Student
{
public:
	// ��Student::Student�� : û�к��ʵ�Ĭ�Ϲ��캯������    ===========> mapʹ��[]ʱ�������ṩĬ�Ϲ��캯��
	Student(int id=0, string name="") :_id(id), _name(name) {}
	//Student(int id, string name) :_id(id), _name(name) {}
	
	// û���ҵ����ܡ�const _Ty�����͵���������������(��û�пɽ��ܵ�ת��)   
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
	return out;   // Ϊ��������ֵ
}

int main()
{
	map<int, Student> stuMap;     // map��ʹ��key������ģ����Բ���Ҫ���رȽ������Ҳ����
	stuMap.insert({ 1030,Student(1000,"��ΰ") });
	stuMap.insert({ 1010,Student(1010, "����") });
	stuMap.insert({ 1020,Student(1020, "����") });

	// stu
	cout << stuMap[1000] << endl;

	for (auto v : stuMap)
	{
		cout << "key:" << v.first << " values:" << v.second;
	}

#if 0 
	set<Student> set2;     //  �����Զ������ͣ���Ҫ���رȽ������
	set2.insert(Student(1020, "���"));
	set2.insert(Student(1000, "����"));
	set2.insert(Student(1010, "����"));

	//for (auto v : set2)
	//{
	//	cout << v;
	//}

	for (auto it = set2.begin(); it != set2.end(); ++it)
	{
		cout << *it;
	}

	/*
	1000 ����
	1010 ����
	1020 ���
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







//=======================================================  5.�����������  ================================================
/*
����������
1.���������ײ�����ݽṹ O(1)  O(log2n)
2.������ɾ�鷽��
���� insert(val)
���� iterator�Լ�����   ����set.find��Ա����
ɾ�� erase(key)  erase(it)
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

	 map��operator[]
	 1����ѯ
	 2. ���key�����ڣ��������һ������[key,string()]
		 �൱��:
			 V& operator[](const K &key)
			 {
				insert({K,V()});
			 }
	*/

	// ���������ݲ��ظ���ȥ�ظ���ʱ��
	//const int ARR_LEN = 100000;
	const int ARR_LEN = 100;
	int arr[ARR_LEN] = { 0 };
	for (int i = 0; i < ARR_LEN; ++i)
	{
		arr[i] = rand() % 20 + 1;
	}

	unordered_set<int> set;
	// ����10��������У������ֽ���ȥ�ش�ӡ
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
	// ����10��������У�ͳ����Щ�����ظ��ˣ�����ͳ�������ظ��Ĵ���
	unordered_map<int, int> map2;
	//for (int i = 0; i < ARR_LEN; ++i)
	//{
	//	//auto it1 = map2.find(arr[i]);
	//	//if (it1 == map2.end())     // �ڹ�ϣ����û���ֹ�
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


	// ��һ�ֱ���
	for (const pair<int, int>& p : map2)
	{
		if (p.second > 1)
		{
			cout << "key:" << p.first << " count:" << p.second << endl;
		}
	}
	cout << "====================================" << endl;
	// �ڶ��ֱ���
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
	map1.insert(make_pair(1000, "����"));     // map������Ԫ��
	map1.insert({ 1010,"����" });
	map1.insert({ 1020,"����" });
	//map1.insert(make_pair(1000, "����"));   // ���ظ�������������
	map1.insert(make_pair(1030, "����"));

	map1.erase(1020);                      // mapɾ��Ԫ��

	auto it1 = map1.find(1030);
	if (it1 != map1.end())      // �ҵ���
	{
		// it1 -> pair 
		cout << "key:" << it1->first << " value:" << it1->second << endl;
	}

	//map1[2000];   // key:2000   // ��ѯ����     map1.insert({2000,""})
	//map1[2000] = "��С��";     // ===> �൱�ڲ������  map1.insert({2000,"��С��"})
	//map1[1000] = "����2";      // �൱���޸Ĳ���

	//cout << map1.size() << endl;   // 4
	//// map operator[](key) ==> value
	//cout << map1[1000] << endl;   // ����
	*/
#if 0  set
	unordered_set<int> set1;   // ����洢keyֵ�ظ���Ԫ��
	for (int i = 0; i < 50; ++i)
	{
		set1.insert(rand() % 20 + 1);    // ��vector/deque/list ��insert(it,val)��ͬ��unordered_set����ָ��λ�ã�unordered_set�ײ����ݽṹΪ��ϣ��λ���ɹ�ϣ��������
	}

	//cout << set1.size() << endl;               // 18
	//cout << set1.count(15) << endl;            // 1

	auto it1 = set1.begin();
	for (; it1 != set1.end(); ++it1)
	{
		cout << *it1 << " ";
	}

	set1.erase(20);   //��ֵɾ��Ԫ��

	for (it1 = set1.begin();it1!=set1.end();)
	{
		if (*it1 == 20)
		{
			it1 = set1.erase(it1);   // ����erase��it1��������ʧЧ��
		}
		else 
		{
			++it1;
		}
	}

	it1 = set1.find(20);  // ������ڣ�����Ԫ�صĵ������������ڷ���end()��
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





//=======================================================  4.����������  ================================================
/*
��׼���� - ����������
��ô���������������
1.�������ײ�û���Լ������ݽṹ����������һ�������ķ�װ�����ķ�����ȫ���ɵײ���������������ʵ�ֵ�
2.������û��ʵ���Լ��ĵ������������õ�����������������

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
stack : push��ջ  pop��ջ  top�鿴ջ��Ԫ��  empty�ж�ջ��  size����Ԫ�ظ���

queue : push���  pop����  front�鿴��ͷԪ��  back�鿴��βԪ��  empty�ж϶ӿ�  size����Ԫ�ظ���
stack ==> deque Ϊʲô������vector�أ�
queue ==> deque Ϊʲô������vector�أ�
1.vector�ĳ�ʼ�ڴ�ʹ��Ч��̫���ˣ���û��deque��    
	queue<int>,stack<int>    vector��ʼ�ڲ���������Ƚ϶ࣨ0-1-2-4-8-16�������ǿ���ͨ��reserve()�����ӿ�Ԥ���ڴ�ռ䣬�����ڴ����ݴ�����    deque 4096/sizeof(int)=1024
2.����queue��˵����Ҫ֧��β�����룬ͷ��ɾ�����������O(1)������ѡ��deque�ȽϺã����queue����vector�������Ч�ʷǳ��ͣ�
3.vector��Ҫ��Ƭ���������ڴ棬��dequeֻ��Ҫ�ֶε��ڴ棬���洢��������ʱ����Ȼdeque���ڴ������ʸ���һЩ

priority_queue: ppush���  pop����  top�鿴�Ӷ�Ԫ��  empty�ж϶ӿ�  size����Ԫ�ظ���   ��Ĭ���Ǵ���ѡ�
priority_queue  ==> vector  Ϊʲô����vector�أ�
                   �ײ�Ĭ�ϰ��������һ������ѽṹ����һ���ڴ������������Ϲ���һ������ѻ���С���ѡ��±��ϵ��
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

//======================================================= 2.deque �� list    ================================================
/*
#inclide<deque>
deque:˫�˶�������
�ײ����ݽṹ����̬���ٵĶ�ά���飬һά�����2��ʼ����2���ķ�ʽ�������ݣ�ÿ�����ݺ�ԭ���ڶ�ά�����飬
���µĵ�һά������±�oldsize/2��ʼ��ţ����¶�Ԥ����ͬ�Ŀ��У�����֧��deque����βԪ�����

deque<int> deq;
���ӣ�
deq.push_back(20):��ĩβ���Ԫ�� O(1)
deq.push_front(20):���ײ����Ԫ�� O(1)
deq.insert(it,20): itָ��λ�����Ԫ��  O(n)

ɾ����
deq.pop_back(): ��ĩβɾ��Ԫ�� O(1)
deq.pop_front(): ���ײ�ɾ��Ԫ�� O(1)
deq.erase(it):  itָ��λ��ɾ��Ԫ��  O(n)

��ѯ������
iterator(������insert��eraseһ��Ҫ���ǵ�����ʧЧ������)
//////////////////////////////////////////////////////// 
std::deque �ṩ��һ�ּ��������ʺ�˫�˲�����Ч�Ե����ݽṹ�����漰Ƶ�������˲���ʱ<����>��std::deque ���ܱ� std::vector ��Ϊ���á�
��Ҫע����ǣ���Ȼ std::deque �����˲����ϸ�Ч�������м�����ɾ��Ԫ�صĲ�����Խ�������Ϊ�����漰������ƶ�
///////////////////////////////////////////////////////

list:��������     �ײ����ݽṹ��˫��ѭ������   pre data next
#include<list>
list<int> mylist;
���ӣ�
mylist.push_back(20):��ĩβ���Ԫ�� O(1)
mylist.push_front(20):���ײ����Ԫ�� O(1)
mylist.insert(it,20): itָ��λ�����Ԫ��   ���Ͳ�������������ԣ�����βO(1)��O(1)  
										//�����н���insert��ʱ����Ҫ����һ��query��ѯ��������������˵����ѯ����Ч�ʾͱȽ�����     

ɾ����
deq.pop_back(): ��ĩβɾ��Ԫ�� O(1)
deq.pop_front(): ���ײ�ɾ��Ԫ�� O(1)
deq.erase(it):  itָ��λ��ɾ��Ԫ��  O(1)

��ѯ������
iterator(������insert��eraseһ��Ҫ���ǵ�����ʧЧ������)
/////////////////////////////////////////////////////////////
std::list ����ೡ���ж���һ��ǿ��Ĺ��ߣ��ر�������ҪƵ�������ɾ��Ԫ�ص�����¡�
////////////////////////////////////////////////////////////

deque��list����vector���������������ɾ���ӿڣ�
push_front��pop_front

*/

//======================================================= 3.vector deque �� list �Ա�    ================================================
/*
vector�ص㣺��̬���飬�ڴ�ʱ�����ģ�2���ķ�ʽ��������
deque�ص㣺��̬���ٵĶ�ά����ռ䣬�ڶ�άʱ�̶����ȵ�����ռ䣻���ݵ�ʱ�򣨵�һά���������2�����ݣ�
			�澭���⣺deque�ײ����ڴ������ģ�  �����ǣ�ÿһ���ڶ�ά��������


���������򿼲죺�������յ����
�����ĺ��򿼲죺������������֮��ĶԱ�
vector��deque֮�������
1.�ײ����ݽṹ
2.ǰ�к����ɾ��Ԫ�ص�ʱ�临�Ӷȣ��м�0(n),ĩβO(1)    ǰ��deque O(1)  vector 0(n)
3.�����ڴ�ʹ��Ч�ʣ� vector��Ҫ���ڴ�ռ������������   deque���Էֿ�������ݴ洢������Ҫ�ڴ�ռ������һƬ�����ġ�
4.���м����insert����erase��vector��deque���ǵ�Ч��˭�ܺ�һ�㣨vector�̣���  ˭����һ�㣨deque��?       ��Ȼʱ�临�Ӷȶ���O��1��������dequeԪ���ƶ�������һЩ


vector��list֮���������   ���飺����/ɾ��0(n)  ��ѯ0(n)  �±����O(1)      ����(������������ʱ��0(n))����ɾ��0(1)
1.�ײ����ݽṹ��   ����         ˫��ѭ������


*/

// 
//======================================================= 1.vector  ================================================
/*
vector:��������
�ײ����ݽṹ����̬���ٵ����飬ÿ����ԭ���ռ��С��2���������ݵ�

vector<int> vec;
���ӣ�
vec.push_back(20);  ĩβ���Ԫ�� O(1)             ���ܻᵼ��Ԫ������
vec.insert(it,20);   it������ָ�����λ�����һ��Ԫ��20    0(n)              ����Ԫ������
ɾ����
vec.pop();    ĩβɾ��Ԫ��
vec.erase(it);    ɾ��it������ָ���Ԫ��  0(n)
��ѯ��
operator[]  �±��������  O(1)
iterator���������б���
find,for_each
foreach�����ڷ�Χ��for��䣩 => ͨ��iterator��ʵ�ֵ�

ע�⣺���������������������ɾ������(insert/erase),һ��Ҫ���µ������������һ��insert����erase��ɺ�,ѭ���ĵ�������ʧЧ��

���÷������ܣ�
size()
empty()
reserve(20):vectorԤ���ռ��    ֻ�������ײ㿪��ָ����С���ڴ�ռ䣬����������µ�Ԫ��
resize():   ���������õ�        �����������ײ㿪��ָ����С���ڴ�ռ䣬������µ�Ԫ��
swap():     ������������Ԫ�ؽ���
*/

#if 0 

int main()
{
	
	vector<int> vec;   // 0 1 2 4 8 16 32 64 128 256
	vec.resize(20);    // ������vector����Ԥ���ռ�

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
	//vec.reserve(20);    // ������vector����Ԥ���ռ�

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
		cout << vec[i] << " ";   // vector��operator[]��������غ���
	}
	cout << endl;

	// ��vec�����е�����ż��ɾ����
	auto it2 = vec.begin();
	for (; it2 != vec.end();)
	{
		if ((*it2 % 2) == 0)
		{
			it2 = vec.erase(it2);        // ������Ϣit2������
		}
		else
		{
			++it2;
		}
	}

	size = vec.size();
	for (int i = 0; i < size; ++i)
	{
		cout << vec[i] << " ";   // vector��operator[]��������غ���
	}
	cout << endl;

	 // ��vec�����е���������ǰ�涼���һ��С������һ��1��ż��
	auto it3 = vec.begin();
	for (; it3 != vec.end(); it3+=2)
	{
		if ((*it3 % 2) != 0)
		{
			it3 = vec.insert(it3, *it3 - 1);
			//++it3;
		}
	}


	// ͨ������������vector����
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
