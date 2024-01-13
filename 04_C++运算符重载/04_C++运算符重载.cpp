
#include<iostream>


//=========================================================== 1.C++���������-ʹ��������̸������ ==========================================
/*
C++��������أ�ʹ�����������ֵúͱ�������������һ��
template<typename T>
T sum(T a,T b)
{
	return a+b;   // a.operator+(b);
}

*/

/*
������
*/
class CComplex
{
public:
	CComplex(int r = 0, int i = 0)
		:_mreal(r)
		,_mimage(i)
	{

	}

	// ָ����������ô��CComplex�����ļӷ�����         // �ṩ��ȫ�ֵ�+���������
	CComplex operator+(const CComplex& other)        
	{
		// ����������c = a + b;  �ӷ��ı���a��ֵ�����ǲ��Եģ����������߼��ϲ�����
		//this->_mimage += other._mimage;
		//this->_mreal += other._mreal;
		//return *this;

		// ����һ��
		//CComplex ctmp;       // �����¶��󣬲��ı�comp1��comp2��ֵ            ���ܷ��ؾֲ���������ú�ָ�루�ֲ������溯�������꣬ջ֡���ˣ����������ڴ��黹��ϵͳ��
		//ctmp._mreal = this->_mreal + other._mreal;
		//ctmp._mimage = this->_mimage + other._mimage;
		//return ctmp;

		// ��������������Ĵ��루������Ż���
		return CComplex(this->_mreal + other._mreal, this->_mimage + other._mimage);   // �Ա�������һ������Ĺ��������

		//��C++�У�������������û����ȷ����������´����Ķ�����������ͨ���ڱ��ʽ�е�һ����ʹ�ã����Ҳ����䵽һ������ı�����������Ҫ���ڶ��ݵġ�һ���ԵĲ���
		//��ע�⣬�����������������ط���һ��ʹ�ã���Ϊ����û�����ơ�ͨ������������������ʱ�����������ǳ��ڴ洢
	}


	void show() { std::cout << "real:" << _mreal << " image:" << _mimage << std::endl; }

	//����++
	CComplex operator++(int)
	{
		//CComplex ctmp = *this;   // �ȱ����ֵ
		//_mreal += 1;
		//_mimage += 1;
		//return ctmp;
		return CComplex(_mreal++,_mimage++);
	}

	//ǰ��++
	CComplex& operator++()   // CComplex&ֵ���ò�����ʱ����
	{
		_mreal += 1;
		_mimage += 1;
		return *this;
	}

	// +=�����
	void operator+=(const CComplex& src)
	{
		_mreal += src._mreal;
		_mimage += src._mimage;
	}


private:
	int _mreal;
	int _mimage;

	// ��������Ϊ��Ԫ�������Ա����ܹ����ʶ����˽�г�Ա
	friend CComplex operator+(const CComplex& lrs, const CComplex& rhs);
	friend std::ostream& operator<<(std::ostream& out, const CComplex& src);
	friend std::istream& operator>>(std::istream& in,CComplex& complex);
};

CComplex operator+(const CComplex& lrs, const CComplex& rhs)       
{
	return CComplex(lrs._mreal + rhs._mreal, lrs._mimage + rhs._mimage);
}

// ȫ�ֵ���������      ��������ͨ���� std::ostream&����֧����ʽ���
std::ostream& operator<<(std::ostream& out,const CComplex& src)
{
	//out << src._mreal << " + " << src._mimage << "i" << std::endl;
	out << "mreal:" <<src._mreal << " mimage:" << src._mimage << std::endl;

	return out;
}

// ���� CComplex& complex ���ܱ�����Ϊ const��������Ϊ�����������Ŀ�����޸Ĵ��ݸ����Ķ��󣬼����������ж�ȡ���ݲ�����洢�� CComplex ������
std::istream& operator>>(std::istream& in, CComplex& complex)
{
	// ���������ж�ȡʵ�����鲿
	in >> complex._mreal >> complex._mimage;
	return in;
}

int main02()
{
	CComplex comp1(10, 10);
	CComplex comp2(20, 20);

	//               comp1.operator+(comp2)   �ӷ�����������غ���                             �����ơ� + ��:��CComplex����������������Ԥ����������ɽ��յ����͵�ת��
	CComplex comp3 = comp1 + comp2;
	//CComplex comp4 = comp1.operator+(comp2);   // ����дҲ���� 
	comp3.show();    // real:30 image30
	//comp4.show();    // real:30 image30

	CComplex comp5 = comp1 + 20;    //comp1.operator+(20),   int==>(����ת��)CComplex     CComplex(int),��ΪCComplex�ṩ��CComplex(int)�Ĺ��캯�������Կ�������CComplex(20)����ʱ����
	comp5.show();  // real:30 image10

	//�����������������ʱ�򣬻���ö������������غ��������ȵ��ó�Ա�����������û�г�Ա����
	// ����ȫ���������Һ��ʵ���������غ���
	//      ::operator+(30,com1)
	 CComplex comp6 = 30 + comp1;          // �����ơ� + ��: û���ҵ����ܡ�CComplex�����͵�ȫ�������(��û�пɽ��ܵ�ת��)  ===>�ṩȫ��+���������       
	 comp6.show();   // real:40 image10

	 // CComplex operator++(int);
	 comp6 = comp1++;   // ++ -- �ǵ�Ŀ�����   operator++():ǰ��++   operator++(int):����++
	 comp1.show();      // real:11 image11
	 comp6.show();      // real : 10 image10

	 // CComplex operator++();
	 comp6 = ++comp1;
	 comp1.show();       // real:12 image12
	 comp6.show();       // real:12 image12

	 // ���������
	 // void         comp6.operator+=(comp1)                    ::operator+=(comp6,comp1)   
	 comp6 += comp1;  
	 comp6.show();   // real:24 image24    ������Ϣ�����


	 // ::operator<<() 
	 std::cout << comp6;

	 CComplex comp7;
	 std::cin >> comp7;
	 std::cout << comp7;
	return 0;
}































