
#include<iostream>


//=========================================================== 1.C++运算符重载-使面向对象编程更加灵活 ==========================================
/*
C++运算符重载：使对象的运算表现得和编译器内置类型一样
template<typename T>
T sum(T a,T b)
{
	return a+b;   // a.operator+(b);
}

*/

/*
复数类
*/
class CComplex
{
public:
	CComplex(int r = 0, int i = 0)
		:_mreal(r)
		,_mimage(i)
	{

	}

	// 指导编译器怎么做CComplex类对象的加法操作         // 提供了全局的+运算符重载
	CComplex operator+(const CComplex& other)        
	{
		// 错误做法：c = a + b;  加法改变了a的值，这是不对的！！！！！逻辑上不符合
		//this->_mimage += other._mimage;
		//this->_mreal += other._mreal;
		//return *this;

		// 做法一：
		//CComplex ctmp;       // 生成新对象，不改变comp1和comp2的值            不能返回局部对象的引用和指针（局部对象随函数运行完，栈帧回退，这个对象的内存会归还给系统）
		//ctmp._mreal = this->_mreal + other._mreal;
		//ctmp._mimage = this->_mimage + other._mimage;
		//return ctmp;

		// 做法二：更优秀的代码（对象的优化）
		return CComplex(this->_mreal + other._mreal, this->_mimage + other._mimage);   // 对比上面少一个对象的构造和析构

		//在C++中，匿名对象是在没有明确命名的情况下创建的对象。匿名对象通常在表达式中的一行内使用，并且不分配到一个具体的变量名。它主要用于短暂的、一次性的操作
		//请注意，匿名对象不能在其他地方进一步使用，因为它们没有名称。通常，匿名对象用于临时操作，而不是长期存储
	}


	void show() { std::cout << "real:" << _mreal << " image:" << _mimage << std::endl; }

	//后置++
	CComplex operator++(int)
	{
		//CComplex ctmp = *this;   // 先保存旧值
		//_mreal += 1;
		//_mimage += 1;
		//return ctmp;
		return CComplex(_mreal++,_mimage++);
	}

	//前置++
	CComplex& operator++()   // CComplex&值不用产生临时对象
	{
		_mreal += 1;
		_mimage += 1;
		return *this;
	}

	// +=运算符
	void operator+=(const CComplex& src)
	{
		_mreal += src._mreal;
		_mimage += src._mimage;
	}


private:
	int _mreal;
	int _mimage;

	// 函数声明为友元函数，以便它能够访问对象的私有成员
	friend CComplex operator+(const CComplex& lrs, const CComplex& rhs);
	friend std::ostream& operator<<(std::ostream& out, const CComplex& src);
	friend std::istream& operator>>(std::istream& in,CComplex& complex);
};

CComplex operator+(const CComplex& lrs, const CComplex& rhs)       
{
	return CComplex(lrs._mreal + rhs._mreal, lrs._mimage + rhs._mimage);
}

// 全局的输出运算符      返回类型通常是 std::ostream&，以支持链式输出
std::ostream& operator<<(std::ostream& out,const CComplex& src)
{
	//out << src._mreal << " + " << src._mimage << "i" << std::endl;
	out << "mreal:" <<src._mreal << " mimage:" << src._mimage << std::endl;

	return out;
}

// 参数 CComplex& complex 不能被声明为 const。这是因为输入运算符的目的是修改传递给它的对象，即从输入流中读取数据并将其存储到 CComplex 对象中
std::istream& operator>>(std::istream& in, CComplex& complex)
{
	// 从输入流中读取实部和虚部
	in >> complex._mreal >> complex._mimage;
	return in;
}

int main02()
{
	CComplex comp1(10, 10);
	CComplex comp2(20, 20);

	//               comp1.operator+(comp2)   加法运算符得重载函数                             二进制“ + ”:“CComplex”不定义该运算符或到预定义运算符可接收的类型的转换
	CComplex comp3 = comp1 + comp2;
	//CComplex comp4 = comp1.operator+(comp2);   // 这样写也可以 
	comp3.show();    // real:30 image30
	//comp4.show();    // real:30 image30

	CComplex comp5 = comp1 + 20;    //comp1.operator+(20),   int==>(类型转换)CComplex     CComplex(int),因为CComplex提供的CComplex(int)的构造函数，所以可以生成CComplex(20)的临时对象
	comp5.show();  // real:30 image10

	//编译器做对象运算的时候，会调用对象的运算符重载函数（优先调用成员方法）；如果没有成员方法
	// 就在全局作用域找合适的运算符重载函数
	//      ::operator+(30,com1)
	 CComplex comp6 = 30 + comp1;          // 二进制“ + ”: 没有找到接受“CComplex”类型的全局运算符(或没有可接受的转换)  ===>提供全局+重载运算符       
	 comp6.show();   // real:40 image10

	 // CComplex operator++(int);
	 comp6 = comp1++;   // ++ -- 是单目运算符   operator++():前置++   operator++(int):后置++
	 comp1.show();      // real:11 image11
	 comp6.show();      // real : 10 image10

	 // CComplex operator++();
	 comp6 = ++comp1;
	 comp1.show();       // real:12 image12
	 comp6.show();       // real:12 image12

	 // 复合运算符
	 // void         comp6.operator+=(comp1)                    ::operator+=(comp6,comp1)   
	 comp6 += comp1;  
	 comp6.show();   // real:24 image24    对象信息的输出


	 // ::operator<<() 
	 std::cout << comp6;

	 CComplex comp7;
	 std::cin >> comp7;
	 std::cout << comp7;
	return 0;
}































