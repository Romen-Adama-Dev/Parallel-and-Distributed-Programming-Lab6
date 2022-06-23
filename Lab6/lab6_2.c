#include <stdlib.h>
#include <stdio.h>
#include "mpi.h"

int main(int argc, char **argv)
{
        if(strtol(argv[1],NULL,10)>=0){

                if(!argc<2){

                        int root=0;
                        int rank,ranksent,size,source,dest,tag,i;
                        int num=strtol(argv[1],NULL,10);

                        MPI_Status status;
                        MPI_Init(&argc,&argv);
                        MPI_Comm_rank(MPI_COMM_WORLD,&rank);
                        MPI_Comm_size(MPI_COMM_WORLD,&size);

                        if(rank==0)
                        {
                        dest=0;
                        tag=0;
                        for(i=1;i<size;i++)
                                MPI_Bcast(&rank,1,MPI_INT,root,MPI_COMM_WORLD);
                        printf("Process %d recived %d\n",rank,num);
                        }
                        else
                        {
                        printf("Process %d recieved %d from %d\n",rank,num,rank-1);

                        }
                MPI_Finalize();
                return(0);
                }else{
                        printf("Not enough arguments\n");

                }
	}else{
                printf("Number cannot be negative\n");
        }
}
//Romen A. Caetano Ramirez