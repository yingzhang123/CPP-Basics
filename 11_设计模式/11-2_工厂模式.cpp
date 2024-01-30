#include<iostream>
#include<string>
#include<memory>

using namespace std;

/*
工厂模式是一种创建型设计模式，其主要目的是将对象的创建和使用分离，通过一个接口来创建对象，而不是直接使用 new 关键字来实例化对象。
工厂模式提供了一种创建对象的统一接口，使得客户端在不必知道具体实现类的情况下就能够创建相应的对象。

在工厂模式中，通常有三种主要的角色：

产品（Product）： 表示被创建的对象，工厂模式要创建的对象都属于某个产品。

工厂（Factory）： 是一个接口，用于创建产品的方法，具体的工厂实现类负责具体产品的实例化。

具体产品（Concrete Product）： 实现了产品接口的具体类，是工厂模式所创建的对象。

*/

/*
①简单工厂
把对象的创建封装在一个接口函数里面，通过传入不同的标识，返回创建的对象
客户不用自己负责new对象，不用了解对象创建的详细过程

提供创建对象实例的接口函数不闭合，不能对修改封闭

②工厂方法
Factory基类，提供了一个纯虚函数（创建产品），定义派生类（具体产品的工厂）负责创建对应的产品
可以做到不同的产品，在不同的工厂里面创建，能够对现有工厂，以及产品的修改封闭

实际上，很多产品是由关联关系的，属于一个产品簇，不应该放在不同的工厂里面去创建，
这样一是不符合实际的产品对象船舰逻辑，二是工厂类太多了，不好维护

③抽象工厂
把有关联关系的属于一个产品簇的所有产品创建的接口函数，放在一个抽象工厂里面AbstractFactory,
派生类（具体产品的工厂）应该负责创建该产品簇里面的所有产品


难以扩展新种类： 当需要添加新的产品种类时，不仅需要添加新的具体产品类，还需要修改抽象工厂及其所有具体工厂的接口。这种修改可能会导致对整个系统的修改，影响到系统的稳定性。
耦合性增加： 抽象工厂模式会增加产品之间的耦合性。由于抽象工厂的接口需要声明一整套产品，如果其中一个产品需要变更，可能会影响到整个系统的其他部分
*/

//=================================================== 抽象工厂 =============================================
/*
抽象工厂：提供一个创建一系列相关或相互依赖对象的接口，而无需指定它们具体的类

抽象工厂模式是一种创建型设计模式，它提供了一种创建一系列相关或相互依赖对象的接口，而无需指定它们具体的类。
抽象工厂模式将一组相关的产品组合成一个工厂，客户端通过使用这个工厂来创建产品，而不需要关心具体的产品是如何创建以及如何组合的。

*/

#if 0
// 汽车产品
class Car
{
public:
	Car(std::string name) : _name(name) {}
	virtual void show() = 0;
protected:
	std::string _name;
};

class BMW : public Car
{
public:
	BMW(std::string name) : Car(name) {}
	void show()
	{
		std::cout << "获取了一辆宝马汽车" << _name << std::endl;
	}
};

class Audi : public Car
{
public:
	Audi(std::string name) : Car(name) {}
	void show()
	{
		std::cout << "获取了一辆奥迪汽车" << _name << std::endl;
	}
};

// 产品二
class Light
{
public:
	virtual void show() = 0;
};

class BmwLight : public Light
{
public:
	void show() { std::cout << "BMW light!" << std::endl; }
};

class AudiLight : public Light
{
public:
	void show() { std::cout << "Audi light!" << std::endl; }
};

// 工厂方法 =======》 抽象工厂       对有一组关联关系的产品簇提供产品对象的统一创建 （工厂类的数量可以少很多）
class AbstractFactory
{
public:
	virtual Car* createCar(std::string name) = 0;     // 工厂方法 创建汽车
	virtual Light* createCarLight() = 0;              // 工厂方法 创建汽车相关联的产品，车灯
};

class BMWFactory : public AbstractFactory
{
public:
	Light* createCarLight()
	{
		return new BmwLight();
	}
	Car* createCar(std::string name)
	{
		return new BMW(name);
	}
};

