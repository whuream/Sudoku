/*数独生成源程序，vc，made by su.whu*/
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#define N 10

int hefa(char a[10][10][10]);
int zhengjie(char a[10][10][10]);
void JByunsuan(char a[10][10][10]);
int ZJ2(char a[10][10][10]);
void zhongpan(char a[][10][10]);
void shunxu5(char a[][10][10]);
void shuchu(char a[][10][10],int b);
int meiju1(char a[10][10][10]);
int count1(char a[][10][10]);
int meiju2(char a[10][10][10]);
int count2(char a[][10][10]);
int check(char a[][10][10]);
int meijuCH(char a[][10][10]);
int input();

int M,TIME;
char static A[10][10];
int P1,P2;


int main()
{
    printf("欢迎进入数独制造程序！********************************************made by su.whu");
    char c='c';
    for(;c=='c';)
    {
        printf("\n\n请输入你要制造数独的个数（以回车键结束输入）：");
        int n=input();
        for(int i=1;i<=n;i++)
        { 
            char a[10][10][10];
            int t=clock();
     	    zhongpan(a);
            shunxu5(a);
            printf("\n%d",i);
            shuchu(a,0);
			check(a);
            printf("\n用时：%dms\n",clock()-t);
        }
        fflush(stdin);
        printf("\n运算结束，退出请按'q'，按'c'继续：");
		c='o';
        for(;(c!='q')&&(c!='c');)
			c=getch();
    }
	return 0;
}


/*数独合法性检验，合法返回1，不合法返回0*/
int hefa(char a[10][10][10])
{
	int i,j,k,num=0;
	char z;
	for(z='1';z<='9';z++)
	{
		for(i=1;i<=9;i++)
		{
			for(j=1;j<=9;j++)
				if(a[0][i][j]==z)
					num++;
			if(num>1)
				return 0;
			num=0;
		}
		for(i=1;i<=9;i++)
		{
			for(j=1;j<=9;j++)
				if(a[0][j][i]==z)
					num++;
			if(num>1)
				return 0;
			num=0;
		}
		for(k=1;k<=3;k++)
		{ 
			for(j=(k-1)*3+1;j<=k*3;j++)
				for(i=(k-1)*3+1;i<=k*3;i++)
					if(a[0][j][i]==z)
						num++;
			if(num>1)
				return 0;
			num=0;
		}
	}
	return 1;
}


/*数独是否填完，填完返回1，未填完返回0*/
int zhengjie(char a[10][10][10])
{
	int i,j;
	for(i=1;i<=9;i++)
		for(j=1;j<=9;j++)
			if(a[0][i][j]=='0')
				return 0;
	return 1;
}


/*数独是否还有空可填，是返回0，不是返回1*/
int ZJ2(char a[10][10][10])
{
	int i1,j1,k1;
	for(i1=1;i1<=9;i1++)
		for(j1=1;j1<=9;j1++)
			for(k1=1;k1<=9;k1++)
				if(a[i1][j1][k1]=='0')
					return 0;	
	return 1;
}


/*按格式输出数独*/
void shuchu(char a[][10][10],int b)
{
    int i,j;
	printf("\n");
	for(i=1;i<=9;i++)
	{
	    if(i==1)
			printf("|-------|-------|-------|\n");
		for(j=1;j<=9;j++)
		{
		    if(j==1)
				printf("| ");
		    printf("%c ",a[b][i][j]);
		    if(j%3==0)
				printf("| ");
		    if(j==9)
				printf("\n");
	    }
	    if(i%3==0)
			printf("|-------|-------|-------|\n");
    }
}


