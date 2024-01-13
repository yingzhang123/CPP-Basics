#include<iostream>
#include<string>  // 库



//  自己实现一个字符串对象
class String
{

public:
	String(const char* p = nullptr)
	{
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
		delete[] _pstr;
		_pstr = nullptr;
	}

	String(const String& src)
	{
		_pstr = new char[src.length() + 1];  //strlen(p):返回字符串的有效个数    _pstr = new char[strlen(src._pstr) + 1]
		strcpy(_pstr, src._pstr);
	}

	String& operator=(const String& str)
	{
		if (this == &str)
			return *this;

		delete[]_pstr;

		_pstr = new char[str.length() + 1];  //strlen(p):返回字符串的有效个数
		strcpy(_pstr, str._pstr);

		return *this;
	}

	bool operator>(const String& str) const
	{
		return strcmp(this->_pstr, str._pstr) > 0;
	}

	bool operator<(const String& str) const
	{
		return strcmp(this->_pstr, str._pstr) < 0;
	}

	bool operator==(const String& str) const
	{
		return strcmp(this->_pstr, str._pstr) == 0;
	}


	int length() const
	{
		return strlen(_pstr);  //返回有效字符个数
	}

	// char ch = str[6];  str[6] = '7';   // 可以修改字符串字符
	char& operator[](int index) 
	{
		return _pstr[index];
	}
	 
	// char ch = str[6];     不可以修改！！！ str[6] = '7';   
	const char& operator[](int index) const
	{
		return _pstr[index];
	}

	const char* c_str()const
	{
		return _pstr;
	}

	// 给String字符串类型提供迭代器实现
	class iterator
	{
	public:
		iterator(char *p =nullptr):_p(p){}
		bool operator!=(const iterator& it)
		{
			return _p != it._p;
		}
		// 前置
		void operator++()             // 前置++效率更高一点，，，没有对象的构造和析构
		{
			++_p;
		}
		iterator operator++(int)
		{
			iterator iter = *this;
			_p = _p + 1;
			return iter;
		}

		char& operator*() { return *_p; }

	private:
		char* _p;
	};

	// 容器需要提供begin，end两种方法
	// begin返回的是底层首元素的迭代器的表示
	iterator begin() { return iterator(_pstr); }
	// end返回的是容器末尾后继位置的迭代器的表示
	iterator end() { return iterator(_pstr + length()); }
private:
	char* _pstr;

	friend String operator+(const String& lhs, const String& rhs);
	friend std::ostream& operator<<(std::ostream& out, const String& str);
	friend std::istream& operator>>(std::istream& in, String& str);
};

String operator+(const String& lhs, const String& rhs)
{
	//char* ptmp = new char[strlen(lhs._pstr) + strlen(rhs._pstr) + 1];           //1.没有delete ===》 内存泄漏
	//strcpy(ptmp, lhs._pstr);
	//strcat(ptmp, rhs._pstr);
	//return String(ptmp);

	//char* ptmp = new char[strlen(lhs._pstr) + strlen(rhs._pstr) + 1];            // 2.这样可以接解决内存泄漏，但是效率很低
	//strcpy(ptmp, lhs._pstr);
	//strcat(ptmp, rhs._pstr);
	//String tmp(ptmp);
	//delete[]ptmp;
	//return tmp;


	//char* ptmp = new char[strlen(lhs._pstr) + strlen(rhs._pstr) + 1];            // 3.效率比2更好一些    ====》 更好的优化 =======》右值引用
	String tmp;
	tmp._pstr = new char[strlen(lhs._pstr) + strlen(rhs._pstr) + 1];
	strcpy(tmp._pstr, lhs._pstr);
	strcat(tmp._pstr, rhs._pstr);
	//String tmp(ptmp);
	//delete[]ptmp;
	return tmp;
}

std::ostream& operator<<(std::ostream& out, const String& str)
{
	out << str._pstr;
	return out;
}

std::istream& operator>>(std::istream& in, String& str)
{
	in >> str._pstr;
	return in;
}

int main03()
{
	//迭代器的功能：提供一种统一的方式，来透明的遍历容器

	//std::string str1 = "hello world!";      // str1叫容器吗？叫！！==>底层放了一组char类型的字符
	//// 容器的迭代器类型
	//std::string::iterator it = str1.begin();
	//for (; it != str1.end(); ++it)
	//{
	//	std::cout << *it << " ";
	//}
	//std::cout << std::endl;


	String str1 = "hello world!";      // str1叫容器吗？叫！！==>底层放了一组char类型的字符
	// 容器的迭代器类型
	auto it = str1.begin();   // String::iterator it = str1.begin();
	for (; it != str1.end(); ++it)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;

	// C++11 foreach的方式来遍历容器的内部元素的值   ====> 底层还是通过迭代器进行遍历的
	// 注释String类的begin(),end()， 下面的遍历会报错  “const _Elem* std::begin(std::initializer_list<_Elem>) noexcept”: 无法从“String”推导出“std::initializer_list<_Elem>”的 模板 参数
	for (char ch : str1)
	{
		std::cout << ch << " ";
	}
	std::cout << std::endl;

// String 类测试 
#if 0
	String str1;
	String str2 = "aaaaa";   // String(const String& src);
	String str3 = "bbbbb";
	String str4 = str2 + str3;
	String str5 = str2 + "ccc";
	String str6 = "ddd" + str2;

	std::cout << "str6:" << str6 << std::endl;

	// bool operator>(const String& str);
	if (str5 > str6)
	{
		std::cout << str5 << " > " << str6 << std::endl;
	}
	else 
	{
		std::cout << str5 << " < " << str6 << std::endl;
	}
	int len = str6.length();
	for (int i = 0; i < len; i++)
	{
		//           char& str6.operator[](i)
		std::cout << str6[i] << " ";
	}
	std::cout << std::endl;

	//String  =====>   char*
	char buf[1024];
	strcpy(buf, str6.c_str());
	std::cout << "buf:" << buf << std::endl;

#endif


	return 0;
}