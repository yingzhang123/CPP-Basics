#include<iostream>
#include<typeinfo>  //�鿴������Ϣ
#include<string>

//======================================================= �̳����̬  ================================================

/*
1.�̳еı��ʺ�ԭ��
2.������Ĺ������
3.���ء����ǡ�����
4.��̬�󶨺Ͷ�̬��     ���ǳ���Ҫ����������
5.��̬ vfptr��vftable
6.����������ԭ��
7.���ؼ̳��Լ�����
8.����� vbptr��vbtable
9.RTTI
10.C++��������ǿת
11.�̳ж�̬�����������������
*/

//======================================================= 11.C++��������ǿת================================================ 
/*
C++���Լ����ṩ����������ת����ʽ
C���ԣ�int a = (int)b;
C++��
const_cast : ȥ��(ָ��/����)�������Ե�һ������ת��
static_cast : �ṩ��������Ϊ��ȫ������ת�� (û���κ���ϵ������ת���ͱ�����)
reinterpret_cast : ������C����ǿ������ת��
dynamic_cast : ��Ҫ���ڼ̳нṹ�У�����֧��RTTI����ʶ�������ת��
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
	// dynamic_cast����pָ���Ƿ�ָ�����һ��Derive2���͵Ķ���
	// p->vfptr->vftable RTTI��Ϣ ����ǣ�dynamic_castת�����ͳɹ�������Derive2������ǵ�ַ������pd2�����򷵻�nullptr
	// static_cast����ʱ�ڵ�����ת��  dynamic_cast����ʱ�ڵ�����ת��    ֧��RTTI��Ϣʶ���
	Derive2* pd2 = dynamic_cast<Derive2*>(p);
	if (pd2 != nullptr)
	{
		pd2->derive2func();
	}
	else
	{
		p->func();       // ��̬��
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

	//// ��static_cast�� : �޷��ӡ�int * ��ת��Ϊ��double* ��            ָ������Ͳ����; ת����Ҫ reinterpret_cast��C ��ʽǿ��ת�����Բ���ŵĺ�����ʽǿ��ת��	
	////double* b = static_cast<double*>(p);

	//double* b = reinterpret_cast<double*>(p);



	// ��
	//const int a = 10;
	//double* p1 = (double*)&a;       
	//int* p2 = const_cast<int*>(&a);   // ֻ��ȥ��const���ʵ�ת����(����int* ==> double*) 

	//const_cast �е����ͱ�����ָ�롢���û�ָ��������ͳ�Ա��ָ��     int* int&
	//int b = const_cast<int>(a);




	return 0;
}




//======================================================= 11.���ؼ̳�--���μ̳� ================================================ 
/*
C++���ؼ̳�--���μ̳е�����    �������ж�ݼ�ӵ����ݣ����ǣ�
�ô����������ĸ���       

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
	// ��A::A�� : û�к��ʵ�Ĭ�Ϲ��캯������    ��̳к�ma�������������Լ���ʼ��
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

	/*   ��̳к�
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


//======================================================= 10.���ؼ̳� ================================================ 
/*
���ؼ̳У����븴��       һ���������ж������

�����ࣨ�д��麯�����ࣩ/�����  ����̳е����������� vbptr��vbtable
virtual
1.���γ�Ա�������麯��
2.�������μ̳з�ʽ������̳С�����̳е��࣬���������
*/


#if 0
class A   
{
public:
	virtual void func() { std::cout << "call A::func" << std::endl; }
private:
	int ma;
};

class B : virtual public A      // A:�����
{
public:
	virtual void func() { std::cout << "call B::func" << std::endl; }
private:
	int mb;
};
/*
A a;  4���ֽ�
B b;   ma,ma  8���ֽ� + 4�ֽڣ�vbptr��= 12���ֽ�

*/

int main()
{
	// ����ָ��ָ�������������Զָ�������������ಿ�����ݵ���ʼ��ַ������
	A* p = new B();
	p->func();
	delete p;

	return 0;
};
#endif


//======================================================= 9.�̳ж�̬�����������������================================================ 







