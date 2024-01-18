#include<iostream>


//=========================================================== 1.C++����ģ�� =====================================
/*
C++����ģ��
ģ������壺������Ҳ���Խ��в�����   ��=========================  ��ģ���ڿ������ʱ��ܳ��ã�
int sum(int a,int b)(return a+b);


����ģ��               ��============ �ǲ����б���ģ���Ϊ���Ͳ�֪��
ģ���ʵ����        ��============  �������õ����ʵ����
ģ�庯��               ��============   ����Ҫ���������������
 
ģ�����Ͳ���         typename/class
ģ������Ͳ���

ģ���ʵ������                ====��      ���Ը����û������ʵ�ε����ͣ����Ƶ���ģ�����Ͳ����ľ�������
ģ�����������ר�û���   ====��      ���⣨���Ǳ������ṩ�ģ������û��ṩ�ģ���ʵ����
����ģ�塢ģ�������������ģ�庯�������ع�ϵ


[ģ������ǲ��ܹ���һ���ļ��ж���ģ�������һ���ļ�ʹ�õ�]
ģ��������ǰ��һ��Ҫ����ģ�嶨��ĵط��������Ļ���ģ����ܹ�����������ʵ�����������ܹ�������������Ĵ���

���ԣ�ģ����붼�Ƿ���ͷ�ļ����еģ�Ȼ����Դ�ļ�����ֱ�ӽ���#include����
*/

#if 0
// ����ģ��
template<typename T>    //����һ��ģ������б�   typename����classҲ����
bool compare(T a, T b)      // compares��һ������ģ��
{
	std::cout << "tempalte compare" << std::endl;
	return a > b;
}

// ģ���������
// ���compare����ģ�壬�ṩconst char*���͵��������汾
template<>
bool compare<const char*>(const char* a, const char* b)
{
	std::cout << "compare<const char*>" << std::endl;
	return strcmp(a, b) > 0;
}

// ��ģ�庯��
// ��ģ�庯�� - ��ͨ���� 
bool compare(const char* a, const char* b)
{
	std::cout << "normal compare" << std::endl;
	return strcmp(a, b) > 0;
}

int main()
{
	// �������õ�
	compare<int>(10, 20);
	compare<double>(10.0, 21.0);

	// ����ģ��ʵ�ε�����
	compare(10, 20);


	// ��compare�� : δ�ҵ�ƥ������غ���     û��������б�ƥ��ĺ���ģ��"compare"ʵ��
	// compare(10, 20.8);
	compare<int>(10, 20.8);  //���ǿ����ֶ�ָ����������     ���ӡ�double��ת������T�������ܶ�ʧ���ݣ�


	// ����ģ��ʵ�ε����� T ===�� const char* 
	// ����ĳЩ������˵������������Ĭ��ʵ������ģ����룬���봦���߼��ǲ����ϵģ������⣩
	// ���������Ȱ�compare����ɺ������֣�û�еĻ�����ȥ��compareģ��
	compare("aaa", "bbb");    

	//compare("aaa", "bbb");    // ����з�ģ�庯�������������ȵ��÷�ģ�庯��

	return 0;
}
#endif

/*
�ں������õ㣬���������û�ָ�������ͣ���ԭģ��ʵ����һ�ݺ���������� ==��ģ�庯��
ģ�庯����
bool compare<int>(int a,int b)
{
	return a>b;
}

bool compare<double>(double a,double b)
{
	return a>b;
}

bool compare<const char*>(const char* a,const char* b)
{
	return a>b;         // �����⣺ֻ�ǱȽ�������ַ��������   ����� return strcmp(a,b)>0;
}

*/


//=========================================================== 2.C++ ��ģ�� =====================================
/*
����ģ��
ģ��ķ����Ͳ���     �������������ͣ��������ߵ�ַ/���ö����ԣ�       ���ǳ�����ֻ��ʹ�ã��������޸�

��ģ��   +===�� ʵ����   ====��  ģ���� 

*/

#if 0
//��ģ��
template<typename T=int>   // ��ģ�廹���Լ�Ĭ�ϲ���
class SeqStack     // SeqStackΪģ���� + ���Ͳ����б� ==�� ������
{
public:
	// ������������������Բ��ü�<T>Ҳ���ԣ���������ģ��ĵط������ϲ����б�
	SeqStack(int size=10) 
		:_pstack(new T[size])
		,_top(0)
		,_size(size)
	{
		//_pstack = new T[size];
	}

	~SeqStack()
	{
		delete[]_pstack;
		_pstack = nullptr;
	}

