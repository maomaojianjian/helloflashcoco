#include "group.h"

__thread int ncclGroupDepth = 0;

inline int ncclGroupStartInternal() {
  ncclGroupDepth++;
  return 0;
}



int ncclGroupStart() {
  int ret = 0;
  ncclGroupStartInternal();
  return ret;
}

int ncclGroupEndInternal() {
#ifdef testaaa
  int ret = 0;
  ncclSimInfo_t internalSimInfo = NCCL_SIM_INFO_INITIALIZER;
  ncclSimInfo_t* internalSimInfoPtr = NULL;
  size_t realSize = 0;

  internalSimInfo.magic = 0;

  if (ncclGroupDepth == 0) {
    WARN("ncclGroupEnd: not in a group call.");
    ret = ncclInvalidUsage;
    goto exit;
  }

  if ((--ncclGroupDepth) > 0) goto exit;

  if ((ret = ncclGroupError) != ncclSuccess) goto fail;

  if (ncclGroupCommHead != nullptr || !ncclIntruQueueEmpty(&ncclAsyncJobs) || ncclGroupCommPreconnectHead != nullptr) {
    ncclGroupJobMain.groupCommHeadPtr = &ncclGroupCommHead;
    ncclGroupJobMain.groupCommPreconnectHeadPtr = &ncclGroupCommPreconnectHead;
    ncclGroupJobMain.groupErrorPtr = &ncclGroupError;
    ncclGroupJobMain.asyncJobsPtr = &ncclAsyncJobs;
    ncclGroupJobMain.abortFlagPtr = &ncclGroupJobAbortFlag;
    ncclGroupJobMain.groupBlockingPtr = &ncclGroupBlocking;
    ncclGroupJobMain.initialized = true;
    ncclGroupJobMainPtr = &ncclGroupJobMain;
    /* make sure ncclGroupBlocking has been set. */
    assert(ncclGroupBlocking == 0 || ncclGroupBlocking == 1);
    if (ncclGroupBlocking == 0 && (ncclGroupCommPreconnectHead != nullptr || !ncclIntruQueueEmpty(&ncclAsyncJobs))) {
      /* nonblocking group */
      if (!ncclIntruQueueEmpty(&ncclAsyncJobs)) {
        ncclAsyncJob* job = ncclIntruQueueHead(&ncclAsyncJobs);
        do {
          NCCLCHECKGOTO(ncclCommSetAsyncError(job->comm, ncclInProgress), ret, fail);
          job->comm->groupJob = ncclGroupJobMainPtr;
          job = job->next;
        } while (job);
      }

      if (ncclGroupCommHead) {
        ncclComm_t comm = ncclGroupCommHead;
        do {
          NCCLCHECKGOTO(ncclCommSetAsyncError(comm, ncclInProgress), ret, fail);
          /* link group job to communicators. */
          comm->groupJob = ncclGroupJobMainPtr;
          comm = comm->groupNext;
        } while (comm);
      }

      ncclGroupJobMainPtr->base.func = groupLaunchNonBlocking;
      SYSCHECKGOTO(pthread_create(&ncclGroupJobMainPtr->base.thread, NULL, ncclAsyncJobMain, (void*)&ncclGroupJobMainPtr->base), ret, fail);
      ret = ncclInProgress;
    } else {
      /* blocking group */
      NCCLCHECKGOTO(groupLaunch(&ncclGroupJobMainPtr->base, internalSimInfoPtr), ret, fail);
      groupResetJobState(ncclGroupJobMainPtr);
    }
  }

exit:
  return ret;
fail:
  groupCleanup(&ncclGroupCommHead, &ncclGroupCommPreconnectHead, &ncclAsyncJobs, &ncclGroupError, &ncclGroupBlocking, &ncclGroupJobAbortFlag, ret);
  goto exit;
#endif
return 0;
}

int ncclGroupEnd() {
  int ret = 0;
  ncclGroupEndInternal();
exit:
  return ret;
}
