#include<iostream>
#include<iomanip>
using namespace std;

double length[9]={0};
double lengthex[9]={0};
double radius[9]={0,8.392,28.432,-23.059,7.7769,-63.2347,-11.774,11.0338,39.986};
double n[5]={0,1.7725,1.71736,1.62299,1.622347};//空气折射率为1
double d[9]={0,4.2,1.15,0.96,1.31,2.69,0.5,4.2,11.24};
double i[9]={0};
double iex[9]={0};
double u[10]={0};//含u'8
//double uex[9]={0};
int h=10;//设投射高度为10mm
double fex;//系统焦距（以主点为原点）
double princi[3]={};//系统主点（基点）位置（以最左侧顶点为原点）
			//这里princi为什么初始化后值有问题？
//——以上首元均置零不用

void clac(int t);//递归式核心计算
void print(int orientation);//追迹结果报告
void kid(int distance,int height);//第三小题
void trace(int orientation);//追迹数据运算（初始化+递归运算）
void invert();//反向追迹，处理数组
//函数声明

int main()
{
	cout<<setiosflags(ios::fixed)<<setiosflags(ios::right);
	trace(1);//正向1，负向2
	invert();//数据数组倒置
	trace(2);
	invert();//数据数组复位
	kid(9000,800);//9m,0.8m的孩子
	kid(10000,800);//10m,0.8m的孩子
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
	//l1=-∞
	i[1]=h/radius[1];//i1初始化（特殊）
	iex[1]=i[1]/n[1];//i1'初始化
	u[1]=0;
	u[2]=u[1]+i[1]-iex[1];//u[t]=uex[t-1]，故省去uex[]
	//lengthex[1]=n[1]/((n[1]-1)/radius[1]);//l1'初始化（特殊）//计算式容易写错
	lengthex[1]=radius[1]*(1+iex[1]/u[2]);//l1'初始化			//法二
	clac(2);//表格剩余必填数据的计算

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
	if(!(t%2))//偶数
	{
		length[t]=lengthex[t-1]-d[t-1];
		i[t]=(length[t]-radius[t])*u[t]/radius[t];
		iex[t]=i[t]*n[t/2];
		u[t+1]=u[t]+i[t]-iex[t];
		lengthex[t]=radius[t]*(1+iex[t]/u[t+1]);
	}
	else//奇数
	{
		length[t]=lengthex[t-1]-d[t-1];
		i[t]=(length[t]-radius[t])*u[t]/radius[t];
		iex[t]=i[t]/n[(t+1)/2];
		u[t+1]=u[t]+i[t]-iex[t];
		lengthex[t]=radius[t]*(1+iex[t]/u[t+1]);
	}
	if(t<9)
		clac(++t);//递归
}

void kid(int distance,int height)
{
	double ltotal=-(distance+princi[1]-1.969436);//注意l是负值,这里的常数是物方主面和像方主面间的距离
	double lextotal=ltotal*fex/(ltotal+fex);
	double betatotal=fex/(ltotal+fex);
	double heightex=betatotal*height;

	cout<<setiosflags(ios::right)<<setw(12)<<"距物镜"<<distance<<"mm处孩子像的位置（以像方主点为原点）";
	cout<<setiosflags(ios::right)<<setw(12)<<setprecision(6)<<lextotal<<endl<<endl;
	cout<<setiosflags(ios::right)<<setw(12)<<setprecision(6)<<"系统垂轴放大率为"<<betatotal<<endl<<endl;
	cout<<setiosflags(ios::right)<<setw(12)<<height<<"mm高孩子像的大小";
	cout<<setiosflags(ios::right)<<setw(12)<<setprecision(6)<<heightex<<endl<<endl;
}

void print(int orientation)
{
	cout<<setiosflags(ios::right)<<setw(12)<<"项目/序号";
	for(int m=1;m<9;++m)
		cout<<setiosflags(ios::right)<<setw(12)<<m;
	cout<<endl;
	cout<<setiosflags(ios::right)<<setw(12)<<"物方截距l";
	if (length[1]==0)
	{
		cout<<setiosflags(ios::right)<<setw(12)<<"-∞";
		for(int m=2;m<9;++m)
			cout<<setiosflags(ios::right)<<setw(12)<<setprecision(6)<<length[m];
	}
	else
	{
		for(int m=1;m<9;++m)
			cout<<setiosflags(ios::right)<<setw(12)<<setprecision(6)<<length[m];
	}
	cout<<endl;
	cout<<setiosflags(ios::right)<<setw(12)<<"入射角i";
	for(int m=1;m<9;++m)
		cout<<setiosflags(ios::right)<<setw(12)<<setprecision(6)<<i[m];
	cout<<endl;
	cout<<setiosflags(ios::right)<<setw(12)<<"折射角i\'";
	for(int m=1;m<9;++m)
		cout<<setiosflags(ios::right)<<setw(12)<<setprecision(6)<<iex[m];
	cout<<endl;
	cout<<setiosflags(ios::right)<<setw(12)<<"像方孔径角u\'";
	for(int m=2;m<10;++m)
		cout<<setiosflags(ios::right)<<setw(12)<<setprecision(6)<<u[m];
	cout<<endl;
	cout<<setiosflags(ios::right)<<setw(12)<<"像方截距l\'";
	for(int m=1;m<9;++m)
		cout<<setiosflags(ios::right)<<setw(12)<<setprecision(6)<<lengthex[m];
	cout<<endl;
	cout<<setiosflags(ios::right)<<setw(12)<<"系统焦距f\'";
	cout<<setiosflags(ios::right)<<setw(12)<<setprecision(6)<<fex<<endl;
	cout<<setiosflags(ios::right)<<setw(12)<<"系统主点（基点）位置（以最左侧顶点为原点）";
	cout<<setiosflags(ios::right)<<setw(12)<<setprecision(6)<<princi[orientation]<<endl<<endl;
}
