#include<iostream>
#include<typeinfo>  //查看类型信息
#include<string>

//======================================================= 继承与多态  ================================================

/*
1.继承的本质和原理
2.派生类的构造过程
3.重载、覆盖、隐藏
4.静态绑定和动态绑定     （非常重要！！！！）
5.多态 vfptr和vftable
6.抽象类的设计原理
7.多重继承以及问题
8.虚基类 vbptr和vbtable
9.RTTI
10.C++四种类型强转
11.继承多态常见笔试面试题分享
*/

//======================================================= 11.C++四种类型强转================================================ 
/*
C++语言级别提供的四种类型转换方式
C语言：int a = (int)b;
C++：
const_cast : 去掉(指针/引用)常量属性的一个类型转换
static_cast : 提供编译器认为安全的类型转换 (没有任何联系的类型转换就被否定了)
reinterpret_cast : 类似于C风格的强制类型转换
dynamic_cast : 主要用于继承结构中，可以支持RTTI类型识别的上下转换
*/


class Base
{
public:
	virtual void func() = 0;
};

class Derive1:public Base
{
public:
	void func()
	{
		std::cout << "call Derive1::func" << std::endl;
	}
};

class Derive2 :public Base
{
public:
	void func()
	{
		std::cout << "call Derive2::func" << std::endl;
	}
	void derive2func()
	{
		std::cout << "call Derive2::derive2func" << std::endl;
	}
};

void showFunc(Base* p)
{
	// dynamic_cast会检查p指针是否指向的是一个Derive2类型的对象
	// p->vfptr->vftable RTTI信息 如果是，dynamic_cast转换类型成功，返回Derive2对象的是地址，赋给pd2；否则返回nullptr
	// static_cast编译时期的类型转换  dynamic_cast运行时期的类型转换    支持RTTI信息识别的
	Derive2* pd2 = dynamic_cast<Derive2*>(p);
	if (pd2 != nullptr)
	{
		pd2->derive2func();
	}
	else
	{
		p->func();       // 动态绑定
	}
}

int main()
{
	Derive1 d1;
	Derive2 d2;
	showFunc(&d1);
	showFunc(&d2);


	//// static_cast
	//int a = 10;
	//int* p = nullptr;

	//// “static_cast” : 无法从“int * ”转换为“double* ”            指向的类型不相关; 转换需要 reinterpret_cast、C 样式强制转换或带圆括号的函数样式强制转换	
	////double* b = static_cast<double*>(p);

	//double* b = reinterpret_cast<double*>(p);



	// ①
	//const int a = 10;
	//double* p1 = (double*)&a;       
	//int* p2 = const_cast<int*>(&a);   // 只能去除const性质的转换，(不能int* ==> double*) 

	//const_cast 中的类型必须是指针、引用或指向对象类型成员的指针     int* int&
	//int b = const_cast<int>(a);




	return 0;
}




//======================================================= 11.多重继承--菱形继承 ================================================ 
/*
C++多重继承--菱形继承的问题    派生类有多份间接的数据（这是）
好处：更多代码的复用       

*/
#if 0
class A
{
public:
	A(int data) :ma(data) { std::cout << "A()" << std::endl; }
	~A() { std::cout << "~A()" << std::endl; }
protected:
	int ma;
};

class B: virtual public A
{
public:
	B (int data) :A(data),mb(data) { std::cout << "B()" << std::endl; }
	~B() { std::cout << "~B()" << std::endl; }
protected:
	int mb;
};

class C : virtual public A
{
public:
	C(int data) :A(data), mc(data) { std::cout << "C()" << std::endl; }
	~C() { std::cout << "~C()" << std::endl; }
protected:
	int mc;
};
//=====================================================================
class D :public B, public C
{
public:
	// “A::A” : 没有合适的默认构造函数可用    虚继承后，ma必须由派生类自己初始化
	D(int data) :A(data),B(data), C(data), md(data) { std::cout << "D()" << std::endl; }
	~D() { std::cout << "~D()" << std::endl; }
protected:
	int md;
};

