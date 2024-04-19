#include<iostream>


//=========================================================== 1.C++函数模板 =====================================
/*
C++函数模板
模板的意义：对类型也可以进行参数化   《=========================  （模板在开发库的时候很常用）
int sum(int a,int b)(return a+b);


函数模板               《============ 是不进行编译的，因为类型不知道
模板的实例化        《============  函数调用点进行实例化
模板函数               《============   才是要被编译器所编译的
 
模板类型参数         typename/class
模板非类型参数

模板的实参推演                ====》      可以根据用户传入的实参的类型，来推导出模板类型参数的具体类型
模板的特例化（专用化）   ====》      特殊（不是编译器提供的，而是用户提供的）的实例化
函数模板、模板的特例化、非模板函数的重载关系


[模板代码是不能够在一个文件中定义的，在另外一个文件使用的]
模板代码调用前，一定要看到模板定义的地方，这样的话，模板才能够进行正常的实例化，产生能够被编译器编译的代码

所以，模板代码都是放在头文件当中的，然后在源文件当中直接进行#include包含
*/

#if 0
// 函数模板
template<typename T>    //定义一个模板参数列表   typename，用class也可以
bool compare(T a, T b)      // compares是一个函数模板
{
	std::cout << "tempalte compare" << std::endl;
	return a > b;
}

// 模板的特例化
// 针对compare函数模板，提供const char*类型的特例化版本
template<>
bool compare<const char*>(const char* a, const char* b)
{
	std::cout << "compare<const char*>" << std::endl;
	return strcmp(a, b) > 0;
}

// 非模板函数
// 非模板函数 - 普通函数 
bool compare(const char* a, const char* b)
{
	std::cout << "normal compare" << std::endl;
	return strcmp(a, b) > 0;
}

int main()
{
	// 函数调用点
	compare<int>(10, 20);
	compare<double>(10.0, 21.0);

	// 函数模板实参的推演
	compare(10, 20);


	// “compare” : 未找到匹配的重载函数     没有与参数列表匹配的函数模板"compare"实例
	// compare(10, 20.8);
	compare<int>(10, 20.8);  //但是可以手动指定参数类型     （从“double”转换到“T”，可能丢失数据）


	// 函数模板实参的推演 T ===》 const char* 
	// 对于某些类型来说，依赖编译器默认实例化的模板代码，代码处理逻辑是不符合的（有问题）
	// 编译器优先把compare处理成函数名字，没有的话，才去找compare模板
	compare("aaa", "bbb");    

	//compare("aaa", "bbb");    // 如果有非模板函数，编译器优先调用非模板函数

	return 0;
}
#endif

/*
在函数调用点，编译器用用户指定的类型，从原模板实例化一份函数代码出来  ==》 模板函数
模板函数：
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
	return a>b;         // 有问题：只是比较两个地址！！！！   应该是 return strcmp(a,b)>0;
}

*/


//=========================================================== 2.C++ 类模板 =====================================
/*
函数模板
模板的非类型参数     必须是整数类型（整数或者地址/引用都可以）       都是常量，只能使用，而不能修改

类模板   +===》 实例化   ====》  模板类 

*/

#if 0
//类模板
template<typename T=int>   // 类模板还可以加默认参数
class SeqStack     // SeqStack为模板名 + 类型参数列表 ==》 类名称
{
public:
	// 构造和析构函数名可以不用加<T>也可以，其他出现模板的地方都加上参数列表
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
		// 不要用memcpy进行拷贝！！！！！（虽然在某些情况下可以使用memcpy()函数来进行内存复制，
		// 对于包含指针或动态内存分配的对象，memcpy()不能正确处理。拷贝构造函数需要确保复制时进行适当的资源管理，以避免资源泄漏或重复释放）
		for (int i = 0; i < top; i++)
		{
			_pstack[i] = other._pstack[i];     // 会调用对象的赋值运算符重载函数
		}
	}

	SeqStack<T>& operator=(const SeqStack<T>& other)
	{
		if (this == &other)   // 防止自赋值
		{
			return *this;
		}

		delete[] _pstack;    // 释放原先占用的内存

		_top = other._top;
		_size = other._size;
		_pstack = new T[_size];
		// 不要用memcpy进行拷贝！！！！！（虽然在某些情况下可以使用memcpy()函数来进行内存复制，
		// 对于包含指针或动态内存分配的对象，memcpy()不能正确处理。拷贝构造函数需要确保复制时进行适当的资源管理，以避免资源泄漏或重复释放）
		for (int i = 0; i < top; i++)
		{
			_pstack[i] = other._pstack[i];     // 会调用对象的赋值运算符重载函数
		}

		return *this;
	}

	void push(const T& val);     // 入栈操作
	//{
	//	if (full())
	//		expand();

	//	_pstack[_top++] = val;
	//}

	void pop()       // 出栈操作
	{
		if (empty())
			return;
		--_top;
	}

	T top() const    // 返回栈顶元素
	{
		if (empty())
			throw "stack is empty";   //抛出异常也代表函数逻辑结束
		return _pstack[_top - 1];
	}
	bool full() const { return _top == _size; }  // 栈满
	bool empty() const { return _top == 0; }     // 栈空

private:
	T* _pstack;
	int _top;
	int _size;

	// 顺序栈底层数组按2倍的方式扩容
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