//======================================================= 8.������ ================================================ 
/*
���������ͨ�������

һ���ʲô����Ƴɳ����ࣿ
// ������ͨ����������һ�����麯�������麯����ͨ������������� "= 0" ��������麯��������ʹ�ø��಻�ܱ�ʵ��������ֻ�ܱ��������ࡣ�������Ŀ����Ϊ���ṩһ���ӿڣ����涨���������ʵ������ӿ�
// �ܵ���˵�����������ڶ���ͨ�õĽӿں͸�����涨���������ʵ����Щ�ӿڡ������಻�ܱ�ʵ������������ͨ��ָ������÷�����������Ķ���
*/

// ����Ļ���    ��ָ           ��->����һ��ʵ������
/*
����Animal�ĳ��ԣ���������Animal����ĳ��ʵ�������
1. string _name;  �����еĶ���ʵ����ͨ���̳�Animalֱ�Ӹ��ø�����  �����븴�ã�
2. �����е������ౣ��ͳһ�ĸ���/��д�ӿ�   ===�������ƣ����ھۣ������һ��

 ӵ�д��麯�����࣬����������
 Animal a;   NO!
 �����಻����ʵ�������󣬵��ǿ��Զ���ָ������ñ��� ����

*/

#if 0
class Animal   
{
public:
	Animal(std::string name) :_name(name) {}
	// ���麯��
	virtual void bark() = 0;
protected:
	std::string _name;
};

// �����Ƕ���ʵ����
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

// ���õ�������
void bark(Animal* p)
{
	p->bark();          // Animal::bark�麯������̬��
	/*
	p->cat Cat vftable &Cat::bark
	p->dog Dog vftable &Dog::bark
	p->pig Pig vftable &Pig::bark
	*/
}


