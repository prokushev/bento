/* Container Manager Error Reporting Support  */
/* Based on Bento Specification Revision 1.0d5 */
/* Author: Yuri Prokushev (C) 2015 */

#include <stdlib.h>
#include <string.h>

#include "cmerrors.h"

#define MAX_MSG_LENGTH 1024

/*

This routine takes the (error) message string in msgString and replaces all
substrings of the form "^n" with the inserts from the variable arg list of insert strings. The
function returns the edited msgString as its result.

The string buffer must be passed in msgString. Its max length is also specified but
this must be a value less than or equal 1024 (not including delimiting null). The message
will be truncated to fit in the buffer. The string pointer is returned as the function result.
The substring "^0" is replaced with the first insert. "^1" is replaced with the second
insert, and so on. It is assumed that there are enough insert strings to cover all the "^n"s
called for (not unlike printf()).

Note, the "^n"s in the message string do not have to be in ascending order. Thus
"^1" could occur before "^0" in the msgString.

*/

CMErrorString CMAddMsgInserts(CMErrorString msgString, CMSize maxLength, ...)
{
  va_list inserts;

  va_start(inserts, maxLength);

  CMVAddMsgInserts(msgString, maxLength, inserts);

  va_end(inserts);

  return (msgString);
}


/*

This routine is the same as CMAddMsgInserts() above, except that the extra
(inserts) arguments are given as a variable argument list as defined by the "stdarg" facility.

*/

CMErrorString CMVAddMsgInserts(CMErrorString msgString, CMSize maxLength, va_list inserts)
{
	CM_CHAR 		 	c, *src, *dst, *p, *insert, msgString0[MAX_MSG_LENGTH];
	CM_ULONG			cnt = (unsigned long)maxLength;
	va_list 			inserts0;
	CM_LONG				n;
	
printf("10\n");
	src = strcpy(msgString0, (dst = msgString));
printf("11\n");
        va_copy(inserts0, inserts);
printf("12\n");
	
	while (((CMBoolean)(c = *src++)) && cnt > 0) {/* scan src buffer for "^n"s...						*/
printf("15\n");
		if (c != '^') {														/* if we don't hace an "^n"...						*/
			*dst++ = c;															/* ...just copy src to dst (output) buffer*/
			--cnt;																	/* ...make sure we don't exceed maxLen		*/
			continue;
		}
printf("16\n");
	
		n = strtoul(src, &p, 10); /* extract the insert number (n) from "^n"*/
		if (p == src) {		/* leave a lone "^" alone											*/
			*dst++ = c;	/* ...they are treated like normal chars	*/
			--cnt;
			continue;
		}
		
printf("17\n");
		inserts=inserts0;												/* get n'th insert (there better be one!)	*/
printf("18\n");
		while (n-- >= 0)													/* there's no way to chk that there isn't	*/
			insert = va_arg(inserts, CM_CHAR *);
	
printf("19\n");
		while (*insert && cnt > 0) {/* copy the insert to the dst buffer... 	*/
			*dst++ = *insert++;
			--cnt;		/* ..careful here too about going to far	*/
		}
printf("20\n");
		
		src = p;																	/* point past "^n" in the input string		*/
printf("21\n");
	} /* while */																/* keep scanning the src, copying to dst	*/
printf("13\n");
	
	*dst = '\0';																/* that's all there is to it!							*/
printf("14\n");
	return (msgString);
}

/* 

This routine takes a defined Container Manager (error) message number and its
corresponding insert strings and returns a (english) string corresponding to the message
number with the inserts filled into their proper positions. It is assumed the error number
and inserts were the ones reported to the error handler.
The string buffer must be passed in errorString. Its max length is also specified but
this must be a value less than or equal 1024 (not including delimiting null). The message
will be truncated to fit in the buffer. The string pointer is returned as the function result.
This routine is provided as a convenience to easily convert the error codes and their
corresponding inserts to a printable string.

*/

CMErrorString CMGetErrorString(CMErrorString errorString, CMSize maxLength, CMErrorNbr errorNumber, ...)
{
  va_list inserts;

  va_start(inserts, maxLength);
printf("1\n");
  CMVGetErrorString(errorString, maxLength, errorNumber, inserts);
printf("2\n");

  va_end(inserts);

  return (errorString);
}