int main()
{
	D d(10);
	/*
	A()
	B()
	A()
	C()
	D()
	~D()
	~C()
	~A()
	~B()
	~A()
	*/

	/*   虚继承后
	A()
	B()
	C()
	D()
	~D()
	~C()
	~B()
	~A()
	*/


	return 0;
}
#endif


//======================================================= 10.多重继承 ================================================ 
/*
多重继承：代码复用       一个派生类有多个基类

抽象类（有纯虚函数的类）/虚基类  被虚继承的类称作虚基类 vbptr和vbtable
virtual
1.修饰成员方法是虚函数
2.可以修饰继承方式，是虚继承。被虚继承的类，称作虚基类
*/


#if 0
class A   
{
public:
	virtual void func() { std::cout << "call A::func" << std::endl; }
private:
	int ma;
};

class B : virtual public A      // A:虚基类
{
public:
	virtual void func() { std::cout << "call B::func" << std::endl; }
private:
	int mb;
};
/*
A a;  4个字节
B b;   ma,ma  8个字节 + 4字节（vbptr）= 12个字节

*/

int main()
{
	// 基类指针指向派生类对象，永远指向的是派生类基类部分数据的起始地址！！！
	A* p = new B();
	p->func();
	delete p;

	return 0;
};
#endif


//======================================================= 9.继承多态常见笔试面试题分享================================================ 







//======================================================= 8.抽象类 ================================================ 
/*
抽象类贺普通类的区别？

一般把什么类设计成抽象类？
// 抽象类通常包含至少一个纯虚函数（纯虚函数是通过在声明中添加 "= 0" 来定义的虚函数），这使得该类不能被实例化，而只能被用作基类。抽象类的目的是为了提供一个接口，并规定派生类必须实现这个接口
// 总的来说，抽象类用于定义通用的接口和概念，并规定派生类必须实现这些接口。抽象类不能被实例化，但可以通过指针或引用访问其派生类的对象。
*/

// 动物的基类    泛指           类->抽象一个实体类型
/*
定义Animal的初衷，并不是让Animal抽象某个实体的类型
1. string _name;  让所有的动物实体类通过继承Animal直接复用该属性  （代码复用）
2. 给所有的派生类保留统一的覆盖/重写接口   ===》软件设计，高内聚，低耦合一点

 拥有纯虚函数的类，叫做抽象类
 Animal a;   NO!
 抽象类不能再实例化对象，但是可以定义指针和引用变量 ※※

*/

#if 0
class Animal   
{
public:
	Animal(std::string name) :_name(name) {}
	// 纯虚函数
	virtual void bark() = 0;
protected:
	std::string _name;
};

// 以下是动物实体类
class Cat :public Animal
{
public:
	Cat(std::string name) :Animal(name) {}
	void bark() { std::cout << "bark:miao miao!" << std::endl; }
};

class Dog :public Animal
{
public:
	Dog(std::string name) :Animal(name) {}
	void bark() { std::cout << "bark:wang wang!" << std::endl; }
};

class Pig :public Animal
{
public:
	Pig(std::string name) :Animal(name) {}
	void bark() { std::cout << "bark:heng heng!" << std::endl; }
};

// 更好的做法：
void bark(Animal* p)
{
	p->bark();          // Animal::bark虚函数，动态绑定
	/*
	p->cat Cat vftable &Cat::bark
	p->dog Dog vftable &Dog::bark
	p->pig Pig vftable &Pig::bark
	*/
}


// 汽车的基类
class Car         // 抽象类
{
public:
	Car(std::string name, double oil):_name(name),_oil(oil){}
	// 获取汽车剩余油量还能跑的公里数
	double getLeftMiles()
	{
		return  _oil * this->getMilesPerGallon();   // 发生动态绑定
	}

	std::string getName() const { return _name; }
protected:
	std::string _name;
	double _oil;

	virtual double getMilesPerGallon() = 0;
};

class Bnze:public Car
{
public:
	Bnze(std::string name, double oil) : Car(name, oil) {}
	double getMilesPerGallon()
	{
		return 20.0;
	}
};

class Audi :public Car
{
public:
	Audi(std::string name, double oil) : Car(name, oil) {}
	double getMilesPerGallon()
	{
		return 18.0;
	}
};

