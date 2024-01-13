#include<iostream>

//======================================================= 3.C++ ��ģ�� ʵ��vector  �ռ�������allocator  ������ӵ���������  ������ʧЧ����  =====================================

// �Զ���ռ�������  ���������Ŀռ�����������C++��׼���allocatorʵ��һ��
template<typename T>
class Allocator
{
public:
	T* allocate(size_t size)  // �����ڴ濪��
	{
		return (T*)malloc(sizeof(T) * size);
	}

	void deallocate(void* p)  // �����ڴ��ͷ�
	{
		free(p);
	}

	void construct(T* p, const T& val)  //���������
	{
		new (p) T(val);   // ��λnew����ָ�����ڴ���ȥ����һ��ֵΪval�Ķ���
	}

	void destroy(T* p)         // �����������
	{
		p->~T();             // ~T() ������T���͵���������
	}
};

/*
�����ײ��ڴ濪�٣��ڴ��ͷţ����������������ͨ��allocator�ռ�������ʵ��
*/
template<typename T = int, typename Alloc = Allocator<T>>
class vector
{
public:
	//vector(int size=10,const Alloc& alloc = Allocator<T>())    // Ҳ�������û�������,����ʹ��Ĭ�ϵ�Allocator<T>
	//	:_allocator(alloc)

	vector(int size = 10)      // 
	{
		// ��Ҫ���ڴ濪�ٺͶ�����ֿ�����  [new�������������һ�����ˣ����Զ����������С�����Ķ��󣬾�����Щ�������ң�������Ҫ��]
		//_first = new T[size];
		_first = _allocator.allocate(size);  // 10��Ԫ�ض���  �����ڴ�ռ�
		_last = _first;
		_end = _first + size;
	}

	~vector()
	{
		// ����������Ч��Ԫ�أ�Ȼ���ͷ�_firstָ��ֱ�ߵĶ��ڴ�  [delete]
		//delete[]_first;

		for (T* p = _first; p != _last; ++p)   // ��_firstָ��ָ����������ЧԪ�ؽ�����������
		{
			_allocator.destroy(p);
		}
		_allocator.deallocate(_first);   //�ͷŶ��ϵ������ڴ�
		_first = _last = _end = nullptr;
	}

	vector(const vector<T>& other)
	{
		int size = other._end - other._first;
		//_first = new T[size];
		_first = _allocator.allocate(size);
		int len = other._last - other._first;
		for (int i = 0; i < len; ++i)
		{
			//	_first[i] = other._first[i];
			_allocator.construct(_first + i, other._first[i]);
		}
		_last = _first + len;
		_end = _first + size;
	}

	vector<T>& operator=(const vector<T>& other)
	{
		if (this == &other)
			return *this;

		//delete[]_first;
		for (T* p = _first; p != _last; ++p)   // ��_firstָ��ָ����������ЧԪ�ؽ�����������
		{
			_allocator.destroy(p);
		}
		_allocator.deallocate(_first);         //�ͷŶ��ϵ������ڴ�

		int size = other._end - other._first;
		//_first = new T[size];
		_first = _allocator.allocate(size);
		int len = other._last - other._first;
		for (int i = 0; i < len; ++i)
		{
			//	_first[i] = other._first[i];
			_allocator.construct(_first + i, other._first[i]);
		}
		_last = _first + len;
		_end = _first + size;

		return *this;
	}


	void push_back(const T& val)   // ������ĩβ���Ԫ��
	{
		if (full())
		{
			expand();
		}
		//*_last++ = val;   // �ȸ�ֵ ָ���1
		_allocator.construct(_last, val);   // _lastָ��ָ����ڴ湹��һ��ֵΪval�Ķ���
		_last++;
	}

	void pop_back()      // ������ĩβɾ������
	{
		if (empty())
		{
			return;
		}
		// erase(it);   ===>  verify(it._ptr,_last);
		// insert(it,val)    ===> verify(it._ptr,_last)
		verify(_last - 1, _last);
		//--_last;
		--_last;         // ����Ҫ��_lastָ��--����Ҫ����ɾ����Ԫ��
		_allocator.destroy(_last);
	}

