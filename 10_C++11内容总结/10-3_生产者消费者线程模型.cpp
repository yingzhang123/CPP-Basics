#include <iostream>
#include <thread>
#include <condition_variable>
#include <queue>              // C++ stl���е������������̰߳�ȫ��!!!!

using namespace std;


// ==========================================================================================================
/*
unique_lock     condition_variable
1.unique_Lock��lock_guard
2.condition_variable     wait��notify_all����
*/

#if 0
std::mutex mtx;
std::condition_variable cv;

int main()
{
	/*
	֪ͨ��cv�ϵȴ����̣߳����������ˣ������ɻ��ˣ�
	������cv�ϵȴ����̣߳��յ�֪ͨ���ӵȴ�״̬====������״̬ ===�� ��ȡ���������� ===�� �̼߳�������
	*/
	cv.notify_all();

	// ������������ʹ���ڼ򵥵��ٽ�������εĻ����¼������У��������ں������ù�����
	unique_lock<std::mutex> lck(mtx);

	cv.wait(lck);  // 1.ʹ�߳̽���ȴ�״̬  2.lck.unlock()���԰�mtx���ͷŵ�

/*
	�������ں����������ݻ��߷���ֵ���У���Ϊ��������͸�ֵ��������غ����ѱ�ɾ������ֻ�����ڼ򵥵��ٽ�������εĻ��⵱��
	lock_guard<std::mutex> guard(mtx);
*/
	
	//mtx.lock();
	//mtx.unlock();

	return 0;
}
#endif

// ===========================================================================================================
#if 0
/*
C++���̱߳�� - �̼߳��ͬ��ͨ�Ż���

���̱߳���������⣺
1.�̼߳以��
��̬���� =�� �ٽ�������� =�� ��֤ԭ�Ӳ��� =��������mutex  �������ĵ�����ʵ��CAS
2.�̼߳��ͬ��ͨ��
	�����ߡ��������߳�ģ��

*/

std::mutex mtx;
std::condition_variable cv;

// ����������һ����Ʒ��֪ͨ����������һ�����������ˣ���������֪ͨ�����߼���������Ʒ
class Queue
{
public:
	void put(int val)
	{
 		std::unique_lock<std::mutex> lck(mtx);
		while (!que.empty())
		{
			// que��Ϊ�գ�������Ӧ��֪ͨ������ȥ���ѣ����������ټ�������
			// �������߳�Ӧ�ý���ȴ�״̬�����Ұ�mtx�������ͷŵ�
			cv.wait(lck);         // wait()�ڲ����ͷŻ�����          ���յ���unique_lock()!!! 
		}
		que.push(val);
		/*
		cv.notify_one()��֪ͨ����һ���߳�
		cv.notify_all()��֪ͨ���������߳�
		�����̵߳õ����̣߳��ͻ�ӵȴ�״̬ ===�� ����״̬ ===�� ��ȡ���������ܼ���ִ��
		*/
		cv.notify_all();       // ֪ͨ���������̣߳���������һ����Ʒ�����ǸϽ����Ѱ�
		std::cout << "������ ������" << val << "����Ʒ" << std::endl;
	}
	int get()
	{
		std::unique_lock<std::mutex> lck(mtx);
		while (que.empty())
		{
			// �������̷߳���que�ǿյģ�֪ͨ�������߳�������Ʒ
			// 1������ȴ�״̬    2���ѻ�����mutex�ͷ�
			cv.wait(lck);
		}
		int val = que.front();
		que.pop();
		cv.notify_all();
		std::cout << "������ ���ѣ�" << val << "����Ʒ" << std::endl;
		return val;
	}
private:
	std::queue<int> que;
};

// �������߳�
void producer(Queue* que)
{
	for (int i = 1; i <= 10; ++i)
	{
		que->put(i);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

// �������߳�
void consumer(Queue* que)
{
	for (int i = 1; i <= 10; ++i)
	{
		que->get();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

int main()
{
	Queue que;

	std::thread t1(producer, &que);
	std::thread t2(consumer, &que);

	t1.join();
	t2.join();

	return 0;
}
#endif 0