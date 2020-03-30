#ifndef SUMMIT_EX_COMMON
#define SUMMIT_EX_COMMON

#include<mpi.h>

void send_event(const char *ename, MPI_Comm *comm);

void wait_for_event(const char *ename, MPI_Comm *comm);

#endif