// �����Ļ���
class Car         // ������
{
public:
	Car(std::string name, double oil):_name(name),_oil(oil){}
	// ��ȡ����ʣ�����������ܵĹ�����
	double getLeftMiles()
	{
		return  _oil * this->getMilesPerGallon();   // ������̬��
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

// ���ⲿ�ṩһ��ͳһ�Ļ�ȡ����ʣ��·������API�ӿ�
void showCarLeftMiles(Car& car)
{
	// car.getLeftMiles() ==����̬��
	std::cout << car.getName() << " left miles::" << car.getLeftMiles() << std::endl;
}


int main()
{
	Bnze b1("����",10);
	Audi a("�µ�", 10);
	BMW b2("����", 10);

	showCarLeftMiles(b1);
	showCarLeftMiles(a);
	showCarLeftMiles(b2);
	/*
	���� left miles::200
	�µ� left miles::180
	���� left miles::190
	*/



	/*
	Cat cat("è��");
	Dog dog("����");
	Pig pig("����");

	bark(&cat);
	bark(&dog);
	bark(&pig);
	*/

	return 0;
}

#endif



//======================================================= 7.��ν��Ͷ�̬ ================================================ 
/*
��ν��Ͷ�̬��
1.��̬������ʱ�ڣ��Ķ�̬���������ء�ģ�壨����ģ�����ģ�壩
bool compare(int,int){}
bool compare(double,double){}

compare(10,10);          // call compare_int_int       �ڱ���׶ξ�ȷ���õ��õĺ����汾
compare(double,double);  // call compare_double_double     �ڱ���׶ξ�ȷ���õ��õĺ����汾


template<typename T>
bool compare(T a,T b){}

compare(10,10);   ===> int ʵ����һ��compare<int>
compare(double,double);   ====> double ʵ����һ�� compare<double>


2.��̬������ʱ�ڣ��Ķ�̬
�ڼ̳нṹ�У�����ָ�루���ã�ָ�����������ͨ����ָ�루���ã�����ͬ�����Ƿ������麯������
����ָ��ָ���ĸ���������󣬾ͻ�����ĸ����������ĸ��Ƿ�������Ϊ��̬��
pbase->show();
 ��̬�ײ���ͨ����̬����ʵ�ֵģ�������  ����ָ��ָ��˭���ͷ���˭��vfptr,��������˭���麯����vftable ====> ��Ȼ���õ��Ƕ�Ӧ�����������ķ�����



 �̳еĺô���
 1.����������ĸ���
 2.�ڻ������ṩͳһ���麯���ӿڣ��������������д��Ȼ��Ϳ���ʹ�ö�̬�ˡ�
*/

#if 0
// ����Ļ���
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
�����һ��bark API�ӿ��޷���������������Ҫ���"��-��"ԭ�� �����ھۡ�����ϣ�
������������ԭ��    ��"��-��ԭ��" ���޸Ĺرգ�����չ����
*/

//void bark(Cat& cat)
//{
//	cat.bark();          //��̬��
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


// ���õ�������
void bark(Animal& an)
{
	an.bark();          // Animal::bark�麯������̬��
}

void bark(Animal* p)
{
	p->bark();          // Animal::bark�麯������̬��
	/*
	p->cat Cat vftable &Cat::bark
	p->dog Dog vftable &Dog::bark
	p->pig Pig vftable &Pig::bark
	*/
}
int main()
{
	Cat cat("è��");
	Dog dog("����");
	Pig pig("����");

	bark(cat);
	bark(dog);
	bark(pig);

	bark(&cat);
	bark(&dog);
	bark(&pig);

	return 0;
}

#endif


//======================================================= 6.��̸��̬�� ================================================ 
/*
  �麯���Ͷ�̬��      
  ���⣺�ǲ����麯���ĵ���һ�����Ƕ�̬�󶨣�   
  �϶����ǵģ�����  ����Ĺ��캯�����У������麯����Ҳ�Ǿ�̬�󶨣����캯���е��������������飩�����ᷢ����̬�󶨣�


  �������ͨ�����û���ָ������������麯�����Ǿ��Ǿ�̬�󶨣�����

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

	// ��̬��   �ö���������麯�����Ǿ�̬��
	b.show();      // �麯�� call Base::show
	d.show();      // �麯�� call Derive::show
	/*
	Base::show()
	Derive::show()
	*/


	// ��̬��  ��������ָ������麯����
	Base* pb1 = &b;
	pb1->show();         
	Base* pb2 = &d;       
	pb2->show();
	/*
	Base::show()
	Derive::show()
	*/


	// ��̬��  �����������ñ��������麯����
	Base& rb1 = b;
	rb1.show();
	Base& rb2 = d;
	rb2.show();
	/*
	Base::show()
	Derive::show()
	*/

	// ��̬��         ���麯��ͨ��ָ��������ñ������ã��Żᷢ����̬�󶨣�
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


//======================================================= 5.���������� ================================================ 
/*
����һ����Щ����������ʵ�ֳ��麯����

�麯��������
1.�麯���ܲ�����ַ���洢��vftable��
2.���������ڣ�vfptr -> vftable ->�麯����ַ��

�ٹ��캯��
1.virtual + ���캯��  N0��                                                       // �麯����vtable�����ڶ�����ʱ�����ģ���˹��캯���������麯��
2.���캯���У������κκ��������Ǿ�̬�󶨵ģ������麯����Ҳ���ᷢ����̬��

��������������  1.�ȵ��õ��ǻ���Ĺ��캯��   2.�ŵ���������Ĺ��캯��


��static��̬��Ա���� NO��
																				// ��̬��Ա������������������������ʵ����������ˣ����ǲ�������Ķ���Ҳ�������麯����


�����������������         �����������õ�ʱ�򣬶����Ǵ��ڵģ���

													���������� ʲôʱ��ѻ����������������ʵ�ֳ��麯���� ������������
�����ָ�루���ã�ָ�����new����������������ʱ��delete pb(�����ָ��)��
����������������ʱ�򣬱��뷢����̬�󶨣�����ᵼ������������������޷�����
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
	// ����������
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
	// ��Base�� : û�к��ʵ�Ĭ�Ϲ��캯������
	Derive(int data)
		:Base(data)                           // ma(data)  ��====   ����������ʼ��      
		,mb(data)
		,ptr(new int(data))
	{
		std::cout << "Derive()" << std::endl;
	}

	// �������������ʱvirtual�麯������ô����������������Զ���Ϊ�麯����������
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
	//Base* pb =&d;           // ��ջ�ϵ��ڴ�
	//pb->show();
	/* 
	Base()
	Derive()
	call Base::show()
	~Derive()
	~Base()
	*/


	Base* pb = new Derive(10);   //�ڶ���new�����Ķ���
	pb->show();         
	delete pb;
	/*  ������������Ϊ��ͨ����ʱ
	Base()
	Derive()
	call Base::show()
	~Base()                 // ���������������û�е��õ�����������������       ===��  ����������ѻ����������������Ϊ����������
	*/

	/*
	û�е��������������������ԭ��
	pb  --> Base����   Base::~Base() ==�� ��ͨ��Ա����  ===�� ���������������ã����Ǿ�̬��

	pb  --> Base���� Base:: virtual ~Base() ==�� �麯��  ===��  ���������������ã����Ƕ�̬����
	pb  --�� Derive   Derive vftable   &Derive::~Derive

	              
	Base()
	Derive()
	call Base::show()
	~Derive()
	~Base()
	*/

	return 0;
}
#endif

//======================================================= 4.��̬�󶨺Ͷ�̬�� ================================================ ���ǳ���Ҫ���ص㡢���ģ���������
/*
�麯������̬�󶨺Ͷ�̬��

���ǣ������������ķ���������ֵ���������������б���ͬ�����һ���ķ������麯����
��ô������ķ������Զ�������麯��������֮���Ϊ���ǹ�ϵ��


һ����������麯�������������ʲôӰ�죿
�ܽ�һ��
һ�������涨�����麯������ô����׶Σ�����������������Ͳ���һ��Ψһ��vftable(�麯����)��
�麯��������Ҫ�洢�����ݾ���RTTI��run time type infomation��ָ����麯����ַ������������ʱ��ÿһ���麯��������ص��ڴ��.rodata����

�ܽ����
һ�������涨�����麯������ô����˶���Ķ���������ʱ���ڴ��еĿ�ʼ���֣���洢һ��vfptr�麯��ָ�룬ָ����Ӧ���͵��麯����vftable��
һ�����Ͷ���Ե�n���������ǵ�vfptr�麯��ָ��ָ��Ķ���ͬһ���麯����

�ܽ�����
һ����������麯���ĸ�������Ӱ�������ڴ��С��vfptr��,Ӱ������麯����Ĵ�С��������������

*/

#if 0
class Base
{
public:
	Base(int data = 10) :ma(data) {};
	// �麯��
	virtual void show() { std::cout << "Base::show()" << std::endl; }
	// �麯��
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
	�ܽ��ģ�
	����������еķ������ͻ���̳�����ĳ������������ֵ���������������б���ͬ��
	���һ���ķ�����virtual�麯������ô�����������������Զ�������麯���������������Ƕ���ʱ��ûд��virtual��
	��д  ��====��  ����              {���ǣ��麯�������麯����ַ�ĸ���}

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
	p->show()   pb��Base���� ==�� Base::show����ͨ�������ͽ��о�̬��

