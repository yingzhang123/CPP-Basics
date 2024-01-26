#include<iostream>
#include<thread>
using namespace std;

/*
C++语言级别得多线程编程 ===》 代码可以跨平台  windows/Linux/Macos
thread/mutex/condition_variable
lock_guard/unique_lock
atomic 原子类型   基于CAS操作得原子类型   线程安全得
sleep_for

     C++ 语言层面thread                          对底层操作系统得api进行封装
        windows                     Linux
           |                           |
      createThread              pthread_create


*/

/*
线程内容：
一、怎么创建启动一个线程
std::thread定义一个线程对象，传入线程所需要得线程函数和参数，线程自动开启执行

二、子线程如何结束
t1.join() : 等待t线程运行完成，当前线程继续往下运行
t1.detach() : 把t线程设置为分离线程，主线程借宿，整个进程结束，所有子线程都自动借宿了！
*/

#if 0
void threadHandler1(int time)
{
    // 让子线程睡眠time秒
    std::this_thread::sleep_for(std::chrono::seconds(time));
    cout << "hello thread1" << endl;
}

void threadHandler2(int time)
{
    // 让子线程睡眠time秒
    std::this_thread::sleep_for(std::chrono::seconds(time));
    cout << "hello thread2" << endl;
}


int main()
{
    // 创建了一个线程对象，传入一个线程函数，新线程就开始运行了
    thread t1(threadHandler1,2);
    thread t2(threadHandler2, 3);
    // 主线程等待子线程结束，主线程继续往下运行
    // t1.join();

    // 把子线程设置为分离线程
   // t1.detach();              // 主程序运行完成，不检查t1是否还在运行与否
    
    t1.join();
    t2.join();

    cout << "main thread done!!" << endl;
    //主线程运行完成，查看如果当前进程还有未运行完成得子线程，进程就会异常终止的
    return 0;

}

// 主线程运行完了，不能够存在正在运行还未结束得子线程   ========》 如果存在，系统报错

#endif