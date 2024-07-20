
#ifndef NCCL_BOOTSTRAP_H_
#define NCCL_BOOTSTRAP_H_

#include "nccl.h"
#include "comm.h"
#include "socket.h"
#include <pthread.h>

struct ncclBootstrapHandle {
  uint64_t magic;
  union ncclSocketAddress addr;
};
// static_assert(sizeof(struct ncclBootstrapHandle) <= sizeof(ncclUniqueId), "Bootstrap handle is too large to fit inside NCCL unique ID");

int bootstrapNetInit();
int bootstrapCreateRoot(struct ncclBootstrapHandle* handle, bool idFromEnv);
int bootstrapGetUniqueId(struct ncclBootstrapHandle* handle);
// int bootstrapInit(struct ncclBootstrapHandle* handle, struct ncclComm* comm);
// int bootstrapSplit(struct ncclBootstrapHandle* handle, struct ncclComm* comm, struct ncclComm* parent, int color, int key, int* parentRanks);
// int bootstrapAllGather(void* commState, void* allData, int size);
// int bootstrapSend(void* commState, int peer, int tag, void* data, int size);
// int bootstrapRecv(void* commState, int peer, int tag, void* data, int size);
// int bootstrapBarrier(void* commState, int rank, int nranks, int tag);
// int bootstrapBroadcast(void* commState, int rank, int nranks, int root, void* bcastData, int size);
// int bootstrapIntraNodeBarrier(void* commState, int *ranks, int rank, int nranks, int tag);
// int bootstrapIntraNodeAllGather(void* commState, int *ranks, int rank, int nranks, void* allData, int size);
// int bootstrapIntraNodeBroadcast(void* commState, int *ranks, int rank, int nranks, int root, void* bcastData, int size);
// int bootstrapClose(void* commState);
// int bootstrapAbort(void* commState);
#endif
