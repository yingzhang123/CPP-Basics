#include<iostream>


//============================================================== 1.类和对象、this指针 =====================================
/*
C++ OOP面向对象  OOP编程，this指针
C：各种各样的函数的定义   struct
C++: 类    ==》  实体的抽象类型
 
实体（属性、行为）   ====》             ADT(abstruct data type)
       |                                       |
    对象            《==== （实例化）   类（属性->成员变量   行为->成员方法）


OOP语言的四大特征是什么？
抽象    封装/隐藏     继承    多态

类    ===》   商品实体
访问限定符：public公有的    private私有的   protected保护的

*/

#if 0
// 类名首字母全部大写  成员方法和属性，首字母小写，其余大写写
const int NAME_LEN = 20;
class CGoods     //   ==》商品的抽象数据类型（不占内存空间）
{
public:          // 给外部提供公有的成员方法，来访问私有的属性 
    // 做商品的初始化用的
    void init(const char* name, double price, int amount);
    // 打印商品信息
    void show();
    // 给成员变量提供一个getXXX或setXXX的方法              类体中实现的方法，自动处理成inline内联函数※
    void setName(char* name) { strcpy(_name, name); }   // 成员方法在类体中实现
    void setPrice(double price) { _price = price; }
    void setAmount(int amount) { _amount = amount; }

    // const修饰返回指针，防止外部通过指针解引用修改对象的属性
    const char* getName() { return _name; }   
    double getPrice() { return _price; }
    int getAmount() { return _amount; }

private:         //属性一般是私有的成员变量
    char _name[NAME_LEN];
    double _price;
    int _amount;
};

// 在类外实现成员方法，一定要在方法名前加上类名作用域               （在类外实现的方法，调用和普通的方法一样，如果想写成inline，需要在前面加上inline）
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

// 字符串常量不能用普通指针接收(怕通过指针解引用修改字符串常量的值，这是不允许的！！！)，要用常指针const char*

int main()
{
    /*
    CGoods可以定义无数的对象，每一个对象都有自己的成员变量，
    但是他们共享一套成员方法

    show()     ====> 怎么知道处理那个对象的信息？
    init(name,price,amount)     =====>       怎么知道把信息初始化给哪一个对象？ 

    类的成员方法一经编译，所有的方法参数，都会加一个this，接收调用该方法的对象地址
     void init(CGoods* this, const char* name, double price, int amount);
    */

    // cl 02_C++面向对象.cpp /dlreportSingleClassLayoutCGoods     可以查看内存大小
    // 对象内存大小的时候，   对象的内存大小 ==》 只和成员变量大小有关
    CGoods good1;     // 类示例化了一个对象
    // init(&good1,"面包", 29.0, 100)     <===========
    good1.init("面包", 29.0, 100); 
    // show(&good1)
    good1.show();
    good1.setPrice(100.0);
    good1.setAmount(60);
    good1.show();

    CGoods good2;
    good2.init("自行车", 629.0, 100);
    good2.show();

    return 0;
}


#endif



//============================================================ 2.掌握构造函数和析构函数 =====================================
/*
构造函数 和 析构函数           OOP编程复习一下
OOP实现一个顺序栈


构造函数和析构函数
函数的名字和类名一样
没有返回值
*/

#if 0
// 顺序栈
class SeqStack
{
public:
    // 构造函数
    SeqStack(int size = 10)  // 是可以带参数的，因此可以提供多个构造函数 
    {
        std::cout << this<< "  " << "SeqStack()" << std::endl;
        _pstack = new int[size];
        _top = -1;
        _size = size;
    }
    // 析构函数
    ~SeqStack()    // 是不带参数的，所有析构函数只能有一个！！！
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
        }  // memcpy(ptmp,_pstack,sizeof(int)*_size);   remalloc()     // 这两个函数都是内存拷贝
        delete[] _pstack;
        _pstack = ptmp;
        _size = _size * 2;
    }
};

SeqStack gs;      // 全局对象，在定义的时候调用构造，，，在程序结束时，析构      .data

