#include <stdio.h>
#include <mpi.h>
#include <math.h>
void mulbymyrank(int my_rank);

int main(void)
{
  double local_start,local_finish,local_elapsed,elapsed;
  int my_rank,comm_sz;

  MPI_Init(NULL,NULL);
  MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
  MPI_Comm_size(MPI_COMM_WORLD,&comm_sz);
  MPI_Barrier(MPI_COMM_WORLD);

  local_start=MPI_Wtime();

  mulbymyrank(my_rank);

  local_finish=MPI_Wtime();
  local_elapsed=local_finish-local_start;

  MPI_Reduce(&local_elapsed,&elapsed,1,MPI_DOUBLE,MPI_MAX,0,MPI_COMM_WORLD);

  if(my_rank==0)
  {
    printf("Elapsed time=%e seconds\n",elapsed);
  }
}


void mulbymyrank(int my_rank)
{
  double a[1000][1000];
  for(int i=0;i<1000;i++)
  {
    for(int j=0;j<1000;j++)
    {
      a[i][j]=(i+j)/(my_rank+1);
      a[i][j]=sin(a[i][j]);
      a[i][j]=exp(a[i][j]);
    }
  }
}
