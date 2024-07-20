#ifndef NCCL_H_
#define NCCL_H_

#include "group.h"
#include "stddef.h"

#define NCCL_SOCKET_IFNAME "eth0"

#define NCCL_MAGIC 0x0280028002800280

#define NCCL_CONFIG_INITIALIZER {                                       \
  sizeof(ncclConfig_t), /* size */                                      \
  0xcafebeef,           /* magic */                                     \
}

typedef struct ncclConfig_v21700 {
  size_t size;
  unsigned int magic;
} ncclConfig_t;

#endif