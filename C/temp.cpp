#include<stdio.h>
int main()
{
	double m;
	scanf("%lf",&m);//adadadada末尾 回车
	int a[500]={0},b[500]={0};
	char ch1,ch2;
	int i=0;
	getchar();//回车
	while((ch1=getchar())!='\n')
	{
		a[i]=(int)ch1;
		i++;
	}
	int l=0;
	while((ch2=getchar())!='\n')
	{
		b[l]=(int)ch2;
		l++;
	}
	
	double s=0.0;
	for(int j=0;j<=i;j++)
	{
		if(a[j]==b[j])
		s++;
	}
	if((s/(i+1))>=m)
	printf("yes");
	else
	printf("no");
	return 0;
}