	T back()const   //��������ĩβ��Ԫ�ص�ֵ
	{
		if (empty())
		{
			// ����һ��Ĭ��ֵ���׳��쳣���Ա�ʾ����Ϊ��
			throw std::out_of_range("Vector is empty");
		}
		return *(_last - 1);
	}


	bool full() const { return _last == _end; }
	bool empty() const { return _first == _last; }
	int size() const { return _last - _first; }

	T& operator[](int index)  // �����±������ vec[2]
	{
		if (index < 0 || index >= size())
		{
			throw "OutOfRangeException";
		}
		return _first[index];
	}

	// 1.������һ��ʵ��Ϊ������Ƕ������    ��������һ�����������������ģ�  
	class iterator
	{
	public:
		friend class vector<T, Alloc>;  //��Ԫ��
		iterator(vector<T,Alloc> *pvec = nullptr,T* ptr=nullptr)          //�����ɵ�ǰ����ĳһ��λ��Ԫ�صĵ�����
			:_ptr(ptr)
			,_pVec(pvec)
		{
			Iterator_Base* itb = new Iterator_Base(this, _pVec->_head._next);       // �൱��ͷ�巨������
			_pVec->_head._next = itb;
		}
		
		bool operator!=(const iterator& it) const
		{
			//������������Ч��
			if (_pVec == nullptr || _pVec != it._pVec)
			{
				throw "iterator incompatable!";
				return false;
			}
			return _ptr != it._ptr;
		}

		void operator++()
		{
			// ������������Ч��
			if (_pVec == nullptr)
			{
				throw "iterator invalid��";
			}
			_ptr++;   // ָ��++
		} 

		T& operator*()    // �ɶ����޸�   �� const ����  
		{ 
			// ������������Ч��
			if (_pVec == nullptr)
			{
				throw "iterator invalid��";
			}
			return *_ptr;
		}            
		const T& operator*() const    // ����ֵҲ��const���ɶ������ǲ����޸ģ� * it = 20;    ��������     const ����
		{ 
			// ������������Ч��
			if (_pVec == nullptr)
			{
				throw "iterator invalid��";
			}
			return *_ptr; 
		}  
		// T& operator*() const { return *_ptr; }  //  �������ʵ�����ǲ��Ϸ��ģ���Ϊ����ͼ�� const �޶��ĳ�Ա�����ڲ����зǳ�����������⿴������һ��ƴд���������һ����̫���ԵĴ��󡣱��������ܻᱨ��
	private:
		T* _ptr;    // ������ָ��������ĳ��Ԫ�أ���ʵ�ǵ�������ָ��ָ����������ײ������ĳһ��λ��
		// ��ǰ���������������ĸ�����
		vector<T, Alloc>* _pVec;
	};

	// 2.��Ҫ�������ṩbegin��end����
	iterator begin() { return iterator(this,_first); }
	iterator end() {return iterator(this,_last); }

	// ��������ʧЧ       ������ʧЧ����
	void verify(T* first, T* last)
	{
		Iterator_Base* pre = &this->_head;
		Iterator_Base* it = this->_head._next;
		while (it != nullptr)
		{
			if (it->_cur->_ptr > first && it->_cur->_ptr <= last)
			{
				// ������ʧЧ����iterator���е�����ָ����Ϊnullptr
				it->_cur->_pVec = nullptr;
				// ɾ����ǰ��㣬�����жϺ���ĵ������ڵ��Ƿ�ʧЧ
				pre->_next = it->_next;
				delete it;
				it = pre->_next;
			}
			else
			{
				pre = it;
				it = it->_next;
			}
		}
	}