/*根据在数独中每行、每列、每个九宫格中只能填一个1~9的数填原数独*/
void JByunsuan(char a[10][10][10])
{
	int i,j,k=0;
	char z;
	for(i=1;i<=9;i++)
		for(j=1;j<=9;j++)
			for(k=1;k<=9;k++)
				a[i][j][k]='0';
	k=0;
	for(z='1';z<='9';z++)
	{
		int word=0,num=0;
		k++;
		for(i=1;i<=9;i++)
			for(j=1;j<=9;j++)
			{
				if(a[0][i][j]!='0')
					a[k][i][j]='1';
				if(a[0][i][j]==z)
				{
					int m;
					for(m=1;m<=9;m++)
						a[k][i][m]=a[k][m][j]='1';
					int x,y;
					for(x=(i-1)/3*3+1;x<=(i-1)/3*3+3;x++)
						for(y=(j-1)/3*3+1;y<=(j-1)/3*3+3;y++)
							a[k][x][y]='1';
				}
			}
		for(i=1;i<=9;i++)
		{
			for(j=1;j<=9;j++)
				if(a[k][i][j]=='0')
					num++;
			if(num==1)
			{
				for(j=1;j<=9;j++)
					if(a[k][i][j]=='0')
					{
						a[0][i][j]=z;
					}
				word=1;
				break;
			}
			num=0;
			for(j=1;j<=9;j++)
				if(a[k][j][i]=='0')
					num++;
			if(num==1)
			{
				for(j=1;j<=9;j++)
					if(a[k][j][i]=='0')
					{
						a[0][j][i]=z;
					}
				word=1;
				break;
			}
			num=0;
		}
		if(word==1)
		{
			z='0';
			k=0;
			continue;
		}
	}
}


/*挖空的顺序，第五种，从上至下*/
void shunxu5(char a[][10][10])
{
	int i,j;
	char b[10][10][10];
	for(i=1;i<=9;i++)
	{
		if(i%2==1)
			for(j=1;j<=9;j++)
			{
				char t;
				t=a[0][i][j];
				a[0][i][j]='0';
				/*你妹你妹，把b[][][]初始化写到外面来浪费了我24小时呀*/
			//	for(int i1=1;i1<=9;i1++)
				//	for(int j1=1;j1<=9;j1++)
					//	b[0][i1][j1]=a[0][i1][j1];
				/*考虑把问题：是否可以用非该值的1~9变换，用count1代替count2*/
				for(char k='1';k<='9';k++)
				{
					for(int i1=1;i1<=9;i1++)
						for(int j1=1;j1<=9;j1++)
							b[0][i1][j1]=a[0][i1][j1];
					if(k!=t)
					{
						b[0][i][j]=k;
						int p=count2(b);
					//	printf("假设%d行%d列填%c返回值2：%d \n",i,j,k,p);
						if(p==1)
							a[0][i][j]=t;
					}
				}
			//	shuchu(a,0);
			//	char c[1][10][10];
			//	for(int I=0;I<=9;I++)
				//	for(int J=0;J<=9;J++)
				//		c[0][I][J]=a[0][I][J];
			//	check(c);
			//	system("pause");
			}
		else
			for(j=9;j>=1;j--)
			{
				char t;
				t=a[0][i][j];
				a[0][i][j]='0';
				for(int i1=1;i1<=9;i1++)
					for(int j1=1;j1<=9;j1++)
						b[0][i1][j1]=a[0][i1][j1];
				for(char k='1';k<='9';k++)
				{
					for(int i1=1;i1<=9;i1++)
						for(int j1=1;j1<=9;j1++)
							b[0][i1][j1]=a[0][i1][j1];
					if(k!=t)
					{
						b[0][i][j]=k;
						int p=count2(b);
				//		printf("假设%d行%d列填%c返回值2：%d \n",i,j,k,p);
						if(p==1)
							a[0][i][j]=t;
					}
				}
			//	shuchu(a,0);
			//	char c[1][10][10];
			//	for(int I=0;I<=9;I++)
				//	for(int J=0;J<=9;J++)
					//	c[0][I][J]=a[0][I][J];
			//	check(c);
			//	system("pause");
			}
	}
}


/*生成一个终盘,生成速度过慢！！！！！！！！！！！！！伪随机数生成仍有问题，差强人意*/
void zhongpan(char a[][10][10])
{
	int i,j;
	for(j=1;j<=9;j++)
		for(i=1;i<=9;i++)
			a[0][i][j]=A[i][j]='0';
	int n=11;
	int a1=2010,a2=2011;
	for(i=1;i<=n;i++)
	{
		srand((unsigned int)clock()*21*i*i*(unsigned int)time( NULL )%767*a1*a2);
		a1=rand()%9+1;
		srand((unsigned int)clock()*23*i*i*i*a2);
		a2=rand()%9+1;
		srand((unsigned int)clock()*32*i*i*i*i*a1);
		if(a[0][a1][a2]=='0')
			a[0][a1][a2]=char(rand()%9+49);
		else
		{
			i--;
			a1=(a1*74+98)/4;
			a2=(a2*86+'p'*'q')/8;
			continue;
		}
		if(!hefa(a))
		{
		//	printf("a[0][%d][%d]=%c\n",a1,a2,a[0][a1][a2]);
		//	printf("不合法！");
			a[0][a1][a2]='0';
			a1=(a1*74+98)/a1;
			a2=(a2*86+'p'*'q')/a2/4;
			i--;
		}
		else
			;
	//	printf("a[0][%d][%d]=%c\n",a1,a2,a[0][a1][a2]);
	}
	if(count1(a)==0)
	{
	//	printf("终盘生成失败\n");
		zhongpan(a);
	}
	else
	{
		for(i=1;i<=9;i++)
			for(j=1;j<=9;j++)
				a[0][i][j]=A[i][j];
	//	shuchu(a,0);
	//	printf("终盘生成成功\n");
	}
}