int main()
{
    /*  三块不同内存区域
    .data
    heap
    stack
    */

    SeqStack* ps = new SeqStack(60);   // 内存开辟在堆上   堆上的对象    heap      =====》malloc内存开辟 + SeqStack(60)对象构造  
    ps->push(43);
    ps->push(70);
    std::cout << ps->top() << std::endl;
    delete ps;      // 堆上的对象需要手动调用delete释放，【调用对象的析构函数，把指针对象指向外部的堆内存释放，然会再把对象的内存释放掉】
                    // 先调用ps->~SeqStack() + 然后free(ps)

    // 定义一个对象： 1、开辟内存  2、调用构造函数   
    SeqStack s;     // stack
   // s.init(5);         // 对象成员的初始化操作

    for (int i= 0; i < 15; i++)
    {
        s.push(rand() % 100);
    }

    while (!s.empty())
    {
        std::cout << s.top() << " ";
        s.pop();
    }

    //s.release();       // 释放对象成员变量占用的外部堆内存

    SeqStack s2(40);


   // s2.~SeqStack();     // 析构函数可以手动调用，构造函数不能手动调用，编译器会根据传入的参数匹配合适的构造函数      【不建议手动调用析构函数】
    // 析构函数调用以后，我们说对象不存在了
    //s2.push(30);    // 语法上没问题，但运行时会产生堆内存非法访问，程序会挂掉
    return 0;           // 函数调用结束，栈上的对象都会依次的进行析构     (调用构造和析构的顺序刚好是相反的，先构造的后析构，后构造的先析构)     // 相当于出栈和入栈的过程
}
#endif


//============================================================ 3.掌握对象的深拷贝和浅拷贝 =====================================
/*
this指针 ===》 类-》很多对象   共享一套成员方法（如何区分不同对象的？通过this指针区分对象）
成员方法一经编译，方法的参数都会添加一个this指针

构造函数：
    定义对象时，自动调用的；可以重载；构造完成，对象就产生了

析构函数：
     不带参数，不能重载；只有一个析构函数；析构完成，对象就不在了

.data的对象：程序启动时构造，程序结束时析构
heap的对象：new的时候构造，delete析构
stack的对象：在定义处构造，函数结束时析构



对象的深拷贝和浅拷贝

对象默认的拷贝构造是做内存内存的数据拷贝

浅拷贝不一定是错的，关键是对象如果占用外部资源，那么浅拷贝就出现问题了！！！！
*/


#if 0
class SeqStack
{
public:
    // 构造函数
    SeqStack(int size = 10)  // 是可以带参数的，因此可以提供多个构造函数 
    {
        std::cout << this << "  " << "SeqStack()" << std::endl;
        _pstack = new int[size];
        _top = -1;
        _size = size;
    }

    // 自定义拷贝构造函数       《==== 默认拷贝构造函数是浅拷贝，对数据成员有指针变量指向外部资源，会有问题
    SeqStack(const SeqStack& src)
    {
        // 默认拷贝构造函数    浅拷贝
        //_pstack = src._pstack;
        //_top = src._top;
        //_size = src._size;

        // 深拷贝
        std::cout << "SeqStack(const SeqStack& src)" << std::endl;
        _pstack = new int[src._size];
        for (int i = 0; i <= src._top; i++)
        {
            _pstack[i] = src._pstack[i];
        }
        _top = src._top;
        _size = src._size;
    }

    // 析构函数
    ~SeqStack()    // 是不带参数的，所有析构函数只能有一个！！！
    {
        std::cout << this << "  " << "~SeqStack()" << std::endl;
        delete _pstack;
        _pstack = nullptr;
    }

    //赋值重载函数
    void operator=(const SeqStack& src)
    {
        // 深拷贝
        std::cout << "operator=" << std::endl;
        // 防止自赋值  s1 = s1
        if (this == &src)
        {
            return;
        }

        // 需要先释放当前对象占用的外部资源          （比拷贝构造多一步）
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
        }  // memcpy(ptmp,_pstack,sizeof(int)*_size);   remalloc()     // 这两个函数都是内存拷贝
        delete[] _pstack;
        _pstack = ptmp;
        _size = _size * 2;
    }
};


int main()
{
    SeqStack s; //没有提供任何构造函数的时候，编译器会自动生成默认构造函数和默认析构函数，是空函数
    SeqStack s1(10);   // 调用带整型参数的构造函数

    // 下面这两种定义方式都是一样的（由一个栈对象构造一个新的栈对象）对象的生成一定会调用构造
    SeqStack s2 = s1;    // 调用默认拷贝构造函数    默认是拷贝构造函数，做直接内存数据的拷贝（浅拷贝）
   // SeqStack s3(s1);     // 调用默认拷贝构造函数


    // void operator=(const SeqStack& src)  //赋值函数
    s2 = s1;   // 默认的赋值函数  ==》 做直接的内存拷贝
    return 0;
}

#endif

#if 0
// 2. 循环队列       memcpy realloc 这两个用作对象的拷贝不太合适[因为存在浅拷贝问题]
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
    int _size;     // 总大小
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
// 1.String类型
class String
{
public:
    String(const char* str = nullptr) // 普通构造函数
    {
        if (str != nullptr)
        {
            m_data = new char[strlen(str) + 1];  // + 1 为了给'\0' 预留位置
            strcpy(this->m_data, str);
        }
        else
        {
            m_data = new char[ 1];    //             保证String对象是一个有效的对象（m_data不为nullptr）
            *m_data = '\0';           // 0
        }
    }  

