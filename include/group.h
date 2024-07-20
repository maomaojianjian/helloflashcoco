
#ifndef NCCL_GROUP_H_
#define NCCL_GROUP_H_

extern __thread int ncclGroupDepth;
int ncclGroupStart();

int ncclGroupEnd();

#endif
