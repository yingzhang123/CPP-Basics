#include <iostream>
#include<memory>

/*
װ����ģʽ����Ҫ������������Ĺ���   ���Խ��ٵĴ���������������ǹ��ܣ����һ����ԶԹ����������װ��         

���ǣ�����������Ĺ��ܣ�����һ����������������һ������

ͨ������ʵ����ǿ�����⣺Ϊ����ǿ������Ĺ��ܣ�ͨ��ʵ������ķ�ʽ����д�ӿڣ��ǿ����깦����չ�ģ����Ǵ�������̫���������ӽ�����

*/

#if 0
class Car   // �������
{
public:
	virtual void show() = 0;
};

class Bmw : public Car
{
public:
	void show() { std::cout << "this is a bmw car�������У���������"; }
};

class Audi : public Car
{
public:
	void show() { std::cout << "this is a audi car�������У���������"; }
};

class Benz : public Car
{
public:
	void show() { std::cout << "this is a benz car�������У���������"; }
};

//// װ��������     ���԰�װ����������ӵĹ��ܳ����������CarDecorator��
//class CarDecorator :public Car       
//{
//public:
//	CarDecorator(Car *p):pCar(p){}
//		virtual void show() = 0;
//private:
//	Car* pCar;
//};

// ����װ����         �����������ܾ���Ӽ��������
class ConcreateDecrator01 : public Car
{
public:
	ConcreateDecrator01(Car* p) : pCar(p) {}
	void show()
	{
		pCar->show();
		std::cout << "������Ѳ��" ;
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
		pCar->show();							// �ȷ��ʻ���ķ�����
		std::cout << "���Զ�ɲ��";				// ������µĹ���
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
		std::cout << "������ƫ��";
	}
private:
	Car* pCar;
};

int main()
{
	/*std::unique_ptr<Car> p1( new ConcreateDecrator01(new Bmw()));*/
	Car* p1 = new ConcreateDecrator01(new Bmw());
	p1 = new ConcreateDecrator02(p1);            // ����¹���
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
	this is a bmw car�������У��������ã�����Ѳ�����Զ�ɲ��������ƫ��
	this is a audi car�������У��������ã��Զ�ɲ��
	this is a benz car�������У��������ã�����ƫ��
	*/
}

#endif