/*解出数独的一个解，返回解得个数*/
int count1(char a[][10][10])
{
	M=0;
	if(hefa(a))
	{
		JByunsuan(a);
		if(!zhengjie(a))
			if(!ZJ2(a))
			{
				TIME=clock();
				int p=meiju1(a);
			//	printf("返回值1：%d",p);
				return p;
			}
			else
				return 0;
		else
			return 1;
	}
	else
		return 0;
}


/*同上*/
int meiju1(char a[10][10][10])
{
    if((clock()-TIME)>2000)
	{
	//	printf("超时？？？\n");
        return 0;
	}
	int i,j,k=0;
	char z;
	for(z='1';z<='9';z++)
	{
		k++;
		for(i=1;i<=9;i++)
		{
			int b[11]={0};
			int p;
			for(j=1;j<=9;j++)
				if(a[k][i][j]=='0')
					for(p=1;p<=9;p++)
						if(b[p]==0)
						{
							b[p]=j;
							break;
						}
			if(b[1]!=0)
			{
				for(p=1;p<=10;p++)
				{
					if(b[p]!=0)
					{
						char c[10][10];
						int x1,x2;
						for(x1=1;x1<=9;x1++)
							for(x2=1;x2<=9;x2++)
								c[x1][x2]=a[0][x1][x2];
						a[0][i][b[p]]=z;
						for(int iK=1;iK<=10;iK++)
							if(b[iK]!=0)
						JByunsuan(a);
				        if(zhengjie(a))
				        {
                            M=1;
						   	for(int i1=1;i1<=9;i1++)
								for(int i2=1;i2<=9;i2++)
									A[i1][i2]=a[0][i1][i2];
						    return 1;
                        }
						else
							if(!ZJ2(a))
							{
							//	printf("***");
								meiju1(a);
							}
						if(M==1)
                            return 1;
                        if((clock()-TIME)>2000)
                            return 0;
						for(x1=1;x1<=9;x1++)
							for(x2=1;x2<=9;x2++)
								a[0][x1][x2]=c[x1][x2];
					}
					else
						return 0;
				}
			}
		}
	}	
}


/*解数独的解，无时限*/
int count2(char a[][10][10])
{
	M=0;
	if(hefa(a))
	{
		JByunsuan(a);
		if(!zhengjie(a))
			if(!ZJ2(a))
				return meiju2(a);
			else
			{
			//	printf("无正解2返回");
			//	shuchu(a,0);
				return 0;
			}
		else
			return 1;
	}
	else
	{
	//	printf("不合法返回！");
	//	shuchu(a,0);
	}
	return 0;
}


/*同上*/
int meiju2(char a[10][10][10])
{
	int i,j,k=0;
	char z;
	for(z='1';z<='9';z++)
	{
		k++;
		for(i=1;i<=9;i++)
		{
			int b[11]={0};
			int p;
			for(j=1;j<=9;j++)
				if(a[k][i][j]=='0')
					for(p=1;p<=9;p++)
						if(b[p]==0)
						{
							b[p]=j;
							break;
						}
			if(b[1]!=0)
			{
				for(p=1;p<=10;p++)
				{
					if(b[p]!=0)
					{
						char c[10][10];
						int x1,x2;
						for(x1=1;x1<=9;x1++)
							for(x2=1;x2<=9;x2++)
								c[x1][x2]=a[0][x1][x2];
						a[0][i][b[p]]=z;
						for(int iK=1;iK<=10;iK++)
							if(b[iK]!=0)
						JByunsuan(a);
				        if(zhengjie(a))
				        {
                            M=1;
						   	for(int i1=1;i1<=9;i1++)
								for(int i2=1;i2<=9;i2++)
									A[i1][i2]=a[0][i1][i2];
						    return 1;
                        }
						else
							if(!ZJ2(a))
							{
							//	printf("***");
								meiju2(a);
							}
						if(M==1)
                            return 1;
						for(x1=1;x1<=9;x1++)
							for(x2=1;x2<=9;x2++)
								a[0][x1][x2]=c[x1][x2];
					}
					else
					{
					//	printf("从函数中返回|||||");
						return 0;
					}
				}
			}
		}
	}	
}


