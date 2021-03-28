#include<iostream>
#include<iomanip>
using namespace std;

double length[9]={0};
double lengthex[9]={0};
double radius[9]={0,8.392,28.432,-23.059,7.7769,-63.2347,-11.774,11.0338,39.986};
double n[5]={0,1.7725,1.71736,1.62299,1.622347};//����������Ϊ1
double d[9]={0,4.2,1.15,0.96,1.31,2.69,0.5,4.2,11.24};
double i[9]={0};
double iex[9]={0};
double u[10]={0};//��u'8
//double uex[9]={0};
int h=10;//��Ͷ��߶�Ϊ10mm
double fex;//ϵͳ���ࣨ������Ϊԭ�㣩
double princi[3]={};//ϵͳ���㣨���㣩λ�ã�������ඥ��Ϊԭ�㣩
			//����princiΪʲô��ʼ����ֵ�����⣿
//����������Ԫ�����㲻��

void clac(int t);//�ݹ�ʽ���ļ���
void print(int orientation);//׷���������
void kid(int distance,int height);//����С��
void trace(int orientation);//׷���������㣨��ʼ��+�ݹ����㣩
void invert();//����׷������������
//��������

int main()
{
	cout<<setiosflags(ios::fixed)<<setiosflags(ios::right);
	trace(1);//����1������2
	invert();//�������鵹��
	trace(2);
	invert();//�������鸴λ
	kid(9000,800);//9m,0.8m�ĺ���
	kid(10000,800);//10m,0.8m�ĺ���
}

void invert()
{
	double temp=0;
    int card=8;
    for (int i=1;i<=card/2;++i) 
	{
        temp=radius[card-i+1];
        radius[card-i+1]=-radius[i];
        radius[i]=-temp;
        temp=d[card-i+1];
        d[card-i+1]=d[i-1];
        d[i-1]=temp;
	}
    card=4;
    for (int i=1;i<=card/2;++i) 
	{
        temp=n[card-i+1];
        n[card-i+1]=n[i];
        n[i]=temp;
	}
}

void trace(int orientation)
{
	int a=1;
	//l1=-��
	i[1]=h/radius[1];//i1��ʼ�������⣩
	iex[1]=i[1]/n[1];//i1'��ʼ��
	u[1]=0;
	u[2]=u[1]+i[1]-iex[1];//u[t]=uex[t-1]����ʡȥuex[]
	//lengthex[1]=n[1]/((n[1]-1)/radius[1]);//l1'��ʼ�������⣩//����ʽ����д��
	lengthex[1]=radius[1]*(1+iex[1]/u[2]);//l1'��ʼ��			//����
	clac(2);//���ʣ��������ݵļ���

	fex=h/u[9];
	while(a<8)
	{
		princi[orientation]+=d[a];
		++a;
	}
	princi[orientation]=princi[orientation]+lengthex[8]-fex;

	print(orientation);
}

void clac(int t)
{
	if(!(t%2))//ż��
	{
		length[t]=lengthex[t-1]-d[t-1];
		i[t]=(length[t]-radius[t])*u[t]/radius[t];
		iex[t]=i[t]*n[t/2];
		u[t+1]=u[t]+i[t]-iex[t];
		lengthex[t]=radius[t]*(1+iex[t]/u[t+1]);
	}
	else//����
	{
		length[t]=lengthex[t-1]-d[t-1];
		i[t]=(length[t]-radius[t])*u[t]/radius[t];
		iex[t]=i[t]/n[(t+1)/2];
		u[t+1]=u[t]+i[t]-iex[t];
		lengthex[t]=radius[t]*(1+iex[t]/u[t+1]);
	}
	if(t<9)
		clac(++t);//�ݹ�
}

void kid(int distance,int height)
{
	double ltotal=-(distance+princi[1]);//ע��l�Ǹ�ֵ
	double lextotal=ltotal*fex/(ltotal+fex);
	double betatotal=fex/(ltotal+fex);
	double heightex=betatotal*height;

	cout<<setiosflags(ios::right)<<setw(12)<<"���ﾵ"<<distance<<"mm���������λ�ã���������Ϊԭ�㣩";
	cout<<setiosflags(ios::right)<<setw(12)<<setprecision(6)<<lextotal<<endl<<endl;
	cout<<setiosflags(ios::right)<<setw(12)<<setprecision(6)<<"ϵͳ����Ŵ���Ϊ"<<betatotal<<endl<<endl;
	cout<<setiosflags(ios::right)<<setw(12)<<height<<"mm�ߺ�����Ĵ�С";
	cout<<setiosflags(ios::right)<<setw(12)<<setprecision(6)<<heightex<<endl<<endl;
}

void print(int orientation)
{
	cout<<setiosflags(ios::right)<<setw(12)<<"��Ŀ/���";
	for(int m=1;m<9;++m)
		cout<<setiosflags(ios::right)<<setw(12)<<m;
	cout<<endl;
	cout<<setiosflags(ios::right)<<setw(12)<<"�﷽�ؾ�l";
	if (length[1]==0)
	{
		cout<<setiosflags(ios::right)<<setw(12)<<"-��";
		for(int m=2;m<9;++m)
			cout<<setiosflags(ios::right)<<setw(12)<<setprecision(6)<<length[m];
	}
	else
	{
		for(int m=1;m<9;++m)
			cout<<setiosflags(ios::right)<<setw(12)<<setprecision(6)<<length[m];
	}
	cout<<endl;
	cout<<setiosflags(ios::right)<<setw(12)<<"�����i";
	for(int m=1;m<9;++m)
		cout<<setiosflags(ios::right)<<setw(12)<<setprecision(6)<<i[m];
	cout<<endl;
	cout<<setiosflags(ios::right)<<setw(12)<<"�����i\'";
	for(int m=1;m<9;++m)
		cout<<setiosflags(ios::right)<<setw(12)<<setprecision(6)<<iex[m];
	cout<<endl;
	cout<<setiosflags(ios::right)<<setw(12)<<"�񷽿׾���u\'";
	for(int m=2;m<10;++m)
		cout<<setiosflags(ios::right)<<setw(12)<<setprecision(6)<<u[m];
	cout<<endl;
	cout<<setiosflags(ios::right)<<setw(12)<<"�񷽽ؾ�l\'";
	for(int m=1;m<9;++m)
		cout<<setiosflags(ios::right)<<setw(12)<<setprecision(6)<<lengthex[m];
	cout<<endl;
	cout<<setiosflags(ios::right)<<setw(12)<<"ϵͳ����f\'";
	cout<<setiosflags(ios::right)<<setw(12)<<setprecision(6)<<fex<<endl;
	cout<<setiosflags(ios::right)<<setw(12)<<"ϵͳ���㣨���㣩λ�ã�������ඥ��Ϊԭ�㣩";
	cout<<setiosflags(ios::right)<<setw(12)<<setprecision(6)<<princi[orientation]<<endl<<endl;
}