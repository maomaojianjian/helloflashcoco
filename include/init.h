#include <stdint.h>
#include "socket.h"

#define NCCL_COMM_ID "192.168.85.137:22"

#define NCCL_UNIQUE_ID_BYTES 128
typedef struct { char internal[NCCL_UNIQUE_ID_BYTES]; } ncclUniqueId;

typedef struct ncclComm* ncclComm_t;

int ncclGetUniqueId(ncclUniqueId* out);

int ncclCommInitRank(ncclComm_t* newcomm, int nranks, ncclUniqueId commId, int myrank);