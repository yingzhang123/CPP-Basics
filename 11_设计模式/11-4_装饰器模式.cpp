#include <iostream>
#include<memory>

/*
装饰器模式：主要是增加现有类的功能   （以较少的代码增加现有类的是功能，而且还可以对功能任意的组装）         

但是：增加现有类的功能，还有一个方法，就是增加一个子类

通过子类实现增强的问题：为了增强现有类的功能，通过实现子类的方式，重写接口，是可以完功能扩展的，但是代码中有太多的子类添加进来了

*/

#if 0
class Car   // 抽象基类
{
public:
	virtual void show() = 0;
};

class Bmw : public Car
{
public:
	void show() { std::cout << "this is a bmw car，配置有：基类配置"; }
};

class Audi : public Car
{
public:
	void show() { std::cout << "this is a audi car，配置有：基类配置"; }
};

class Benz : public Car
{
public:
	void show() { std::cout << "this is a benz car，配置有：基类配置"; }
};

//// 装饰器基类     可以把装饰器公共添加的功能抽象出来放在CarDecorator中
//class CarDecorator :public Car       
//{
//public:
//	CarDecorator(Car *p):pCar(p){}
//		virtual void show() = 0;
//private:
//	Car* pCar;
//};

// 具体装饰器         新增几个功能就添加几个类就行
class ConcreateDecrator01 : public Car
{
public:
	ConcreateDecrator01(Car* p) : pCar(p) {}
	void show()
	{
		pCar->show();
		std::cout << "，定速巡航" ;
	}
private:
	Car* pCar;
};

class ConcreateDecrator02 : public Car
{
public:
	ConcreateDecrator02(Car* p) : pCar(p) {}
	void show()
	{
		pCar->show();							// 先访问基类的方法，
		std::cout << "，自动刹车";				// 再添加新的功能
	}
private:
	Car* pCar;
};

class ConcreateDecrator03 : public Car
{
public:
	ConcreateDecrator03(Car* p) : pCar(p) {}
	void show()
	{
		pCar->show();
		std::cout << "，车道偏离";
	}
private:
	Car* pCar;
};

int main()
{
	/*std::unique_ptr<Car> p1( new ConcreateDecrator01(new Bmw()));*/
	Car* p1 = new ConcreateDecrator01(new Bmw());
	p1 = new ConcreateDecrator02(p1);            // 添加新功能
	p1 = new ConcreateDecrator03(p1);

	Car* p2 = new ConcreateDecrator02(new Audi());
	Car* p3 = new ConcreateDecrator03(new Benz());

	p1->show();
	std::cout << std::endl;
	p2->show();
	std::cout << std::endl;
	p3->show();

	return 0;

	/*   
	this is a bmw car，配置有：基类配置，定速巡航，自动刹车，车道偏离
	this is a audi car，配置有：基类配置，自动刹车
	this is a benz car，配置有：基类配置，车道偏离
	*/
}

#endif