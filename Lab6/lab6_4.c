#include<stdio.h>
#include<mpi.h>
#include<string.h>
#include<time.h>
typedef struct {
        char l1;
        char l2;
        char l3;
	char l4;
	char l5;
} Data;

int main(int argc, char **argv)
{
        double start,stop;
        int rank, size, r;
        int src, dst, tag, i;
        int position = 0;
        MPI_Status status;
        char buffer[300];
        MPI_Datatype new_type;
        MPI_Datatype type[5] = { MPI_CHAR, MPI_CHAR,MPI_CHAR,MPI_CHAR,MPI_CHAR };
        int blen[5] = {  1,1,1,1,1 };
        MPI_Aint disp[5];
        MPI_Aint base, addr;
        Data tabrecord,tabrecieved;

        MPI_Init(&argc, &argv);
        MPI_Comm_size(MPI_COMM_WORLD, &size);

	MPI_Get_address(&tabrecord, &base);
        MPI_Get_address(&(tabrecord.l1), &addr);
        disp[0] = addr - base;
        MPI_Get_address(&(tabrecord.l2), &addr);
        disp[1] = addr - base;
        MPI_Get_address(&(tabrecord.l3), &addr);
        disp[2] = addr - base;
        MPI_Get_address(&(tabrecord.l4), &addr);
        disp[3] = addr - base;
        MPI_Get_address(&(tabrecord.l5), &addr);
        disp[4] = addr - base;
      
        MPI_Type_create_struct(5, blen, disp, type, &new_type);
        MPI_Type_commit(&new_type);
        start=MPI_Wtime();
        if (size < 2)
        {
                printf("Please run with 2 processes.\n");fflush(stdout);
                MPI_Finalize();
                return 1;
        }

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

        if(rank == 0)
        {
        	tabrecord.l1='A';
                tabrecord.l2='D';
		tabrecord.l3='A';
		tabrecord.l4='M';
		tabrecord.l5='A';
                
        MPI_Pack(&tabrecord, 1, new_type, buffer, 300, &position, MPI_COMM_WORLD);
        MPI_Send(buffer, position, MPI_PACKED, 1, 100, MPI_COMM_WORLD);
        }

	if(rank == 1)
        {
                tabrecieved.l1='R';
                tabrecieved.l2='O';
		tabrecieved.l3='M';
		tabrecieved.l4='E';
		tabrecieved.l5='N';
                printf("In process %d I have name: %c%c%c%c%c\n ",rank,tabrecieved.l1,tabrecieved.l2,tabrecieved.l3,tabrecieved.l4,tabrecieved.l5);
                MPI_Recv(buffer, 300, MPI_PACKED, 0, 100, MPI_COMM_WORLD, &status);
                MPI_Unpack(buffer, 300, &position, &tabrecieved, 1, new_type, MPI_COMM_WORLD);
                printf("In process %d I have name: %c%c%c%c%c\n ",rank,tabrecieved.l1,tabrecieved.l2,tabrecieved.l3,tabrecieved.l4,tabrecieved.l5);
        }
        MPI_Barrier(MPI_COMM_WORLD);
        stop=MPI_Wtime();
        printf("Execution time:%f s\n",stop-start);
        MPI_Finalize();
        return 0;
}
//Romen Adama Caetano Ramirez