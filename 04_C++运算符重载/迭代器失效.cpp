#include<iostream>
#include<vector>


#if 0 
/*
迭代器的失效问题？
1.迭代器为什么会失效？
a:当容器调用erase方法后，当前位置到容器末尾元素的所有迭代器全部失效了
b.当容器调用insert方法后，当前位置到容器末尾元素的所有迭代器全部失效了

			迭代器依然有效                        迭代器全部失效
首元素    ----------------->    插入点/删除点    ---------------->   末尾元素

c.对insert来说，如果引起容器内存扩容
					原来容器的所有迭代器就全部失效了
首元素    ----------------->    插入点/删除点    ---------------->   末尾元素


d:不同容器的迭代器是不能进行比较运算的！！！！

2.迭代器失效了以后，问题怎么解决？
对插入/删除点的迭代器进行更新操作
*/


int main()
{

	std::vector<int> vec;
	for (int i = 0; i < 20; i++)
	{
		vec.push_back(rand() % 100+1);
	}

	for (int ch : vec)
	{
		std::cout << ch << " ";
	}
	std::cout << std::endl;

#if 1
	//给vec容器中所有的偶数前面添加一个小于偶数值1的数字
	auto it = vec.begin();
	//for (; it != vec.end(); ++it)
	//{
	//	if (*it % 2 == 0)
	//	{
	//		// 这里的迭代器在第一次insert之后，iterator就失效了
	//		vec.insert(it, *it - 1);   //已退出，代码为 -1073741819。
	//		//break;
	//	}
	//}


	for (; it != vec.end(); ++it)
	{
		if (*it % 2 == 0)
		{
			it = vec.insert(it, *it - 1);
			++it;      // 更新2次
		}
	}

	for (int ch : vec)
	{
		std::cout << ch << " ";
	}
	std::cout << std::endl;


#endif

#if 0
	//把vec容器中所有偶数全部删除
	auto it = vec.begin();
	//for (; it != vec.end(); ++it)
	//{
	//	if (*it % 2 == 0)
	//	{
	//		//// 迭代器失效的问题，第一次调用erase之后，迭代器it就失效了
	//		//vec.erase(it);     // insert(it,val)   erase(it)    // 已退出，代码为 -1073741819。
	//		////break;

	//	}
	//}

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
	std::cout<<std::endl;
#endif
	return 0;
}


#endif
