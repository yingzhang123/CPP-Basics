#include<iostream>
#include<mutex>
using namespace std;

/*
����ģʽ��һ���಻�ܴ������ٴζ�����Զֻ�ܵõ�������һ������ʾ��

���õ��ģ�������־ģ�飬�ڴ��ģ�飬���ݿ�ģ��

����ģʽ��
����ʽ����ģʽ����û��ȡʵ������ʵ��������Ѿ�������             ���������ʽ�������࣬��������һ��ʼ�������
����ʽ����ģʽ��Ψһ��ʵ������ֱ����һ�λ�ȡ����ʱ��Ų���       �����ܻ�ӭ��
*/


//=================================================== (�̰߳�ȫ��)��������ģʽ  �����棩==========================================================
#if 0
/*
�̰߳�ȫ����������ģʽ

��Ĵ���ʹ����C++11����ľֲ���̬����������һ�ָ��Ӽ����̰߳�ȫ�ĵ���ģʽʵ�ַ�ʽ��
�����ַ�ʽ�У�instance ���ڵ�һ�ε��� getInstance ʱ����ʼ����
�������ھֲ���̬�����ĳ�ʼ����C++11��׼�����̰߳�ȫ�ģ����������������
*/
class Singleton
{
public:
    static Singleton* getInstance()    // #3 ��ȡ���Ψһʵ������Ľӿڷ���
    {
        // // ������̬�ֲ������ĳ�ʼ�����ڻ��ָ�����Ѿ��Զ�����̻߳���ָ����      ���õ������̰߳�ȫ������
        static Singleton instance;       // #2 ����һ��Ψһ�����ʵ������           // // �ֲ���̬���������ڵ�һ�ε��ã����е����ʱ��ʼ���������̰߳�ȫ��
        return &instance;
    }
private:
  
    Singleton()                       // #1 ���캯��˽�л� �������û����ⲿ��new,ջ��ȫ�֣���������ˣ�
    {
        std::cout << "Singleton()" << std::endl;
    }
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    // ɾ���������캯���͸�ֵ�������� ͨ�����������캯���͸�ֵ����������Ϊɾ����ȷ���˵������󲻻ᱻ���ơ�
};



int main()
{
    Singleton* p1 = Singleton::getInstance();
    Singleton* p2 = Singleton::getInstance();
    Singleton* p3 = Singleton::getInstance();
    std::cout << p1 << std::endl;
    std::cout << p2 << std::endl;
    std::cout << p3 << std::endl;

    return 0;
}
#endif

//=================================================== (�̰߳�ȫ��)��������ģʽ ==========================================================
#if 0
/*
ʹ�õ����༶�������std::mutex������ᵼ���ڵ��� getInstance ʱ������������ס���Ӷ������˲������ܡ�
����ڸ߲��������£�Ƶ������ getInstance��������ʵ�ֿ��ܻ��Ϊ����ƿ����
Ϊ��������ȣ������ʹ��˫������Double-Checked Locking�����ƣ�������Ҫʱ�ż��������Լ�С�������ȣ���߲������ܡ�
*/
class Singleton
{
public:
    static Singleton* getInstance()    // #3 ��ȡ���Ψһʵ������Ľӿڷ���
    {
       // std::lock_guard<std::mutex> lock(mutex_);    // ��������̫����
        if (instance == nullptr)
        {
            std::lock_guard<std::mutex> lock(mutex_);       // �� + ˫���жϣ�����
            if (instance == nullptr)
            {
                /*
                �����ڴ�
                �������
                ��instance��ֵ
                */
                instance = new Singleton();
            }
        }
        return instance;
    }
private:
    static Singleton* volatile instance;       // #2 ����һ��Ψһ�����ʵ������
    static std::mutex mutex_; // ���ڱ�֤�̰߳�ȫ
    Singleton()                       // #1 ���캯��˽�л� �������û����ⲿ��new,ջ��ȫ�֣���������ˣ�
    {
        std::cout << "Singleton()" << std::endl;
    }
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    // ɾ���������캯���͸�ֵ�������� ͨ�����������캯���͸�ֵ����������Ϊɾ����ȷ���˵������󲻻ᱻ���ơ�
};

// static��Ա����һ��Ҫ��������ж��岢�ҳ�ʼ��
Singleton* volatile Singleton::instance = nullptr;
std::mutex Singleton::mutex_;

