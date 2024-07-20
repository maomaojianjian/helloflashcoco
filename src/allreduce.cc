#include "allreduce.h"
#include "stddef.h"
#include "comm.h"

int ncclEnqueueCheck(struct ncclInfo* info) {
#ifdef testaaa
  ncclGroupStartInternal();
  int ret = ncclSuccess;
  int devOld = -1;

  CommCheck(info->comm, info->opName, "comm");
  ncclCommEnsureReady(info->comm);

  if (info->comm->checkPointers) {
    CUDACHECKGOTO(cudaGetDevice(&devOld), ret, fail);
    CUDACHECKGOTO(cudaSetDevice(info->comm->cudaDev), ret, fail);
  }
  ArgsCheck(info);

  taskAppend(info->comm, info);

exit:
  if (devOld != -1) CUDACHECK(cudaSetDevice(devOld));
  ncclGroupErrCheck(ret);
  ncclGroupEndInternal();
  if (info->comm && !info->comm->config.blocking) { (ncclCommGetAsyncError(info->comm, &ret)) };
  return ret;
fail:
  if (info->comm && !info->comm->config.blocking) (void) ncclCommSetAsyncError(info->comm, ret);
  goto exit;
#endif
return 0;
}

void ncclAllReduce(const void* sendbuff, void* recvbuff, size_t count,
    ncclComm* comm) {
#ifdef testaaa
  struct NvtxParamsAllReduce {
    size_t bytes;
    ncclRedOp_t op;
  };
  static constexpr nvtxPayloadSchemaEntry_t AllReduceSchema[] = {
    {0, NVTX_PAYLOAD_ENTRY_TYPE_SIZE, "Message size [bytes]"},
    {0, NVTX_PAYLOAD_ENTRY_NCCL_REDOP, "Reduction operation", nullptr, 0,
      offsetof(NvtxParamsAllReduce, op)}
  };

  struct ncclInfo info = { ncclFuncAllReduce, "AllReduce", sendbuff, recvbuff, count, 0, comm, /* Args */
    ALLREDUCE_CHUNKSTEPS, ALLREDUCE_SLICESTEPS };
  ncclEnqueueCheck(&info);
  return 1;
#endif
}