// 类外实现
template<typename T>
void SeqStack<T>::push(const T& val)
{
	if (full())
		expand();

	_pstack[_top++] = val;
}


int main()
{
	// 类模板的选择性实例化（当需要使用到类的某些函数是，才会实例化，没用用到的函数编译器不会产生）
	// 模板类  class SeqStack<int>{};
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

//   模板的非类型参数 
#if 0      
template<typename T, int SIZE>   // int SIZE:模板的非类型参数
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
	const int size = sizeof(arr) / sizeof(arr[0]);   // size必须定义为const,常量
	sort<int,size>(arr);
	for(int val:arr)
	{
		std::cout << val << " ";
	}

	return 0;
}
#endif



//======================================================= 3.C++ 类模板 实现vector  空间配置器allocator=====================================
/*
类模板  ==》 实现一个C++ STL 里面得一个顺序容器  vector向量容器

容器：queue SeqStack
空间配置器allocator

STL的vecor定义：
template<class _Ty>,class _Alloc = allocator<_Ty>> 
class vector{};

容器的空间配置器allocator 做四件事情  内存开辟/内存释放    对象构造/对象析构
*/


// 自定义空间配置器  定义容器的空间配置器，和C++标准库的allocator实现一样
template<typename T>
class Allocator
{
public:
	T* allocate(size_t size)  // 负责内存开辟
	{
		return (T*)malloc(sizeof(T) * size);
	}

	void deallocate(void* p)  // 负责内存释放
	{
		free(p);
	}

	void construct(T* p, const T& val)  //负责对象构造
	{
		new (p) T(val);   // 定位new，在指定的内存上去构造一个值为val的对象
	}

	void destroy(T* p)         // 负责对象析构
	{
		p->~T();             // ~T() 代表了T类型的析构函数
	}
};

/*
容器底层内存开辟，内存释放，对象构造和析构，都通过allocator空间配置器实现
*/
template<typename T=int,typename Alloc = Allocator<T>>
class vector
{
public:
	//vector(int size=10,const Alloc& alloc = Allocator<T>())    // 也可以让用户传进来,不传使用默认的Allocator<T>
	//	:_allocator(alloc)

	vector(int size=10)      // 
	{
		// 需要把内存开辟和对象构造分开处理  [new运算符把这两步一起做了，会自动构造数组大小个数的对象，尽管这些对象不是我，我们想要的]
		//_first = new T[size];
		_first = _allocator.allocate(10);  // 10个元素对象  开辟内存空间
		_last = _first;
		_end = _first+size;
	}

	~vector()
	{
		// 析构容器有效的元素，然后释放_first指针直线的堆内存  [delete]
		//delete[]_first;

		for (T* p = _first; p != _last; ++p)   // 把_first指针指向的数组的有效元素进行析构操作
		{
			_allocator.destroy(p);
		}
		_allocator.deallocate(_first);   //释放堆上的数组内存
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
		for (T* p = _first; p != _last; ++p)   // 把_first指针指向的数组的有效元素进行析构操作
		{
			_allocator.destroy(p);
		}
		_allocator.deallocate(_first);         //释放堆上的数组内存

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


	void push_back(const T& val)   // 向容器末尾添加元素
	{
		if (full())
		{
			expand();
		}
		//*_last++ = val;   // 先赋值 指针加1
		_allocator.construct(_last, val);   // _last指针指向的内存构造一个值为val的对象
		_last++;
	}

	void pop_back()      // 从容器末尾删除容器
	{
		if (empty())
		{
			return;
		}
		//--_last;
		--_last;         // 不仅要把_last指针--，还要析构删除的元素
		_allocator.destroy(_last);
	}
	
	T back()const   //返回容器末尾得元素的值
	{
		if (empty())
		{
			// 返回一个默认值或抛出异常，以表示容器为空
			throw std::out_of_range("Vector is empty");
		}
		return *(_last - 1);
	}


	bool full() const { return _last == _end; }
	bool empty() const { return _first == _last; }
	int size() const { return _last - _first; }
private:
	T* _first;      // 指向数组起始的位置
	T* _last;       // 指向数组中有效元素的后继位置
	T* _end;        // 指向数组空间的后继位置

	Alloc _allocator;     //定义容器的空间配置器对象

	void expand()   // 容器的二倍扩容
	{
		int size = _end - _first;   //原来容器大小
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


// 在C++中，指针的 + 1 操作并不是简单的将指针的值加 1，而是基于指针指向的类型进行增加。具体而言， + 1 操作会使指针向前移动一个存储单元的大小，即增加一个偏移，这个偏移是由指针的类型确定的


class Test
{
public:
	Test() { std::cout << "Test()" << std::endl; };
	~Test() { std::cout << "~Test()" << std::endl; }
	Test(const Test& other) { std::cout << "Test(const Test& other)" << std::endl; };
};

int main()
{
	// 测试自定义的vector
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

//	vector<Test> vec;   //构造函数使用的是new,默认会构造10个Test()对象    《============  【定义空容器，逻辑上应该只有内存空间，没有对象】
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
	vec.pop_back();   // 只需要析构对象。      ====》  要把对象的析构和内存释放分离开， 【delete把这两件事都做完了，这不符合逻辑】
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

	///////////  使用空间配置器
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


// 未添加空间配置器版本vector
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
			// 返回一个默认值或抛出异常，以表示容器为空
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