class BMW :public Car
{
public:
	BMW(std::string name,double oil) : Car(name, oil) {}
	double getMilesPerGallon()
	{
		return 19.0;
	}
};

// 给外部提供一个统一的获取汽车剩余路程数的API接口
void showCarLeftMiles(Car& car)
{
	// car.getLeftMiles() ==》静态绑定
	std::cout << car.getName() << " left miles::" << car.getLeftMiles() << std::endl;
}


int main()
{
	Bnze b1("奔驰",10);
	Audi a("奥迪", 10);
	BMW b2("宝马", 10);

	showCarLeftMiles(b1);
	showCarLeftMiles(a);
	showCarLeftMiles(b2);
	/*
	奔驰 left miles::200
	奥迪 left miles::180
	宝马 left miles::190
	*/



	/*
	Cat cat("猫咪");
	Dog dog("二哈");
	Pig pig("佩奇");

	bark(&cat);
	bark(&dog);
	bark(&pig);
	*/

	return 0;
}

#endif



//======================================================= 7.如何解释多态 ================================================ 
/*
如何解释多态？
1.静态（编译时期）的多态：函数重载、模板（函数模板和类模板）
bool compare(int,int){}
bool compare(double,double){}

compare(10,10);          // call compare_int_int       在编译阶段就确定好调用的函数版本
compare(double,double);  // call compare_double_double     在编译阶段就确定好调用的函数版本


template<typename T>
bool compare(T a,T b){}

compare(10,10);   ===> int 实例化一个compare<int>
compare(double,double);   ====> double 实例化一个 compare<double>


2.动态（运行时期）的多态
在继承结构中，基类指针（引用）指向派生类对象，通过该指针（引用）调用同名覆盖方法（虚函数），
基类指针指向哪个派生类对象，就会调用哪个派生类对象的覆盖方法，称为多态。
pbase->show();
 多态底层是通过动态绑定来实现的！！！！  基类指针指向谁，就访问谁的vfptr,进而访问谁的虚函数表vftable ====> 当然调用的是对应的派生类对象的方法了



 继承的好处：
 1.可以做代码的复用
 2.在基类中提供统一的虚函数接口，让派生类进行重写，然后就可以使用多态了。
*/

#if 0
// 动物的基类
class Animal
{
public:
	Animal(std::string name) :_name(name) {}
	virtual void bark() {}
protected:
	std::string _name;
};


class Cat :public Animal
{
public:
	Cat(std::string name) :Animal(name) {}
	void bark() { std::cout << "bark:miao miao!" << std::endl; }
};

class Dog :public Animal
{
public:
	Dog(std::string name) :Animal(name) {}
	void bark() { std::cout << "bark:wang wang!" << std::endl; }
};

class Pig :public Animal
{
public:
	Pig(std::string name) :Animal(name) {}
	void bark() { std::cout << "bark:heng heng!" << std::endl; }
};


/*
下面的一组bark API接口无法做到我们软件设计要求的"开-闭"原则 （高内聚、低耦合）
软件设计有六大原则    ①"开-闭原则" 对修改关闭，对扩展开放
*/

//void bark(Cat& cat)
//{
//	cat.bark();          //动态绑定
//}
//
//void bark(Dog& dog)
//{
//	dog.bark();
//}
//
//void bark(Pig& pig)
//{
//	pig.bark();
//}


// 更好的做法：
void bark(Animal& an)
{
	an.bark();          // Animal::bark虚函数，动态绑定
}

void bark(Animal* p)
{
	p->bark();          // Animal::bark虚函数，动态绑定
	/*
	p->cat Cat vftable &Cat::bark
	p->dog Dog vftable &Dog::bark
	p->pig Pig vftable &Pig::bark
	*/
}
int main()
{
	Cat cat("猫咪");
	Dog dog("二哈");
	Pig pig("佩奇");

	bark(cat);
	bark(dog);
	bark(pig);

	bark(&cat);
	bark(&dog);
	bark(&pig);

	return 0;
}

#endif


//======================================================= 6.再谈动态绑定 ================================================ 
/*
  虚函数和动态绑定      
  问题：是不是虚函数的调用一定就是动态绑定？   
  肯定不是的！！！  再类的构造函数当中，调用虚函数，也是静态绑定（构造函数中调用其他函数（虚），不会发生动态绑定）


  如果不是通过引用或者指针变量来调用虚函数，那就是静态绑定！！！

*/


