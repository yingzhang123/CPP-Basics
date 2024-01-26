#include <iostream>
#include <list>
#include <thread>
#include <atomic> // �����˺ܶ�ԭ������


volatile std::atomic_bool isReady = false;
volatile std::atomic_int count = 0;         // volatile ��ֹ���̳߳���Թ����������

void task()
{
    while (!isReady)
    {
        std::this_thread::yield();        // �̳߳��õ�ǰ��cpuʱ��Ƭ���ȴ���һ�ε���
    }

    for (int i = 0; i < 100; ++i)
    {
        count++;
    }
}

int main()
{
    std::list<std::thread> tlist;
    for (int i = 0; i < 10; ++i)
    {
        tlist.push_back(std::thread(task));
    }

    std::this_thread::sleep_for(std::chrono::seconds(3));
    isReady = true;

    for (std::thread& t : tlist)
    {
        t.join();
    }
    std::cout << "count: " << count << std::endl;

    return 0;
}