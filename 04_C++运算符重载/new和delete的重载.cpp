#include<iostream>

/*
 ����������أ���Ա������ȫ�ַ���
 �ڴ��      ���̳�     �̳߳�       ���ӳ�       �����
*/

// �����
template<typename T>
class Queue
{
public:
	Queue()
	{
		_front = _rear = new QueueItem();   // ͷ�ڵ�
	}
	~Queue()
	{
		QueueItem *cur = _front;
		while (cur !=nullptr)
		{
			_front = _front->_next;
			delete cur;
			cur = _front;
		}
	}

	void push(const T& val)   //��Ӳ���
	{
		QueueItem *item = new QueueItem(val);
		_rear->_next = item;
		_rear = item;
	}

	void pop()   //���Ӳ���
	{
		if (empty())
			return;
		QueueItem *first = _front->_next;
		_front-> _next = first->_next;
		if (_front->_next == nullptr)
		{
			_rear = _front;
		}
		delete first;
	}

	T front()const
	{
		return _front->_next->_data;
	}

	bool empty()const
	{
		return _front == _rear;
	}


private:
	struct QueueItem
	{
		QueueItem(T data = T())
			:_data(data)
			, _next(nullptr)
		{}

		void* operator new(size_t size)
		{
			// �����û�������ڴ�ռ�
			if (_itemPool == nullptr)
			{
				_itemPool = (QueueItem*)new char[POOL_ITEM_SIZE*sizeof(QueueItem)];   //���ֽڿ����ڴ�ռ�
				QueueItem *p = _itemPool;
				for (;p < _itemPool + POOL_ITEM_SIZE -1 ; ++p)
				{
					p->_next = p + 1;
				}
				p->_next = nullptr;
			}
			QueueItem* p = _itemPool;
			_itemPool = _itemPool->_next;
			return p;
		}

		void operator delete(void *ptr)
		{
			QueueItem* p = (QueueItem*)ptr;
			p->_next = _itemPool;
			_itemPool = p;
		}

		T _data;
		QueueItem *_next;
		static QueueItem* _itemPool;
		static const int POOL_ITEM_SIZE = 100000;
	};

	QueueItem *_front;   //ָ��ͷ�ڵ�
	QueueItem *_rear;    // ָ�����һ���ڵ�
};

template<typename T>
typename Queue<T>::QueueItem* Queue<T>::QueueItem::_itemPool = nullptr;

int main()
{
	Queue<int> que;
	for (int i = 0; i < 1000000; ++i)
	{
		//��ʱ���ڴ�������new��delete  ==> malloc/free
		que.push(i);                           
		que.pop();
	}
	std::cout << que.empty() << std::endl;

}


#if 0
//==================================================================== �������new��delete�������ԭ�� ======================================================================
/*
1.malloc��new������
a.malloc�ǰ��ֽڿ����ڴ�ռ�ģ�new�����ڴ�ʱ��Ҫָ������,����new int(10)
	����malloc�����ڴ淵�صĶ���void*              operator new ->int* 

b.mallocֵ�����ڴ�ռ䣬new��������malloc�Ĺ��ܣ����Խ������ݵĳ�ʼ�� new int(20);    new int[20]();  
	                                      
c.malloc�����ڴ�ʧ�ܷ���nullPtrָ�룻new�׳�����bad_alloc���͵����쳣

2.free��delete������
delete p:����������������free(p);


new -> operator new�������غ����ĵ���
delete -> operator delete()���غ����ĵ���

new��delete�ܻ�����C++Ϊʲô���ֵ���Ԫ�غ�������ڴ������ͷ��أ�
new delete
new[]  delete[]
������ͨ�ı������������ͣ�int,long,double....�� new/delete[]   new[]/delete    ���Ի��ã�û����

�Զ���������ͣ�������������Ϊ�˵�����ȷ��������������ô���ٶ��������ʱ�򣬻�࿪��4���ֽڣ���¼����ĸ���    ���Դ�ʱnew��delete�����ܻ��ã��������ʹ��

*/


// �ȵ���operator new�����ڴ�ռ䡢Ȼ����ö���Ĺ��캯������ʼ����
void* operator new(size_t size)
{
	void *p = malloc(size);
	if (p == nullptr)
	{
		throw std::bad_alloc();
	}
	std::cout << "operator new addr:" << p << std::endl;
	return p;
}


// delete p;   �ȵ���pָ��������������,�ٵ���operator delete�ͷ��ڴ�ռ�   �����pָ����Ǳ������������ͣ��������������ֱ���ͷ��ڴ�ռ䣩
void operator delete(void* ptr)
{
	std::cout << "operator delete addr:" << ptr << std::endl;
	free(ptr);
}

void* operator new[](size_t size)
{
	void* p = malloc(size);
	if (p == nullptr)
	{
		throw std::bad_alloc();
	}
	std::cout << "operator new[] addr:" << p << std::endl;
	return p;
}

void operator delete[](void* ptr)
{
	std::cout << "operator delete[] addr:" << ptr << std::endl;
	free(ptr);
}

class Test
{
public:
	//Test(int data = 10):ptr(new int(data)){ std::cout << "Test()" << std::endl; }
	//~Test() { delete ptr; std::cout << "~Test()" << std::endl; }
	Test(int data = 10)
	{ 
		std::cout << "Test()" << std::endl;
	}

	~Test() 
	{ 
		std::cout << "~Test()" << std::endl; 
	}
private:
	//int* ptr;
};

int main()
{
	Test* p1 = new Test();
	//delete[] p1;   // ��.exe (���� 26348)���˳�������Ϊ -1073741819��
	delete p1;


	Test* p2 = new Test[5];
	// delete p2;   //����ֱ�ӱ���
	delete[]p2;

#if 0
	try 
	{
		int* p = new int;  // ���Է����ڴ�
		// ����ɹ���pָ��һ����̬�����int
		delete p;  // �ͷ��ڴ�

		int* p1 = new int[10];
		delete[]p1;

	}
	catch (const std::bad_alloc& e) 
	{
		// �ڴ����ʧ��ʱ�����쳣
		std::cerr << "Memory allocation failed: " << e.what() << std::endl;
	}

	//int* p1 = new int[10];
	//delete[]p1;
#endif  


	return 0;
}
#endif 






