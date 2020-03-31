/* put.c : Example 1: DataSpaces put tutorial 
 * This example will show you the simplest way 
 * to put a 1D array of 3 elements into the DataSpace.
 * */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>

#include "common.h"

#include "dataspaces.h"
#include "mpi.h"

int main(int argc, char **argv)
{
        int err;
        int nprocs, rank;
        MPI_Comm gcomm;
        int timestep;
        int datalower, dataupper, datarange;
        uint64_t lb, ub;
        char var_name[128];
        int *data = NULL;
        int i;
        int totaldata, numts;

        srand(time(NULL));

        MPI_Init(&argc, &argv);
        MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        gcomm = MPI_COMM_WORLD;

        if(argc != 3) {
            printf("Usage: put <data_size> <num_timesteps>\n");
            return(1);
        }

        totaldata = atoi(argv[1]);
        numts = atoi(argv[2]);

        data_decomp(totaldata, rank, nprocs, &datalower, &dataupper);
        datarange = (dataupper-datalower) + 1;
        if(datalower <= dataupper) {
            data = malloc(sizeof(*data) * datarange);
        }
        lb = datalower;
        ub = dataupper;

        if(rank == 0) {
            printf("Writing %d integers across %d ranks for %d timesteps.\n", 
                        totaldata, nprocs, numts);
        }

        //Name the Data that will be writen
        sprintf(var_name, "ex_sample_data");

        // Initalize DataSpaces
        // # of Peers, Application ID, ptr MPI comm, additional parameters
        // # Peers: Number of connecting clients to the DS server
        // Application ID: Unique idenitifier (integer) for application
        // Pointer to the MPI Communicator, allows DS Layer to use MPI barrier func
        // Addt'l parameters: Placeholder for future arguments, currently NULL.
        dspaces_init(nprocs, 1, &gcomm, NULL);
        
        for(timestep = 0; timestep < numts; timestep++) {        
                // Populate data array with random values from 0 to 99
                for(i = 0; i < datarange; i++) {
                    data[i] =  rand() % 100;
                    printf("Rank %d: Timestep %d: put data[%d] = %d\n", 
                            rank, timestep, i + datalower, data[i]);
                }

                // DataSpaces: Put data array into the space
                // Usage: dspaces_put(Name of variable, version num, 
                // size (in bytes of each element), dimensions for bounding box,
                // lower bound coordinates, upper bound coordinates,
                // ptr to data buffer 
                int ndim = 1;
                if(data) {
                    dspaces_put(var_name, timestep, sizeof(*data), ndim, 
                                            &lb, &ub, data);
                }
                send_event("put_data", &gcomm);
        }

        // DataSpaces: Finalize and clean up DS process
        dspaces_finalize();

        MPI_Barrier(gcomm);
        MPI_Finalize;

        free(data);

        return 0;
}
