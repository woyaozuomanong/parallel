#include <stdio.h>
#include <mpi.h>

#define N 8
#define LOCAL_N  2

void get_input(int my_rank,int comm_sz,double *a,double *b,int total_n,int local_n,MPI_Comm comm);
void dual(int my_rank,double *b,int local_n);

int main(void)
{
  int my_rank,comm_sz;
  double a[N],b[LOCAL_N];
  double local_start,local_finish,local_elapsed,elapsed;

  MPI_Init(NULL,NULL);
  MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
  MPI_Comm_size(MPI_COMM_WORLD,&comm_sz);
  MPI_Barrier(MPI_COMM_WORLD);

  local_start=MPI_Wtime();
  get_input(my_rank,comm_sz,a,b,N,LOCAL_N,MPI_COMM_WORLD);
  for(int i=0;i<LOCAL_N;i++)
  {
    printf("this is process %d,b[%d]=%lf\n",my_rank,i,b[i]);
  }
  dual(my_rank,b,LOCAL_N);
  for(int i=0;i<LOCAL_N;i++)
  {
    printf("this is process %d,b[%d]=%lf\n",my_rank,i,b[i]);
  }
  MPI_Gather(b,LOCAL_N,MPI_DOUBLE,a,LOCAL_N,MPI_DOUBLE,0,MPI_COMM_WORLD);
  local_finish=MPI_Wtime();
  local_elapsed=local_finish-local_start;
  MPI_Reduce(&local_elapsed,&elapsed,1,MPI_DOUBLE,MPI_MAX,0,MPI_COMM_WORLD);
  if(my_rank==0)
  {
    for(int i=0;i<N;i++)
    {
      printf("this is process %d output:a[%d]=%lf\n",my_rank,i,a[i]);
    }
    printf("Elapsed time=%e seconds\n",elapsed);
  }

  return 0;
}



void get_input(int my_rank,int comm_sz,double *a,double *b,int total_n,int local_n,MPI_Comm comm)
{
  if(my_rank==0)
  {
    printf("please input %d numbers:\n",total_n);

    for(int i=0;i<total_n;i++)
    {
      scanf("%lf",a+i);
    }

    MPI_Scatter(a,local_n,MPI_DOUBLE,b,local_n,MPI_DOUBLE,0,comm);
  }
  
  else
    MPI_Scatter(a,local_n,MPI_DOUBLE,b,local_n,MPI_DOUBLE,0,comm);
}

void dual(int my_rank,double *b,int local_n)
{
  for(int i=0;i<local_n;i++)
  {
    b[i]*=my_rank;
  }
}
