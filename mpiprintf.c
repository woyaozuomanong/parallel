/*************************************************************************
	> File Name: mpiprintf.c
	> Author: 
	> Mail: 
	> Created Time: 2018年07月23日 星期一 22时10分31秒
 ************************************************************************/

#include<stdio.h>
#include<mpi/mpi.h>

int main(void)
{
    int my_rank,comm_sz;

    MPI_Init(NULL,NULL);
    MPI_Comm_size(MPI_COMM_WORLD,&comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);

    printf("Proc %d of %d > Does anyone have a toothpick?\n",my_rank,comm_sz);

    MPI_Finalize();
    return 0;
    
}
