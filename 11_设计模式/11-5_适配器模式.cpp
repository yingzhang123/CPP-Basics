#include <iostream>
#include <string>


/*
适配器模式：让不兼容的接口可以在一起工作
*/

/*
适配器模式（Adapter Pattern）是一种结构性设计模式，它允许接口不兼容的类能够一起工作。
适配器模式的目标是使原本由于接口不匹配而无法在一起工作的类能够合作无间。

适配器通常包括两种类型：
对象适配器： 通过组合来实现适配器。适配器类中包含要适配的类的实例，并在适配器的方法中调用这个实例的方法。
类适配器： 使用多重继承或接口实现来实现适配器。适配器类同时继承了需要适配的类并实现目标接口。

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

// TV01 表示支持VGA接口的投影仪
class TV01 : public VGA
{
public:
	void play()
	{
		std::cout << "通过VGA接口连接投影仪，进行视频播放" << std::endl;
	}
};

// 进了一批新的投影仪，但是新的投影仪都是只支持HDMI接口
class TV02 : public HDMI
{
public:
	void play()
	{
		std::cout << "通过HDMI接口连接投影仪，进行视频播放" << std::endl;
	}
};


// 实现一个电脑类（值支持VGA接口）
class Computer
{
public:
	// 由于电脑只支持VGA接口，所以该方法的参数也只能支持VGA接口的指针/引用
	void playVideo(VGA* pVGA)
	{
		pVGA->play();
	}
};

/*
方法一：换一个支持HDMI接口的电脑，这个就代码重构
方法二：买一个转换头（适配器），能够把VGA信号转成HDMI信号，这个叫添加适配器类
*/
// 由于电脑（VGA接口）和投影仪（HDMI）无法直接相连，所以需要添加适配器类
class VGAToHDMIAdapter : public VGA   // 继承VGA
{
public:
	VGAToHDMIAdapter(HDMI* p) : pHdmi(p) {}
	void play()     //该方法相当于转换头，做不同接口的信号转换
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