//char *CMReturnContainerName(CMContainer container)
//{
//}

/*
Generally the errors reported are provided with at least one insert that identifies
which container we're talking about. The wording of the messages defined for the
Container Manager assume this identification insert. The identification takes the form of
the container "name" which is obtained from a handler routine provided for that purpose.
This routine is provided to test if the container metahandler provides a name
handler, and call the handler if it exists. If it doesn't exist the container type name is
returned.

Note, this routine is available to handler writers so that they can generalize their
error reporting/message routines and word their messages with the container identification.

*/


/* 

In the list of error code definitions below, the comment is the error message that is
provided for the error code. The "^n"s (^0, ^1, etc.) in the comments show where the
inserts would go. ^0 is the first insert, ^1 the second, and so on.

*/

/*
This routine is the same as CMGetErrorString() above, except that the extra
(inserts) arguments are given as a variable argument list as defined by the "stdarg" facility.
*/

#define ERR_MSG(num, msg) case num: msgStr=(CM_PCHAR)msg; break;

CMErrorString CMVGetErrorString(CMErrorString errorString, CMSize maxLength, CMErrorNbr errorNumber, va_list inserts)
{
  CMErrorString msgStr, msg[MAX_MSG_LENGTH];
  CMBoolean	gotInserts = TRUE;

printf("3\n");

  switch (errorNumber) {
    case CMERR_GenericMessage: msgStr = (CMErrorString)"^0"; gotInserts = TRUE; break;
    case CMERR_BadTocSize: msgStr = (CMErrorString)"TOC index table size out of range (^0 <= range <= ^1)"; break;
    case CMERR_NoSession: msgStr = (CMErrorString)"Unable to allocate session (task) global data"; break;
    case CMERR_NoHandler: msgStr = (CMErrorString)"Cannot allocate space for handler for type \"^0\""; break;
    case CMERR_BadWriteUse: msgStr = (CMErrorString)"Cannot do a CMOpenNewContainer(...^0...) with useFlags set for update-in-place"; break;
    case CMERR_NoContainer: msgStr = (CMErrorString)"Cannot allocate CCB space for type \"^0\""; break;
    case CMERR_UndefMetaHandler: msgStr = (CMErrorString)"Metahandler was not defined for type \"^0\""; break;
    case CMERR_HandlerError: msgStr = (CMErrorString)"Allocation problem while looking up handler for type \"^0\""; break;
    case CMERR_NullMetaPtr: msgStr = (CMErrorString)"Null metahandler pointer for type \"^0\""; break;
    case CMERR_UndefRoutine: msgStr = (CMErrorString)"Handler routine(s) missing for operation type(s): ^0"; break;
    case CMERR_NoTOC: msgStr = (CMErrorString)"Cannot allocate TOC for container \"^0\""; break;
    case CMERR_BadReadUse: msgStr = (CMErrorString)"Cannot do a CMOpenContainer(...\"^0\"...) with useFlags set for ^1"; break;
    case CMERR_BadMagicBytes: msgStr = (CMErrorString)"Invalid magic byte sequence in label for container \"^0\" - expected \"^1\", got \"^2\""; break;
    case CMERR_BadVersion: msgStr = (CMErrorString)"Invalid version fields in label for container \"^0\" - expected ^2.^3, got ^4.^5"; break;
    case CMERR_BadTOCRead: msgStr = (CMErrorString)"Incorrect byte length read while reading TOC for container \"^0\""; break;
    case CMERR_NoObjEntry: msgStr = (CMErrorString)"Cannot allocate space for TOC object entry for container \"^0\""; break;
    case CMERR_MultDef: msgStr = (CMErrorString)"Multiple definition for TOC object ^0 for container \"^1\""; break;
    case CMERR_NoPropEntry: msgStr = (CMErrorString)"Cannot allocate space for TOC property entry for container \"^0\""; break;
    case CMERR_BadContinue: msgStr = (CMErrorString)"Invalid continued value (inconsistent types) in container \"^0\""; break;
    case CMERR_NoValueEntry: msgStr = (CMErrorString)"Cannot allocate space for TOC value entry for container \"^0\""; break;
    case CMERR_BadOffset: msgStr = (CMErrorString)"Invalid offset or value (^0, ^1) for TOC value entry for container \"^2\""; break;
    case CMERR_UndefObjects: msgStr = (CMErrorString)"There is (are) ^0 undefined object(s) in container \"^1\""; break;
    case CMERR_NoStrValue: msgStr = (CMErrorString)"Cannot allocate space for constant value in container \"^0\""; break;
    case CMERR_DupBaseType: msgStr = (CMErrorString)"Cannot add dup base type \"^0\" to type \"^1\" in container \"^2\""; break;
    case CMERR_BadTOCWrite: msgStr = (CMErrorString)"Incorrect byte length written while writing TOC for \"^0\""; break;
    case CMERR_NotGlobalName: msgStr = (CMErrorString)"Have global name tied to value of wrong type in containter \"^0\""; break;
    case CMERR_BadGNameWrite: msgStr = (CMErrorString)"Incorrect byte length written while writing global name \"^0\" in container \"^1\""; break;
    case CMERR_DupGlobalName: msgStr = (CMErrorString)"Duplicate global name definition for \"^0\" in container \"^1\""; break;
    case CMERR_MultGlblNames: msgStr = (CMErrorString)"Object ^0 alread defined -- trying to redefine it for \"^1\" (container \"^2\")"; break;
    case CMERR_NoGlobalName: msgStr = (CMErrorString)"Cannot allocate space for global name \"^0\" in container \"^1\""; break;
    case CMERR_NoGNameLoad: msgStr = (CMErrorString)"Cannot allocate space for global name during load in container \"^0\""; break;
    case CMERR_BadGNameRead: msgStr = (CMErrorString)"Incorrect byte length read while reading global name in container \"^0\""; break;
    case CMERR_NotGName: msgStr = (CMErrorString)"Invalid global name string read in container \"^0\""; break;
    case CMERR_BadType: msgStr = (CMErrorString)"Invalid ^0 type passed to ^1 for container \"^2\""; break;
    case CMERR_2Containers: msgStr = (CMErrorString)"Objects not in same containers (containers \"^0\" and \"^1\")"; break;
    case CMERR_3Containers: msgStr = (CMErrorString)"Objects not in same containers (containers \"^0\", \"^1\", and \"^2\")"; break;
    case CMERR_MissingMinIDSeed: msgStr = (CMErrorString)"Min ID seed value missing in TOC object 1 in container \"^0\""; break;
    case CMERR_MissingTOCObj: msgStr = (CMErrorString)"TOC object ID 1 missing in TOC in container \"^0\""; break;
    case CMERR_NotConverting: msgStr = (CMErrorString)"Cannot use CMDefineValueData except for converting container \"^0\""; break;
    case CMERR_BadDefineData: msgStr = (CMErrorString)"Attempt to define offset (^0) out of range in container \"^1\""; break;
    case CMERR_BadValue: msgStr = (CMErrorString)"Attempt to use a deleted value in container \"^0\""; break;
    case CMERR_BadObject: msgStr = (CMErrorString)"Attempt to use a deleted object in container \"^0\""; break;
    case CMERR_BadContainer: msgStr = (CMErrorString)"Container for ^0 (\"^1\") does not belong to the container being used (\"^2\")"; break;
    case CMERR_NoValue: msgStr = (CMErrorString)"No value defined for object ID ^0, property \"^1\" in container \"^2\""; break;
    case CMERR_HasValue: msgStr = (CMErrorString)"Cannot set a (sub)value to an already defined value (container \"^0\")"; break;
    case CMERR_AlreadyReleased: msgStr = (CMErrorString)"Attempting to release a value already completely released in container \"^0\""; break;
    case CMERR_NotReleased: msgStr = (CMErrorString)"A dynamic value has not been fully released in container \"^0\""; break;
    case CMERR_MissingFreeTotal: msgStr = (CMErrorString)"Total free space value missing in TOC object 1 in container \"^0\""; break;
    case CMERR_DupType: msgStr = (CMErrorString)"Attempt to insert two values with the same type (^0) in container \"^1\""; break;
    case CMERR_HasNoValue: msgStr = (CMErrorString)"No value defined for CMReadValueData in container \"^0\""; break;
    case CMERR_BadWrite: msgStr = (CMErrorString)"Write error writing to container \"^0\""; break;
    case CMERR_CantWriteGlbl: msgStr = (CMErrorString)"Cannot write to a global name in container \"^0\""; break;
    case CMERR_Offset2Big: msgStr = (CMErrorString)"Write/insert offset (^0) beyond end of a value in container \"^1\""; break;
    case CMERR_Internal1: msgStr = (CMErrorString)"Internal error! Unknown flags setting (0x^0)"; break;
    case CMERR_MissingIDSeed: msgStr = (CMErrorString)"ID seed value missing in TOC object 1 in container \"^0\""; break;
    case CMERR_AmbiguousType: msgStr = (CMErrorString)"^0 object is ambiguous in container \"^1\""; break;
    case CMERR_TypeNotGlobal: msgStr = (CMErrorString)"^0 object is not for a global name in container \"^1\""; break;
    case CMERR_MissingFreeList: msgStr = (CMErrorString)"Internal error - empty free list for property in container \"^0\""; break;
    case CMERR_NoNewValueHandler: msgStr = (CMErrorString)"A \"new value\" handler is not defined for type \"^0\""; break;
    case CMERR_UndefReference: msgStr = (CMErrorString)"Object ID ^0 from a reference is undefined in container \"^1\""; break;
    case CMERR_BadObjectKind: msgStr = (CMErrorString)"Invalid kind of object -- expected ^0 in container \"^1\""; break;
    case CMERR_WriteIllegal1: msgStr = (CMErrorString)"Cannot write to a container (\"^0\") opened for reading"; break;
    case CMERR_WriteIllegal2: msgStr = (CMErrorString)"Attempt to write to a protected object in container \"^0\""; break;
    case CMERR_ReadIllegal: msgStr = (CMErrorString)"Cannot read from a container (\"^0\") opened for writing"; break;
    case CMERR_MissingSize: msgStr = (CMErrorString)"Size value missing in TOC object 1 in container \"^0\""; break;
    case CMERR_BadSize: msgStr = (CMErrorString)"Inconsistent size values between container label and TOC (container \"^0\")"; break;
    case CMERR_Internal2: msgStr = (CMErrorString)"Internal error! TOC offset to offset/size value not found in container \"^0\""; break;
    case CMERR_CantDelete1: msgStr = (CMErrorString)"Attempt to delete to a protected object in container \"^0\""; break;
    case CMERR_CantDelete2: msgStr = (CMErrorString)"Attempt to delete to a property with a protected value in container \"^0\""; break;
    case CMERR_CantDelete3: msgStr = (CMErrorString)"Attempt to delete to a protected value in container \"^0\""; break;
    case CMERR_StillOpen: msgStr = (CMErrorString)"Container \"^0\" is still open at session close time"; break;
    case CMERR_EmptyRead: msgStr = (CMErrorString)"Cannot read from an empty embedded container value (container \"^0\")"; break;
    case CMERR_NoEmbedding: msgStr = (CMErrorString)"Cannot allocate space to save embedding status while opening container \"^0\""; break;
    case CMERR_BadGenNbr: msgStr = (CMErrorString)"Invalid generation number (^0) passed to ^1 (container \"^2\")"; break;
    case CMERR_NoRef: msgStr = (CMErrorString)"Connot allocate space for an object reference in container \"^0\")"; break;
    case CMERR_CantGetBase: msgStr = (CMErrorString)"CMGetBaseValue() may only be called from a dynamic value handler in container \"^0\""; break;
    case CMERR_MultTypeProp: msgStr = (CMErrorString)"Attempt to register a ^0 name (^1) in container \"^2\" -- already defined as a ^3"; break;
    case CMERR_NotSameMode: msgStr = (CMErrorString)"Embedded container (\"^0\") must be opened in same mode as its parent (\"^1\")"; break;
    case CMERR_CantDelete4: msgStr = (CMErrorString)"Cannot delete a value currently in use in container \"^0\""; break;
    case CMERR_MissingHandler: msgStr = (CMErrorString)"Memory allocator and dealocator handlers must be supplied"; break;
    case CMERR_NoMissingBuffer: msgStr = (CMErrorString)"Unable to allocate private temporary buffer while opening type \"^0\""; break;
    case CMERR_MoveIllegal: msgStr = (CMErrorString)"Cannot move a value in a container (\"^0\") not opened for writing"; break;
    case CMERR_DeleteIllegal: msgStr = (CMErrorString)"Attempt to delete ^0 in a container (\"^1\") not opened for writing"; break;
    case CMERR_BadDefineType: msgStr = (CMErrorString)"Attempt to define additional data for a immediate value in container \"^0\""; break;
    case CMERR_NoExtensions: msgStr = (CMErrorString)"Cannot allocate space for TOC dynamic value entry for type \"^0\" in container \"^1\""; break;
    case CMERR_HandlerRecursed: msgStr = (CMErrorString)"Attempt to use dynamic value handler for ^0() recursively in container \"^1\""; break;
    case CMERR_BadRealValue: msgStr = (CMErrorString)"Invalid base (\"real\") value passed to ^0() in container \"^1\""; break;
    case CMERR_NoMetahandler: msgStr = (CMErrorString)"A value operations metahandler is not defined for type \"^0\" in container \"^1\""; break;
    case CMERR_NotDynValue: msgStr = (CMErrorString)"A \"use value\" metahandler did not create a dynamic value in container \"^0\""; break;
    case CMERR_NoGlobalTable: msgStr = (CMErrorString)"Cannot allocate globally unique name table for container \"^0\""; break;
    case CMERR_BadMetaSpec: msgStr = (CMErrorString)"Invalid metadata format specification (%^0) for type \"^1\" in container \"^2\""; break;
    case CMERR_NoDeletesList: msgStr = (CMErrorString)"Internal error - empty \"deletes\" list for property in container \"^0\""; break;
    case CMERR_NoDataPacket: msgStr = (CMErrorString)"Cannot allocate space for data packet for type \"^0\" in container \"^1\""; break;
    case CMERR_BaseRelAttempted: msgStr = (CMErrorString)"A dynamic value release handler attempted to release its base in container \"^0\""; break;
    case CMERR_NoDynMetahandler: msgStr = (CMErrorString)"\"Use value\" handler for type \"^0\" in container \"^1\" MUST return a metahandler"; break;
    case CMERR_MissingTotalSize: msgStr = (CMErrorString)"Total container size value missing in TOC object 1 in container \"^0\""; break;
    case CMERR_Internal3: msgStr = (CMErrorString)"Internal error! TOC offset to container value not found in container \"^0\""; break;
    case CMERR_AmbiguousUseFlags: msgStr = (CMErrorString)"Ambiguous updating useFlags passed to CMOpenNewContainer (...\"^0\"...) - ^1"; break;
    case CMERR_NoTypeHandler: msgStr = (CMErrorString)"Dynamic value type handler not defined for updating in container \"^0\""; break;
    case CMERR_NotDynamicValue: msgStr = (CMErrorString)"Dynamic value in container \"^0\" not created to access target for updating"; break;
    case CMERR_NoMetaDataHandler: msgStr = (CMErrorString)"A \"metadata\" handler is not defined for type \"^0\""; break;
    case CMERR_NoDataBuffer: msgStr = (CMErrorString)"Cannot allocate space for data I/O buffer in container \"^0\""; break;
    case CMERR_BadUpdateRead: msgStr = (CMErrorString)"Incorrect byte length read while reading updates in container \"^0\""; break;
    case CMERR_BadUpdateWrite: msgStr = (CMErrorString)"Write error while writing updates in container \"^0\""; break;
    case CMERR_Internal4: msgStr = (CMErrorString)"Internal error! End-of-updates signal not detected in container \"^0\""; break;
    case CMERR_Internal5: msgStr = (CMErrorString)"Internal error! TOC offset to updates TOC subsection not found in container \"^0\""; break;
    case CMERR_NoNewValuesTOC: msgStr = (CMErrorString)"\"New values\" TOC offset/size missing in TOC object 1 in container \"^0\""; break;
    case CMERR_wrappedIDs: msgStr = (CMErrorString)"Too many objects in container \"^0\" or next user object ID > 0xFFFFFFFF"; break;
    case CMERR_NoTouchedEntry: msgStr = (CMErrorString)"Cannot allocate space for recording updating operation in container \"^0\""; break;
    case CMERR_NoUpdateObject: msgStr = (CMErrorString)"Container \"^0\" updating -- cannot find object ID ^1 to be ^2"; break;
    case CMERR_NoUpdateProperty: msgStr = (CMErrorString)"Container \"^0\" updating -- cannot find a property ID ^1 in object ID ^2 to be ^3"; break;
    case CMERR_BadUpdateControl: msgStr = (CMErrorString)"Container \"^0\" updating -- unknown control byte read (0x^1, during ^2)"; break;
    case CMERR_NoUpdateType: msgStr = (CMErrorString)"Container \"^0\" updating -- cannot find value (type ID ^1) in object ^2, property ^3"; break;
    case CMERR_UndefUpdateObject: msgStr = (CMErrorString)"Container \"^0\" updating -- cannot find ^1 (ID ^2) to use in ^3"; break;
    case CMERR_UpdateBadGenNbr: msgStr = (CMErrorString)"Container \"^0\" updating -- invalid generation number (^1)"; break;
    case CMERR_BadInsertData: msgStr = (CMErrorString)"Container \"^0\" updating -- bad updating info (0 segment insert encountered)"; break;
    case CMERR_BadInsertOffset: msgStr = (CMErrorString)"Container \"^0\" updating -- insert offset (^1) beyond end of a value"; break;
    case CMERR_CantRepImmediate: msgStr = (CMErrorString)"Container \"^0\" updating -- attempt to replace non-immediate with immediate"; break;
    case CMERR_CantRepBaseType: msgStr = (CMErrorString)"Container \"^0\" updating -- attempt to replace non-base type value with a base type"; break;
    case CMERR_CantReference: msgStr = (CMErrorString)"Value and referenced object not in the same containers (containers \"^0\" and \"^1\")"; break;
    case CMERR_GlobalNameError: msgStr = (CMErrorString)"Allocation problem while looking up global name \"^0\" in container \"^1\""; break;
    case CMERR_FlushErr: msgStr = (CMErrorString)"Error detected in flushing output while closing container ^0"; break;
    case CMERR_CantDelete5: msgStr = (CMErrorString)"Cannot delete an object with unreleased dynamic values in use in container \"^0\""; break;
    case CMERR_NoTOCBuffer: msgStr = (CMErrorString)"Cannot allocate space for TOC I/O buffer in container \"^0\""; break;
    case CMERR_BadTOCCode: msgStr = (CMErrorString)"Invalid TOC code read (0x^0) from TOC in container \"^1\""; break;
    case CMERR_TOCoutOfSync: msgStr = (CMErrorString)"TOC reading out-of-sync (trying to read across buffer boundary) in container \"^0\""; break;
    case CMERR_TOCParseErr1: msgStr = (CMErrorString)"TOC parse error - expected object ID, got 0x^0 in container \"^1\""; break;
    case CMERR_TOCParseErr2: msgStr = (CMErrorString)"TOC \"parse\" error - got 0x^0 at an unexpected time in container \"^1\""; break;
    case CMERR_Unsupported1: msgStr = (CMErrorString)"8-byte offset in container \"^0\" are not supported in this implementation"; break;
    case CMERR_CantDelete6: msgStr = (CMErrorString)"Cannot delete an object currently in use in container \"^1\""; break;
    case CMERR_AlreadyReleased2: msgStr = (CMErrorString)"Attempting to release an object already completely released in container \"^0\""; break;
    case CMERR_BadRefRead: msgStr = (CMErrorString)"Read error while reading references in container ^0"; break;
    case CMERR_Internal6: msgStr = (CMErrorString)"Internal error! Missing reference property or value in container \"^0\""; break;
    case CMERR_ZeroRefKey: msgStr = (CMErrorString)"Attempt to use a CMReference key of 0 in container \"^0\""; break;
    case CMERR_NoRefShadowList: msgStr = (CMErrorString)"Cannot allocate space to record reference in container \"^0\""; break;
    default: msgStr = (CMErrorString)errorString; gotInserts = FALSE;  break;
  }

printf("4\n");

  if (gotInserts) CMVAddMsgInserts(msgStr, maxLength, inserts);
printf("5\n");

  if ((CMSize)strlen(msgStr) <= maxLength)
  {
printf("6\n");
    strcpy(errorString, msgStr);
  } else {
printf("7\n");
    strncpy(errorString, msgStr, maxLength);
    *(errorString + maxLength) = '\0';
  }

  return errorString;
}

	



