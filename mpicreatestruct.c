#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <math.h>

void build_mpi_type(double *xlabel,double *ylabel,int nlabel,double *r,char *name,int num,MPI_Datatype *input_mpi_t_p);
void get_input(int my_rank,int comm_sz,double *xlabel,double *ylabel,int nlabel,double *r,char *name,int num);

int main(void)
{
  int my_rank,comm_sz;
  double *xlabel,*ylabel;
  int nlabel,num;
  char *name;
  double r;

  MPI_Init(NULL,NULL);
  MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
  MPI_Comm_size(MPI_COMM_WORLD,&comm_sz);

  printf("please input nlabel:\n");
  scanf("%d",&nlabel);

  printf("please input num:\n");
  scanf("%d",&num);

  xlabel=malloc(nlabel*sizeof(double));
  ylabel=malloc(nlabel*sizeof(double));
  name=malloc(num*sizeof(char));

  get_input(my_rank,comm_sz,xlabel,ylabel,nlabel,&r,name,num);
  

  if(my_rank==0)
  {
    printf("the distance between p1 and p2 is %lf\n",sqrt(pow(xlabel[1]-xlabel[0],2)+pow(ylabel[1]-ylabel[0],2)));  
  }
  else if(my_rank==1)
    {
      printf("the area of circle is %lf\n",3.14*r*r);
    }
  else
  {
    printf("the name is %s\n",name);
  }
  
  free(xlabel);
  free(ylabel);
  free(name);
}


void build_mpi_type(double *xlabel,double *ylabel,int nlabel,double *r,char *name,int num,MPI_Datatype *input_mpi_t_p)
{
  int array_of_blocklengths[4]={nlabel,nlabel,1,num};
  MPI_Datatype array_of_types[4]={MPI_DOUBLE,MPI_DOUBLE,MPI_INT,MPI_CHAR};
  MPI_Aint x_addr,y_addr,r_addr,name_addr;
  MPI_Aint array_of_displacements[4]={0};

  MPI_Get_address(xlabel,&x_addr);
  MPI_Get_address(ylabel,&y_addr);
  MPI_Get_address(r,&r_addr);
  MPI_Get_address(name,&name_addr);

  array_of_displacements[1]=y_addr-x_addr;
  array_of_displacements[2]=r_addr-x_addr;
  array_of_displacements[3]=name_addr-x_addr;

  MPI_Type_create_struct(4,array_of_blocklengths,array_of_displacements,array_of_types,input_mpi_t_p);
  MPI_Type_commit(input_mpi_t_p);
}

void get_input(int my_rank,int comm_sz,double *xlabel,double *ylabel,int nlabel,double *r,char *name,int num)
{
  MPI_Datatype input_mpi_t;
  
  build_mpi_type(xlabel,ylabel,nlabel,r,name,num,&input_mpi_t);

  if(my_rank==0)
  {
    printf("please input %d xlables in double precision\n",nlabel);
    for(int i=0;i<nlabel;i++)
    {
      scanf("%lf",xlabel+i);
    }

    printf("please input %d ylables in double precision\n",nlabel);
    for(int i=0;i<nlabel;i++)
    {
      scanf("%lf",ylabel+i);
    }

    printf("please input radius in double precision\n");
    scanf("%lf",r);

    printf("please input name including %d characters\n",num-1);
    for(int i=0;i<num-1;i++)
    {
      scanf("%c",name+i);
      getchar();
    }
  }

  MPI_Bcast(xlabel,1,input_mpi_t,0,MPI_COMM_WORLD);
  
  MPI_Type_free(&input_mpi_t);
}
