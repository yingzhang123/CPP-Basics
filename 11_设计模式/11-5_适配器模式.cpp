#include <iostream>
#include <string>


/*
������ģʽ���ò����ݵĽӿڿ�����һ����
*/

/*
������ģʽ��Adapter Pattern����һ�ֽṹ�����ģʽ��������ӿڲ����ݵ����ܹ�һ������
������ģʽ��Ŀ����ʹԭ�����ڽӿڲ�ƥ����޷���һ���������ܹ������޼䡣

������ͨ�������������ͣ�
������������ ͨ�������ʵ�������������������а���Ҫ��������ʵ���������������ķ����е������ʵ���ķ�����
���������� ʹ�ö��ؼ̳л�ӿ�ʵ����ʵ������������������ͬʱ�̳�����Ҫ������ಢʵ��Ŀ��ӿڡ�

*/

#if 0
class VGA
{
public:
	virtual void play() = 0;
};

class HDMI
{
public:
	virtual void play() = 0;
};

// TV01 ��ʾ֧��VGA�ӿڵ�ͶӰ��
class TV01 : public VGA
{
public:
	void play()
	{
		std::cout << "ͨ��VGA�ӿ�����ͶӰ�ǣ�������Ƶ����" << std::endl;
	}
};

// ����һ���µ�ͶӰ�ǣ������µ�ͶӰ�Ƕ���ֻ֧��HDMI�ӿ�
class TV02 : public HDMI
{
public:
	void play()
	{
		std::cout << "ͨ��HDMI�ӿ�����ͶӰ�ǣ�������Ƶ����" << std::endl;
	}
};


// ʵ��һ�������ֵ֧ࣨ��VGA�ӿڣ�
class Computer
{
public:
	// ���ڵ���ֻ֧��VGA�ӿڣ����Ը÷����Ĳ���Ҳֻ��֧��VGA�ӿڵ�ָ��/����
	void playVideo(VGA* pVGA)
	{
		pVGA->play();
	}
};

/*
����һ����һ��֧��HDMI�ӿڵĵ��ԣ�����ʹ����ع�
����������һ��ת��ͷ�������������ܹ���VGA�ź�ת��HDMI�źţ�����������������
*/
// ���ڵ��ԣ�VGA�ӿڣ���ͶӰ�ǣ�HDMI���޷�ֱ��������������Ҫ�����������
class VGAToHDMIAdapter : public VGA   // �̳�VGA
{
public:
	VGAToHDMIAdapter(HDMI* p) : pHdmi(p) {}
	void play()     //�÷����൱��ת��ͷ������ͬ�ӿڵ��ź�ת��
	{ 
		pHdmi->play(); 
	}
private:
	HDMI* pHdmi;
};

int main()
{
	Computer computer;
	computer.playVideo(new TV01());
	computer.playVideo(new VGAToHDMIAdapter(new TV02()));

	return 0;
}

#endif