#if 0
class Base
{
public:
	Base(int data = 0) :ma(data) {}
	virtual void show() { std::cout << "Base::show()" << std::endl; }
protected:
	int ma;
};

class Derive : public Base
{
public:
	Derive(int data = 0):Base(data),mb(data){}
	void show() { std::cout << "Derive::show()" << std::endl; }
private:
	int mb;
};

int main()
{

	Base b;
	Derive d;

	// 静态绑定   用对象本身调用虚函数，是静态绑定
	b.show();      // 虚函数 call Base::show
	d.show();      // 虚函数 call Derive::show
	/*
	Base::show()
	Derive::show()
	*/


	// 动态绑定  （必须由指针调用虚函数）
	Base* pb1 = &b;
	pb1->show();         
	Base* pb2 = &d;       
	pb2->show();
	/*
	Base::show()
	Derive::show()
	*/


	// 动态绑定  （必须由引用变量调用虚函数）
	Base& rb1 = b;
	rb1.show();
	Base& rb2 = d;
	rb2.show();
	/*
	Base::show()
	Derive::show()
	*/

	// 动态绑定         （虚函数通过指针或者引用变量调用，才会发生动态绑定）
	Derive* pd1 = &d;
	pd1->show();
	Derive& rd1 = d;
	rd1.show();
	/*
	Derive::show()
	Derive::show()
	*/
	return 0;
}
#endif


//======================================================= 5.虚析构函数 ================================================ 
/*
问题一：哪些函数不能是实现成虚函数？

虚函数依赖：
1.虚函数能产生地址，存储在vftable中
2.对象必须存在（vfptr -> vftable ->虚函数地址）

①构造函数
1.virtual + 构造函数  N0！                                                       // 虚函数表（vtable）是在对象构造时建立的，因此构造函数不能是虚函数
2.构造函数中（调用任何函数，都是静态绑定的）调用虚函数。也不会发生动态绑定

派生类对象构造过程  1.先调用的是基类的构造函数   2.才调用派生类的构造函数


②static静态成员方法 NO！
																				// 静态成员函数与类关联，而不是与类的实例关联。因此，它们不属于类的对象，也不会有虚函数表


问题二：虚析构函数         析构函数调用的时候，对象是存在的！！

													※※※※※ 什么时候把基类的析构函数必须实现成虚函数？ ※※※※※※
基类的指针（引用）指向堆上new出来的派生类对象的时候，delete pb(基类的指针)，
他调用析构函数的时候，必须发生动态绑定，构造会导致派生类的析构函数无法调用
*/


#if 0
class Base
{
public:
	Base(int data)
		:ma(data)
	{
		std::cout << "Base()" << std::endl;
	}
	// 虚析构函数
	virtual ~Base()
	{
		std::cout << "~Base()" << std::endl;
	}
	virtual void show() { std::cout << "call Base::show()" << std::endl; }
protected:
	int ma;
};


class Derive : public Base
{
public:
	// “Base” : 没有合适的默认构造函数可用
	Derive(int data)
		:Base(data)                           // ma(data)  《====   不能这样初始化      
		,mb(data)
		,ptr(new int(data))
	{
		std::cout << "Derive()" << std::endl;
	}

	// 基类的析构函数时virtual虚函数，那么派生类的析构函数自动成为虚函数！！！！
	~Derive()
	{
		std::cout << "~Derive()" << std::endl;
	}
private:
	int mb;
	int *ptr;
};

int main()
{
	//Derive d(10);         
	//Base* pb =&d;           // 在栈上的内存
	//pb->show();
	/* 
	Base()
	Derive()
	call Base::show()
	~Derive()
	~Base()
	*/


	Base* pb = new Derive(10);   //在堆上new出来的对象
	pb->show();         
	delete pb;
	/*  基类析构函数为普通函数时
	Base()
	Derive()
	call Base::show()
	~Base()                 // 派生类的析构函数没有调用到！！！！！！！！       ===》  解决方法：把基类的析构函数设置为虚析构函数
	*/

	/*
	没有调用派生类的析构函数的原因：
	pb  --> Base类型   Base::~Base() ==》 普通成员函数  ===》 对于析构函数调用，就是静态绑定

	pb  --> Base类型 Base:: virtual ~Base() ==》 虚函数  ===》  对于析构函数调用，就是动态绑定了
	pb  --》 Derive   Derive vftable   &Derive::~Derive

	              
	Base()
	Derive()
	call Base::show()
	~Derive()
	~Base()
	*/

	return 0;
}
#endif