	SeqStack(const SeqStack<T>& other)
		:_top(other._top)
		,_size(other._size)
	{
		_pstack = new T[other.size];
		// ��Ҫ��memcpy���п�����������������Ȼ��ĳЩ����¿���ʹ��memcpy()�����������ڴ渴�ƣ�
		// ���ڰ���ָ���̬�ڴ����Ķ���memcpy()������ȷ�����������캯����Ҫȷ������ʱ�����ʵ�����Դ�����Ա�����Դй©���ظ��ͷţ�
		for (int i = 0; i < top; i++)
		{
			_pstack[i] = other._pstack[i];     // ����ö���ĸ�ֵ��������غ���
		}
	}

	SeqStack<T>& operator=(const SeqStack<T>& other)
	{
		if (this == &other)   // ��ֹ�Ը�ֵ
		{
			return *this;
		}

		delete[] _pstack;    // �ͷ�ԭ��ռ�õ��ڴ�

		_top = other._top;
		_size = other._size;
		_pstack = new T[_size];
		// ��Ҫ��memcpy���п�����������������Ȼ��ĳЩ����¿���ʹ��memcpy()�����������ڴ渴�ƣ�
		// ���ڰ���ָ���̬�ڴ����Ķ���memcpy()������ȷ�����������캯����Ҫȷ������ʱ�����ʵ�����Դ�����Ա�����Դй©���ظ��ͷţ�
		for (int i = 0; i < top; i++)
		{
			_pstack[i] = other._pstack[i];     // ����ö���ĸ�ֵ��������غ���
		}

		return *this;
	}

	void push(const T& val);     // ��ջ����
	//{
	//	if (full())
	//		expand();

	//	_pstack[_top++] = val;
	//}

	void pop()       // ��ջ����
	{
		if (empty())
			return;
		--_top;
	}

	T top() const    // ����ջ��Ԫ��
	{
		if (empty())
			throw "stack is empty";   //�׳��쳣Ҳ�������߼�����
		return _pstack[_top - 1];
	}
	bool full() const { return _top == _size; }  // ջ��
	bool empty() const { return _top == 0; }     // ջ��

private:
	T* _pstack;
	int _top;
	int _size;

	// ˳��ջ�ײ����鰴2���ķ�ʽ����
	void expand()
	{
		T* ptmp = new T[_size * 2];
		for (int i = 0; i < top; i++)
		{
			ptmp[i] = _pstack[i];
		}
		delete[] _pstack;
		_pstack = ptmp;
		_size *= 2;
	}
};

// ����ʵ��
template<typename T>
void SeqStack<T>::push(const T& val)
{
	if (full())
		expand();

	_pstack[_top++] = val;
}


int main()
{
	// ��ģ���ѡ����ʵ����������Ҫʹ�õ����ĳЩ�����ǣ��Ż�ʵ������û���õ��ĺ������������������
	// ģ����  class SeqStack<int>{};
	SeqStack<int> s1;
	s1.push(32);
	s1.push(92);
	s1.push(82);
	s1.push(42);
	s1.push(22);
	s1.push(12);
	s1.pop();
	std::cout << s1.top() << std::endl;

	SeqStack<> s2;

	return 0;
}
#endif

