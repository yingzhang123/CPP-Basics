#include<iostream>
#include<string>
#include<memory>

using namespace std;

/*
����ģʽ��һ�ִ��������ģʽ������ҪĿ���ǽ�����Ĵ�����ʹ�÷��룬ͨ��һ���ӿ����������󣬶�����ֱ��ʹ�� new �ؼ�����ʵ��������
����ģʽ�ṩ��һ�ִ��������ͳһ�ӿڣ�ʹ�ÿͻ����ڲ���֪������ʵ���������¾��ܹ�������Ӧ�Ķ���

�ڹ���ģʽ�У�ͨ����������Ҫ�Ľ�ɫ��

��Ʒ��Product���� ��ʾ�������Ķ��󣬹���ģʽҪ�����Ķ�������ĳ����Ʒ��

������Factory���� ��һ���ӿڣ����ڴ�����Ʒ�ķ���������Ĺ���ʵ���ฺ������Ʒ��ʵ������

�����Ʒ��Concrete Product���� ʵ���˲�Ʒ�ӿڵľ����࣬�ǹ���ģʽ�������Ķ���

*/

/*
�ټ򵥹���
�Ѷ���Ĵ�����װ��һ���ӿں������棬ͨ�����벻ͬ�ı�ʶ�����ش����Ķ���
�ͻ������Լ�����new���󣬲����˽���󴴽�����ϸ����

�ṩ��������ʵ���Ľӿں������պϣ����ܶ��޸ķ��

�ڹ�������
Factory���࣬�ṩ��һ�����麯����������Ʒ�������������ࣨ�����Ʒ�Ĺ��������𴴽���Ӧ�Ĳ�Ʒ
����������ͬ�Ĳ�Ʒ���ڲ�ͬ�Ĺ������洴�����ܹ������й������Լ���Ʒ���޸ķ��

ʵ���ϣ��ܶ��Ʒ���ɹ�����ϵ�ģ�����һ����Ʒ�أ���Ӧ�÷��ڲ�ͬ�Ĺ�������ȥ������
����һ�ǲ�����ʵ�ʵĲ�Ʒ���󴬽��߼������ǹ�����̫���ˣ�����ά��

�۳��󹤳�
���й�����ϵ������һ����Ʒ�ص����в�Ʒ�����Ľӿں���������һ�����󹤳�����AbstractFactory,
�����ࣨ�����Ʒ�Ĺ�����Ӧ�ø��𴴽��ò�Ʒ����������в�Ʒ


������չ�����ࣺ ����Ҫ����µĲ�Ʒ����ʱ��������Ҫ����µľ����Ʒ�࣬����Ҫ�޸ĳ��󹤳��������о��幤���Ľӿڡ������޸Ŀ��ܻᵼ�¶�����ϵͳ���޸ģ�Ӱ�쵽ϵͳ���ȶ��ԡ�
��������ӣ� ���󹤳�ģʽ�����Ӳ�Ʒ֮�������ԡ����ڳ��󹤳��Ľӿ���Ҫ����һ���ײ�Ʒ���������һ����Ʒ��Ҫ��������ܻ�Ӱ�쵽����ϵͳ����������
*/

//=================================================== ���󹤳� =============================================
/*
���󹤳����ṩһ������һϵ����ػ��໥��������Ľӿڣ�������ָ�����Ǿ������

���󹤳�ģʽ��һ�ִ��������ģʽ�����ṩ��һ�ִ���һϵ����ػ��໥��������Ľӿڣ�������ָ�����Ǿ�����ࡣ
���󹤳�ģʽ��һ����صĲ�Ʒ��ϳ�һ���������ͻ���ͨ��ʹ�����������������Ʒ��������Ҫ���ľ���Ĳ�Ʒ����δ����Լ������ϵġ�

*/

#if 0
// ������Ʒ
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
		std::cout << "��ȡ��һ����������" << _name << std::endl;
	}
};

class Audi : public Car
{
public:
	Audi(std::string name) : Car(name) {}
	void show()
	{
		std::cout << "��ȡ��һ���µ�����" << _name << std::endl;
	}
};

// ��Ʒ��
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

// �������� =======�� ���󹤳�       ����һ�������ϵ�Ĳ�Ʒ���ṩ��Ʒ�����ͳһ���� ������������������ٺࣩܶ
class AbstractFactory
{
public:
	virtual Car* createCar(std::string name) = 0;     // �������� ��������
	virtual Light* createCarLight() = 0;              // �������� ��������������Ĳ�Ʒ������
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
��������: ����һ��������Ʒ�Ľӿڣ� �ɾ���Ĺ���ʵ���ฺ��ʵ��������Ĳ�Ʒ����
*/
//=================================================== �������� =============================================
#if 0
// ������Ʒ
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
		std::cout << "��ȡ��һ����������" << _name << std::endl;
	}
};

class Audi : public Car
{
public:
	Audi(std::string name) : Car(name) {}
	void show()
	{
		std::cout << "��ȡ��һ���µ�����" << _name << std::endl;
	}
};
// �����ӿ�
class Factory
{
public:
	virtual Car* createCar(std::string name) = 0;
};
// ���幤�� BMWFactory
class BMWFactory : public Factory
{
public:
	Car* createCar(std::string name)
	{
		return new BMW(name);
	}
};
// ���幤�� AudiFactory
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
�򵥹���: (��������һ�����������еĶ��󴴽�==�����������ܴ����ֻ�������,���ԣ��ɻ�)    �����߼�==��һ����������һ���Ʒ�Ĵ���

�򵥹���:ʹ��һ��ר�ŵĹ����ฺ�𴴽����еĲ�Ʒ���ͻ���ֻ��Ҫ֪����Ʒ�����ͼ���
*/
//=================================================== �򵥹��� =============================================
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
		std::cout << "��ȡ��һ����������" << _name << std::endl;
	}
};

class Audi : public Car
{
public:
	Audi(std::string name) : Car(name) {}
	void show()
	{
		std::cout << "��ȡ��һ���µ�����" << _name << std::endl;
	}
};


enum CarType
{
	BMw, AUDI
};

class SimpleFactory
{
public:
	Car* createCar(CarType ct, std::string name)      // ������  "����ԭ��" ������       �ӿڲ����
	{
		switch (ct)
		{
		case BMw:
			return new BMW(name);
		case AUDI:
			return new Audi(name);
		default:
			std::cerr << "���빤���Ĳ�������ȷ��" << ct << std::endl;
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