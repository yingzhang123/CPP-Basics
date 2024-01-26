#include <iostream>
#include <thread>
#include <mutex>
#include <list>


/*
���̳߳���
��̬���������߳�ִ�еĽ����һ�µģ���������cpu��ͬ�ĵ���˳�򣬶�������ͬ�����н����

*/

/*
C++ thread ģ�⳵վ����������Ʊ�ĳ���

�̼߳�Ļ��� ===�� ������mutex(��Ҫ�ֶ���������) ===��lock_guard��װmutex
 
*/


#if 0
int ticketCount = 10;    // ��վ��100�ų�Ʊ����3������һ����
std::mutex mtx;          // ȫ�ֵ�һ�ѻ�����

//ģ����Ʊ���̺߳���
void sellTicket(int index)
{
	while (ticketCount > 0) // ��+˫���ж�      ��    // ticketCount = 1
	{
		//mtx.lock();
		// �ٽ��������  ===�� ԭ�Ӳ���  ===�� �̼߳以��  ===�� mutex
		{
			// ��֤�����̶߳����ͷ�������ֹ��������ķ��� 
			std::lock_guard<std::mutex> lock(mtx);   // ����ջ�϶�����������������ص㣬��֤�����̶߳����ͷ�������ֹ����              ������ scoped_ptr 
			//std::unique_lock<std::mutex> lck(mtx);                                                                                // ������ unique_ptr 
			//lck.lock();
			if (ticketCount > 0)         // �ж�  ��
			{
				std::cout << "����: " << index << "������: " << ticketCount << "��Ʊ!" << std::endl;
				ticketCount--;
			}
			//lck.unlock();
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		//mtx.unlock();
	}
}

int main()
{
	std::list<std::thread> tlist;
	for (int i = 1; i <= 3; ++i)
	{
		tlist.push_back(std::thread(sellTicket, i));
		//std::this_thread::sleep_for(std::chrono::seconds(2));
	}
	for (std::thread& t : tlist)
	{
		t.join();
	}
	std::cout << "���д�����Ʊ������" << std::endl;

	return 0;
}

#endif