//   ģ��ķ����Ͳ��� 
#if 0      
template<typename T, int SIZE>   // int SIZE:ģ��ķ����Ͳ���
void sort(T *arr)
{
	for (int i = 0; i < SIZE - 1; ++i)
	{
		for (int j = 0; j < SIZE - 1 - i; ++j)
		{
			if (arr[j] > arr[j + 1])
			{
				T temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}


int main()
{
	int arr[] = { 12,5,7,32,89,21,35 };
	const int size = sizeof(arr) / sizeof(arr[0]);   // size���붨��Ϊconst,����
	sort<int,size>(arr);
	for(int val:arr)
	{
		std::cout << val << " ";
	}

	return 0;
}
#endif



//======================================================= 3.C++ ��ģ�� ʵ��vector  �ռ�������allocator=====================================
/*
��ģ��  ==�� ʵ��һ��C++ STL �����һ��˳������  vector��������

������queue SeqStack
�ռ�������allocator

STL��vecor���壺
template<class _Ty>,class _Alloc = allocator<_Ty>> 
class vector{};

�����Ŀռ�������allocator ���ļ�����  �ڴ濪��/�ڴ��ͷ�    ������/��������
*/


// �Զ���ռ�������  ���������Ŀռ�����������C++��׼���allocatorʵ��һ��
template<typename T>
class Allocator
{
public:
	T* allocate(size_t size)  // �����ڴ濪��
	{
		return (T*)malloc(sizeof(T) * size);
	}

	void deallocate(void* p)  // �����ڴ��ͷ�
	{
		free(p);
	}

	void construct(T* p, const T& val)  //���������
	{
		new (p) T(val);   // ��λnew����ָ�����ڴ���ȥ����һ��ֵΪval�Ķ���
	}

	void destroy(T* p)         // �����������
	{
		p->~T();             // ~T() ������T���͵���������
	}
};

/*
�����ײ��ڴ濪�٣��ڴ��ͷţ����������������ͨ��allocator�ռ�������ʵ��
*/
template<typename T=int,typename Alloc = Allocator<T>>
class vector
{
public:
	//vector(int size=10,const Alloc& alloc = Allocator<T>())    // Ҳ�������û�������,����ʹ��Ĭ�ϵ�Allocator<T>
	//	:_allocator(alloc)

	vector(int size=10)      // 
	{
		// ��Ҫ���ڴ濪�ٺͶ�����ֿ�����  [new�������������һ�����ˣ����Զ����������С�����Ķ��󣬾�����Щ�������ң�������Ҫ��]
		//_first = new T[size];
		_first = _allocator.allocate(10);  // 10��Ԫ�ض���  �����ڴ�ռ�
		_last = _first;
		_end = _first+size;
	}

	~vector()
	{
		// ����������Ч��Ԫ�أ�Ȼ���ͷ�_firstָ��ֱ�ߵĶ��ڴ�  [delete]
		//delete[]_first;

		for (T* p = _first; p != _last; ++p)   // ��_firstָ��ָ����������ЧԪ�ؽ�����������
		{
			_allocator.destroy(p);
		}
		_allocator.deallocate(_first);   //�ͷŶ��ϵ������ڴ�
		_first = _last = _end = nullptr;
	}

	vector(const vector<T>& other)
	{
		int size = other._end - other._first;
		//_first = new T[size];
		_first = _allocator.allocate(size);
		int len = other._last - other._first;
		for (int i = 0; i < len; ++i)
		{
		//	_first[i] = other._first[i];
			_allocator.construct(_first + i, other._first[i]);
		}
		_last = _first + len;
		_end = _first + size;
	}

	vector<T>& operator=(const vector<T>& other)
	{
		if (this == &other)
			return *this;

		//delete[]_first;
		for (T* p = _first; p != _last; ++p)   // ��_firstָ��ָ����������ЧԪ�ؽ�����������
		{
			_allocator.destroy(p);
		}
		_allocator.deallocate(_first);         //�ͷŶ��ϵ������ڴ�

		int size = other._end - other._first;
		//_first = new T[size];
		_first = _allocator.allocate(size);
		int len = other._last - other._first;
		for (int i = 0; i < len; ++i)
		{
			//	_first[i] = other._first[i];
			_allocator.construct(_first + i, other._first[i]);
		}
		_last = _first + len;
		_end = _first + size;

		return *this;
	}


	void push_back(const T& val)   // ������ĩβ���Ԫ��
	{
		if (full())
		{
			expand();
		}
		//*_last++ = val;   // �ȸ�ֵ ָ���1
		_allocator.construct(_last, val);   // _lastָ��ָ����ڴ湹��һ��ֵΪval�Ķ���
		_last++;
	}

	void pop_back()      // ������ĩβɾ������
	{
		if (empty())
		{
			return;
		}
		//--_last;
		--_last;         // ����Ҫ��_lastָ��--����Ҫ����ɾ����Ԫ��
		_allocator.destroy(_last);
	}
	
	T back()const   //��������ĩβ��Ԫ�ص�ֵ
	{
		if (empty())
		{
			// ����һ��Ĭ��ֵ���׳��쳣���Ա�ʾ����Ϊ��
			throw std::out_of_range("Vector is empty");
		}
		return *(_last - 1);
	}


	bool full() const { return _last == _end; }
	bool empty() const { return _first == _last; }
	int size() const { return _last - _first; }
private:
	T* _first;      // ָ��������ʼ��λ��
	T* _last;       // ָ����������ЧԪ�صĺ��λ��
	T* _end;        // ָ������ռ�ĺ��λ��

	Alloc _allocator;     //���������Ŀռ�����������

	void expand()   // �����Ķ�������
	{
		int size = _end - _first;   //ԭ��������С
		//T* ptmp = new T[size * 2];
		T* ptmp = _allocator.allocate(size * 2);

		for (int i = 0; i < size; i++)
		{
			//ptmp[i] = _first[i];
			_allocator.construct(ptmp + i, _first[i]);
		}
		// delete[]_first;
		for (T* p =_first;p!=_last;++p)
		{
			_allocator.destroy(p);
		}
		_allocator.deallocate(_first);

		_first = ptmp;
		_last = _first + size;
		_end = _first + (size * 2);
	}
};


// ��C++�У�ָ��� + 1 ���������Ǽ򵥵Ľ�ָ���ֵ�� 1�����ǻ���ָ��ָ������ͽ������ӡ�������ԣ� + 1 ������ʹָ����ǰ�ƶ�һ���洢��Ԫ�Ĵ�С��������һ��ƫ�ƣ����ƫ������ָ�������ȷ����


class Test
{
public:
	Test() { std::cout << "Test()" << std::endl; };
	~Test() { std::cout << "~Test()" << std::endl; }
	Test(const Test& other) { std::cout << "Test(const Test& other)" << std::endl; };
};

int main()
{
	// �����Զ����vector
	//vector<int> vec;
	//for (int i = 0; i < 20; i++)
	//{
	//	vec.push_back(rand() % 100);
	//}
	//vec.pop_back();
	//while (!vec.empty())
	//{
	//	std::cout << vec.back() << " ";
	//	vec.pop_back();
	//}

//	vector<Test> vec;   //���캯��ʹ�õ���new,Ĭ�ϻṹ��10��Test()����    ��============  ��������������߼���Ӧ��ֻ���ڴ�ռ䣬û�ж���
/*
		Test() 
		Test()
		Test()
		Test()
		Test()
		Test()
		Test()
		Test()
		Test()
		Test()
		~Test()
		~Test()
		~Test()
		~Test()
		~Test()
		~Test()
		~Test()
		~Test()
		~Test()
		~Test()
*/

	Test t1, t2, t3;
	std::cout << "======================================" << std::endl;
	vector<Test> vec;

	vec.push_back(t1);
	vec.push_back(t2);
	vec.push_back(t3);
	std::cout << "======================================" << std::endl;
	vec.pop_back();   // ֻ��Ҫ��������      ====��  Ҫ�Ѷ�����������ڴ��ͷŷ��뿪�� ��delete���������¶������ˣ��ⲻ�����߼���
	std::cout << "======================================" << std::endl;
	/*
	Test()
	Test()
	Test()
	======================================
	Test()
	Test()
	Test()
	Test()
	Test()
	Test()
	Test()
	Test()
	Test()
	Test()
	======================================
	======================================
	~Test()
	~Test()
	~Test()
	~Test()
	~Test()
	~Test()
	~Test()
	~Test()
	~Test()
	~Test()
	~Test()
	~Test()
	~Test()

	///////////  ʹ�ÿռ�������
	Test()
	Test()
	Test()
	======================================
	======================================
	~Test()
	======================================
	~Test()
	~Test()
	~Test()
	~Test()
	~Test()
	*/
	return 0;
}


// δ��ӿռ��������汾vector
#if 0
#include <iostream>

template<typename T = int>
class vector {
public:
	vector(int size = 10) {
		_first = new T[size];
		_last = _first;
		_end = _first + size;
	}

	~vector() {
		delete[] _first;
		_first = _last = _end = nullptr;
	}

	vector(const vector<T>& other) {
		int size = other._end - other._first;
		_first = new T[size];
		int len = other._last - other._first;
		for (int i = 0; i < len; ++i) {
			_first[i] = other._first[i];
		}
		_last = _first + len;
		_end = _first + size;
	}

	vector<T>& operator=(const vector<T>& other) {
		if (this == &other)
			return *this;

		delete[] _first;

		int size = other._end - other._first;
		_first = new T[size];
		int len = other._last - other._first;
		for (int i = 0; i < len; ++i) {
			_first[i] = other._first[i];
		}
		_last = _first + len;
		_end = _first + size;

		return *this;
	}

	void push_back(const T& val) {
		if (full()) {
			expand();
		}
		*_last++ = val;
	}

	void pop_back() {
		if (empty()) {
			return;
		}
		--_last;
	}

	T back() const {
		if (empty()) {
			// ����һ��Ĭ��ֵ���׳��쳣���Ա�ʾ����Ϊ��
			throw std::out_of_range("Vector is empty");
		}
		return *(_last - 1);
	}

	bool full() const { return _last == _end; }
	bool empty() const { return _first == _last; }
	int size() const { return _last - _first; }

private:
	T* _first;
	T* _last;
	T* _end;

	void expand() {
		int size = _end - _first;
		T* ptmp = new T[size * 2];
		for (int i = 0; i < size; i++) {
			ptmp[i] = _first[i];
		}
		delete[] _first;
		_first = ptmp;
		_last = _first + size;
		_end = _first + (size * 2);
	}
};

int main() {
	vector<int> vec;
	for (int i = 0; i < 20; i++) {
		vec.push_back(rand() % 100);
	}

	while (!vec.empty()) {
		std::cout << vec.back() << " ";
		vec.pop_back();
	}

	return 0;
}
#endif