/*检验生成的数独的难度，返回值无效*/
int check(char a[][10][10])
{
	M=0;
	P1=P2=0;
	int t=clock();
	printf("\n数独的评价：\n");
	if(hefa(a))
	{
		int kong=0,kong1=0;
		printf("\n数独合法\n");
		for(int i=1;i<=9;i++)
			for(int j=1;j<=9;j++)
				if(a[0][i][j]=='0')
					kong++;
		printf("数字数：%d\n",81-kong);
		printf("空格数：%d\n",kong);
		JByunsuan(a);
		for(int i=1;i<=9;i++)
			for(int j=1;j<=9;j++)
				if(a[0][i][j]=='0')
					kong1++;
		printf("通过基本运算填的空格数：%d\n",kong-kong1);
		printf("基本运算后的空格数：%d\n",kong1);
		if(!zhengjie(a))
			if(!ZJ2(a))
			{
				P1++;
				meijuCH(a);
			}
			else
				return 0;
		else
		{
			M++;
		//	printf("\n第%d个解：\n",M);
			printf("解：\n");
			shuchu(a,0);
		}
		printf("该数独共有%d解。\n",M);
		printf("最少回溯次数：%d\n",P2);
		printf("最大回溯次数：%d\n",P1);
	}
	else
		printf("该数独共有0个解。\n");
	printf("解用时%dms\n",clock()-t);
	return 0;
}


/*同上*/
int meijuCH(char a[][10][10])
{
	int i,j,k=0;
	char z;
	for(z='1';z<='9';z++)
	{
		k++;
		for(i=1;i<=9;i++)
		{
			int b[11]={0};
			int p;
			for(j=1;j<=9;j++)
				if(a[k][i][j]=='0')
					for(p=1;p<=9;p++)
						if(b[p]==0)
						{
							b[p]=j;
							break;
						}
			if(b[1]!=0)
			{
				for(p=1;p<=10;p++)
				{
					if(b[p]!=0)
					{
						char c[10][10];
						int x1,x2;
						for(x1=1;x1<=9;x1++)
							for(x2=1;x2<=9;x2++)
								c[x1][x2]=a[0][x1][x2];
						a[0][i][b[p]]=z;
						JByunsuan(a);
				        if(zhengjie(a))
						{
							M++;
							printf("解：");
							P2=P1;
							shuchu(a,0);
						}
						if((!zhengjie(a))&&(!ZJ2(a)))
						{
							P1++;
							meijuCH(a);
						}
						for(x1=1;x1<=9;x1++)
							for(x2=1;x2<=9;x2++)
								a[0][x1][x2]=c[x1][x2];
					}
					else
						return 0;
				}
			}
		}
	}	
}


/*控制输入*/
int input()
{
	char b[N];
	for(int i=0;i<N;i++)
		b[i]='\0';
	char c;
	for(;(c=getch())!='\r';)
	{
		if((c>='0')&&(c<='9'))
		{
			for(int i=0;i<N;i++)
				if(b[i]=='\0')
				{
					b[i]=c;
					printf("%c",b[i]);
					break;
				}
		}
		if(c=='\b')
			for(int i=N-1;i>=0;i--)
				if(b[i]!='\0')
				{
					b[i]='\0';
					printf("\b \b");
					break;
				}
	}
    printf("\n");
	int num=0,k=1;
	for(int i=N-1;i>=0;i--)
		if(b[i]!='\0')
		{
			num+=((int)b[i]-48)*k;
			k*=10;
		}
	return num;
}


/*时间主要花在生成终盘上，伪随机数生成不懂，怎样在极短的时间间隔内生成不同的伪随机数？算法需要时间过长*/