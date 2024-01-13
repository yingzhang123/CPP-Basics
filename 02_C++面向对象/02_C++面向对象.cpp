#include<iostream>


//============================================================== 1.��Ͷ���thisָ�� =====================================
/*
C++ OOP�������  OOP��̣�thisָ��
C�����ָ����ĺ����Ķ���   struct
C++: ��    ==��  ʵ��ĳ�������
 
ʵ�壨���ԡ���Ϊ��   ====��             ADT(abstruct data type)
       |                                       |
    ����            ��==== ��ʵ������   �ࣨ����->��Ա����   ��Ϊ->��Ա������


OOP���Ե��Ĵ�������ʲô��
����    ��װ/����     �̳�    ��̬

��    ===��   ��Ʒʵ��
�����޶�����public���е�    private˽�е�   protected������

*/

#if 0
// ��������ĸȫ����д  ��Ա���������ԣ�����ĸСд�������дд
const int NAME_LEN = 20;
class CGoods     //   ==����Ʒ�ĳ����������ͣ���ռ�ڴ�ռ䣩
{
public:          // ���ⲿ�ṩ���еĳ�Ա������������˽�е����� 
    // ����Ʒ�ĳ�ʼ���õ�
    void init(const char* name, double price, int amount);
    // ��ӡ��Ʒ��Ϣ
    void show();
    // ����Ա�����ṩһ��getXXX��setXXX�ķ���              ������ʵ�ֵķ������Զ������inline����������
    void setName(char* name) { strcpy(_name, name); }   // ��Ա������������ʵ��
    void setPrice(double price) { _price = price; }
    void setAmount(int amount) { _amount = amount; }

    // const���η���ָ�룬��ֹ�ⲿͨ��ָ��������޸Ķ��������
    const char* getName() { return _name; }   
    double getPrice() { return _price; }
    int getAmount() { return _amount; }

private:         //����һ����˽�еĳ�Ա����
    char _name[NAME_LEN];
    double _price;
    int _amount;
};

// ������ʵ�ֳ�Ա������һ��Ҫ�ڷ�����ǰ��������������               ��������ʵ�ֵķ��������ú���ͨ�ķ���һ���������д��inline����Ҫ��ǰ�����inline��
void CGoods::init(const char* name, double price, int amount)
{
    strcpy(this->_name, name);
    this->_price = price;
    this->_amount = amount;
}

void CGoods::show()
{
    std::cout << "name:" << this->_name << std::endl;
    std::cout << "price:" << this->_price << std::endl;
    std::cout << "amount:" << this->_amount << std::endl;
}

// �ַ���������������ָͨ�����(��ͨ��ָ��������޸��ַ���������ֵ�����ǲ�����ģ�����)��Ҫ�ó�ָ��const char*

int main()
{
    /*
    CGoods���Զ��������Ķ���ÿһ���������Լ��ĳ�Ա������
    �������ǹ���һ�׳�Ա����

    show()     ====> ��ô֪�������Ǹ��������Ϣ��
    init(name,price,amount)     =====>       ��ô֪������Ϣ��ʼ������һ������ 

    ��ĳ�Ա����һ�����룬���еķ��������������һ��this�����յ��ø÷����Ķ����ַ
     void init(CGoods* this, const char* name, double price, int amount);
    */

    // cl 02_C++�������.cpp /dlreportSingleClassLayoutCGoods     ���Բ鿴�ڴ��С
    // �����ڴ��С��ʱ��   ������ڴ��С ==�� ֻ�ͳ�Ա������С�й�
    CGoods good1;     // ��ʾ������һ������
    // init(&good1,"���", 29.0, 100)     <===========
    good1.init("���", 29.0, 100); 
    // show(&good1)
    good1.show();
    good1.setPrice(100.0);
    good1.setAmount(60);
    good1.show();

    CGoods good2;
    good2.init("���г�", 629.0, 100);
    good2.show();

    return 0;
}


#endif



