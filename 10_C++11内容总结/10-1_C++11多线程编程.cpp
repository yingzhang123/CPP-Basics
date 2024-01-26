#include<iostream>
#include<thread>
using namespace std;

/*
C++���Լ���ö��̱߳�� ===�� ������Կ�ƽ̨  windows/Linux/Macos
thread/mutex/condition_variable
lock_guard/unique_lock
atomic ԭ������   ����CAS������ԭ������   �̰߳�ȫ��
sleep_for

     C++ ���Բ���thread                          �Եײ����ϵͳ��api���з�װ
        windows                     Linux
           |                           |
      createThread              pthread_create


*/

/*
�߳����ݣ�
һ����ô��������һ���߳�
std::thread����һ���̶߳��󣬴����߳�����Ҫ���̺߳����Ͳ������߳��Զ�����ִ��

�������߳���ν���
t1.join() : �ȴ�t�߳�������ɣ���ǰ�̼߳�����������
t1.detach() : ��t�߳�����Ϊ�����̣߳����߳̽��ޣ��������̽������������̶߳��Զ������ˣ�
*/

#if 0
void threadHandler1(int time)
{
    // �����߳�˯��time��
    std::this_thread::sleep_for(std::chrono::seconds(time));
    cout << "hello thread1" << endl;
}

void threadHandler2(int time)
{
    // �����߳�˯��time��
    std::this_thread::sleep_for(std::chrono::seconds(time));
    cout << "hello thread2" << endl;
}


int main()
{
    // ������һ���̶߳��󣬴���һ���̺߳��������߳̾Ϳ�ʼ������
    thread t1(threadHandler1,2);
    thread t2(threadHandler2, 3);
    // ���̵߳ȴ����߳̽��������̼߳�����������
    // t1.join();

    // �����߳�����Ϊ�����߳�
   // t1.detach();              // ������������ɣ������t1�Ƿ����������
    
    t1.join();
    t2.join();

    cout << "main thread done!!" << endl;
    //���߳�������ɣ��鿴�����ǰ���̻���δ������ɵ����̣߳����̾ͻ��쳣��ֹ��
    return 0;

}

// ���߳��������ˣ����ܹ������������л�δ���������߳�   ========�� ������ڣ�ϵͳ����

#endif