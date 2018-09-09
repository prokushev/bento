#include "cmcontainer.h"

/* 

Containers (files and blocks of memory) are always accessed through handlers, to
provide platform independence and support nested containers. Handlers are responsible
for creating a container if necessary, opening and closing it, managing stream I/O to
it, and reading and writing the container label (which provides such information as the
location of the Table of Contents). The interfaces to container handlers are documented
in the Appendix B.

The types of storage that can be used as containers are limited only by the types of
handlers available.

*/

/*
This routine can be used to get at the user's session refCon saved as part of the
session data created by CMStartSession(). The session data is "tied" to each container
created by CMOpen[New]Container(). Thus typically the refCon will be accessed via a
container refNum.

*/

CMRefCon APIENTRY CMGetSessionRefCon(CMContainer container)
{
  // Указатель на внутренние данные сессии.
  CMSessionInternalData sessionData=((ContainerPtr)container)->sessionData;
  
  // Проверяем входнае данные
  if (!container) return NULL;
  if (!sessionData) return NULL;
  
  // Возращаем указатель на данные пользователя
  return sessionData->refCon;
}


/*

This routine may be called to change the user's session refCon associated with the
session data.

*/

void APIENTRY CMSetSessionRefCon(CMContainer container,
                                 CMRefCon refCon)
{
  // Указатель на внутренние данные сессии.
  CMSessionInternalData sessionData=((ContainerPtr)container)->sessionData;

  // Сохраняем указатель на данные пользователя  
  sessionData->refCon = (!container||!sessionData) ? NULL : refCon;
}




void CMGetContainerInfo(const CMContainer container,
CMGeneration *generation,
CMContainerFlags *containerFlags,
CMGlobalName typeName);

/* The corresponding values for the designated container are returned. NULL may be
passed for any reference; in that case the corresponding value is not returned.
CMSession CMGetSession(CMContainer container)
The session global data pointer returned from CMStartSession() is passed to most of
the handler routines defined in this file. This routine is provided to make it easier to
retrieve the pointer as a function of the container refNum.

*/

VOID CMCloseContainer(CMContainer container);

/* 
If the container was open for writing, all I/O to the designated container is
completed, and the table of contents and label are built and written out.

This call closes the specified container and all its currently opened embedded
containers (if any).

This call destroys the association between the container refnum and the designated
container. On return the specifed container refNum and all the others corresponding to
the embedded containers are invalid. All memory associated with a container's data
structures is freed. After this call the container refNum may be returned by a subsequent
CMOpenContainer call, designating another container.

*/

VOID CMAbortContainer(CMconst_CMContainer container);

/*

The container is closed without further writing to the container, i.e., as if it were
opened for reading even when opened for writing. This is intended to be used to abort
processing of the container from unrecoverable errors.

All memory allocated by the container data structures is freed (if possible) and the
container close handler called to physically close the container. All dynamic values
currently in use are released in an attempt to allow them to properly clean up any files
and memory allocated by their handlers. No further API calls should be done on the
container as it will be closed upon return.

Note, this routine will return to its caller. It is up to the user to actually abort execution
if that is required.

*/

CMObject CMGetNextObject(CMContainer targetContainer,
CMObject currObject);

/*

A refum for the next object defined in the same container is returned. currObject is
generally a refNum previously returned from this routine. Successive calls to this routine
will thus yield all the objects in the container.
Objects are returned in order of increasing ID. If there are no larger object IDs
defined, NULL is returned. To begin the iteration, pass NULL as the object refnum.
Since type and property descriptions are objects, they will be returned in sequence
as they are encountered. Only objects in the current container will be returned, not objects
in any base containers.

*/
