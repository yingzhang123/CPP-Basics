#include<iostream>

using namespace std;


/*
C++11 标准相关内容 总结一下
一：关键字和语法
1、auto:	可以根据右值，推导出右值的类型，然后左边变量的类型也就知道了
2、nullptr:	给指针专用的（能够和整数进行区别）     #define NULL 0
3、foreach:	可以遍历数组，容器等
	for(Type val:container)     =======》 底层就是通过指针或者迭代器来实现的
	{
		cout<<val<<" ";
	}
4、右值引用: move移动语义函数和forward类型完美转发
5、模板的一个新特性：typename... A  表示可变参

二：绑定器和函数对象
function: 函数对象  函数包装器
bind: 绑定器

三：智能指针
shared_ptr和weak_ptr     

四：容器
unordered_set和unordered_map（底层是哈希表O（1））  (这两个是C++11新增的，以前只有set和map(底层是红黑树 O（logN）))
array:数组（固定大小的数组）  #include<array>                           建议用vector
forward_list：前向链表（单向链表）   #include<forward_list>             建议用list(双向循环链表)

五、C++语言级别支持的多线程编程 #include<thread>

*/
