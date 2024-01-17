#include<iostream>
#include<cstring>  // ��
//#include<vector>
using namespace std;


#if 0

//  �Լ�ʵ��һ���ַ�������
class String
{

public:
	String(const char* p = nullptr)
	{
		cout << "String(const char* p)" << endl;
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
		cout << "~String()" << endl;
		delete[] _pstr;
		_pstr = nullptr;
	}

	// ����ֵ���ò����Ŀ�������
	String(const String& str)
	{
		cout << "String(const String&)" << endl;
		_pstr = new char[strlen(str._pstr) + 1];     //strlen(p):�����ַ�������Ч����    _pstr = new char[strlen(src._pstr) + 1]
		strcpy(_pstr, str._pstr);
	}

	// ����ֵ���ò����Ŀ�������
	String(String&& str)       // str���õ���һ����ʱ����
	{
		cout << "String(String&& str)" << endl;
		_pstr = str._pstr;
		str._pstr = nullptr;
	}

	// ����ֵ���ò����ĸ�ֵ���غ���
	String& operator=(const String& str)
	{
		cout << "operator=(const String&)" << endl;
		if (this == &str)
			return *this;

		delete[]_pstr;

		_pstr = new char[strlen(str._pstr) + 1];   //strlen(p):�����ַ�������Ч����
		strcpy(_pstr, str._pstr);

		return *this;
	}

	// ����ֵ���ò����ĸ�ֵ���غ���
	String& operator=(String&& str)      // ��ʱ����ƥ�䵽�������
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

// �������������
String operator+(const String& lhs, const String& rhs)
{
	// 1���ڴ�й©������û��delete     
	//char* ptmp = new char[strlen(lhs._pstr) + strlen(rhs._pstr) + 1];
	//strcpy(ptmp, lhs._pstr);
	//strcat(ptmp, rhs._pstr);
	//return String(ptmp);


	// 2. ������ڴ�й©���⣬����Ч�ʵ�
	//char* ptmp = new char[strlen(lhs._pstr) + strlen(rhs._pstr) + 1];
	//strcpy(ptmp, lhs._pstr);
	//strcat(ptmp, rhs._pstr);
	//String tmpstr(ptmp);
	//delete []ptmp;
	//return tmpstr;
	
	// 3��������ʱ���� ====�� ������ֵ���õÿ������캯��  ====�� Ч�ʸ���
	String tmpstr;
	tmpstr = new char[strlen(lhs._pstr) + strlen(rhs._pstr) + 1];
	strcpy(tmpstr._pstr, lhs._pstr);
	strcat(tmpstr._pstr, rhs._pstr);
	return tmpstr;

}
 
// ������������
ostream& operator<<(ostream& out, const String& str)
{
	out << str._pstr;
	return out;
}


//========================================== move�ƶ������forward��������ת�� ============================
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
	/*
	void construct(T* p, const T& val)  //���������
	{
		new (p) T(val);                              // ��λnew����ָ�����ڴ���ȥ����һ��ֵΪval�Ķ���
	}

	void construct(T* p, T&& val)     //���������
	{
		new (p) T(std::move(val));                               // ��λnew����ָ�����ڴ���ȥ����һ��ֵΪval�Ķ���
	}
	*/

	template<typename Ty>
	void construct(T* p, Ty&& val)
	{
		new (p) T(std::forward<Ty>(val));                              
	}

	void destroy(T* p)         // �����������
	{
		p->~T();             // ~T() ������T���͵���������
	}
};

/*
�����ײ��ڴ濪�٣��ڴ��ͷţ����������������ͨ��allocator�ռ�������ʵ��
*/
template<typename T = int, typename Alloc = Allocator<T>>
class vector
{
public:
	//vector(int size=10,const Alloc& alloc = Allocator<T>())    // Ҳ�������û�������,����ʹ��Ĭ�ϵ�Allocator<T>
	//	:_allocator(alloc)