	p->show()   pb��Base���� ==�� Base::show���麯�����ͽ��ж�̬����
	*/
	p->show();    // Base::show()    //��̬������ʱ�ڣ��İ󶨣������ĵ��ã�  ===>            00007FF73FB02657  call        Base::show (07FF73FB013E8h) 

	/*
	Base::show(int)  ��һ���麯������ʱ�͵ö�̬���� 

	*/
	p->show(10);  // Base::show(int)                                                         00007FF73FB02665  call        Base::show (07FF73FB010DCh)

/*  32λϵͳ
	p->show();    // Base::show()    //��̬������ʱ�ڣ��İ󶨣������ĵ��ã�  ===>            00007FF73FB02657  call        Base::show (07FF73FB013E8h)
	009D28FF  mov         eax,dword ptr [p]
	009D2902  mov         edx,dword ptr [eax]
	009D2904  mov         esi,esp
	009D2906  mov         ecx,dword ptr [p]
	009D2909  mov         eax,dword ptr [edx+4]
	009D290C  call        eax    ���麯���ĵ�ַ�� ��̬������ʱ�ڣ��󶨣������ĵ��ã�                      
	//���ô洢�� eax �Ĵ����еĺ�����ַ���õ�ַ�Ǵ� edx + 4 �м��صġ���������������еĳ���ģʽ�����ж�����麯����vtable���ĵ�һ����Ŀ��ָ���麯�����ָ��
	009D290E  cmp         esi,esp
	009D2910  call        __RTC_CheckEsp (09D12C1h)
		p->show(10);  // Base::show(int)                                                         00007FF73FB02665  call        Base::show (07FF73FB010DCh)
	009D2915  mov         esi,esp
	009D2917  push        0Ah
	009D2919  mov         eax,dword ptr [p]
	009D291C  mov         edx,dword ptr [eax]
	009D291E  mov         ecx,dword ptr [p]
	009D2921  mov         eax,dword ptr [edx]
	009D2923  call        eax     //���ô洢�� eax �Ĵ����еĺ�����ַ���õ�ַ�Ǵ� edx + 4 �м��صġ���������������еĳ���ģʽ�����ж�����麯����vtable���ĵ�һ����Ŀ��ָ���麯�����ָ��
	009D2925  cmp         esi,esp
	009D2927  call        __RTC_CheckEsp (09D12C1h)
*/

