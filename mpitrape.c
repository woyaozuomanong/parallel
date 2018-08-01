/*************************************************************************
	> File Name: mpitrape.c
	> Author: 
	> Mail: 
	> Created Time: 2018年07月23日 星期一 22时31分56秒
 ************************************************************************/

#include<stdio.h>
#include<mpi/mpi.h>
#include<math.h>
double Trap(double left_endpt,double right_endpt,int trap_count,double base_len);
void Get_input(int my_rank,int comm_sz,double *a_p,double *b_p,int *n_p);

int main(void)
{
    int my_rank,comm_sz,n,local_n;
    double a,b,h,local_a,local_b;
    double local_int,total_int;
    int source;

    MPI_Init(NULL,NULL);
    MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
    MPI_Comm_size(MPI_COMM_WORLD,&comm_sz);
    Get_input(my_rank,comm_sz,&a,&b,&n);
    h=(b-a)/n;
    local_n=n/comm_sz;

    local_a=a+my_rank*local_n*h;
    local_b=local_a+local_n*h;
    local_int=Trap(local_a,local_b,local_n,h);
    for(source=0;source<comm_sz;source++)
    {
        MPI_Reduce(&local_int,&total_int,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
    }
   /* if(my_rank!=0)
    {
        MPI_Send(&local_int,1,MPI_DOUBLE,0,0,MPI_COMM_WORLD);
    }
    else
    {
        total_int=local_int;
        for(source=1;source<comm_sz;source++)
        {
            MPI_Recv(&local_int,1,MPI_DOUBLE,source,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            total_int+=local_int;
        }
    }
   */


    if(my_rank==0)
    {
        printf("With n=%d trapezoids,our estimate\n",n);
        printf("of the integral from %f to %f = %.15e\n",a,b,total_int);
    }

    MPI_Finalize();
    return 0;
}


double Trap(double left_endpt,double right_endpt,int trap_count,double base_len)
{
    double estimate,x;
    int i;

    estimate=(left_endpt+right_endpt)/2.0;
    for(i=1;i<=trap_count-1;i++)
    {
        x=left_endpt+i*base_len;
        estimate+=x;
    }
    estimate=estimate*base_len;

    return estimate;
}



void Get_input(int my_rank,int comm_sz,double *a_p,double *b_p,int *n_p)
{
    int dest;

    if(my_rank==0)
    {
        printf("Enter a,b and n\n");
        scanf("%lf %lf %d",a_p,b_p,n_p);
       /* for(dest=1;dest<comm_sz;dest++)
        {
            MPI_Send(a_p,1,MPI_DOUBLE,dest,0,MPI_COMM_WORLD);
            MPI_Send(b_p,1,MPI_DOUBLE,dest,0,MPI_COMM_WORLD);
            MPI_Send(n_p,1,MPI_INT,dest,0,MPI_COMM_WORLD);
        }*/ 
    }
   /* else
    {
        MPI_Recv(a_p,1,MPI_DOUBLE,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        MPI_Recv(b_p,1,MPI_DOUBLE,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        MPI_Recv(n_p,1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
    } */
    MPI_Bcast(a_p,1,MPI_DOUBLE,0,MPI_COMM_WORLD);
    MPI_Bcast(b_p,1,MPI_DOUBLE,0,MPI_COMM_WORLD);
    MPI_Bcast(n_p,1,MPI_DOUBLE,0,MPI_COMM_WORLD);
}
