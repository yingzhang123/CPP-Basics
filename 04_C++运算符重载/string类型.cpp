#include<iostream>
#include<string>  // ��



//  �Լ�ʵ��һ���ַ�������
class String
{

public:
	String(const char* p = nullptr)
	{
		if (p != nullptr)
		{
			_pstr = new char[strlen(p) + 1];  //strlen(p):�����ַ�������Ч����
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
		_pstr = new char[src.length() + 1];  //strlen(p):�����ַ�������Ч����    _pstr = new char[strlen(src._pstr) + 1]
		strcpy(_pstr, src._pstr);
	}

	String& operator=(const String& str)
	{
		if (this == &str)
			return *this;

		delete[]_pstr;

		_pstr = new char[str.length() + 1];  //strlen(p):�����ַ�������Ч����
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
		return strlen(_pstr);  //������Ч�ַ�����
	}

	// char ch = str[6];  str[6] = '7';   // �����޸��ַ����ַ�
	char& operator[](int index) 
	{
		return _pstr[index];
	}
	 
	// char ch = str[6];     �������޸ģ����� str[6] = '7';   
	const char& operator[](int index) const
	{
		return _pstr[index];
	}

	const char* c_str()const
	{
		return _pstr;
	}

	// ��String�ַ��������ṩ������ʵ��
	class iterator
	{
	public:
		iterator(char *p =nullptr):_p(p){}
		bool operator!=(const iterator& it)
		{
			return _p != it._p;
		}
		// ǰ��
		void operator++()             // ǰ��++Ч�ʸ���һ�㣬����û�ж���Ĺ��������
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

	// ������Ҫ�ṩbegin��end���ַ���
	// begin���ص��ǵײ���Ԫ�صĵ������ı�ʾ
	iterator begin() { return iterator(_pstr); }
	// end���ص�������ĩβ���λ�õĵ������ı�ʾ
	iterator end() { return iterator(_pstr + length()); }
private:
	char* _pstr;

	friend String operator+(const String& lhs, const String& rhs);
	friend std::ostream& operator<<(std::ostream& out, const String& str);
	friend std::istream& operator>>(std::istream& in, String& str);
};

String operator+(const String& lhs, const String& rhs)
{
	//char* ptmp = new char[strlen(lhs._pstr) + strlen(rhs._pstr) + 1];           //1.û��delete ===�� �ڴ�й©
	//strcpy(ptmp, lhs._pstr);
	//strcat(ptmp, rhs._pstr);
	//return String(ptmp);

	//char* ptmp = new char[strlen(lhs._pstr) + strlen(rhs._pstr) + 1];            // 2.�������Խӽ���ڴ�й©������Ч�ʺܵ�
	//strcpy(ptmp, lhs._pstr);
	//strcat(ptmp, rhs._pstr);
	//String tmp(ptmp);
	//delete[]ptmp;
	//return tmp;


	//char* ptmp = new char[strlen(lhs._pstr) + strlen(rhs._pstr) + 1];            // 3.Ч�ʱ�2����һЩ    ====�� ���õ��Ż� =======����ֵ����
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
	//�������Ĺ��ܣ��ṩһ��ͳһ�ķ�ʽ����͸���ı�������

	//std::string str1 = "hello world!";      // str1�������𣿽У���==>�ײ����һ��char���͵��ַ�
	//// �����ĵ���������
	//std::string::iterator it = str1.begin();
	//for (; it != str1.end(); ++it)
	//{
	//	std::cout << *it << " ";
	//}
	//std::cout << std::endl;


	String str1 = "hello world!";      // str1�������𣿽У���==>�ײ����һ��char���͵��ַ�
	// �����ĵ���������
	auto it = str1.begin();   // String::iterator it = str1.begin();
	for (; it != str1.end(); ++it)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;

	// C++11 foreach�ķ�ʽ�������������ڲ�Ԫ�ص�ֵ   ====> �ײ㻹��ͨ�����������б�����
	// ע��String���begin(),end()�� ����ı����ᱨ��  ��const _Elem* std::begin(std::initializer_list<_Elem>) noexcept��: �޷��ӡ�String���Ƶ�����std::initializer_list<_Elem>���� ģ�� ����
	for (char ch : str1)
	{
		std::cout << ch << " ";
	}
	std::cout << std::endl;

// String ����� 
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