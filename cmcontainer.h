#ifndef _cmcontainer_h_
#define _cmcontainer_h_

typedef struct CMContainer_ *CMContainer;

CMContainer CMOpenContainer(CMSession sessionData, CMRefCon attributes, const CMGlobalName typeName, CMContainerUseMode useFlags);

CMContainer CMOpenNewContainer(CMSession sessionData,
CMRefCon attributes,
const CMGlobalName typeName,
CMContainerUseMode useFlags,
CMGeneration generation,
CMContainerFlags containerFlags,
...);

VOID CMGetContainerInfo(const CMContainer container, CMGeneration *generation, CMContainerFlags *containerFlags, CMGlobalName typeName);

VOID CMCloseContainer(CMContainer container);

VOID CMAbortContainer(CMconst_CMContainer container);

#endif /* _cmcontainer_h_ */