int main()
{
    Singleton* p1 = Singleton::getInstance();
    Singleton* p2 = Singleton::getInstance();
    Singleton* p3 = Singleton::getInstance();
    std::cout << p1 << std::endl;
    std::cout << p2 << std::endl;
    std::cout << p3 << std::endl;
    /*
    Singleton()
    0064FC30
    0064FC30
    0064FC30
    */
    return 0;
}
#endif

//=================================================== ��������ģʽ ==========================================================
// ��������    �̲߳���ȫ 
#if 0
class Singleton
{
public:
    static Singleton* getInstance()    // #3 ��ȡ���Ψһʵ������Ľӿڷ���
    {
        //�ڶ��̻߳����´����̰߳�ȫ�����⡣�������߳�ͬʱ���� getInstance ���������� instance ��δ�����������п��ܵ��¶��ʵ����������Υ���˵���ģʽ�����ԭ��
        if (instance == nullptr)
        {
            /*
            �����ڴ�
            �������
            ��instance��ֵ
            */
            instance = new Singleton();
        }
        return instance;
    }
private:
    static Singleton* instance;       // #2 ����һ��Ψһ�����ʵ������
    Singleton()                       // #1 ���캯��˽�л� �������û����ⲿ��new,ջ��ȫ�֣���������ˣ�
    {
        std::cout << "Singleton()" << std::endl;
    }
    Singleton(const Singleton&) = delete;    
    Singleton& operator=(const Singleton&) = delete;
    // ɾ���������캯���͸�ֵ�������� ͨ�����������캯���͸�ֵ����������Ϊɾ����ȷ���˵������󲻻ᱻ���ơ�
};

// static��Ա����һ��Ҫ��������ж��岢�ҳ�ʼ��
Singleton* Singleton::instance = nullptr; 

int main()
{
    Singleton* p1 = Singleton::getInstance();
    Singleton* p2 = Singleton::getInstance();
    Singleton* p3 = Singleton::getInstance();
    std::cout << p1 << std::endl;
    std::cout << p2 << std::endl;
    std::cout << p3 << std::endl;
    /*
    Singleton()
    0064FC30
    0064FC30
    0064FC30
    */
    return 0;
}
#endif

//=================================================== ����ʽ����ģʽ ==========================================================
#if 0
//  ����ʽ����ģʽ��������ص�ʱ��ʹ���ʵ������˲������̰߳�ȫ�����⡣
//  ����ʽ����ģʽ: һ�����̰߳�ȫ��
//  ����ʽ����ģʽ: ��û��ȡʵ������ʵ��������Ѿ�������
class Singleton
{
public:
    static Singleton* getInstance()    // #3 ��ȡ���Ψһʵ������Ľӿڷ���
    {
        return &instance;
    }
private:
    static Singleton instance;       // #2 ����һ��Ψһ�����ʵ������
    Singleton()                       // #1 ���캯��˽�л� �������û����ⲿ��new,ջ��ȫ�֣���������ˣ�
    {
        std::cout << "Singleton()" << std::endl;
    }
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    // ɾ���������캯���͸�ֵ�������� ͨ�����������캯���͸�ֵ����������Ϊɾ����ȷ���˵������󲻻ᱻ���ơ�
};

// static��Ա����һ��Ҫ��������ж��岢�ҳ�ʼ��
Singleton Singleton::instance;                   // �൱��ȫ�ֱ�����./data��

int main()
{
    //Singleton* p1 = Singleton::getInstance();
    //Singleton* p2 = Singleton::getInstance();
    //Singleton* p3 = Singleton::getInstance();
    //std::cout << p1 << std::endl;
    //std::cout << p2 << std::endl;
    //std::cout << p3 << std::endl;

    return 0;
}

// ��һ��ʵ��
//class Singleton {
//public:
//    // ��ȡΨһʵ���ľ�̬����
//    static Singleton* getInstance() {
//        return instance;
//    }
//
//    // ������Ա���������ݳ�Ա...
//
//private:
//    // ˽�еĹ��캯��
//    Singleton() {}
//
//    // ��ֹ��������͸�ֵ����
//    Singleton(const Singleton&);
//    Singleton& operator=(const Singleton&);
//
//    // �������ʱ����Ψһʵ��
//    static Singleton* instance;
//};
//
//// ��������о�̬��Ա�����Ķ���ͳ�ʼ��
//Singleton* Singleton::instance = new Singleton();


#endif




