//============================================================ 2.���չ��캯������������ =====================================
/*
���캯�� �� ��������           OOP��̸�ϰһ��
OOPʵ��һ��˳��ջ


���캯������������
���������ֺ�����һ��
û�з���ֵ
*/

#if 0
// ˳��ջ
class SeqStack
{
public:
    // ���캯��
    SeqStack(int size = 10)  // �ǿ��Դ������ģ���˿����ṩ������캯�� 
    {
        std::cout << this<< "  " << "SeqStack()" << std::endl;
        _pstack = new int[size];
        _top = -1;
        _size = size;
    }
    // ��������
    ~SeqStack()    // �ǲ��������ģ�������������ֻ����һ��������
    {
        std::cout << this << "  " << "~SeqStack()" << std::endl;
        delete _pstack;
        _pstack = nullptr;
    }

    void init(int size = 10)
    {
        _pstack = new int[size];
        _top = -1;
        _size = size;
    }

    void release() 
    {
        delete _pstack;
        _pstack = nullptr;
    }

    void push(int val)
    {
        if (full())
            resize();
        _pstack[++_top] = val;
    }

    void pop()
    {
        if (empty())
            return;
        _top--;
    }

    int top()
    {
        return _pstack[_top];
    }

    bool full()
    {
        return _top == (_size-1);
    }

    bool empty()
    {
        return _top == -1;
    }

private:
    int* _pstack;
    int _top;
    int _size;

    void resize()
    {
        int* ptmp = new int[_size * 2];
        for (int i = 0; i < _size; i++)
        {
            ptmp[i] = _pstack[i];
        }  // memcpy(ptmp,_pstack,sizeof(int)*_size);   remalloc()     // ���������������ڴ濽��
        delete[] _pstack;
        _pstack = ptmp;
        _size = _size * 2;
    }
};

SeqStack gs;      // ȫ�ֶ����ڶ����ʱ����ù��죬�����ڳ������ʱ������      .data

int main()
{
    /*  ���鲻ͬ�ڴ�����
    .data
    heap
    stack
    */

    SeqStack* ps = new SeqStack(60);   // �ڴ濪���ڶ���   ���ϵĶ���    heap      =====��malloc�ڴ濪�� + SeqStack(60)������  
    ps->push(43);
    ps->push(70);
    std::cout << ps->top() << std::endl;
    delete ps;      // ���ϵĶ�����Ҫ�ֶ�����delete�ͷţ������ö����������������ָ�����ָ���ⲿ�Ķ��ڴ��ͷţ�Ȼ���ٰѶ�����ڴ��ͷŵ���
                    // �ȵ���ps->~SeqStack() + Ȼ��free(ps)

    // ����һ������ 1�������ڴ�  2�����ù��캯��   
    SeqStack s;     // stack
   // s.init(5);         // �����Ա�ĳ�ʼ������

    for (int i= 0; i < 15; i++)
    {
        s.push(rand() % 100);
    }

    while (!s.empty())
    {
        std::cout << s.top() << " ";
        s.pop();
    }

    //s.release();       // �ͷŶ����Ա����ռ�õ��ⲿ���ڴ�

    SeqStack s2(40);


   // s2.~SeqStack();     // �������������ֶ����ã����캯�������ֶ����ã�����������ݴ���Ĳ���ƥ����ʵĹ��캯��      ���������ֶ���������������
    // �������������Ժ�����˵���󲻴�����
    //s2.push(30);    // �﷨��û���⣬������ʱ��������ڴ�Ƿ����ʣ������ҵ�
    return 0;           // �������ý�����ջ�ϵĶ��󶼻����εĽ�������     (���ù����������˳��պ����෴�ģ��ȹ���ĺ������������������)     // �൱�ڳ�ջ����ջ�Ĺ���
}
#endif


