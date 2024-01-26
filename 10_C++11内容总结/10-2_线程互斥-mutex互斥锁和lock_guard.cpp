#include <iostream>
#include <thread>
#include <mutex>
#include <list>


/*
多线程程序
竞态条件：多线程执行的结果是一致的，不会随着cpu不同的调度顺序，而产生不同的运行结果。

*/

/*
C++ thread 模拟车站三个窗口买票的程序

线程间的互斥 ===》 互斥锁mutex(需要手动加锁解锁) ===》lock_guard封装mutex
 
*/


#if 0
int ticketCount = 10;    // 车站有100张车票，由3个窗口一起卖
std::mutex mtx;          // 全局的一把互斥锁

//模拟卖票的线程函数
void sellTicket(int index)
{
	while (ticketCount > 0) // 锁+双重判断      ①    // ticketCount = 1
	{
		//mtx.lock();
		// 临界区代码段  ===》 原子操作  ===》 线程间互斥  ===》 mutex
		{
			// 保证所有线程都能释放锁，防止死锁问题的发生 
			std::lock_guard<std::mutex> lock(mtx);   // 利用栈上对象出作用域析构的特点，保证所有线程都能释放锁，防止死锁              类似与 scoped_ptr 
			//std::unique_lock<std::mutex> lck(mtx);                                                                                // 类似与 unique_ptr 
			//lck.lock();
			if (ticketCount > 0)         // 判断  ②
			{
				std::cout << "窗口: " << index << "卖出第: " << ticketCount << "张票!" << std::endl;
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
	std::cout << "所有窗口卖票结束！" << std::endl;

	return 0;
}

#endif