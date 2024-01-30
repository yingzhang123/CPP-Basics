#include <iostream>
#include <memory>

/*
代理模式是一种结构型设计模式，其目的是通过创建一个代理类来控制对其他对象的访问。
代理模式可以在不改变原始类的情况下，对其进行扩展、增强或限制。
*/
/*
代理Proxy模式：通过代理类，来控制实际对象的访问权限
*/

#if 0
class VideoSite // #1 抽象类
{
public:
	virtual void freeMovie() = 0;         // 免费电影
	virtual void vipMovie() = 0;          // vip电影
	virtual void ticketMovie() = 0;       // 用券观看电影
};

class FixBugVideoSite : public VideoSite      // #2 委托类
{
public:
	virtual void freeMovie()
	{
		std::cout << "观看免费电影" << std::endl;
	}
	virtual void vipMovie()
	{
		std::cout << "观看vip电影" << std::endl;
	}
	virtual void ticketMovie()
	{
		std::cout << "观看用券电影" << std::endl;
	}
};


// 代理类 代理FixBugVideoSite
class FreeVideoSiteProxy : public VideoSite    // # 代理类
{
public:
	FreeVideoSiteProxy() { pVideo = new FixBugVideoSite(); }
	~FreeVideoSiteProxy() { delete pVideo; }
	void freeMovie()           // 免费电影
	{
		pVideo->freeMovie();     // 通过地理对象的freeMovie,来访问真正委托类对象的freeMovie
	}
	void vipMovie()
	{
		std::cout << "您目前只是普通游客，需要升级成VIP，才能观看VIP电影" << std::endl;
	}
	void ticketMovie()
	{
		std::cout << "您目前只是普通游客，需要购买电影卷，才能观看VIP电影" << std::endl;
	}
private:
	VideoSite* pVideo;   // #4        代理类和委托类是组合关系 （不用指针直接定义对象也是可以的）      以组合的方式使用代理对象
};

// 代理类 代理FixBugVideoSite
class VIPVideoSiteProxy : public VideoSite
{
public:
	VIPVideoSiteProxy() { pVideo = new FixBugVideoSite(); }
	~VIPVideoSiteProxy() { delete pVideo; }
	void freeMovie()           // 免费电影
	{
		pVideo->freeMovie();   // 通过地理对象的freeMovie,来访问真正委托类对象的freeMovie
	}
	void vipMovie()
	{
		pVideo->vipMovie();
	}
	void ticketMovie()
	{
		std::cout << "您目前只是普通游客，需要购买电影卷，才能观看VIP电影" << std::endl;
	}
private:
	VideoSite* pVideo;       // 代理类和委托类是组合关系
};


// 这些都是通用的API接口，使用的都是基类的指针或者引用
void watchMovice(std::unique_ptr<VideoSite>& ptr)
{
	ptr->vipMovie();
	ptr->freeMovie();
	ptr->ticketMovie();
}

int main()
{
	std::unique_ptr<VideoSite> p(new FreeVideoSiteProxy());  // # 5 实际使用的都是代理对象   客户直接访问代理对象
	//watchMovice(std::move(p));            // void watchMovice(std::unique_ptr<VideoSite>ptr)

	std::unique_ptr<VideoSite> p2(new VIPVideoSiteProxy());

	watchMovice(p);
	watchMovice(p2);


	return 0;
}
#endif

/*

这段代码实现了代理模式的一个简单示例，模拟了一个视频网站的情景，包括免费电影、VIP电影和用券观看电影。

以下是代码的主要结构和作用：
VideoSite 是一个抽象类，定义了观看电影的接口，包括免费电影、VIP电影和用券观看电影。

FixBugVideoSite 是具体的委托类，实现了 VideoSite 接口，提供了真正的观影功能。

FreeVideoSiteProxy 和 VIPVideoSiteProxy 是代理类，它们也实现了 VideoSite 接口。
这两个代理类分别代理免费电影和VIP电影的观看
。在代理类中，通过包含一个 FixBugVideoSite 对象，实现对委托类的调用。                            <=================
*/