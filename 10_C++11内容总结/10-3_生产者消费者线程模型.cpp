#include <iostream>
#include <thread>
#include <condition_variable>
#include <queue>              // C++ stl所有的容器都不是线程安全的!!!!

using namespace std;


// ==========================================================================================================
/*
unique_lock     condition_variable
1.unique_Lock和lock_guard
2.condition_variable     wait和notify_all方法
*/

#if 0
std::mutex mtx;
std::condition_variable cv;

int main()
{
	/*
	通知在cv上等待的线程，条件成立了，起来干活了！
	其他在cv上等待的线程，收到通知，从等待状态====》阻塞状态 ===》 获取到互斥锁了 ===》 线程继续运行
	*/
	cv.notify_all();

	// 他不仅仅可以使用在简单的临界区代码段的互斥事件操作中，还能用在函数调用过程中
	unique_lock<std::mutex> lck(mtx);

	cv.wait(lck);  // 1.使线程进入等待状态  2.lck.unlock()可以把mtx给释放掉

/*
	不能用在函数参数传递或者返回值当中（因为拷贝构造和赋值运算符重载函数已被删除），只能用在简单的临界区代码段的互斥当中
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
C++多线程编程 - 线程间的同步通信机制

多线程编程两个问题：
1.线程间互斥
竞态条件 =》 临界区代码段 =》 保证原子操作 =》互斥锁mutex  轻量级的的无锁实现CAS
2.线程间的同步通信
	生产者、消费者线程模型

*/

std::mutex mtx;
std::condition_variable cv;

// 生产者生产一个物品，通知消费者消费一个；消费完了，消费者再通知生产者继续生产物品
class Queue
{
public:
	void put(int val)
	{
 		std::unique_lock<std::mutex> lck(mtx);
		while (!que.empty())
		{
			// que不为空，生产者应该通知消费者去消费，消费完了再继续生产
			// 生产者线程应该进入等待状态，并且把mtx互斥锁释放掉
			cv.wait(lck);         // wait()内部回释放互斥锁          接收的是unique_lock()!!! 
		}
		que.push(val);
		/*
		cv.notify_one()：通知另外一个线程
		cv.notify_all()：通知其他所有线程
		其他线程得到该线程，就会从等待状态 ===》 阻塞状态 ===》 获取互斥锁才能继续执行
		*/
		cv.notify_all();       // 通知其他所有线程，我生产了一个物品，你们赶紧消费吧
		std::cout << "生产者 生产：" << val << "号物品" << std::endl;
	}
	int get()
	{
		std::unique_lock<std::mutex> lck(mtx);
		while (que.empty())
		{
			// 消费者线程发现que是空的，通知生产者线程生产物品
			// 1、进入等待状态    2、把互斥锁mutex释放
			cv.wait(lck);
		}
		int val = que.front();
		que.pop();
		cv.notify_all();
		std::cout << "消费者 消费：" << val << "号物品" << std::endl;
		return val;
	}
private:
	std::queue<int> que;
};

// 生产者线程
void producer(Queue* que)
{
	for (int i = 1; i <= 10; ++i)
	{
		que->put(i);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

// 消费者线程
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