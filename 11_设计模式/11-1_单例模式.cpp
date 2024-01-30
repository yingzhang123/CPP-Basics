#include<iostream>
#include<mutex>
using namespace std;

/*
单例模式：一个类不管创建多少次对象，永远只能得到该类型一个对象示例

常用到的：比如日志模块，内存池模块，数据库模块

单例模式：
饿汉式单例模式：还没获取实例对象，实例对象就已经产生了             （如果饿汉式单例过多，程序运行一开始会很慢）
懒汉式单例模式：唯一的实例对象，直到第一次获取它的时候才产生       （更受欢迎）
*/


//=================================================== (线程安全的)懒汉单例模式  （简介版）==========================================================
#if 0
/*
线程安全的懒汉单例模式

你的代码使用了C++11引入的局部静态变量，这是一种更加简洁和线程安全的单例模式实现方式。
在这种方式中，instance 是在第一次调用 getInstance 时被初始化，
而且由于局部静态变量的初始化在C++11标准中是线程安全的，因此无需额外的锁。
*/
class Singleton
{
public:
    static Singleton* getInstance()    // #3 获取类的唯一实例对象的接口方法
    {
        // // 函数静态局部变量的初始化，在汇编指令上已经自动添加线程互斥指令了      不用担心有线程安全的问题
        static Singleton instance;       // #2 定义一个唯一的类的实例对象           // // 局部静态变量，会在第一次调用（运行到这里）时初始化，且是线程安全的
        return &instance;
    }
private:
  
    Singleton()                       // #1 构造函数私有化 （不让用户在外部（new,栈，全局）定义对象了）
    {
        std::cout << "Singleton()" << std::endl;
    }
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    // 删除拷贝构造函数和赋值操作符： 通过将拷贝构造函数和赋值操作符声明为删除，确保了单例对象不会被复制。
};



int main()
{
    Singleton* p1 = Singleton::getInstance();
    Singleton* p2 = Singleton::getInstance();
    Singleton* p3 = Singleton::getInstance();
    std::cout << p1 << std::endl;
    std::cout << p2 << std::endl;
    std::cout << p3 << std::endl;

    return 0;
}
#endif

//=================================================== (线程安全的)懒汉单例模式 ==========================================================
#if 0
/*
使用的是类级别的锁（std::mutex），这会导致在调用 getInstance 时整个函数被锁住，从而降低了并发性能。
如果在高并发环境下，频繁调用 getInstance，这样的实现可能会成为性能瓶颈。
为了提高粒度，你可以使用双检锁（Double-Checked Locking）机制，它在需要时才加锁，可以减小锁的粒度，提高并发性能。
*/
class Singleton
{
public:
    static Singleton* getInstance()    // #3 获取类的唯一实例对象的接口方法
    {
       // std::lock_guard<std::mutex> lock(mutex_);    // 锁的粒度太大了
        if (instance == nullptr)
        {
            std::lock_guard<std::mutex> lock(mutex_);       // 锁 + 双重判断！！！
            if (instance == nullptr)
            {
                /*
                开辟内存
                构造对象
                给instance赋值
                */
                instance = new Singleton();
            }
        }
        return instance;
    }
private:
    static Singleton* volatile instance;       // #2 定义一个唯一的类的实例对象
    static std::mutex mutex_; // 用于保证线程安全
    Singleton()                       // #1 构造函数私有化 （不让用户在外部（new,栈，全局）定义对象了）
    {
        std::cout << "Singleton()" << std::endl;
    }
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    // 删除拷贝构造函数和赋值操作符： 通过将拷贝构造函数和赋值操作符声明为删除，确保了单例对象不会被复制。
};

// static成员变量一定要在类外进行定义并且初始化
Singleton* volatile Singleton::instance = nullptr;
std::mutex Singleton::mutex_;