	std::cout << sizeof(Base) << std::endl;   //4
	std::cout << sizeof(Derive) << std::endl;   //8


	std::cout << typeid(p).name() << std::endl;  // class Base * __ptr64
	/*
	pb�����ͣ�Base  -�� ��û���麯��
	���Baseû���麯����*pbʶ��þ��Ǳ���ʱ�ڵ�����  *pb <==> Base����
	���Base���麯���� *pbʶ��þ�������ʱ�ڵ����� RTTI����  
	*/
	std::cout << typeid(*p).name() << std::endl;   // class Base

	/*  // Base��show����δ��virtual�ؼ���       Base������show����������ͨ����
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

	/*  X86��ϵ32λϵͳ             ��Base������show���������virtual����
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

//======================================================= 3.���ء����ǡ�����  ================================================
/*
���ء����ǡ�����
1.���ع�ϵ
һ�麯��Ҫ���أ����봦��ͬһ���������У����Һ���������ͬ�������б�ͬ

2.���أ�����������أ���ϵ
�ڼ̳нṹ���У��������ͬ����Ա���ѻ����ͬ����Ա��������Ա�����ͳ�Ա�����������ص���


==============================================================================================================================
1.�Ѽ̳л�����Ҳ˵�ɴ��ϣ����ࣩ���£������ࣩ�Ľṹ
2.
������� -> ���������      N
������  -> �������      Y

����ָ�루���ã� ->  ���������        N
������ָ�루���ã� -> �������       Y

�ܽ᣺�ڼ̳нṹ�н������µ�����ת����Ĭ��ֻ֧�ִ��µ������͵�ת�� �����ǿ�������ǿת������Σ�գ�������ڴ�Ƿ����ʣ���������  OK

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

	// �������b <- ���������d      ���ʹ��µ��ϵ�ת��   Y
	b = d;

	// ���������d <- �������b      ���ʹ��ϵ��µ�ת��   N
	//d = b;                                                     // C2679	��Ԫ�� = ��: û���ҵ����ܡ�Base�����͵��Ҳ������������(��û�пɽ��ܵ�ת��)

	// ����ָ�루���ã� <- ���������    ���ʹ��µ��ϵ�ת��   Y
	Base* pb = &d;
	//pb->show();
	//pb->show(10);
	/*              pbĬ��ֻ�ܵ��ôӻ���ļ̳й����ķ�����
	Base::show()
	Base::show(int)
	*/

	((Derive*)pb)->show();     // ����ǿת
	pb->show(10);
	/*
	Derive::show()
	Base::show(int)
	*/

	// ������ָ�루���ã� <-  ����ָ��        ���ʹ��ϵ��µ�ת��   N
	// Derive* pd = &b;                                         // "Base *" ���͵�ֵ�������ڳ�ʼ�� "Derive *" ���͵�ʵ��
	Derive* pd = (Derive*) & b;    // ����ȫ��������ڴ�ķǷ����ʣ����� 
	pd->show();  // Derive::show()    ============�� ���show����ʹ�õ�������������ݳ�Ա����ᷢ���ڴ�ķǷ����ʣ�����          ��Ϊ�ڴ��ϸ���û����������󣡣�����


#if 0
	Derive d;
	d.show();

