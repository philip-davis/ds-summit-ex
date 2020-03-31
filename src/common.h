#ifndef SUMMIT_EX_COMMON
#define SUMMIT_EX_COMMON

#include<mpi.h>
#include<stdlib.h>

void send_event(const char *ename, MPI_Comm *comm);

void wait_for_event(const char *ename, MPI_Comm *comm);

void data_decomp(size_t dsize, int rank, int nranks, int *lb, int *ub);

#endif
