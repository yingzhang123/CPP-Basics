#include<iostream>

using namespace std;


/*
C++11 ��׼������� �ܽ�һ��
һ���ؼ��ֺ��﷨
1��auto:	���Ը�����ֵ���Ƶ�����ֵ�����ͣ�Ȼ����߱���������Ҳ��֪����
2��nullptr:	��ָ��ר�õģ��ܹ���������������     #define NULL 0
3��foreach:	���Ա������飬������
	for(Type val:container)     =======�� �ײ����ͨ��ָ����ߵ�������ʵ�ֵ�
	{
		cout<<val<<" ";
	}
4����ֵ����: move�ƶ����庯����forward��������ת��
5��ģ���һ�������ԣ�typename... A  ��ʾ�ɱ��

���������ͺ�������
function: ��������  ������װ��
bind: ����

��������ָ��
shared_ptr��weak_ptr     

�ģ�����
unordered_set��unordered_map���ײ��ǹ�ϣ��O��1����  (��������C++11�����ģ���ǰֻ��set��map(�ײ��Ǻ���� O��logN��))
array:���飨�̶���С�����飩  #include<array>                           ������vector
forward_list��ǰ��������������   #include<forward_list>             ������list(˫��ѭ������)

�塢C++���Լ���֧�ֵĶ��̱߳�� #include<thread>

*/
