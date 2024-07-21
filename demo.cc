
#include "mpi.h"
#include "nccl.h"
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "init.h"
#include "comm.h"
#include <iostream>

static uint64_t getHostHash(const char *string) {
  // Based on DJB2a, result = result * 33 ^ char
  uint64_t result = 5381;
  for (int c = 0; string[c] != '\0'; c++) {
    result = ((result << 5) + result) ^ string[c];
  }
  return result;
}

static void getHostName(char *hostname, int maxlen) {
  gethostname(hostname, maxlen);
  for (int i = 0; i < maxlen; i++) {
    if (hostname[i] == '.') {
      hostname[i] = '\0';
      return;
    }
  }
}

int main(int argc, char *argv[]) {
  int size = 32 * 1024 * 1024;

  int myRank, nRanks, localRank = 0;

  // initializing MPI
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
  MPI_Comm_size(MPI_COMM_WORLD, &nRanks);

  // calculating localRank which is used in selecting a GPU
  uint64_t hostHashs[nRanks];
  char hostname[1024];
  getHostName(hostname, 1024);
  hostHashs[myRank] = getHostHash(hostname);
  std::cout<< "myRank:" << myRank << "  hostname:" << hostname << std::endl;
  MPI_Allgather(MPI_IN_PLACE, 0, MPI_DATATYPE_NULL, hostHashs,
                         sizeof(uint64_t), MPI_BYTE, MPI_COMM_WORLD);
  for (int p = 0; p < nRanks; p++) {
    if (p == myRank)
      break;
    if (hostHashs[p] == hostHashs[myRank])
      localRank++;
  }

  // each process is using two GPUs
  int nDev = 2;

  float *sendbuff = (float *)malloc(nDev * sizeof(float));
  float *recvbuff = (float *)malloc(nDev * sizeof(float));

  ncclUniqueId id;
  ncclComm_t comms[nDev];

  if (myRank == 0)
    ncclGetUniqueId(&id);
  MPI_Bcast((void *)&id, sizeof(id), MPI_BYTE, 0, MPI_COMM_WORLD);

  // ncclGroupStart();
  // for (int i = 0; i < nDev; i++) {
  //   ncclCommInitRank(comms + i, nRanks * nDev, id, myRank * nDev + i);
  // }
  // ncclGroupEnd();

  // ncclGroupStart();
  // for (int i = 0; i < nDev; i++)
  //   // ncclAllReduce((const void *)(sendbuff + i), (void *)(recvbuff + i),
  //   //                         size, ncclFloat, ncclSum, comms[i], s[i]);
  // ncclGroupEnd();
  free(sendbuff);
  free(recvbuff);
  MPI_Finalize();

  printf("[MPI Rank %d] Success \n", myRank);
  return 0;
}