	// �Զ���vector����insert������ʵ��
	iterator insert(iterator it, const T& val)
	{
		/*  
		1.����������      verify(_first, _last);
		2.������it._ptr��ָ��Ϸ���     ��===== Ϊ�˼�
		*/
		verify(it._ptr - 1, _last);
		T* p = _last;
		while (p > it._ptr)
		{
			_allocator.construct(p, *(p - 1));
			_allocator.destroy(p - 1);
			p--;
		}
		_allocator.construct(p, val);
		_last++;
		return iterator(this, p);
	}

	iterator erase(iterator it)
	{
		verify(it._ptr - 1, _last);
		T* p = it._ptr;
		while (p < _last-1)
		{
			_allocator.destroy(p);
			_allocator.construct(p, *(p + 1));
			p++;
		}
		_allocator.destroy(p);
		_last--;
		return iterator(this, it._ptr);
	}

private:
	T* _first;      // ָ��������ʼ��λ��
	T* _last;       // ָ����������ЧԪ�صĺ��λ��
	T* _end;        // ָ������ռ�ĺ��λ��

	Alloc _allocator;     //���������Ŀռ�����������

	// ����������ʧЧ���Ӵ���
	struct Iterator_Base
	{
		Iterator_Base(iterator* c = nullptr, Iterator_Base* n = nullptr)
			:_cur(c)
			,_next(n)
		{

		}

		iterator* _cur;         // ά��ĳ����������ָ��
		Iterator_Base* _next;   // �������������ĸ�Ԫ�صĵ�����
	};
	Iterator_Base _head;

	void expand()   // �����Ķ�������
	{
		int size = _end - _first;   //ԭ��������С
		//T* ptmp = new T[size * 2];
		T* ptmp = _allocator.allocate(size * 2);

		for (int i = 0; i < size; i++)
		{
			//ptmp[i] = _first[i];
			_allocator.construct(ptmp + i, _first[i]);
		}
		// delete[]_first;
		for (T* p = _first; p != _last; ++p)
		{
			_allocator.destroy(p);
		}
		_allocator.deallocate(_first);

		_first = ptmp;
		_last = _first + size;
		_end = _first + (size * 2);
	}
};


// ��C++�У�ָ��� + 1 ���������Ǽ򵥵Ľ�ָ���ֵ�� 1�����ǻ���ָ��ָ������ͽ������ӡ�������ԣ� + 1 ������ʹָ����ǰ�ƶ�һ���洢��Ԫ�Ĵ�С��������һ��ƫ�ƣ����ƫ������ָ�������ȷ����

int main04()
{
	vector<int> vec(200);
	for (int i = 0; i < 20; i++)
	{
		vec.push_back(rand() % 100);
	}
	for (int ch : vec)
	{
		std::cout << ch << " ";
	}
	std::cout << std::endl;

	auto it = vec.begin();
	while (it != vec.end())
	{
		if (*it % 2 == 0)
		{
			it = vec.erase(it);
		}
		else
		{
			++it;
		}
	}


	for (int ch : vec)
	{
		std::cout << ch << " ";
	}
	std::cout << std::endl;
#if 0
	auto it = vec.begin();
	for (; it != vec.end(); ++it)
	{
		if (*it % 2 == 0)
		{
			it = vec.insert(it, (*it - 1));
			++it;      // ����2��
		}
	}

	for (int ch : vec)
	{
		std::cout << ch << " ";
	}
	std::cout << std::endl;
#endif



#if 0
	//ʹ��[]����       // ���vector��������
	int size = vec.size();
	for (int i = 0; i < size; i++)
	{
		std::cout << vec[i] << " ";
	}
	std::cout << std::endl;

	// ʹ�õ���������
	vector<int>::iterator it = vec.begin();   // auto it = vec.begin();
	for (; it != vec.end(); ++it)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;


	for (int ch : vec)  // ��ײ�ԭ������ͨ�������ĵ�������ʵ������������
	{
		std::cout << ch << " ";
	}
	std::cout << std::endl;
#endif
	return 0;
}