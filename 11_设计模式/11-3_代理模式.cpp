#include <iostream>
#include <memory>

/*
����ģʽ��һ�ֽṹ�����ģʽ����Ŀ����ͨ������һ�������������ƶ���������ķ��ʡ�
����ģʽ�����ڲ��ı�ԭʼ�������£����������չ����ǿ�����ơ�
*/
/*
����Proxyģʽ��ͨ�������࣬������ʵ�ʶ���ķ���Ȩ��
*/

#if 0
class VideoSite // #1 ������
{
public:
	virtual void freeMovie() = 0;         // ��ѵ�Ӱ
	virtual void vipMovie() = 0;          // vip��Ӱ
	virtual void ticketMovie() = 0;       // ��ȯ�ۿ���Ӱ
};

class FixBugVideoSite : public VideoSite      // #2 ί����
{
public:
	virtual void freeMovie()
	{
		std::cout << "�ۿ���ѵ�Ӱ" << std::endl;
	}
	virtual void vipMovie()
	{
		std::cout << "�ۿ�vip��Ӱ" << std::endl;
	}
	virtual void ticketMovie()
	{
		std::cout << "�ۿ���ȯ��Ӱ" << std::endl;
	}
};


// ������ ����FixBugVideoSite
class FreeVideoSiteProxy : public VideoSite    // # ������
{
public:
	FreeVideoSiteProxy() { pVideo = new FixBugVideoSite(); }
	~FreeVideoSiteProxy() { delete pVideo; }
	void freeMovie()           // ��ѵ�Ӱ
	{
		pVideo->freeMovie();     // ͨ����������freeMovie,����������ί��������freeMovie
	}
	void vipMovie()
	{
		std::cout << "��Ŀǰֻ����ͨ�οͣ���Ҫ������VIP�����ܹۿ�VIP��Ӱ" << std::endl;
	}
	void ticketMovie()
	{
		std::cout << "��Ŀǰֻ����ͨ�οͣ���Ҫ�����Ӱ�����ܹۿ�VIP��Ӱ" << std::endl;
	}
private:
	VideoSite* pVideo;   // #4        �������ί��������Ϲ�ϵ ������ָ��ֱ�Ӷ������Ҳ�ǿ��Եģ�      ����ϵķ�ʽʹ�ô������
};

// ������ ����FixBugVideoSite
class VIPVideoSiteProxy : public VideoSite
{
public:
	VIPVideoSiteProxy() { pVideo = new FixBugVideoSite(); }
	~VIPVideoSiteProxy() { delete pVideo; }
	void freeMovie()           // ��ѵ�Ӱ
	{
		pVideo->freeMovie();   // ͨ����������freeMovie,����������ί��������freeMovie
	}
	void vipMovie()
	{
		pVideo->vipMovie();
	}
	void ticketMovie()
	{
		std::cout << "��Ŀǰֻ����ͨ�οͣ���Ҫ�����Ӱ�����ܹۿ�VIP��Ӱ" << std::endl;
	}
private:
	VideoSite* pVideo;       // �������ί��������Ϲ�ϵ
};


// ��Щ����ͨ�õ�API�ӿڣ�ʹ�õĶ��ǻ����ָ���������
void watchMovice(std::unique_ptr<VideoSite>& ptr)
{
	ptr->vipMovie();
	ptr->freeMovie();
	ptr->ticketMovie();
}

int main()
{
	std::unique_ptr<VideoSite> p(new FreeVideoSiteProxy());  // # 5 ʵ��ʹ�õĶ��Ǵ������   �ͻ�ֱ�ӷ��ʴ������
	//watchMovice(std::move(p));            // void watchMovice(std::unique_ptr<VideoSite>ptr)

	std::unique_ptr<VideoSite> p2(new VIPVideoSiteProxy());

	watchMovice(p);
	watchMovice(p2);


	return 0;
}
#endif

/*

��δ���ʵ���˴���ģʽ��һ����ʾ����ģ����һ����Ƶ��վ���龰��������ѵ�Ӱ��VIP��Ӱ����ȯ�ۿ���Ӱ��

�����Ǵ������Ҫ�ṹ�����ã�
VideoSite ��һ�������࣬�����˹ۿ���Ӱ�Ľӿڣ�������ѵ�Ӱ��VIP��Ӱ����ȯ�ۿ���Ӱ��

FixBugVideoSite �Ǿ����ί���࣬ʵ���� VideoSite �ӿڣ��ṩ�������Ĺ�Ӱ���ܡ�

FreeVideoSiteProxy �� VIPVideoSiteProxy �Ǵ����࣬����Ҳʵ���� VideoSite �ӿڡ�
������������ֱ������ѵ�Ӱ��VIP��Ӱ�Ĺۿ�
���ڴ������У�ͨ������һ�� FixBugVideoSite ����ʵ�ֶ�ί����ĵ��á�                            <=================
*/