//======================================================= 4.静态绑定和动态绑定 ================================================ （非常重要、重点、核心！！！！）
/*
虚函数，静态绑定和动态绑定

覆盖：基类和派生类的方法，返回值、函数名、参数列表都相同，而且基类的方法是虚函数，
那么派生类的方法就自动处理成虚函数，他们之间成为覆盖关系。


一个类添加了虚函数，对这个类有什么影响？
总结一：
一个类里面定义了虚函数，那么编译阶段，编译器给这个类类型产生一个唯一的vftable(虚函数表)，
虚函数表中主要存储的内容就是RTTI（run time type infomation）指针和虚函数地址。当程序运行时，每一张虚函数表都会加载到内存的.rodata区。

总结二：
一个类里面定义了虚函数，那么这个了定义的对象，其运行时，内存中的开始部分，多存储一个vfptr虚函数指针，指向相应类型的虚函数表vftable。
一个类型定义对的n个对象，它们的vfptr虚函数指针指向的都是同一张虚函数表

总结三：
一个类里面的虚函数的个数，不影响对象的内存大小（vfptr）,影响的是虚函数表的大小！！！！！！！

*/

#if 0
class Base
{
public:
	Base(int data = 10) :ma(data) {};
	// 虚函数
	virtual void show() { std::cout << "Base::show()" << std::endl; }
	// 虚函数
	virtual void show(int) { std::cout << "Base::show(int)" << std::endl; }
private:
	int ma;
};

class Derive : public Base
{
public:
	Derive(int data = 20)
		:Base(data)
		, mb(data)
	{

	}
	/*
	总结四：
	如果派生类中的方法，和基类继承来的某个方法，返回值，函数名，参数列表相同，
	而且基类的方法是virtual虚函数，那么派生类的这个方法，自动处理成虚函数！！（尽管我们定义时，没写上virtual）
	重写  《====》  覆盖              {覆盖：虚函数表中虚函数地址的覆盖}

	*/
	void show() { std::cout << "Derive::show()" << std::endl; }
private:
	int mb;
};


