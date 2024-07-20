
#ifndef NCCL_COMM_H_
#define NCCL_COMM_H_
#include <stdint.h>

struct ncclComm {
  uint64_t startMagic;
  // int* topParentRanks;
  // int* topParentLocalRanks;
  // int netPluginLoaded;
  // void* bootstrap;
  // uint64_t* connectSend;
  // uint64_t* connectRecv;
  // bool initAlgoChannels[6];
  // bool runtimeConn;
  // int cuMemSupport;

  // uint64_t magic;
  // uint64_t commHash;
  // int rank;
  // int nRanks;
  // int cudaDev;
  // int nvmlDev;
  // int compCap;
  // int minCompCap, maxCompCap;
  // int64_t busId
  // int cudaArch;

  // int cpuArch;
  // int cpuVendor;

  // int node;
  // int nNodes;
  // int localRank;
  // int localRanks;
  // int maxLocalRanks;
  // int* rankToNode;
  // int* rankToLocalRank;
  // int* localRankToRank;
  // struct ncclNodeRanks* nodeRanks;
  // int MNNVL;
  // int cliqueRank;

  // bool checkPointers;
  // bool dmaBufSupport;

  // uint64_t opCount;

  // int nChannels;
  // int collChannels;
  // int nvlsChannels;
  // int nvlsHeads[32];
  // int p2pnChannels;
  // int p2pnChannelsPerPeer;

  // bool allocP2pNetLLBuffers;

  // int buffSizes[3];
  // int p2pChunkSize;
  // int nvlsChunkSize;

  // ssize_t threadThresholds[6][3];
  // float latencies[5][6][3];
  // float bandwidths[5][6][3];
  // float ringbdw[5][3];
  // int maxThreads[6][3];

  // int asyncResult;

  // uint32_t* abortFlag;
  // uint32_t* abortFlagDev;
  // int* abortFlagRefCount;
  // uint32_t* childAbortFlag;
  // uint32_t* childAbortFlagDev;
  // uint32_t destroyFlag;

  // struct ncclDevComm* devComm;

  // uint32_t workArgsBytes;
  // uint32_t workFifoBytes;
  // void* workFifoBuf;
  // void* workFifoBufDev;
  // void* workFifoBufGdrHandle;

  // uint32_t* workFifoConsumed
  // uint32_t workFifoConsumedLeast;
  // uint32_t workFifoProduced;

  // struct ncclComm* intraComm0; 
  // struct ncclComm* intraNext;
  // int intraRank;
  // int intraRanks;
  // uint32_t intraBarrierPhase;
  // char intraPad1[64 - sizeof(uint64_t)];
  // uint64_t intraBarrierCounter; 
  // char intraPad2[64 - sizeof(uint64_t)];
  // uint64_t intraBarrierGate;

  // struct ncclProxyState* proxyState;
  // int proxyRefCountOld;
  
  // int collNetSupport;
  // bool collNetRegSupport;
  // uint8_t collNetSupportMatrix[4][10];
  // int intraHighestTransportType;
  // int* collNetHeads;
  // int collNetHeadsNum;
  // int* collNetDenseToUserRank;
  // int* collNetUserToDenseRank;
  // int nvlsSupport;
  // int nvlsRegSupport;
  // struct ncclComm* groupNext;
  // struct ncclComm* preconnectNext;
  // int persistentRefs;
  // struct P2pSchedulePair { int sendRank; int recvRank; } *p2pSchedule;

  // int userRedOpCapacity, userRedOpFreeHead;
  // bool finalizeCalled;
  // int finalizeRankCnt;
  // struct ncclGroupJob *groupJob;

  // int tunerPluginLoaded;
  // void *tunerContext;
  // uint64_t endMagic;
};

#endif
