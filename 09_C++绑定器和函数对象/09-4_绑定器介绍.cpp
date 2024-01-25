#include <iostream>
#include <functional>
#include <vector>
#include <thread>
using namespace std;
using namespace placeholders;   // ռλ�������ռ�


/*
C++11 bind����  ==�� ���ؽ������һ����������
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
    cout << bind(&Test::sum, Test(), 20, 30)() << endl;  // 50       ��ĳ�Ա������������������ܵ���
     
    // ����ռλ��         ����������䣬�޷�����ʹ��
    bind(hello, _1)("hello bind 2!");
    cout << bind(sum, placeholders::_1, _2)(200, 300) << endl;        // bind����20������

    // ������������޷�����ʹ���ˣ���˽���function������
    // �˴���bind���صİ���binder�͸���������
    function<void(string)> func1 = bind(hello, _1);
    func1("hello zy");
    func1("hello ����");
    func1("hello �����");

    return 0;
}
#endif

#if 0
//========================================================= bind��functionʵ�ּ򵥵��̳߳� ==================================================
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
        // �ͷ�Thread����ռ�õĶ���Դ����Ϊvector��ŵ���ָ�룬���Ƕ�������Ҫ�ֶ��ͷţ�
        for (unsigned int i = 0; i < _pool.size(); ++i)
        {
            delete _pool[i];
        }
    }
    // �����̳߳�
    void startPool(int size)
    {
        for (int i = 0; i < size; ++i)
        {
            _pool.push_back(new Thread(bind(&ThreadPool::runInThread, this, _1), i));
        }
        for (int i = 0; i < size; ++i)
        {
            _handler.push_back(_pool[i]->start());  // _pool[i]->start();���صĵ�thread����
        }
        for (thread& t : _handler) { t.join(); }
    }
private:
    vector<Thread*> _pool;
    vector<thread> _handler;
    // �̺߳���
    // ��runInThread�����Ա�����䵱�̺߳���    thread   pthread_create   
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






