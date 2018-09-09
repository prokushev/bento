/* Error reporting types */

#ifndef __CM_ERRORS__
#define __CM_ERRORS__

/* C Includes */
#include <stdarg.h>

/* CM Includes */
#include "cmdefs.h"
#include "cmtypes.h"

CMErrorString CMAddMsgInserts(CMErrorString msgString, CMSize maxLength, ...);
CMErrorString CMVAddMsgInserts(CMErrorString msgString, CMSize maxLength, va_list inserts);
CMErrorString CMGetErrorString(CMErrorString errorString, CMSize maxLength, CMErrorNbr errorNumber, ...);
CMErrorString CMVGetErrorString(CMErrorString errorString, CMSize maxLength, CMErrorNbr errorNumber, va_list inserts);
//CMErrorString CMReturnContainerName(CMContainer container);



/* Error Codes */

/* In specification not all error codes has CM_err prefix */


#define CMERR_GenericMessage      0
#define CMERR_BadTocSize          1
#define CMERR_NoSession           2
#define CMERR_NoHandler           3
#define CMERR_BadWriteUse         4
#define CMERR_NoContainer         5
#define CMERR_UndefMetaHandler    6
#define CMERR_HandlerError        7
#define CMERR_NullMetaPtr         8
#define CMERR_UndefRoutine        9
#define CMERR_NoTOC               10
#define CMERR_BadReadUse          11
#define CMERR_BadMagicBytes       12
#define CMERR_BadVersion          13
#define CMERR_BadTOCRead          14
#define CMERR_NoObjEntry          15
#define CMERR_MultDef             16
#define CMERR_NoPropEntry         17
#define CMERR_BadContinue         18
#define CMERR_NoValueEntry        19
#define CMERR_BadOffset           20
#define CMERR_UndefObjects        21
#define CMERR_NoStrValue          22
#define CMERR_DupBaseType         23
#define CMERR_BadTOCWrite         24
#define CMERR_NotGlobalName       25
#define CMERR_BadGNameWrite       26
#define CMERR_DupGlobalName       27
#define CMERR_MultGlblNames       28
#define CMERR_NoGlobalName        29
#define CMERR_NoGNameLoad         30
#define CMERR_BadGNameRead        31
#define CMERR_NotGName            32
#define CMERR_BadType             33
#define CMERR_2Containers         34
#define CMERR_3Containers         35
#define CMERR_MissingMinIDSeed    36
#define CMERR_MissingTOCObj       37
#define CMERR_NotConverting       38
#define CMERR_BadDefineData       39
#define CMERR_BadValue            40
#define CMERR_BadObject           41
#define CMERR_BadContainer        42
#define CMERR_NoValue             43
#define CMERR_HasValue            44
#define CMERR_AlreadyReleased     45
#define CMERR_NotReleased         46
#define CMERR_MissingFreeTotal    47
#define CMERR_DupType             48
#define CMERR_HasNoValue          49
#define CMERR_BadWrite            50
#define CMERR_CantWriteGlbl       51
#define CMERR_Offset2Big          52
#define CMERR_Internal1           53
#define CMERR_MissingIDSeed       54
#define CMERR_AmbiguousType       55
#define CMERR_TypeNotGlobal       56
#define CMERR_MissingFreeList     57
#define CMERR_NoNewValueHandler   58
#define CMERR_UndefReference      59
#define CMERR_BadObjectKind       60
#define CMERR_WriteIllegal1       61
#define CMERR_WriteIllegal2       62
#define CMERR_ReadIllegal         63
#define CMERR_MissingSize         64
#define CMERR_BadSize             65
#define CMERR_Internal2           66
#define CMERR_CantDelete1         67
#define CMERR_CantDelete2         68
#define CMERR_CantDelete3         69
#define CMERR_StillOpen           70
#define CMERR_EmptyRead           71
#define CMERR_NoEmbedding         72
#define CMERR_BadGenNbr           73
#define CMERR_NoRef               74
#define CMERR_CantGetBase         75
#define CMERR_MultTypeProp        76
#define CMERR_NotSameMode         77
#define CMERR_CantDelete4         78
#define CMERR_MissingHandler      79
#define CMERR_NoMissingBuffer     80
#define CMERR_MoveIllegal         81
#define CMERR_DeleteIllegal       82
#define CMERR_BadDefineType       83
#define CMERR_NoExtensions        84
#define CMERR_HandlerRecursed     85
#define CMERR_BadRealValue        86
#define CMERR_NoMetahandler       87
#define CMERR_NotDynValue         88
#define CMERR_NoGlobalTable       89
#define CMERR_BadMetaSpec         90
#define CMERR_NoDeletesList       91
#define CMERR_NoDataPacket        92
#define CMERR_BaseRelAttempted    93
#define CMERR_NoDynMetahandler    94
#define CMERR_MissingTotalSize    95
#define CMERR_Internal3           96
#define CMERR_AmbiguousUseFlags   97
#define CMERR_NoTypeHandler       98
#define CMERR_NotDynamicValue     99
#define CMERR_NoMetaDataHandler   100
#define CMERR_NoDataBuffer        101
#define CMERR_BadUpdateRead       102
#define CMERR_BadUpdateWrite      103
#define CMERR_Internal4           104
#define CMERR_Internal5           105
#define CMERR_NoNewValuesTOC      106
#define CMERR_wrappedIDs          107
#define CMERR_NoTouchedEntry      108
#define CMERR_NoUpdateObject      109
#define CMERR_NoUpdateProperty    110
#define CMERR_BadUpdateControl    111
#define CMERR_NoUpdateType        112
#define CMERR_UndefUpdateObject   113
#define CMERR_UpdateBadGenNbr     114
#define CMERR_BadInsertData       115
#define CMERR_BadInsertOffset     116
#define CMERR_CantRepImmediate    117
#define CMERR_CantRepBaseType     118
#define CMERR_CantReference       119
#define CMERR_GlobalNameError     120
#define CMERR_FlushErr            121
#define CMERR_CantDelete5         122
#define CMERR_NoTOCBuffer         123
#define CMERR_BadTOCCode          124
#define CMERR_TOCoutOfSync        125
#define CMERR_TOCParseErr1        126
#define CMERR_TOCParseErr2        127
#define CMERR_Unsupported1        128
#define CMERR_CantDelete6         129
#define CMERR_AlreadyReleased2    130
#define CMERR_BadRefRead          131
#define CMERR_Internal6           132
#define CMERR_ZeroRefKey          133
#define CMERR_NoRefShadowList     134

#endif /* __CM_ERRORS__ */

