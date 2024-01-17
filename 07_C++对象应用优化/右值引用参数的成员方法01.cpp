#include<iostream>
#include<cstring>  // 库
//#include<vector>
using namespace std;


#if 0

//  自己实现一个字符串对象
class String
{

public:
	String(const char* p = nullptr)
	{
		cout << "String(const char* p)" << endl;
		if (p != nullptr)
		{
			_pstr = new char[strlen(p) + 1];  //strlen(p):返回字符串的有效个数
			strcpy(_pstr, p);
		}
		else
		{
			_pstr = new char[1];
			*_pstr = '\0';
		}
	}

	~String()
	{
		cout << "~String()" << endl;
		delete[] _pstr;
		_pstr = nullptr;
	}

	// 带左值引用参数的拷贝构造
	String(const String& str)
	{
		cout << "String(const String&)" << endl;
		_pstr = new char[strlen(str._pstr) + 1];     //strlen(p):返回字符串的有效个数    _pstr = new char[strlen(src._pstr) + 1]
		strcpy(_pstr, str._pstr);
	}

	// 带右值引用参数的拷贝构造
	String(String&& str)       // str引用的是一个临时对象
	{
		cout << "String(String&& str)" << endl;
		_pstr = str._pstr;
		str._pstr = nullptr;
	}

	// 带左值引用参数的赋值重载函数
	String& operator=(const String& str)
	{
		cout << "operator=(const String&)" << endl;
		if (this == &str)
			return *this;

		delete[]_pstr;

		_pstr = new char[strlen(str._pstr) + 1];   //strlen(p):返回字符串的有效个数
		strcpy(_pstr, str._pstr);

		return *this;
	}

	// 带右值引用参数的赋值重载函数
	String& operator=(String&& str)      // 临时对象匹配到这个函数
	{
		cout << "operator=(String&&)" << endl;
		if (this == &str)
			return *this;

		delete[]_pstr;

		_pstr = str._pstr;
		str._pstr = nullptr;

		return *this;
	}

	const char* c_str()const 
	{ 
		return _pstr;
	}

	friend String operator+(const String& lhs, const String& rhs);
	friend ostream& operator<<(ostream& out, const String& str);
private:
	char* _pstr;
};

// 复制运算符重载
String operator+(const String& lhs, const String& rhs)
{
	// 1、内存泄漏！！！没有delete     
	//char* ptmp = new char[strlen(lhs._pstr) + strlen(rhs._pstr) + 1];
	//strcpy(ptmp, lhs._pstr);
	//strcat(ptmp, rhs._pstr);
	//return String(ptmp);


	// 2. 解决了内存泄漏问题，但是效率低
	//char* ptmp = new char[strlen(lhs._pstr) + strlen(rhs._pstr) + 1];
	//strcpy(ptmp, lhs._pstr);
	//strcat(ptmp, rhs._pstr);
	//String tmpstr(ptmp);
	//delete []ptmp;
	//return tmpstr;
	
	// 3、返回临时对象 ====》 调用右值引用得拷贝构造函数  ====》 效率更高
	String tmpstr;
	tmpstr = new char[strlen(lhs._pstr) + strlen(rhs._pstr) + 1];
	strcpy(tmpstr._pstr, lhs._pstr);
	strcat(tmpstr._pstr, rhs._pstr);
	return tmpstr;

}
 
// 输出运算符重载
ostream& operator<<(ostream& out, const String& str)
{
	out << str._pstr;
	return out;
}


//========================================== move移动语义和forward类型完美转发 ============================
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
	/*
	void construct(T* p, const T& val)  //负责对象构造
	{
		new (p) T(val);                              // 定位new，在指定的内存上去构造一个值为val的对象
	}

	void construct(T* p, T&& val)     //负责对象构造
	{
		new (p) T(std::move(val));                               // 定位new，在指定的内存上去构造一个值为val的对象
	}
	*/

	template<typename Ty>
	void construct(T* p, Ty&& val)
	{
		new (p) T(std::forward<Ty>(val));                              
	}

	void destroy(T* p)         // 负责对象析构
	{
		p->~T();             // ~T() 代表了T类型的析构函数
	}
};

/*
容器底层内存开辟，内存释放，对象构造和析构，都通过allocator空间配置器实现
*/
template<typename T = int, typename Alloc = Allocator<T>>
class vector
{
public:
	//vector(int size=10,const Alloc& alloc = Allocator<T>())    // 也可以让用户传进来,不传使用默认的Allocator<T>
	//	:_allocator(alloc)

