// 01_C++基础部分.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

#include <new> // std::nothrow
//==============================================  形参带默认值的函数  ===================================================================
/*
======》1.形参带默认值的函数
1.给默认值的时候，只能从右向左给
2.调用效率的问题
3.定义处可以给形参默认值，声明也可以给形参默认值（定义处给，声明不给，不行；声明处给，定义出不给也可以）
4.形参给默认值的时候，不管是定义处给，还是声明处给，形参默认值只能出现一次 （否则报重定义默认参数的错误）
*/
// int sum(int 10, int);   //×，默认形参只能从右到左给


//int sum(int a = 10, int b = 20);
// int sum(int a, int b=10);  // “sum”: 重定义默认参数: 参数 1

#if 0
int sum(int a ,int b = 20);     // 函数声明可以多次！！
int sum(int a = 10, int b);
int main()
{
    int a = 10;
    int b = 20;
    /*
    mov eax,dword ptr[ebp-8]     // b, 参数右向左入栈
    push eax
    mov ecx,dword ptr[ebp-4]     // a,
    push ecx
    call sum
    */
    int ret = sum(a, b);
    std::cout << "ret:" << ret << std::endl;

    /*
    push 14H
    mov ecx,dword ptr[ebp-4]     // a,
    push ecx
    call sum
    */
    ret = sum(a);  //形参使用默认值
    std::cout << "ret:" << ret << std::endl;


    /*   //比上面少了两句指令，效率高一点
    push 14H
    push 0AH
    call sum
    */
    ret = sum();  //形参使用默认值
    std::cout << "ret:" << ret << std::endl;
}


//int sum(int a = 10, int b = 20)
int sum(int a, int b)
{
    return a + b;
}
#endif // 0

//============================================= inline内联函数 和 普通函数的区别 ====================================================================
/*
======》 2.inline内联函数 和 普通函数的区别
①inline内联函数：在编译的过程中，就没有函数调用开销了，
在函数的调用点直接把函数的代码进行展开处理了

如果这个函数在短时间内大量调用，而且这个函数是非常简单的，尽量设置为内联函数

②
inline函数不再生成相应的函数符号

③
inline只是建议编译器把这个函数处理成内联函数，最终是否处理为内联由编译器自己来决定！！！！！！！！！！！！！！！
但是不是所有的inline都会被编译器处理成内联函数====》递归


在debug版本上，inline是不起作用的; inline函数只有在release版本下才能出现
*/

#if 0
inline int sum(int a, int b)       //*.o    sum_int_int    .text
{
    return a + b;
}

int main()
{
    int a = 10;
    int b = 20;
    
    int ret = sum(a, b);
    //此处有标准的函数调用过程  参数压栈，函数栈帧的开辟和回退的过程
    // 有函数调用的开销

    int ret = a + b;

    return 0;
}
#endif // 0



//======================================================  函数重载  =========================================================
/*
======》3.函数重载
1、C++为什么支持函数重载，c语言不支持函数重载？
C++代码产生函数符号的时候，函数名+参数列表类型组成堵塞         comparae_int_int
C代码产生函数符号的时候，函数名来决定符号名

2、函数重载需要注意什么？


3、C++和C语言代码之间如何互相调用？


什么是函数重载？
①一组函数，其中函数名相同，参数列表的个数或者类型不同，那么这一组函数就被称作--函数重载
②一组函数要称的上重载，一定先是处在同一作用域当中的
③const或者volatile的时候,是怎样影响形参类型的？？？？？？？
④一组函数，函数名相同，参数列表也相同，仅仅是返回值不同？不叫重载


请你解析一下，什么是多态？
静态（编译时期）的多态：函数重载，模板
动态（运行时期）的多态：

C调用C++ ： 无法直接调用了！！！！   怎么办？ 把C++源代码括在extern"C{}里面
C++调用C代码：无法直接调用了！！！！       怎么办？ 把C函数的声明括在extern"C"{}里面， 就可以调用了

// __FILE__  // 编译器内置的宏
// __LINE__
// 只要是C++编译器，都内置了__cplusplus这个宏名
*/  
// 这样写更灵活，无论C编译器还是C++编译器，这个函数都可以直接被C代码调用，生成都是C接口的函数
#if 0 
#ifdef __cplusplus
extern"C" {
#endif 
    int sum(int a, int b) {
        return a + b;
    }
#ifdef __cplusplus
}
#endif 
#endif