//============================================================ 3.���ն���������ǳ���� =====================================
/*
thisָ�� ===�� ��-���ܶ����   ����һ�׳�Ա������������ֲ�ͬ����ģ�ͨ��thisָ�����ֶ���
��Ա����һ�����룬�����Ĳ����������һ��thisָ��

���캯����
    �������ʱ���Զ����õģ��������أ�������ɣ�����Ͳ�����

����������
     �����������������أ�ֻ��һ������������������ɣ�����Ͳ�����

.data�Ķ��󣺳�������ʱ���죬�������ʱ����
heap�Ķ���new��ʱ���죬delete����
stack�Ķ����ڶ��崦���죬��������ʱ����



����������ǳ����

����Ĭ�ϵĿ������������ڴ��ڴ�����ݿ���

ǳ������һ���Ǵ�ģ��ؼ��Ƕ������ռ���ⲿ��Դ����ôǳ�����ͳ��������ˣ�������
*/


#if 0
class SeqStack
{
public:
    // ���캯��
    SeqStack(int size = 10)  // �ǿ��Դ������ģ���˿����ṩ������캯�� 
    {
        std::cout << this << "  " << "SeqStack()" << std::endl;
        _pstack = new int[size];
        _top = -1;
        _size = size;
    }

    // �Զ��忽�����캯��       ��==== Ĭ�Ͽ������캯����ǳ�����������ݳ�Ա��ָ�����ָ���ⲿ��Դ����������
    SeqStack(const SeqStack& src)
    {
        // Ĭ�Ͽ������캯��    ǳ����
        //_pstack = src._pstack;
        //_top = src._top;
        //_size = src._size;

        // ���
        std::cout << "SeqStack(const SeqStack& src)" << std::endl;
        _pstack = new int[src._size];
        for (int i = 0; i <= src._top; i++)
        {
            _pstack[i] = src._pstack[i];
        }
        _top = src._top;
        _size = src._size;
    }

    // ��������
    ~SeqStack()    // �ǲ��������ģ�������������ֻ����һ��������
    {
        std::cout << this << "  " << "~SeqStack()" << std::endl;
        delete _pstack;
        _pstack = nullptr;
    }

    //��ֵ���غ���
    void operator=(const SeqStack& src)
    {
        // ���
        std::cout << "operator=" << std::endl;
        // ��ֹ�Ը�ֵ  s1 = s1
        if (this == &src)
        {
            return;
        }

        // ��Ҫ���ͷŵ�ǰ����ռ�õ��ⲿ��Դ          ���ȿ��������һ����
        delete []_pstack;    

        _pstack = new int[src._size];
        for (int i = 0; i <= src._top; i++)
        {
            _pstack[i] = src._pstack[i];
        }
        _top = src._top;
        _size = src._size;
    }

    void init(int size = 10)
    {
        _pstack = new int[size];
        _top = -1;
        _size = size;
    }

    void release()
    {
        delete _pstack;
        _pstack = nullptr;
    }

    void push(int val)
    {
        if (full())
            resize();
        _pstack[++_top] = val;
    }

    void pop()
    {
        if (empty())
            return;
        _top--;
    }

    int top()
    {
        return _pstack[_top];
    }

    bool full()
    {
        return _top == (_size - 1);
    }

    bool empty()
    {
        return _top == -1;
    }

private:
    int* _pstack;
    int _top;
    int _size;

    void resize()
    {
        int* ptmp = new int[_size * 2];
        for (int i = 0; i < _size; i++)
        {
            ptmp[i] = _pstack[i];
        }  // memcpy(ptmp,_pstack,sizeof(int)*_size);   remalloc()     // ���������������ڴ濽��
        delete[] _pstack;
        _pstack = ptmp;
        _size = _size * 2;
    }
};