    String(const String& other) // 拷贝构造函数
    {
        m_data = new char[strlen(other.m_data) + 1];
        strcpy(this->m_data, other.m_data);
    }
    ~String() // 析构函数
    {
        delete []m_data;
        m_data = nullptr;
    }

    // 赋值重载函数        // 返回String&是为了支持连续operator=赋值，   否则为void也可以
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
    char* m_data; // 用于保存字符串
};
//请编写 String 的上述 4 个函数。

int main()
{
    // 调用带const char*参数的构造函数
    String str1;
    String str2("hello");   // 两者一样
    String str3 = "world";

    // 调用拷贝构造函数
    String str5 = str3;
    String str4(str3);

    // 调用赋值重载函数
    /*
    str1 = str2
    str1.operator=(str2)   ===> void
    str3 = void;   //×，  所有要返回String&，为了支持可以连续赋值

    str1 = str2
    str1.operator=(str2)   ===> str1
    str3 = str1;   //√，  所有要返回String&，为了支持可以连续赋值
    */
    str3 = str1 = str2;

    return 0;
}
#endif



//=========================================================== 4.掌握构造函数的初始化列表=====================================

#if 0
//2.
class Test
{
public:
    // 在OOP编程中，能把成员变量写在初始化列中中初始化，尽量写在初始化列表中
    Test(int data = 10):mb(data),ma(mb){}
    void show()
    {
        std::cout << "ma:" << ma << " mb:" <<mb << std::endl;
    }
private:
    //成员变量的初始化和它们定义的顺序有关，和构造函数初始化列表中出现的先后顺序无关！！1
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
日期类
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
构造函数的初始化列表:可以指定当前对象成员变量的初始化方式（尤其时对成员对象而言！！！！需要指定成员对象的构造方式）

CDate信息  CGoods商品信息的一部分  a part of...  组合的关系
*/

class CGoods
{
public:
    //CDate” : 没有合适的默认构造函数可用   ====> 解决方法指定CDate的构造函数
    CGoods(const char* n,int a,double p, int y, int m, int d)
        :_date(y,m,d)        // 1.构造函数的初始化列表  （先执行）         CDate _date(y,m,d)  指定_date对象的构造方式
        ,_amount(a)          // 在初始化列表写   相当于   int _amount = a;   定义变量的时候做了初始化  直接初始化
        ,_price(p)
    {
        // 2.当前类类型构造函数体  （后执行）
        // 初始化列表只能执行简单的初始化，例如像调用函数strcpy()的初始化不能在构造函数初始化列表中
        strcpy(_name, n);
       // _amount = a;          // 在函数体写    相当于   int _amount;  _amount=a;   // 先定义_amount,在用a给_amount赋值      两种方式对于编译器内置类型，在指令执行上是没区别的（可以看汇编指令）
       // _price = p;
        //_date = CDate(y,m,d);    // 先构造一个CDate对象，再给_date对象赋值     
        
        /*
        两种方式对于编译器内置类型，在指令执行上是没区别的（可以看汇编指令）
        对于自定义类型(类类型)，CDate _date;  _date = CDate(y,m,d); 定义_date时，会调用默认构造函数，由于没有默认构造，所以报错！！！  所以必须把成员对象的初始化放在初始化列表中
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
    CDate _date;   // 成员对象    对象的生成有两部分：1.分配内存 2.调用构造函数    
    // [在C++定义一个对象没有指定用那个构造函数，编译器会自动调用默认构造函数，但CDate由于自定义了构造函数，就没有默认构造函数，所以报错：//CDate” : 没有合适的默认构造函数可用
    // 解决方法：指定定义CDate对象时调用的构造函数
};

int main()
{
    CGoods goods("商品", 100, 689, 2023, 12, 28);
    goods.show();

    return 0;
}

#endif


//=========================================================== 5.掌握类的各种成员方法以及区别=====================================

/*
类的各种成员  -成员方法/变量

普通的成员方法  ==》 编译器会添加一个this形参指针
1.属于类的作用域
2.调用该方法时，需要一个一个对象 【常对象是无法调用的  实参：const CGoods*     形参：CGoods *this】
3.可以任意访问对象的私有成员  

static静态成员方法  ==》  不会生成this形参指针
1.属于类的作用域
2.用类名作用域来调用方法
3.可以任意访问对象的私有成员，但仅限于不依赖对象的成员（只能调用其他的static静态成员）

const常成员方法 ===》 产生的是const CGoods *this
1.属于类的作用域
2.调用依赖一个对象，普通对象或者常对象都可以
3.可以任意访问对象的私有成员，但是只能读不能写  ！！！1

*/

#if 0
/*
日期类
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
    //CDate” : 没有合适的默认构造函数可用   ====> 解决方法指定CDate的构造函数
    CGoods(const char* n, int a, double p, int y, int m, int d)
        :_date(y, m, d)        // 1.构造函数的初始化列表  （先执行）         CDate _date(y,m,d)  指定_date对象的构造方式
        , _amount(a)          // 在初始化列表写   相当于   int _amount = a;   定义变量的时候做了初始化  直接初始化
        , _price(p)
    {
        strcpy(_name, n);
        _count++;   // 记录所有产生的新对象的数量
    }

    // 普通成员方法   (常对象无法调用，常对象传入的实参的this指针是 const CGoods*,而普通方法的形参this指针为 CGoods* !!!!!!!!)
    void show()      //打印商品私有的信息      CGoods *this
    {
        std::cout << "name:" << _name << std::endl;
        std::cout << "amount:" << _amount << std::endl;
        std::cout << "price:" << _price << std::endl;
        _date.show();
    }

    // 常成员方法    只要是只读操作的成员方法，一路实现成const常成员方法（这样普通对象常对象都能调用）   
    void show() const    //打印商品私有的信息      const CGoods *this(this指针被修饰为const)
    {
        std::cout << "name:" << _name << std::endl;
        std::cout << "amount:" << _amount << std::endl;
        std::cout << "price:" << _price << std::endl;
        _date.show();     // 这个也需要设置为const
    }

    // 静态成员方法     没有this指针的
    static void showCGoodsCount()    // 打印的是所有商品共享的信息 
    {
        std::cout << "所有商品的种类数量是：" << _count << std::endl;
        // 静态方法无法访问普通的成员变量的！！！！
    }
private:
    char _name[20];
    int _amount;
    double _price;
    CDate _date;   // 成员对象    对象的生成有两部分：1.分配内存 2.调用构造函数    

    static int _count;   // 不属于对象，而是属于类级别的   声明 用来记录商品对象的总数量    在数据段（.data  .bss）

};

// static成员变量一定要在类外进行定义并且初始化
int CGoods::_count = 0;

int main()
{
    CGoods goods1("商品1", 100, 689, 2023, 12, 28);
    goods1.show();

    CGoods goods2("商品2", 100, 689, 2023, 12, 28);
    goods2.show();

    CGoods goods3("商品3", 100, 689, 2023, 12, 28);
    goods3.show();

    CGoods goods4("商品4", 100, 689, 2023, 12, 28);
    goods4.show();

    // 统计所有商品的总数量
    CGoods::showCGoodsCount();

    const CGoods good5("非买品商品5", 100, 35.0, 2019, 5, 12);
     good5.show();   // good5.show()    CGoods*   <==== const CGoods *     ×    ===》 解决方法 ====》 将形参指针设为const CGoods*

    // good5.show();   // good5.show()    CGoods*   <==== const CGoods *    
    return 0;
}
#endif


//=========================================================== 6.指向类成员的指针=====================================
/*
指向类成员（成员变量和成员方法）的指针

*/

#if 0
class Test
{
public:
    void func() { std::cout << "call Test::func" << std::endl; }
    static void static_func(){ std::cout << "call Test::static_func" << std::endl; }
    int ma;

    static int mb;    // 不依赖对象
};

// static成员变量一定要在类外进行定义并且初始化
int Test::mb = 0;    

int main()
{
    Test t1;
    Test* t2 = new Test();


    // 指向成员方法的指针
    // “初始化” : 无法从“void(__cdecl Test::*)(void)”转换为“void(__cdecl*)(void)”
    //void(*pfunc)() = &Test::func;
    //(*pfunc)();

    void(Test::*pfunc)() = &Test::func;
    (t1.*pfunc)();    // call Test::func
    (t2->*pfunc)();   // call Test::func

    // 如何定义函数指针指向类的static成员方法
    void(* pfunc1)() = &Test::static_func;
    (*pfunc1)();   //call Test::static_func



#if 0    // 指向成员变量的指针
    //"int Test::*" 类型的值不能用于初始化 "int *" 类型的实体
    // int* p = &Test::ma;

    int Test::* p = &Test::ma;     // 定义指针指向类的普通成员变量   需要加一个类的作用域
    t1.*p = 20;
    std::cout << t1.*p << std::endl;   // 20

    t2->*p = 30;
    std::cout << t2->*p << std::endl;   // 30


    int* p1 = &Test::mb;   // 静态成员不依赖对象，使用普通指针指向即可
    *p1 = 40;
    std::cout << *p1 << std::endl;    // 40
#endif

    delete t2;
    return 0;
}
#endif



















