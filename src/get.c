/* get.c : Example 1: DataSpaces get tutorial
 *  This example will show you the simplest way 
 *  to get a 1D array of 3 elements out of the DataSpace
 *  and store it in a local variable.
 *  */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

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
        int totaldata, numts;
        int i;

        MPI_Init(&argc, &argv);
        MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        gcomm = MPI_COMM_WORLD;

        if(argc != 3) {
            printf("Usage: get <data_size> <num_timesteps>\n");
            return(1);
        }

        totaldata = atoi(argv[1]);
        numts = atoi(argv[2]);

        // DataSpaces: Initalize and identify application
        // Usage: dspaces_init(num_peers, appid, Ptr to MPI comm, parameters)
        // Note: appid for get.c is 2 [for put.c, it was 1]
        dspaces_init(nprocs, 2, &gcomm, NULL);

        // Name our data.
        sprintf(var_name, "ex_sample_data");

        data_decomp(totaldata, rank, nprocs, &datalower, &dataupper);
        datarange = (dataupper-datalower) + 1;
        if(datalower <= dataupper) {
            data = malloc(sizeof(*data) * datarange);
        }
        lb = datalower;
        ub = dataupper;

        for(timestep = 0; timestep < numts; timestep++) {
                //printf("Rank %d: timestep: %d, datarange = %d\n", rank, timestep, datarange);
                wait_for_event("put_data", &gcomm);
    
                // Define the dimensionality of the data to be received 
                int ndim = 1;

                // DataSpaces: Get data array from the space
                // Usage: dspaces_get(Name of variable, version num, 
                // size (in bytes of each element), dimensions for bounding box,
                // lower bound coordinates, upper bound coordinates,
                // ptr to data buffer 
                if(data) {
                    dspaces_get(var_name, timestep, sizeof(*data), ndim,
                            &lb, &ub, data);
                }

                for(i = 0; i < datarange; i++) {
                    printf("Rank %d: Timestep %d: data[%d] = %d\n",
                        rank, timestep, i + datalower, data[i]);
                }
        }

        // DataSpaces: tell the server to terminate
        if(rank == 0) {
            dspaces_kill();
        }

        // DataSpaces: Finalize and clean up DS process
        dspaces_finalize();

        MPI_Barrier(gcomm);
        MPI_Finalize;

        free(data);

        return 0;
}