int main()
{
    SeqStack s; //û���ṩ�κι��캯����ʱ�򣬱��������Զ�����Ĭ�Ϲ��캯����Ĭ�������������ǿպ���
    SeqStack s1(10);   // ���ô����Ͳ����Ĺ��캯��

    // ���������ֶ��巽ʽ����һ���ģ���һ��ջ������һ���µ�ջ���󣩶��������һ������ù���
    SeqStack s2 = s1;    // ����Ĭ�Ͽ������캯��    Ĭ���ǿ������캯������ֱ���ڴ����ݵĿ�����ǳ������
   // SeqStack s3(s1);     // ����Ĭ�Ͽ������캯��


    // void operator=(const SeqStack& src)  //��ֵ����
    s2 = s1;   // Ĭ�ϵĸ�ֵ����  ==�� ��ֱ�ӵ��ڴ濽��
    return 0;
}

#endif

#if 0
// 2. ѭ������       memcpy realloc ��������������Ŀ�����̫����[��Ϊ����ǳ��������]
class Queue
{
public:
    Queue(int size=20)
    {
        _pQue = new int[size];
        _front = _rear = 0;
        _size = size;
    }

     //Queue(const Queue& other) = delete;
     //Queue& operator=(const Queue&) = delete;
    Queue(const Queue& other)
    {
        _size = other._size;
        _front = other._front;
        _rear = other._rear;
        _pQue = new int[other._size];
        for (int i = _front; i!=_rear; i = (i+1)%_size)
        {
            _pQue[i] = other._pQue[i];
        }
    }

    Queue& operator=(const Queue& other)
    {
        if (this == &other)
        {
            return *this;
        }

        delete []_pQue;

        _size = other._size;
        _front = other._front;
        _rear = other._rear;
        _pQue = new int[other._size];
        for (int i = _front; i != _rear; i = (i + 1) % _size)
        {
            _pQue[i] = other._pQue[i];
        }

    }

    ~Queue()
    {
        delete[]_pQue;
        _pQue = nullptr;
    }

    void push(int val)
    {
        if (full())
        {
            resize();
        }
        _pQue[_rear] = val;
        _rear = (_rear + 1) % _size;
    }

    void pop()
    {
        if (empty())
        {
            return;
        }
        _front = (_front + 1) % _size;
    }

    int front()
    {
        return _pQue[_front];
    }

    bool full()
    {
        return ((_rear + 1) % _size == _front);
    }

    bool empty()
    {
        return _front == _rear;
    }
    void resize()
    {
        int* ptmp = new int[_size * 2];
        int index = 0;
       // for (int i = _front,j=0; i != _rear; i = (i + 1) % _size,j++)
        for (int i = _front; i != _rear; i = (i + 1) % _size)
        {
            //ptmp[j] = _pQue[i];

            ptmp[index++] = _pQue[i];
        }
        delete[]_pQue;
        _pQue = ptmp;

        _size = _size * 2;
        _front = 0;
        _rear = index;
    }
private:
    int* _pQue;
    int _front;
    int _rear;
    int _size;     // �ܴ�С
};


int main()
{
    Queue queue;
    for (int i = 0; i < 20; ++i)
    {
        queue.push(rand() % 100);
    }

    while (!queue.empty())
    {
        std::cout << queue.front() << " ";
        queue.pop();
    }
    std::cout << std::endl;


    Queue queue2 = queue;

    return 0;
}
#endif

#if 0
// 1.String����
class String
{
public:
    String(const char* str = nullptr) // ��ͨ���캯��
    {
        if (str != nullptr)
        {
            m_data = new char[strlen(str) + 1];  // + 1 Ϊ�˸�'\0' Ԥ��λ��
            strcpy(this->m_data, str);
        }
        else
        {
            m_data = new char[ 1];    //             ��֤String������һ����Ч�Ķ���m_data��Ϊnullptr��
            *m_data = '\0';           // 0
        }
    }  

    String(const String& other) // �������캯��
    {
        m_data = new char[strlen(other.m_data) + 1];
        strcpy(this->m_data, other.m_data);
    }
    ~String() // ��������
    {
        delete []m_data;
        m_data = nullptr;
    }

