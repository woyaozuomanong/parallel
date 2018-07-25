/*************************************************************************
	> File Name: openmptest.c
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: 2018年07月25日 星期三 15时18分15秒
 ************************************************************************/

#include<stdio.h>
#include<omp.h>
#include<math.h>
#include <sys/time.h>

#define MAX 10000
double a[MAX][MAX],b[MAX][MAX],c[MAX][MAX];

int main()
{
	struct timeval start,end;
	gettimeofday(&start,NULL);
#pragma omp parallel for
	for(int i=0;i<MAX;i++)
	{
		for(int j=0;j<MAX;j++)
		{
			a[i][j]=sqrt(sin(i)*sin(j)+fabs(j));
			b[i][j]=log(i+j+1);
			c[i][j]=a[i][j]+b[i][j];
		}
	}
	gettimeofday(&end,NULL);

	int timeuse=1000000*(end.tv_sec-start.tv_sec)+end.tv_usec-start.tv_usec;
	printf("time:%d us\n",timeuse);
	return 0;
}
