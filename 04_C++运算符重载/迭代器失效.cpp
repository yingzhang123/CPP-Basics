#include<iostream>
#include<vector>


#if 0 
/*
��������ʧЧ���⣿
1.������Ϊʲô��ʧЧ��
a:����������erase�����󣬵�ǰλ�õ�����ĩβԪ�ص����е�����ȫ��ʧЧ��
b.����������insert�����󣬵�ǰλ�õ�����ĩβԪ�ص����е�����ȫ��ʧЧ��

			��������Ȼ��Ч                        ������ȫ��ʧЧ
��Ԫ��    ----------------->    �����/ɾ����    ---------------->   ĩβԪ��

c.��insert��˵��������������ڴ�����
					ԭ�����������е�������ȫ��ʧЧ��
��Ԫ��    ----------------->    �����/ɾ����    ---------------->   ĩβԪ��


d:��ͬ�����ĵ������ǲ��ܽ��бȽ�����ģ�������

2.������ʧЧ���Ժ�������ô�����
�Բ���/ɾ����ĵ��������и��²���
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
	//��vec���������е�ż��ǰ�����һ��С��ż��ֵ1������
	auto it = vec.begin();
	//for (; it != vec.end(); ++it)
	//{
	//	if (*it % 2 == 0)
	//	{
	//		// ����ĵ������ڵ�һ��insert֮��iterator��ʧЧ��
	//		vec.insert(it, *it - 1);   //���˳�������Ϊ -1073741819��
	//		//break;
	//	}
	//}


	for (; it != vec.end(); ++it)
	{
		if (*it % 2 == 0)
		{
			it = vec.insert(it, *it - 1);
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
	//��vec����������ż��ȫ��ɾ��
	auto it = vec.begin();
	//for (; it != vec.end(); ++it)
	//{
	//	if (*it % 2 == 0)
	//	{
	//		//// ������ʧЧ�����⣬��һ�ε���erase֮�󣬵�����it��ʧЧ��
	//		//vec.erase(it);     // insert(it,val)   erase(it)    // ���˳�������Ϊ -1073741819��
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
