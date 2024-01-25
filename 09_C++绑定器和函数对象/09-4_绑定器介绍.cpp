#include <iostream>
#include <functional>
#include <vector>
#include <thread>
using namespace std;
using namespace placeholders;   // 占位符命名空间


/*
C++11 bind绑定器  ==》 返回结果还是一个函数对象
*/

#if 0
void hello(string str) { cout << str << endl; }
int sum(int a, int b) { return a + b; }
class Test
{
public:
    int sum(int a, int b) { return a + b; }
};
int main()
{
    bind(hello, "hello bind!")();     // hello bind!
    cout << bind(sum, 10, 10)() << endl;    // 20
    cout << bind(&Test::sum, Test(), 20, 30)() << endl;  // 50       类的成员方法必须依赖对象才能调用
     
    // 参数占位符         绑定器出了语句，无法继续使用
    bind(hello, _1)("hello bind 2!");
    cout << bind(sum, placeholders::_1, _2)(200, 300) << endl;        // bind最多绑定20个参数

    // 绑定器出了语句无法继续使用了，因此借助function来复用
    // 此处把bind返回的绑定器binder就复用起来了
    function<void(string)> func1 = bind(hello, _1);
    func1("hello zy");
    func1("hello 夏日");
    func1("hello 新年好");

    return 0;
}
#endif

#if 0
//========================================================= bind和function实现简单的线程池 ==================================================
class Thread
{
public:
    Thread(function<void(int)> func, int no) : _func(func), _no(no) {}
    thread start()
    {
        thread t(_func, _no);
        return t;
    }
private:
    function<void(int)> _func;
    int _no;
};

class ThreadPool
{
public:
    ThreadPool() {}
    ~ThreadPool()
    {
        // 释放Thread对象占用的堆资源（因为vector存放的是指针，不是对象，所以要手动释放）
        for (unsigned int i = 0; i < _pool.size(); ++i)
        {
            delete _pool[i];
        }
    }
    // 开启线程池
    void startPool(int size)
    {
        for (int i = 0; i < size; ++i)
        {
            _pool.push_back(new Thread(bind(&ThreadPool::runInThread, this, _1), i));
        }
        for (int i = 0; i < size; ++i)
        {
            _handler.push_back(_pool[i]->start());  // _pool[i]->start();返回的的thread对象
        }
        for (thread& t : _handler) { t.join(); }
    }
private:
    vector<Thread*> _pool;
    vector<thread> _handler;
    // 线程函数
    // 把runInThread这个成员方法充当线程函数    thread   pthread_create   
    void runInThread(int id)
    {
        cout << "call runInThread! id:" << id << endl;
    }
};

int main()
{
    ThreadPool pool;
    pool.startPool(10);

    return 0;
}
#endif