#if 0 
extern"C"    // 标明这个函数一C风格代码编译，函数符号生成按C的风格生成，给C代码调用
{
    int sum(int a, int b) {     
        return a + b;
    }
}
#endif

#if 0
void func(int a){}
// int func(int a) {};  // C++ 无法重载仅按返回类型区分的函数
// void func(const int a){}  //报错，int func(int)已有主体



// 发生错误  ，// LNK2019	无法解析的外部符号 " 
// int __cdecl sum(int,int)" (? sum@@YAHHH@Z)，函数 main 中引用了该符号	
extern"C"   // 告诉编译器按c语言生成sum的符号
{
    int sum(int a, int b);  // 该函数定义在test_01.c中       //符号：sum_int_int   
}  

int main()
{
    int ret = sum(10, 20);
    std::cout << "ret:" << ret << std::endl;
    return 0;
}
#endif

#if 0
bool compare(int a, int b)
{
    std::cout << "comparae_int_int" << std::endl;
    return a > b;
}

bool compare(double a, double b)
{
    std::cout << "comparae_double_double" << std::endl;
    return a > b;
}

bool compare(const char* a, const char* b)
{
    std::cout << "comparae_char*_char*" << std::endl;
    return strcmp(a, b) > 0;
}

int main()
{

    bool compare(int a, int b);  //函数的声明        作用域

    compare(10, 20);
    compare(10.0, 20.0);
    ::compare("ssssss", "ddddddd");  
    return 0;
}
#endif


//============================================= 全面掌握const的用法 ====================================================================
/*
======》4.全面掌握const的用法
（1）const怎么理解？ 
const修饰的变量不能够再作为左值！！！初始化完成后，值不能被修改！！！

（2）C和C++中const的区别是什么？
const的编译方式不同，C中，const就是当作一个变量来编译生成指令的，
C++中，所有出现const常量名字的地方，都被常量的初始化替换了

C++的const
必须初始化，叫常量！！！！！！

使用变量初始化，那么就退化为常变量了    因为初始值不是立即数，是一个变量
*/

#if 0
int main()
{
    //int b = 20;
   // const int a=b;    // 这样常量就退化为常变量了，
    //int arr[a] = {}; // √

    const int a=20;   
    //int arr[a] = {}; // √


    int* p = (int*)&a;
    *p = 30;
    // 20,30,20 
    printf("%d,%d,%d \n", a, *p, *(&a));
}
#endif


//============================================  掌握const和一二级指针的结合应用 =====================================================================
/*
======》5.掌握const和一二级指针的结合应用

const修饰的量 叫常量
普通变量和区别是什么？   C++有两点区别？ 1.编译方式不同  2.不能作为左值了

C++;
const修饰的量常出现的错误是：
①常量不能再作为左值  《=== 直接修改常量的值
②不能把常量的地址泄漏给一个普通指针或者普通的引用变量 《=== 可以间接修改常量的值


const和一级指针的结合：有两种情况
C++的语言规范：const修饰的离它最近的类型
①const int* p=&a;  ==>*p = 20; p=&b;
可以任意指向不同的int类型的内存，但是不能通过指针间接修改指向的内存和值
②int const*p;  情况通①相同

③int *const p = &a;  // const 修饰的是 int*
这个指针现在是常量，不能在指向其他内存，但是可以通过指针解引用修改指向的内存的值

④const int * const p =&a;   // ①和③的结合



const如果右边没有指针*的话，const是不参与类型的！
总结const和指针的类型转换公式
int* <= const int*   // 是错误的！    不能把const int* 赋值给int*
const int* <== int*   // 是可以的！


int** <== const int**   // 是错误的！  
const int** <==int **    // 是错误的！  

int** <== int*const*    // 是错误的！ 
int*const* <== int**   // 是可以的！

*/

void main04()
{
    // 1、
    //const int a = 10;
    //int* p = &a;  // const int* 类型的值不能用于初始化 int* 类型的实体


    // 2、
    //int a = 10;
    //int* p = &a;
    //const int* p2 = &a;  //const int*  <== int*
    //int* const p3 = &a;  // int*  <=== int*   可以转换
    //int* p4 = p3;   // int*  <=== int*


    //// const如果右边没有指针*的话，const是不参与类型的
    //int* q1 = nullptr;
    //int* const q2 = nullptr;
    ////int * __ptr64
    ////int* __ptr64
    //std::cout << typeid(q1).name() << std::endl;
    //std::cout << typeid(q2).name() << std::endl;
}


