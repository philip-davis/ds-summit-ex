#include<dataspaces.h>
#include<mpi.h>

void send_event(const char *ename, MPI_Comm *comm)
{
    dspaces_lock_on_write(ename, comm);
    dspaces_unlock_on_write(ename, comm);
}

void wait_for_event(const char *ename, MPI_Comm *comm)
{
    dspaces_lock_on_read(ename, comm);
    dspaces_unlock_on_read(ename, comm);
}