    // ��ֵ���غ���        // ����String&��Ϊ��֧������operator=��ֵ��   ����ΪvoidҲ����
    String& operator=(const String& other)
    {
        if (this == &other)
        {
            return *this;
        }

        delete []m_data;

        m_data = new char[strlen(other.m_data) + 1];
        strcpy(this->m_data, other.m_data);

        return *this;
    }

private:
    char* m_data; // ���ڱ����ַ���
};
//���д String ������ 4 ��������

int main()
{
    // ���ô�const char*�����Ĺ��캯��
    String str1;
    String str2("hello");   // ����һ��
    String str3 = "world";

    // ���ÿ������캯��
    String str5 = str3;
    String str4(str3);

    // ���ø�ֵ���غ���
    /*
    str1 = str2
    str1.operator=(str2)   ===> void
    str3 = void;   //����  ����Ҫ����String&��Ϊ��֧�ֿ���������ֵ

    str1 = str2
    str1.operator=(str2)   ===> str1
    str3 = str1;   //�̣�  ����Ҫ����String&��Ϊ��֧�ֿ���������ֵ
    */
    str3 = str1 = str2;

    return 0;
}
#endif



//=========================================================== 4.���չ��캯���ĳ�ʼ���б�=====================================

#if 0
//2.
class Test
{
public:
    // ��OOP����У��ܰѳ�Ա����д�ڳ�ʼ�������г�ʼ��������д�ڳ�ʼ���б���
    Test(int data = 10):mb(data),ma(mb){}
    void show()
    {
        std::cout << "ma:" << ma << " mb:" <<mb << std::endl;
    }
private:
    //��Ա�����ĳ�ʼ�������Ƕ����˳���йأ��͹��캯����ʼ���б��г��ֵ��Ⱥ�˳���޹أ���1
    int ma;
    int mb;
};

int main()
{
    Test test;
    test.show();   // ma:-858993460 mb : 10
    return 0;
}
#endif

// 1.
#if 0
/*
������
*/
class CDate
{
public:
    CDate(int y,int m,int d)
    {
        _year = y;
        _month = m;
        _day = d;
    }

    void show()
    {
        std::cout << _year << "/" << _month << "/" << _day << std::endl;
    }
private:
    int _year;
    int _month;
    int _day;
};

/*
���캯���ĳ�ʼ���б�:����ָ����ǰ�����Ա�����ĳ�ʼ����ʽ������ʱ�Գ�Ա������ԣ���������Ҫָ����Ա����Ĺ��췽ʽ��

CDate��Ϣ  CGoods��Ʒ��Ϣ��һ����  a part of...  ��ϵĹ�ϵ
*/

class CGoods
{
public:
    //CDate�� : û�к��ʵ�Ĭ�Ϲ��캯������   ====> �������ָ��CDate�Ĺ��캯��
    CGoods(const char* n,int a,double p, int y, int m, int d)
        :_date(y,m,d)        // 1.���캯���ĳ�ʼ���б�  ����ִ�У�         CDate _date(y,m,d)  ָ��_date����Ĺ��췽ʽ
        ,_amount(a)          // �ڳ�ʼ���б�д   �൱��   int _amount = a;   ���������ʱ�����˳�ʼ��  ֱ�ӳ�ʼ��
        ,_price(p)
    {
        // 2.��ǰ�����͹��캯����  ����ִ�У�
        // ��ʼ���б�ֻ��ִ�м򵥵ĳ�ʼ������������ú���strcpy()�ĳ�ʼ�������ڹ��캯����ʼ���б���
        strcpy(_name, n);
       // _amount = a;          // �ں�����д    �൱��   int _amount;  _amount=a;   // �ȶ���_amount,����a��_amount��ֵ      ���ַ�ʽ���ڱ������������ͣ���ָ��ִ������û����ģ����Կ����ָ�
       // _price = p;
        //_date = CDate(y,m,d);    // �ȹ���һ��CDate�����ٸ�_date����ֵ     
        
        /*
        ���ַ�ʽ���ڱ������������ͣ���ָ��ִ������û����ģ����Կ����ָ�
        �����Զ�������(������)��CDate _date;  _date = CDate(y,m,d); ����_dateʱ�������Ĭ�Ϲ��캯��������û��Ĭ�Ϲ��죬���Ա�������  ���Ա���ѳ�Ա����ĳ�ʼ�����ڳ�ʼ���б���
        */
    }
    