/*
const和二级指针的结合

*/
int main05()
{
    return 0;
}


//======================================================== C++左值引用和初识右值引用 =========================================================
/*
======》6.C++左值引用和初识右值引用
C++的引用    引用和指针打算区别
1.左值引用和右值引用


2.引用的实列


引用是一种更安全的指针
1.引用是必须初始化的，指针可以不初始化
2.引用只有一级引用，没有多级引用；指针可以有一级指针，也可以有多级指针
3.定义一个引用变量，和定义一个指针变量，其汇编指令是一模一样的；
通过引用变量修改所引用内存的值，和通过指针解引用修改指针指向的内存的值，其底层指令也是一模一样的


//右值引用
1.int &&C=20;专门用来引用右值类型，指令上，可以自动产生临时量，然后直接引用临时量 
2.右值引用变量本身是一个左值，只能用左值引用来引用它
3.不能用一个右值应用变量，来引用一个左值
*/



#if 0
int main()
{
#if 0
    int a = 10;
    int* p = &a;
    int& b = a;

    *p = 20;
    //20 20 20
    std::cout << a << " " << *p << " " << b << std::endl;

    b = 30;
    //30 30 30
    std::cout << a << " " << *p << " " << b << std::endl;
    /*
    int a = 10;
    00007FF7B7496A1D  mov         dword ptr [a],0Ah  
        int* p = &a;
    00007FF7B7496A24  lea         rax,[a]  
    00007FF7B7496A28  mov         qword ptr [p],rax  
        int& b = a;
    00007FF7B7496A2C  lea         rax,[a]  
    00007FF7B7496A30  mov         qword ptr [b],rax 
    */
#endif
}
#endif


#if 0
int main()
{
    int array[5] = {};
    int* p = array;
    // 定义一个引用变量，来应用array数组
    // int* p = &array;  // E0144	"int (*)[5]" 类型的值不能用于初始化 "int *" 类型的实体
    int(*p1)[5] = &array;
    int(&q)[5] = array;    // 数组引用    

    std::cout << sizeof array << std::endl;  //20
    std::cout << sizeof p << std::endl;      // 8
    std::cout << sizeof p1 << std::endl;      // 8
    std::cout << sizeof q << std::endl;      // 20
    return 0;
}
#endif

#if 0
int main() 
{
    int a = 10;  // 左值：它右内存，有名字，值可以修改的
    int& b = a;

    // int& a = 20;  // 20是右值：没内存，没名字
    // C++11提供了右值引用
    int&& c = 20;
    c = 30;

    int& e = c;  // 右值引用变量本身是一个左值
}
#endif

// =====================================================  new和delete  ============================================================
/*
new和delete
new和malloc的区别是什么？

delete和free的区别是什么？

malloc和free，称作C的库函数
new和delete，称作运算符

new不仅可以左内存开辟，还可以作内存初始化操作
malloc开辟内存失败，是通过返回值和nullptr做比较；而new开辟内存失败，则是通过抛出bad_alloc类型的异常来判断的。

因为new开辟内存的时候是指定类型的，所以指针不用类型强转；malloc仅仅是按字节开辟内存空间，所以返回的指针需要类型强转。  
*/

int main02()
{
    // new有多少种？
    int* p1 = new int(20);   // 抛出异常的new 

    int* p2 = new (std::nothrow) int;  // 不抛出异常的new，通过malloc一样，可以通过判断指针是否为空，判断内存是否开辟成功

    //int* p3 = new const int(40);    //×，在堆上申请一个常量

     const int* p3 = new const int(40);  


     // 定位new
     int data = 0;
     int* p4 = new (&data) int(50);       //在指定地址下划分空间
     std::cout << "data:" << data << std::endl;   // data:50


#if 0
    int* p = (int*)malloc(sizeof(int));   // malloc函数返回指针是void*，需要强制类型转换
    if (p == nullptr)
    {
        return -1;
    }
    *p = 20;
    free(p);

    int* p1;
    try {
        p1 = new int(20);  // 内存初始化
    }
    catch(const std::bad_alloc &e)
    {

    }
    delete p1;  


    //定义数组
    int* q = (int*)malloc(sizeof(int) * 20);
    if (q == nullptr)
    {
        return -1;
    }
    free(q);

    int* q1 = new int[20];  //20个int,不初始化
    int* q2 = new int[20]();  //20个int,初始化

    delete[] q1;
    delete[] q2;

    return 0;
#endif
}









// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