int main()
{
	Derive d(50);
	Base *p = &d;

	/*
	p->show()   pb是Base类型 ==》 Base::show是普通函数，就进行静态绑定

	p->show()   pb是Base类型 ==》 Base::show是虚函数，就进行动态绑定了
	*/
	p->show();    // Base::show()    //静态（编译时期）的绑定（函数的调用）  ===>            00007FF73FB02657  call        Base::show (07FF73FB013E8h) 

	/*
	Base::show(int)  是一个虚函数，此时就得动态绑定了 

	*/
	p->show(10);  // Base::show(int)                                                         00007FF73FB02665  call        Base::show (07FF73FB010DCh)

/*  32位系统
	p->show();    // Base::show()    //静态（编译时期）的绑定（函数的调用）  ===>            00007FF73FB02657  call        Base::show (07FF73FB013E8h)
	009D28FF  mov         eax,dword ptr [p]
	009D2902  mov         edx,dword ptr [eax]
	009D2904  mov         esi,esp
	009D2906  mov         ecx,dword ptr [p]
	009D2909  mov         eax,dword ptr [edx+4]
	009D290C  call        eax    （虚函数的地址） 动态（运行时期）绑定（函数的调用）                      
	//调用存储在 eax 寄存器中的函数地址。该地址是从 edx + 4 中加载的。这是面向对象编程中的常见模式，其中对象的虚函数表（vtable）的第一个条目是指向虚函数表的指针
	009D290E  cmp         esi,esp
	009D2910  call        __RTC_CheckEsp (09D12C1h)
		p->show(10);  // Base::show(int)                                                         00007FF73FB02665  call        Base::show (07FF73FB010DCh)
	009D2915  mov         esi,esp
	009D2917  push        0Ah
	009D2919  mov         eax,dword ptr [p]
	009D291C  mov         edx,dword ptr [eax]
	009D291E  mov         ecx,dword ptr [p]
	009D2921  mov         eax,dword ptr [edx]
	009D2923  call        eax     //调用存储在 eax 寄存器中的函数地址。该地址是从 edx + 4 中加载的。这是面向对象编程中的常见模式，其中对象的虚函数表（vtable）的第一个条目是指向虚函数表的指针
	009D2925  cmp         esi,esp
	009D2927  call        __RTC_CheckEsp (09D12C1h)
*/

	std::cout << sizeof(Base) << std::endl;   //4
	std::cout << sizeof(Derive) << std::endl;   //8


	std::cout << typeid(p).name() << std::endl;  // class Base * __ptr64
	/*
	pb得类型：Base  -》 有没有虚函数
	如果Base没有虚函数，*pb识别得就是编译时期得类型  *pb <==> Base类型
	如果Base有虚函数， *pb识别得就是运行时期得类型 RTTI类型  
	*/
	std::cout << typeid(*p).name() << std::endl;   // class Base

	/*  // Base类show方法未加virtual关键字       Base的两个show函数都是普通函数
	Base::show()
	Base::show(int)
	4
	8
	class Base * __ptr64
	class Base
	*/

	/*  
	Derive::show()
	Base::show(int)
	16
	24
	class Base * __ptr64
	class Derive
	*/

	/*  X86体系32位系统             给Base的两个show函数定义成virtual函数
	Derive::show()
	Base::show(int)
	8
	12
	class Base *
	class Derive
	*/
	return 0;
}
#endif

//======================================================= 3.重载、覆盖、隐藏  ================================================
/*
重载、覆盖、隐藏
1.重载关系
一组函数要重载，必须处在同一个作用域当中；而且函数名字相同，参数列表不同

2.隐藏（作用域的隐藏）关系
在继承结构当中，派生类的同名成员，把基类的同名成员（包括成员方法和成员变量）给隐藏掉了


==============================================================================================================================
1.把继承机构，也说成从上（基类）到下（派生类）的结构
2.
基类对象 -> 派生类对象      N
派生类  -> 基类对象      Y

基类指针（引用） ->  派生类对象        N
派生类指针（引用） -> 基类对象       Y

总结：在继承结构中进行上下的类型转换，默认只支持从下到上类型的转换 【但是可以类型强转，但很危险，会出现内存非法访问！！！！】  OK

*/

#if 0
class Base
{
public:
	Base(int data = 10) :ma(data) {};
	void show() { std::cout << "Base::show()" << std::endl; }
	void show(int){ std::cout << "Base::show(int)" << std::endl; }
private:
	int ma;
};

class Derive : public Base
{
public:
	Derive(int data = 20)
		:Base(data)
		, mb(data)
	{

	}

	void show() { std::cout << "Derive::show()" << std::endl; }
private:
	int mb;
};


int main()
{
	Base b(10);
	Derive d(20);

	// 基类对象b <- 派生类对象d      类型从下到上的转换   Y
	b = d;

	// 派生类对象d <- 基类对象b      类型从上到下的转换   N
	//d = b;                                                     // C2679	二元“ = ”: 没有找到接受“Base”类型的右操作数的运算符(或没有可接受的转换)

	// 基类指针（引用） <- 派生类对象    类型从下到上的转换   Y
	Base* pb = &d;
	//pb->show();
	//pb->show(10);
	/*              pb默认只能调用从基类的继承过来的方法，
	Base::show()
	Base::show(int)
	*/

	((Derive*)pb)->show();     // 类型强转
	pb->show(10);
	/*
	Derive::show()
	Base::show(int)
	*/

	// 派生类指针（引用） <-  基类指针        类型从上到下的转换   N
	// Derive* pd = &b;                                         // "Base *" 类型的值不能用于初始化 "Derive *" 类型的实体
	Derive* pd = (Derive*) & b;    // 不安全，设计了内存的非法访问！！！ 
	pd->show();  // Derive::show()    ============》 如果show里面使用到了派生类的数据成员，则会发生内存的非法访问！！！          因为内存上根本没有派生类对象！！！！


#if 0
	Derive d;
	d.show();

	//“Derive::show”: 函数不接受 1 个参数	05_继承与多态
	// d.show(10);      //优先找的是派生类自己作用域的show名字成员；没有的话，才去基类里面找

	d.Base::show();
	d.Base::show(10);
#endif


	return 0;
}