class AudiFactory : public AbstractFactory
{
public:
	Light* createCarLight()
	{
		return new AudiLight();
	}
	Car* createCar(std::string name)
	{
		return new Audi(name);
	}
};


int main()
{
	std::unique_ptr<AbstractFactory> bmwfty(new BMWFactory());
	std::unique_ptr<AbstractFactory> audifty(new AudiFactory());
	std::unique_ptr<Car> p1(bmwfty->createCar("X6"));
	std::unique_ptr<Car> p2(audifty->createCar("A6"));
	std::unique_ptr<Light> l1(bmwfty->createCarLight());
	std::unique_ptr<Light> l2(audifty->createCarLight());
	p1->show(); 
	p2->show();
	l1->show();
	l2->show();

	return 0;
}
#endif


/* Factory Method
工厂方法: 定义一个创建产品的接口， 由具体的工厂实现类负责实例化具体的产品对象
*/
//=================================================== 工厂方法 =============================================
#if 0
// 汽车产品
class Car
{
public:
	Car(std::string name) : _name(name) {}
	virtual void show() = 0;
protected:
	std::string _name;
};

class BMW : public Car
{
public:
	BMW(std::string name) : Car(name) {}
	void show()
	{
		std::cout << "获取了一辆宝马汽车" << _name << std::endl;
	}
};

class Audi : public Car
{
public:
	Audi(std::string name) : Car(name) {}
	void show()
	{
		std::cout << "获取了一辆奥迪汽车" << _name << std::endl;
	}
};
// 工厂接口
class Factory
{
public:
	virtual Car* createCar(std::string name) = 0;
};
// 具体工厂 BMWFactory
class BMWFactory : public Factory
{
public:
	Car* createCar(std::string name)
	{
		return new BMW(name);
	}
};
// 具体工厂 AudiFactory
class AudiFactory : public Factory
{
public:
	Car* createCar(std::string name)
	{
		return new Audi(name);
	}
};

int main()
{
	std::unique_ptr<Factory> bmwfty(new BMWFactory());
	std::unique_ptr<Factory> audifty(new AudiFactory());
	std::unique_ptr<Car> p1(bmwfty->createCar("X6"));
	std::unique_ptr<Car> p2(audifty->createCar("A6"));
	p1->show();
	p2->show();
}
#endif


/* Simple Factory
简单工厂: (不可能用一个工厂把所有的对象创建==》工厂不可能创建手机，汽车,电脑，飞机)    正常逻辑==》一个工厂负责一类产品的创建

简单工厂:使用一个专门的工厂类负责创建所有的产品，客户端只需要知道产品的类型即可
*/
//=================================================== 简单工厂 =============================================
#if 0
class Car
{
public:
	Car(std::string name) : _name(name) {}
	virtual void show() = 0;
protected:
	std::string _name;
};

class BMW : public Car
{
public:
	BMW(std::string name) : Car(name) {}
	void show()
	{
		std::cout << "获取了一辆宝马汽车" << _name << std::endl;
	}
};

class Audi : public Car
{
public:
	Audi(std::string name) : Car(name) {}
	void show()
	{
		std::cout << "获取了一辆奥迪汽车" << _name << std::endl;
	}
};


enum CarType
{
	BMw, AUDI
};

class SimpleFactory
{
public:
	Car* createCar(CarType ct, std::string name)      // 软件设计  "开闭原则" 不满足       接口不封闭
	{
		switch (ct)
		{
		case BMw:
			return new BMW(name);
		case AUDI:
			return new Audi(name);
		default:
			std::cerr << "传入工厂的参数不正确：" << ct << std::endl;
			break;
		}
		return nullptr;
	}
};

int main()
{
	//Car* p1 = new BMW("X1");
	//Car* p2 = new Audi("A6");

	std::unique_ptr<SimpleFactory> factory(new SimpleFactory());
	std::unique_ptr<Car> p1(factory->createCar(BMw, "X6"));
	std::unique_ptr<Car> p2(factory->createCar(AUDI, "A6"));
	p1->show();
	p2->show();

	return 0;
}
#endif