	//��Derive::show��: ���������� 1 ������	05_�̳����̬
	// d.show(10);      //�����ҵ����������Լ��������show���ֳ�Ա��û�еĻ�����ȥ����������

	d.Base::show();
	d.Base::show(10);
#endif


	return 0;
}

#endif


//======================================================= 2.������Ĺ������  ================================================
/*
1.������Ӽ̳п��Լ̳������еĳ�Ա�������ͷ��������������캯������������

��������ô��ʼ���ӻ���̳й����ĳ�Ա������
���ͨ�����û�����Ӧ�Ĺ��캯������ʼ��

������Ĺ��캯�������������������ʼ�������������ಿ��
������ӻ���̳����ĳ�Ա�ĳ�ʼ����������˭�����أ�    ==========�� ���ɻ���Ĺ��캯�����������������𣡣�


>>>>>>>>>>>>>>>>>>>�����������������Ĺ����ǣ�
1.��������û���Ĺ��캯������ʼ���ӻ���̳����ĳ�Ա
2.�����������Լ��Ĺ��캯������ʼ���������Լ����еĳ�Ա
...........
...........���������������������ˣ�
3.����������������������ͷ��������Ա����ռ�õ��ⲿ��Դ�����ڴ棬�ļ�...��
4.���û���������������ͷ��������ڴ��У��ӻ���̳й����ĳ�Ա����ռ�õ��ⲿ��Դ�����ڴ棬�ļ�...��
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
	// ��Base�� : û�к��ʵ�Ĭ�Ϲ��캯������
	Derive(int data)
		:Base(data)                           // ma(data)  ��====   ����������ʼ��      
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


//======================================================= 1.�̳еı��ʺ�ԭ��  ================================================
#if 0
/*
1.�̳еı��ʺ�ԭ��
�̳еı��ʣ�a.���븴��  b.

�����֮���ϵ
��ϣ�a part of...   .... һ���ֵĹ�ϵ
�̳У�a kind of...   .... һ�ֵĹ�ϵ


�̳з�ʽ            ����ķ����޶�                  ������ķ����޶�                 ��main���ⲿ�ķ���
public
					  public                           public                               Y
					  protected                        protected                            N
					  private                          ���ɼ���                             N

protected ������ĳ�Ա�ķ����޶����������������ǲ����ܳ����̳з�ʽ�ģ�������            
					  public                           protected                            N
					  protected                        protected                            N
					  private                          ���ɼ���                             N
private
					  public                           private                              N
					  protected                        private                              N
					  private                          ���ɼ���                             N



�ܽ᣺
1���ⲿֻ�ܷ��ʶ���public�ĳ�Ա��protected��private�ĳ�Ա�޷�ֱ�ӷ���
2.�ڼ̳нṹ�У�������ӻ�����Լ̳й���private�ĳ�Ա������������ȴ�޷�ֱ�ӷ���
3.protected��private�������ڻ����ж���ĳ�Ա���뱻��������ʣ����ǲ��뱻�ⲿ���ʣ�
��ô�ڻ����У�����س�Ա�����protected�����ģ������������ⲿ����������ʣ�
��ô�ڻ����У��Ͱ���س�Ա�����private˽�е�

Ĭ�ϵļ̳з�ʽ��ʲô��
Ҫ��������ʱ��class����Ļ���struct����ģ���
class���������࣬Ĭ�ϼ̳з�ʽ����private˽�е�
struct���������࣬Ĭ�ϼ̳з�ʽ����public���е�

*/



class A
{
public:
	int ma;
protected:
	int mb;
private:
	int mc;      // ֻ���Լ�������Ԫ�ܷ���˽�еĳ�Ա

};

// �̳�     A:����/����    B ������/����
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
	// ��C���棬����ma�ķ����޶���ʲô�� ���ɼ��ģ������ܼ̳���(��ma��C����ռ�ڴ��)
};

int main()
{
	B b;
	
	std::cout << "ma:" << b.ma << std::endl;
	return 0;

}

#endif






