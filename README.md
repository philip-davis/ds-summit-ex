This repo provides an example of using DataSpaces to create a coupled workflow on Summit. The example builds and run two seperate programs: **put** and **get**.

**put** Populates a 1-D array and signals that the data has been written.
**get** Waits for **put**'s signal, then reads the 1-D array.

The codes run iteratively through multiple timesteps.

**put** and **get** each take two arguments:

`put/get <data size> <# timesteps>`

data size is the total number of integers being written/read across the process groups. # timesteps is the number of iterations. For a given run to be correct, the respective values of these paramters must match for **put** and **get**.

# Building
This has been tested with the gcc compiler on Summit.

The **init.sh** script downloads and builds DataSpaces, the example code, and creates a sample job script.

`init.sh <Project ID>`

Project ID is the project at OLCF that should be used for job submission (e.g. csc143, etc.)

# Running
From the `run/` directory, submit `job.sh` with `bsub job.sh`.

The example job script runs one rank of the dataspaces server, two ranks of **put** on one node eand two ranks of **get** on one node.

# Verify Output
The **verify.sh** script compares the output of **put** and **get** to verify that the same data that was written by **put** was read by **get**.
