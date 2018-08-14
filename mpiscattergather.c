/*************************************************************************
	> File Name: mpitrape.c
	> Author: 
	> Mail: 
	> Created Time: 2018年07月23日 星期一 22时31分56秒
 ************************************************************************/

#include<stdio.h>
#include<mpi.h>
#include<math.h>
#include<stdlib.h>

#define N 8

void dual(int my_rank,double *local_start,int n);
void Get_input(int my_rank,int comm_sz,double *a,double *b,int n,MPI_Comm comm);


int main(void)
{
    int my_rank,comm_sz;
    double a[N];
    double *b;

    MPI_Init(NULL,NULL);
    MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
    MPI_Comm_size(MPI_COMM_WORLD,&comm_sz);
    b=malloc(N/comm_sz*sizeof(double));
    if(my_rank==0)
    {
    
    Get_input(my_rank,comm_sz,a,b,N,MPI_COMM_WORLD);
    dual(my_rank,a+N/comm_sz*my_rank,N/comm_sz);
    for(int i=0;i<N;i++)
    {
      printf("a%d=%f\n",i,a[i]);
    }
      MPI_Gather(b,N/comm_sz,MPI_DOUBLE,a,N/comm_sz,MPI_DOUBLE,0,MPI_COMM_WORLD);
      for(int i=0;i<N;i++)
      {
        printf("%f\n",a[i]);
      }
    }
    else
    {
      
      Get_input(my_rank,comm_sz,a,b,N,MPI_COMM_WORLD);
      dual(my_rank,a+N/comm_sz*my_rank,N/comm_sz);
      MPI_Gather(b,N/comm_sz,MPI_DOUBLE,a,N/comm_sz,MPI_DOUBLE,0,MPI_COMM_WORLD);
    }


    MPI_Finalize();
    free(b);
    return 0;
}


void Get_input(int my_rank,int comm_sz,double *a,double *b,int n,MPI_Comm comm)
{
    if(my_rank==0)
    {
      printf("please input %d numbers\n",n);
      for(int i=0;i<n;i++)
      {
        scanf("%f",a+i);
      }

      MPI_Scatter(a,n/comm_sz,MPI_FLOAT,b,n/comm_sz,MPI_FLOAT,0,comm);

    }
    else
    {
      MPI_Scatter(a,n/comm_sz,MPI_FLOAT,b,n/comm_sz,MPI_FLOAT,0,comm);
    }
}



void dual(int my_rank,double *local_start,int n)
{
    int i=0;
    while(i++!=n)
    {
        *(local_start+i)*=my_rank;
    }
}