	vector(int size = 10)      // 
	{
		// 需要把内存开辟和对象构造分开处理  [new运算符把这两步一起做了，会自动构造数组大小个数的对象，尽管这些对象不是我们想要的]
		//_first = new T[size];
		_first = _allocator.allocate(size);  // 10个元素对象  开辟内存空间
		_last = _first;
		_end = _first + size;
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
/*
	// 接收左值
	void push_back(const T& val)   // 向容器末尾添加元素
	{
		if (full())
		{
			expand();
		}
		//*_last++ = val;   // 先赋值  后指针加1
		_allocator.construct(_last, val);   // _last指针指向的内存构造一个值为val的对象
		_last++;
	}

	// 接收右值
	void push_back(T&& val)   // 向容器末尾添加元素
	{
		if (full())
		{
			expand();
		}
		_allocator.construct(_last, std::move(val));      // 一个右值引用变量，本身是一个左值 ！！！！！
		_last++;
	}
*/
	// String& + && = void push_back(String &val) 
	// String&& + && = void push_back(String &&val) 
	template<typename Ty>      // 函数模板得类型推演 + 引用折叠
	void push_back(Ty &&val)   //  String& + && = String& (引用折叠)     String&& + && = String&& (引用折叠)
	{
		if (full())
		{
			expand();
		}

		// move：移动语义，得到右值类型（类型强制转换为右值类型）
		// forward:类型得完美转发 能够识别左值和右值
		_allocator.construct(_last,std::forward<Ty>(val));      // 一个右值引用变量，本身是一个左值 ！！！！！
		_last++;
	}

	void pop_back()      // 从容器末尾删除容器
	{
		if (empty())
		{
			return;
		}
		// erase(it);   ===>  verify(it._ptr,_last);
		// insert(it,val)    ===> verify(it._ptr,_last)
		verify(_last - 1, _last);
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
		for (T* p = _first; p != _last; ++p)
		{
			_allocator.destroy(p);
		}
		_allocator.deallocate(_first);

		_first = ptmp;
		_last = _first + size;
		_end = _first + (size * 2);
	}
};

int main()
{
	String str1 = "aaaa";
	vector<String> vec;

	cout << "---------------------------------" << endl;
	vec.push_back(str1);  // String&
	cout << "---------------------------------" << endl;
	vec.push_back(String("bbbb"));  // String&&
	cout << "---------------------------------" << endl;
	return 0;
}
#endif

#if 0
int main()
{
	String str1 = "aaaa";
	vector<String> vec;
	vec.reserve(10);

	cout << "---------------------------------" << endl;
	vec.push_back(str1);
	cout << "---------------------------------" << endl;
	vec.push_back(String("bbbb"));
	cout << "---------------------------------" << endl;
	/*
	String(const char* p)
	---------------------------------
	String(const String&)
	---------------------------------
	String(const char* p)
	String(String&& str)
	~String()
	---------------------------------
	~String()
	~String()
	~String()
	*/




	/*
	String str1 = "hello ";
	String str2 = "world!";
	cout << "-----------------------" << endl;
	String str3 = str1 + str2;
	cout << "-----------------------" << endl;
	cout << str3 << endl;
	*/

	return 0;
}
#endif



#if 0
String GetString(String& str)
{
	const char* pstr = str.c_str();
	String tmpStr(pstr);
	return tmpStr;
}
int main()
{
	String  str1("aaaaaaaaaaaaaaaa");
	String str2;
	str2 = GetString(str1);
	cout << str2.c_str() << endl;
	return 0;
}

/*
String(const char* p)
String(const char* p)
String(const char* p)
String(const String& p)     ===> tmpStr拷贝构造main函数栈帧上的临时对象       （有的编译器会优化掉，新一点的编译器）
~String()
operator=(const String&)    ===>  main函数栈帧上的临时对象给str2赋值
~String()
aaaaaaaaaaaaaaaa
~String()
~String()
*/

/*
String(const char* p)
String(const char* p)
String(const char* p)
operator=(String&&)
~String()
aaaaaaaaaaaaaaaa
~String()
~String()

*/
#endif

#if 0        // 区分左值和右值
int main()
{
	// 右值引用

	int a = 10;
	int& b = a;    // b是左值引用                  左值：有内存，有名字       右值：没名字（临时量），没内存
	// int&& c = a;   // c是右值 无法将右值引用绑定到左值 (a是左值)



	// int& c = 20;   // 不能用左值引用绑定一个右值

	/*
	int tmp = 20;        // 先用生成临时量
	const int &c = tmp;  // 再用常引用 引用临时量
	*/
	const int& c = 20;   //                                          （不可以通过引用改变值）
	//  00007FF71DAB27CB  mov         dword ptr[rbp + 64h], 14h
	//	00007FF71DAB27D2  lea         rax, [rbp + 64h]
	//	00007FF71DAB27D6  mov         qword ptr[c], rax


	/*
	int tmp = 20;        // 先用生成临时量
	const int &c = tmp;  // 再用常引用 引用临时量
	汇编指令和上面的一模一样
	*/
	int&& d = 20;        // 可以把一个右值绑定一个右值引用上         （可以通过d改变值） 
	//  00007FF71DAB27DA  mov         dword ptr[rbp + 0A4h], 14h
	//	00007FF71DAB27E4  lea         rax, [rbp + 0A4h]
	//	00007FF71DAB27EB  mov         qword ptr[d], rax

	// String& e = String("aaaa");  // 无法从“String”转换为“String & ”
	const String& e = String("aaaa");
	String&& f = String("bbbbbb");              // 临时量是右值


//	int&& g = d;  //  无法从“int”转换为“int &&    ===》  一个右值引用变量，本身是一个左值

	return 0;
}
#endif