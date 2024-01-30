#include <iostream>
#include <unordered_map>
#include <list>


/*
行为型模式：主要关注的是是对象之间的通信

观察者模式（Observer Pattern）（监听者模式）/（发布-订阅模式）：主要关注的是对象的一对多的关系，也就是多个对象都依赖一个对象，当该对象的状态发生改变时，其他对象都能接收到相应的通知！！！！

一组数据（数据对象）  ===》 通过这一组数据==》 曲线图（对象1）/柱状图（对象2）/饼状图（对象3）
当数据对象改变时，对象1、对象2、对象3应该及时的收到相应的通知！

Observer1       Observer2         Observer13
			    
				Subject（主题）主题有更改，应该及时通知相应的观察者，去处理相应的事件
*/

/*
观察者模式（Observer Pattern）是一种行为型设计模式，
它定义了一种一对多的依赖关系，让多个观察者对象同时监听某一个主题对象。
当主题对象状态发生变化时，所有依赖于它的观察者都会得到通知并更新。
*/


// 观察者抽象类
class Observer
{
public:
	// 处理消息的接口
	virtual void handle(int msgid) = 0;
};

// 第一个观察者实例
class Observer1 : public Observer
{
public:
	void handle(int msgid)
	{
		switch (msgid)
		{
		case 1:
			std::cout << "Observer1 recv 1 msg!" << std::endl;
			break;
		case 2:
			std::cout << "Observer1 recv 2 msg!" << std::endl;
			break;
		default:
			std::cout << "Observer1 recv unknown msg!" << std::endl;
			break;
		}
	}
};

class Observer2 : public Observer
{
public:
	void handle(int msgid)
	{
		switch (msgid)
		{
		case 2:
			std::cout << "Observer2 recv 2 msg!" << std::endl;
			break;
		default:
			std::cout << "Observer2 recv unknown msg!" << std::endl;
			break;
		}
	}
};

class Observer3 : public Observer
{
public:
	void handle(int msgid)
	{
		switch (msgid)
		{
		case 1:
			std::cout << "Observer3 recv 1 msg!" << std::endl;
			break;
		case 3:
			std::cout << "Observer3 recv 3 msg!" << std::endl;
			break;
		default:
			std::cout << "Observer3 recv unknown msg!" << std::endl;
			break;
		}
	}
};

class Subject
{
public:
	// 给主题增加观察者对象
	void addObserver(Observer* obser, int msgid)
	{
		_subMap[msgid].push_back(obser);
		/*auto it = _subMap.find(msgid);
		if (it != _subMap.end())
		{
			it->second.push_back(obser);
		}
		else
		{
			std::list<Observer*> lis;
			lis.push_back(obser);
			_subMap.insert({ msgid, lis });
		}*/
	}

	// 主题检测发生改变，通知相应的观察者对象处理事件
	void dispatch(int msgid)
	{
		auto it = _subMap.find(msgid);
		if (it != _subMap.end())        // 找到了
		{
			for (Observer* p : it->second)          
			{
				p->handle(msgid);
			}
		}
		else
		{
			std::cout << "no observer" << std::endl;
		}
	}
private:
	std::unordered_map<int, std::list<Observer*>> _subMap;
};

int main()
{
	Subject subject;
	Observer* p1 = new Observer1();
	Observer* p2 = new Observer2();
	Observer* p3 = new Observer3();
	subject.addObserver(p1, 1);
	subject.addObserver(p1, 2);
	subject.addObserver(p2, 2);
	subject.addObserver(p3, 1);
	subject.addObserver(p3, 3);
	subject.dispatch(1);
	subject.dispatch(5);


	return 0;
}