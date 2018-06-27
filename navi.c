// including required header files
#include  <stdio.h>
#include <string.h>
#include  "mpi.h"
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

// main function
int  main(argc,argv)
int    argc;
char  **argv;
{
	// declaring variables
	int rank, size, i, j, dup, k;
       	MPI_Init(&argc,&argv); 
	MPI_Status status;
	MPI_Request req;
       	MPI_Comm_size(MPI_COMM_WORLD,&size); 
       	MPI_Comm_rank(MPI_COMM_WORLD,&rank); 
	
	// for time cntrolled loop
	time_t endwait;
	time_t start;
	time_t seconds;

	int localcount = 0;
	int val = 0;
	int looprep = 0;

	// start istaken as the current time 
	// second refers to the time of execution (60 s)
	start = time(NULL);
	seconds = 60;
	endwait = start + seconds;
	
	// while the execution time has not exceeded 60 s
	while(start < endwait){

		//declaring in and out variables for reduce function
		// the size of array = number of processors
		int out[size];
		int in[size];
		
		// initializing with all 0s
		memset( in, 0, size*sizeof(int) );	
		memset( out, 0, size*sizeof(int) );
	
		// a variable for counting the number of loop execution
		looprep++;

		// if size is less than 3 send error message
		if(size < 3) 
		{
			if(rank == 0)
				printf("Error. Atleast 3 processes are required");
			fflush(stdout);
			return 0;
 		}
	
		// get a random position between 0 and 999
		srand((time(NULL)) ^ rank);
		int r = rand() % 1000;

		// reduce operation with matrix containing position
		in[rank] = r;
		MPI_Reduce( &in, &out, size, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD );

		// processor 0 counts the strikes
		if(rank == 0)
		{
			// for each odd number 
			for (i=1;i<size;i+=2)
			{
				dup = 0;
				// checks for duplicates
				for(k=i+2;k<size;k+=2)
				{
					if(out[i] == out[k])
						dup = 1;
				}
				// if there is a duplicate (another odd in the same position) skip for now
				if(dup == 1)
					continue;

				localcount = 0;
				// count the even in that position 
				for(j=0;j<size;j+=2)
				{
					if(out[i] == out[j])
					{
						localcount ++;
					}
				}
				// if there are 2 or more thats a strike, increase the count 
				if(localcount > 1)
					val++;
			}
		}
		
		start = time(NULL);
		// sleep for not crashing 
		usleep(1000);
	}

	// rank 0 prints the results
	if(rank == 0)
	{
		printf("\n%d \t %d \t %d\n",size, val, looprep);
		fflush( stdout);
	}
	MPI_Finalize();
	return 0;
}
				
		
	