	vector(int size = 10)      // 
	{
		// ��Ҫ���ڴ濪�ٺͶ�����ֿ�����  [new�������������һ�����ˣ����Զ����������С�����Ķ��󣬾�����Щ������������Ҫ��]
		//_first = new T[size];
		_first = _allocator.allocate(size);  // 10��Ԫ�ض���  �����ڴ�ռ�
		_last = _first;
		_end = _first + size;
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
/*
	// ������ֵ
	void push_back(const T& val)   // ������ĩβ���Ԫ��
	{
		if (full())
		{
			expand();
		}
		//*_last++ = val;   // �ȸ�ֵ  ��ָ���1
		_allocator.construct(_last, val);   // _lastָ��ָ����ڴ湹��һ��ֵΪval�Ķ���
		_last++;
	}

	// ������ֵ
	void push_back(T&& val)   // ������ĩβ���Ԫ��
	{
		if (full())
		{
			expand();
		}
		_allocator.construct(_last, std::move(val));      // һ����ֵ���ñ�����������һ����ֵ ����������
		_last++;
	}
*/
	// String& + && = void push_back(String &val) 
	// String&& + && = void push_back(String &&val) 
	template<typename Ty>      // ����ģ����������� + �����۵�
	void push_back(Ty &&val)   //  String& + && = String& (�����۵�)     String&& + && = String&& (�����۵�)
	{
		if (full())
		{
			expand();
		}

		// move���ƶ����壬�õ���ֵ���ͣ�����ǿ��ת��Ϊ��ֵ���ͣ�
		// forward:���͵�����ת�� �ܹ�ʶ����ֵ����ֵ
		_allocator.construct(_last,std::forward<Ty>(val));      // һ����ֵ���ñ�����������һ����ֵ ����������
		_last++;
	}

	void pop_back()      // ������ĩβɾ������
	{
		if (empty())
		{
			return;
		}
		// erase(it);   ===>  verify(it._ptr,_last);
		// insert(it,val)    ===> verify(it._ptr,_last)
		verify(_last - 1, _last);
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
String(const String& p)     ===> tmpStr��������main����ջ֡�ϵ���ʱ����       ���еı��������Ż�������һ��ı�������
~String()
operator=(const String&)    ===>  main����ջ֡�ϵ���ʱ�����str2��ֵ
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

#if 0        // ������ֵ����ֵ
int main()
{
	// ��ֵ����

	int a = 10;
	int& b = a;    // b����ֵ����                  ��ֵ�����ڴ棬������       ��ֵ��û���֣���ʱ������û�ڴ�
	// int&& c = a;   // c����ֵ �޷�����ֵ���ð󶨵���ֵ (a����ֵ)



	// int& c = 20;   // ��������ֵ���ð�һ����ֵ

	/*
	int tmp = 20;        // ����������ʱ��
	const int &c = tmp;  // ���ó����� ������ʱ��
	*/
	const int& c = 20;   //                                          ��������ͨ�����øı�ֵ��
	//  00007FF71DAB27CB  mov         dword ptr[rbp + 64h], 14h
	//	00007FF71DAB27D2  lea         rax, [rbp + 64h]
	//	00007FF71DAB27D6  mov         qword ptr[c], rax


	/*
	int tmp = 20;        // ����������ʱ��
	const int &c = tmp;  // ���ó����� ������ʱ��
	���ָ��������һģһ��
	*/
	int&& d = 20;        // ���԰�һ����ֵ��һ����ֵ������         ������ͨ��d�ı�ֵ�� 
	//  00007FF71DAB27DA  mov         dword ptr[rbp + 0A4h], 14h
	//	00007FF71DAB27E4  lea         rax, [rbp + 0A4h]
	//	00007FF71DAB27EB  mov         qword ptr[d], rax

	// String& e = String("aaaa");  // �޷��ӡ�String��ת��Ϊ��String & ��
	const String& e = String("aaaa");
	String&& f = String("bbbbbb");              // ��ʱ������ֵ


//	int&& g = d;  //  �޷��ӡ�int��ת��Ϊ��int &&    ===��  һ����ֵ���ñ�����������һ����ֵ

	return 0;
}
#endif