    void show()
    {
        std::cout << "name:" << _name << std::endl;
        std::cout << "amount:" << _amount << std::endl;
        std::cout << "price:" << _price << std::endl;
        _date.show();
    }
private:
    char _name[20];
    int _amount;
    double _price;
    CDate _date;   // ��Ա����    ����������������֣�1.�����ڴ� 2.���ù��캯��    
    // [��C++����һ������û��ָ�����Ǹ����캯�������������Զ�����Ĭ�Ϲ��캯������CDate�����Զ����˹��캯������û��Ĭ�Ϲ��캯�������Ա���//CDate�� : û�к��ʵ�Ĭ�Ϲ��캯������
    // ���������ָ������CDate����ʱ���õĹ��캯��
};

int main()
{
    CGoods goods("��Ʒ", 100, 689, 2023, 12, 28);
    goods.show();

    return 0;
}

#endif


//=========================================================== 5.������ĸ��ֳ�Ա�����Լ�����=====================================

/*
��ĸ��ֳ�Ա  -��Ա����/����

��ͨ�ĳ�Ա����  ==�� �����������һ��this�β�ָ��
1.�������������
2.���ø÷���ʱ����Ҫһ��һ������ �����������޷����õ�  ʵ�Σ�const CGoods*     �βΣ�CGoods *this��
3.����������ʶ������˽�г�Ա  

static��̬��Ա����  ==��  ��������this�β�ָ��
1.�������������
2.�����������������÷���
3.����������ʶ����˽�г�Ա���������ڲ���������ĳ�Ա��ֻ�ܵ���������static��̬��Ա��

const����Ա���� ===�� ��������const CGoods *this
1.�������������
2.��������һ��������ͨ������߳����󶼿���
3.����������ʶ����˽�г�Ա������ֻ�ܶ�����д  ������1

*/

#if 0
/*
������
*/
class CDate
{
public:
    CDate(int y, int m, int d)
    {
        _year = y;
        _month = m;
        _day = d;
    }

    void show() const
    {
        std::cout << _year << "/" << _month << "/" << _day << std::endl;
    }
private:
    int _year;
    int _month;
    int _day;
};

class CGoods
{
public:
    //CDate�� : û�к��ʵ�Ĭ�Ϲ��캯������   ====> �������ָ��CDate�Ĺ��캯��
    CGoods(const char* n, int a, double p, int y, int m, int d)
        :_date(y, m, d)        // 1.���캯���ĳ�ʼ���б�  ����ִ�У�         CDate _date(y,m,d)  ָ��_date����Ĺ��췽ʽ
        , _amount(a)          // �ڳ�ʼ���б�д   �൱��   int _amount = a;   ���������ʱ�����˳�ʼ��  ֱ�ӳ�ʼ��
        , _price(p)
    {
        strcpy(_name, n);
        _count++;   // ��¼���в������¶��������
    }

    // ��ͨ��Ա����   (�������޷����ã����������ʵ�ε�thisָ���� const CGoods*,����ͨ�������β�thisָ��Ϊ CGoods* !!!!!!!!)
    void show()      //��ӡ��Ʒ˽�е���Ϣ      CGoods *this
    {
        std::cout << "name:" << _name << std::endl;
        std::cout << "amount:" << _amount << std::endl;
        std::cout << "price:" << _price << std::endl;
        _date.show();
    }

