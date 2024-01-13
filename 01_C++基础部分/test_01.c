#include<stdio.h>

#if 0
int sum(int a, int b); 

// C调用C++代码
int main()
{
    int ret = sum(10, 20);
    printf("ret:%d\n", ret);
    return 0;
}
#endif


/*
在C中,const修饰的量，可以不用初始化，但是不能再作为左值赋值。（虽然不用初始化，但还是建议初始化）
不叫常量，叫常变量。除了不能作为左值，其他和变量没什么差别。
*/

void main03()
{
    const int a;   // const只是语法上保证a不能作为左值被修改  其内存是可以修改的
    //a = 20;  // 报错 C++ 表达式必须是可修改的左值
    // int arr[a] = {}; // ×


    int* p = (int*)&a;
    *p = 30;
    // 30,30,30
    printf("%d,%d,%d \n", a, *p, *(&a));
}