int main()
{
    Singleton* p1 = Singleton::getInstance();
    Singleton* p2 = Singleton::getInstance();
    Singleton* p3 = Singleton::getInstance();
    std::cout << p1 << std::endl;
    std::cout << p2 << std::endl;
    std::cout << p3 << std::endl;
    /*
    Singleton()
    0064FC30
    0064FC30
    0064FC30
    */
    return 0;
}
#endif

//=================================================== 懒汉单例模式 ==========================================================
// 懒汉单例    线程不安全 
#if 0
class Singleton
{
public:
    static Singleton* getInstance()    // #3 获取类的唯一实例对象的接口方法
    {
        //在多线程环境下存在线程安全性问题。如果多个线程同时进入 getInstance 函数，并且 instance 尚未被创建，就有可能导致多个实例被创建，违反了单例模式的设计原则。
        if (instance == nullptr)
        {
            /*
            开辟内存
            构造对象
            给instance赋值
            */
            instance = new Singleton();
        }
        return instance;
    }
private:
    static Singleton* instance;       // #2 定义一个唯一的类的实例对象
    Singleton()                       // #1 构造函数私有化 （不让用户在外部（new,栈，全局）定义对象了）
    {
        std::cout << "Singleton()" << std::endl;
    }
    Singleton(const Singleton&) = delete;    
    Singleton& operator=(const Singleton&) = delete;
    // 删除拷贝构造函数和赋值操作符： 通过将拷贝构造函数和赋值操作符声明为删除，确保了单例对象不会被复制。
};

// static成员变量一定要在类外进行定义并且初始化
Singleton* Singleton::instance = nullptr; 

int main()
{
    Singleton* p1 = Singleton::getInstance();
    Singleton* p2 = Singleton::getInstance();
    Singleton* p3 = Singleton::getInstance();
    std::cout << p1 << std::endl;
    std::cout << p2 << std::endl;
    std::cout << p3 << std::endl;
    /*
    Singleton()
    0064FC30
    0064FC30
    0064FC30
    */
    return 0;
}
#endif

//=================================================== 饿汉式单例模式 ==========================================================
#if 0
//  饿汉式单例模式是在类加载的时候就创建实例，因此不存在线程安全的问题。
//  饿汉式单例模式: 一定是线程安全的
//  饿汉式单例模式: 还没获取实例对象，实例对象就已经产生了
class Singleton
{
public:
    static Singleton* getInstance()    // #3 获取类的唯一实例对象的接口方法
    {
        return &instance;
    }
private:
    static Singleton instance;       // #2 定义一个唯一的类的实例对象
    Singleton()                       // #1 构造函数私有化 （不让用户在外部（new,栈，全局）定义对象了）
    {
        std::cout << "Singleton()" << std::endl;
    }
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    // 删除拷贝构造函数和赋值操作符： 通过将拷贝构造函数和赋值操作符声明为删除，确保了单例对象不会被复制。
};

// static成员变量一定要在类外进行定义并且初始化
Singleton Singleton::instance;                   // 相当于全局变量，./data段

int main()
{
    //Singleton* p1 = Singleton::getInstance();
    //Singleton* p2 = Singleton::getInstance();
    //Singleton* p3 = Singleton::getInstance();
    //std::cout << p1 << std::endl;
    //std::cout << p2 << std::endl;
    //std::cout << p3 << std::endl;

    return 0;
}

// 另一种实现
//class Singleton {
//public:
//    // 获取唯一实例的静态方法
//    static Singleton* getInstance() {
//        return instance;
//    }
//
//    // 其他成员函数和数据成员...
//
//private:
//    // 私有的构造函数
//    Singleton() {}
//
//    // 禁止拷贝构造和赋值操作
//    Singleton(const Singleton&);
//    Singleton& operator=(const Singleton&);
//
//    // 在类加载时创建唯一实例
//    static Singleton* instance;
//};
//
//// 在类外进行静态成员变量的定义和初始化
//Singleton* Singleton::instance = new Singleton();


#endif




