    // ����Ա����    ֻҪ��ֻ�������ĳ�Ա������һ·ʵ�ֳ�const����Ա������������ͨ���󳣶����ܵ��ã�   
    void show() const    //��ӡ��Ʒ˽�е���Ϣ      const CGoods *this(thisָ�뱻����Ϊconst)
    {
        std::cout << "name:" << _name << std::endl;
        std::cout << "amount:" << _amount << std::endl;
        std::cout << "price:" << _price << std::endl;
        _date.show();     // ���Ҳ��Ҫ����Ϊconst
    }

    // ��̬��Ա����     û��thisָ���
    static void showCGoodsCount()    // ��ӡ����������Ʒ�������Ϣ 
    {
        std::cout << "������Ʒ�����������ǣ�" << _count << std::endl;
        // ��̬�����޷�������ͨ�ĳ�Ա�����ģ�������
    }
private:
    char _name[20];
    int _amount;
    double _price;
    CDate _date;   // ��Ա����    ����������������֣�1.�����ڴ� 2.���ù��캯��    

    static int _count;   // �����ڶ��󣬶��������༶���   ���� ������¼��Ʒ�����������    �����ݶΣ�.data  .bss��

};

// static��Ա����һ��Ҫ��������ж��岢�ҳ�ʼ��
int CGoods::_count = 0;

int main()
{
    CGoods goods1("��Ʒ1", 100, 689, 2023, 12, 28);
    goods1.show();

    CGoods goods2("��Ʒ2", 100, 689, 2023, 12, 28);
    goods2.show();

    CGoods goods3("��Ʒ3", 100, 689, 2023, 12, 28);
    goods3.show();

    CGoods goods4("��Ʒ4", 100, 689, 2023, 12, 28);
    goods4.show();

    // ͳ��������Ʒ��������
    CGoods::showCGoodsCount();

    const CGoods good5("����Ʒ��Ʒ5", 100, 35.0, 2019, 5, 12);
     good5.show();   // good5.show()    CGoods*   <==== const CGoods *     ��    ===�� ������� ====�� ���β�ָ����Ϊconst CGoods*

    // good5.show();   // good5.show()    CGoods*   <==== const CGoods *    
    return 0;
}
#endif


//=========================================================== 6.ָ�����Ա��ָ��=====================================
/*
ָ�����Ա����Ա�����ͳ�Ա��������ָ��

*/

#if 0
class Test
{
public:
    void func() { std::cout << "call Test::func" << std::endl; }
    static void static_func(){ std::cout << "call Test::static_func" << std::endl; }
    int ma;

    static int mb;    // ����������
};

// static��Ա����һ��Ҫ��������ж��岢�ҳ�ʼ��
int Test::mb = 0;    

int main()
{
    Test t1;
    Test* t2 = new Test();


    // ָ���Ա������ָ��
    // ����ʼ���� : �޷��ӡ�void(__cdecl Test::*)(void)��ת��Ϊ��void(__cdecl*)(void)��
    //void(*pfunc)() = &Test::func;
    //(*pfunc)();

    void(Test::*pfunc)() = &Test::func;
    (t1.*pfunc)();    // call Test::func
    (t2->*pfunc)();   // call Test::func

    // ��ζ��庯��ָ��ָ�����static��Ա����
    void(* pfunc1)() = &Test::static_func;
    (*pfunc1)();   //call Test::static_func



#if 0    // ָ���Ա������ָ��
    //"int Test::*" ���͵�ֵ�������ڳ�ʼ�� "int *" ���͵�ʵ��
    // int* p = &Test::ma;

    int Test::* p = &Test::ma;     // ����ָ��ָ�������ͨ��Ա����   ��Ҫ��һ�����������
    t1.*p = 20;
    std::cout << t1.*p << std::endl;   // 20

    t2->*p = 30;
    std::cout << t2->*p << std::endl;   // 30


    int* p1 = &Test::mb;   // ��̬��Ա����������ʹ����ָͨ��ָ�򼴿�
    *p1 = 40;
    std::cout << *p1 << std::endl;    // 40
#endif

    delete t2;
    return 0;
}
#endif



