#endif


//======================================================= 2.派生类的构造过程  ================================================
/*
1.派生类从继承可以继承来所有的成员（变量和方法），包括构造函数和析构函数

派生类怎么初始化从基类继承过来的成员变量？
解答：通过调用基类相应的构造函数来初始化

派生类的构造函数和析构函数，负责初始化和清理派生类部分
派生类从基类继承来的成员的初始化和清理由谁负责呢？    ==========》 是由基类的构造函数和析构函数来负责！！


>>>>>>>>>>>>>>>>>>>派生类对象构造和析构的过程是：
1.派生类调用基类的构造函数，初始化从基类继承来的成员
2.调用派生类自己的构造函数，初始化派生类自己特有的成员
...........
...........（派生类对象的作用域到期了）
3.调用派生类的析构函数，释放派生类成员可能占用的外部资源（堆内存，文件...）
4.调用基类的析构函数，释放派生类内存中，从基类继承过来的成员可能占用的外部资源（堆内存，文件...）
*/

#if 0
class Base
{
public:
	Base(int data) 
		:ma(data)
	{
		std::cout << "Base()" << std::endl;
	}
	~Base()
	{
		std::cout << "~Base()" << std::endl;
	}
protected:
	int ma;
};


class Derive : public Base
{
public:
	// “Base” : 没有合适的默认构造函数可用
	Derive(int data)
		:Base(data)                           // ma(data)  《====   不能这样初始化      
		,mb(data)
	{
		std::cout << "Derive()" << std::endl;
	}

	~Derive()
	{
		std::cout << "~Derive()" << std::endl;
	}
private:
	int mb;
};

int main()
{
	Derive d(20);
	/*
		Base()
		Derive()
		~Derive()
		~Base()
	*/

	return 0;
}
#endif


//======================================================= 1.继承的本质和原理  ================================================
#if 0
/*
1.继承的本质和原理
继承的本质：a.代码复用  b.

类和类之间关系
组合：a part of...   .... 一部分的关系
继承：a kind of...   .... 一种的关系


继承方式            基类的访问限定                  派生类的访问限定                 （main）外部的访问
public
					  public                           public                               Y
					  protected                        protected                            N
					  private                          不可见的                             N

protected （基类的成员的访问限定，在派生类里面是不可能超过继承方式的！！！）            
					  public                           protected                            N
					  protected                        protected                            N
					  private                          不可见的                             N
private
					  public                           private                              N
					  protected                        private                              N
					  private                          不可见的                             N



总结：
1、外部只能访问对象public的成员，protected和private的成员无法直接访问
2.在继承结构中，派生类从基类可以继承过来private的成员，但是派生类却无法直接访问
3.protected和private的区别？在基类中定义的成员，想被派生类访问，但是不想被外部访问，
那么在基类中，把相关成员定义成protected保护的；如果派生类和外部都不打算访问，
那么在基类中，就把相关成员定义成private私有的

默认的继承方式是什么？
要看派生类时用class定义的还是struct定义的！！
class定义派生类，默认继承方式就是private私有的
struct定义派生类，默认继承方式就是public公有的

*/



class A
{
public:
	int ma;
protected:
	int mb;
private:
	int mc;      // 只有自己或者友元能访问私有的成员

};

// 继承     A:基类/父类    B 派生类/子类
class B:public  A       
{
public:
	void func()
	{
		std::cout << "ma:" << mb << std::endl;
	}

	int md;
protected:
	int me;
private:
	int mf;

};

class C :public B
{
	// 在C里面，请问ma的访问限定是什么？ 不可见的，但是能继承来(即ma在C中是占内存的)
};

int main()
{
	B b;
	
	std::cout << "ma:" << b.ma << std::endl;
	return 0;

}

#endif






