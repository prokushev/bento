

/* All the I/O calls in the current API do I/O to or from a buffer provided by the application.
The generation number can be set, but it is not passed in the NewValue call.
NewValue defaults the generation number to the current generation value for the
container. Normally this is what is wanted.
*/
CMCount CMCountValues(CMObject object,
CMProperty property,
CMType type);

/*
A property for an object can be defined to have more than one value. This routine
returns the number of values for the specified property belonging to the specified object.
If the type is specified as NULL, the total number of values for the object's property is
returned. If the type is not NULL, 1 is returned if a value of that type is present (because
there can be a maximum of one value of that type), and 0 otherwise. If the property is not
defined for the object, 0 is always returned.
*/

CMValue CMUseValue(CMObject object,
CMProperty property,
CMType type);

/*

This routine is used to get the refNum for the value of an object's property of the
given type. NULL is returned if the value does not exist, or if or the object does not contain
the property. If the type of the value corresponds to a global type name that has an associated
"use value" handler, or if its base types (if any) have associated "use value"
handlers, a the refnum returned will refer to a dynamic value rather than the base value.
(Normally, an application will never be aware of this difference.)
If the value is typed as an embedded container, then this refnum can be passed to
CMOpenContainer as the attributes argument.

*/

CMValue CMGetNextValue(CMObject object,
CMProperty property,
CMValue currValue)

/*
This routine returns the refNum for the next value (according to the current value
order) in the objects property following currValue. If currValue is NULL, the refNum for
the first value for that object's property is returned. If currValue is not NULL, the next
value for that object's property is returned. NULL is returned if there are no more type
values following currValue or the object does not contain the property.
currValue is generally a refNum previously returned from this routine. Successive
calls to this routine will thus yield all the values for the specified property of the specified
object as long as no other operations change the value order.

*/
CMValue CMNewValue(CMObject object,
CMProperty property,
CMType type,
...);

/* A new entry is created for the designated object, with the designated property and
type and a refnum to the entry is returned. The generation number of the value defaults
to the generation number of the container, but it may be set with CMSetValueGeneration.
An object's properties can have more than one value. However, the all the types for
the values belonging to a given object property must be unique. It is an error to attempt
to create a value for a property when there is already a value of the same type for that
property.

If the specified type corresponds to a global type name that has an associated “use
value” handler, or if its base types (if any) have associated “use value” handlers, a
dynamic value will be created and returned. The value will be initialized using the
dataInitParams arguments, which must correspond to the initialization arguments for
a value of that type. See Chapter 5: Types and Dynamic Values for details.
Note that the value refnum at this point has no associated data. The value data is set
with CMWriteValueData or CMOpenNewContainer (to write an embedded container).
If the value will be used as an embedded container it must have the embedded container
type. Using CMWriteValueData on a value of this type is an error.
The value is created at an unspecified location in the sequence of values for the specified
property. Creating a new value may cause the order of the values for that property
to change.

*/ 

CMValue CMVNewValue(CMObject object,
CMProperty property,
CMType type,
va_list dataInitParams)

/* This routine is the same as CMNewValue() above, except that the dynamic value
data initialization (i.e., "...") parameters are given as a variable argument list as defined by
the "stdarg" facility.
This routine assumes the caller sets up and terminates the variable arg list using the
"stdarg.h" calls as follows:
#include <stdarg.h>
callersRoutine(args, ...)
{
va_list dataInitParams;
- - -
va_start(dataInitParams, args);
value = CMVNewValue(object, property, type, dataInitParams);
va_end(dataInitParams);
- - -
}

*/

CMSize CMGetValueSize(CMValue value);

/* The size of the designated value is returned.
If the storage size of the value is different from its size as seen by the application (for
example, if it is compressed) the value handlers are responsible for keeping track of the
application visible size and responding correctly. See Chapter 5: Types and Dynamic
Values for details.

*/

CMSize CMReadValueData(CMValue value,
CMPtr buffer,
CMCount offset,
CMSize maxSize)

/* 
The data, starting at the offset, for the value is read into the buffer. The size of the
data read is returned. Up to maxSize characters will be read (can be 0).
The data is read starting at the offset, up to the end of the data, or maxSize characters,
whichever comes first. Offsets are relative to 0. If the starting offset is greater than or
equal to the current data size, no data is read and 0 returned.
It is an error to attempt to read a value which has no data, i.e., a value where only a
CMNewValue has been done.

*/

void CMWriteValueData(CMValue value,
CMPtr buffer,
CMCount offset,
CMSize size)

/* 
The buffer is written to the container and defined as the data for the value. If the
value already has data associated with it, the buffer overwrites the "old" data starting at
the offset character position. size bytes are written.
If the current size of the value data is T (it will be 0 for a new value created by
CMNewValue), then the offset may be any value from 0 to T+1. That is, existing data may
be overwritten or the value extended with new data. The value of T can be gotten using
CMGetValueSize. Note that no "holes" can be created. It is an error to use an offset
greater than T+1.
Once data has been written to the container, it may be read using CMReadValue-
Data. CMWriteValueData may only be used on an updateable container.
CMWriteValueData calls for a particular value do not have to be contiguous.
Writes for other values can be done in between writes to a given value. The library takes
care of generating separate value segments. The data is physically not contiguous in the
container in this case. CMWriteValueData and CMReadValueData hide this by
allowing the user to view the data as contiguous. The input offset is mapped to the proper
starting segment and to the offset within that segment.

CMWriteValueData() may only be used for a container opend for writing (or
converting) using CMOpenNewContainer(). It is an error to write to protected values,
which are created implicitly by the API. This includes the predefined TOC objects (seed
and offset values) and objects representing currently opened embedded containers.
For creating embedded containers, CMOPenNewContainer is used instead of
CMWriteValueData. See CMNewValue and CMOpenContainer for further details.

*/

VOID CMInsertValueData(CMValue value,
CMPtr buffer,
CMCount offset,
CMSize size)

/* 
If the current size of the value data is T, offset must be
 
 T+1. The existing data in
the value is “pushed aside” and the buffer is written in the space created.

*/

VOID CMDeleteValueData(CMValue value,
CMCount offset,
CMSize size)

/*

Let T be the length of the value data. The bytes from offset to offset + size are
deleted from the value, and the value is “closed up”. After this operation, the size of the
value data is T-size (assuming offset+size is
 
 T). If offset is greater than T, no data
is deleted. If offset+size is greater than T, all the data from offset to T is deleted.
Neither case produces an error.
Existing value data:
T+size
Inserted data:
Size:
Offset:
0 offset offset+size
Existing value data:
T-size
Deleted data:
Size:
Offset:
0 offset offset+size
*/

VOID CMDefineValueData(CMValue value,
CMSize offset,
CMSize size);

/* 
Existing data in the container, which must have been in the container when it was
opened by Bento, is defined as the data for the value. No data is written to the container.
The container must have been opened using CMOpenNewContainer, with the flag
kCMConverting set in the useMode.
The designated value is set to reference the indicated data. The offset given is the
offset from the beginning of the container. It is an error to give an offset or a size that
would result in the value containing bytes outside of the data that was in the container
when it was opened. The offset therefore, must be in the range of 0 to N-1, where N is the
size of preexisting data at the time the container was opened.
Additional calls to CMDefineValueData() for the same value will define additional.
i.e., continued, segments when the offset produces noncontiguous data definition. If the
size of the last (most recent) value segment is T, and the offset for that segment is such that
offset+T equals the offset for the additional segment, then the last segment is simply
extended. This follows the same rules as CMWriteValueData().
*/

void CMMoveValue(CMValue value,
CMObject object,
CMProperty property)

/*
Moves the specified value from its original object property to the specified object
property. The value is physically deleted from its original object/property as if a
CMDeleteValue() were done on it. If the value deleted is the only one for the property,
the property itself is deleted as in CMDeleteObjectProperty().
The value is added to the "to"s object propery in the same manner as a
CMNewValue(). The order of the values for both the value's original object property and
for the value's new object property may be changed.
Note, that although the effect of a move is logically a combination CMDeleteValue()
and CMNewValue(), the refnum of the value remains valid. Its association is now
with the new object property.
This operation may be done at any time. No data need be assoicated with the value
at the time of the move. Only moves within the same container are allowed.
*/

VOID CMGetValueInfo(CMValue value,
CMContainer *container,
CMObject *object,
CMProperty *property,
CMGeneration *generation);

/* 
The container, object, property, and generation of the designated entry are returned.
NULL may be passed for any argument except the first.

*/

void CMSetValueType(CMValue value,
CMType type)

/*
The type of the value is set as specified.

*/

void CMSetValueGeneration(CMValue value,
CMGeneration generation)

/*

The generation for the specified value is set. The generation number must be greater
than or equal to 1. Normally this routine doesn’t need to be used since the value inherits
its generation from its container.

*/

void CMDeleteValue(CMValue value);

/*

The designated value is deleted from its object property. A deleted value will be
treated by all Bento operations as though it does not exist. For example, it will not be
found by CMUseValue, counted by CMCountValues, etc. .
If the value deleted is the only one for the property, the property itself is deleted as
in CMDeleteObjectProperty. If that property is the only one for the object, the object
is also deleted as in CMDeleteObject. Some values are protected from deletion.
Protected values include the predefined TOC object values (seed and offset) and any
currently open embedded container values.

*/ 

void CMReleaseValue(CMValue value);

/* The association between the Value refnum and the entry is destroyed. After this call
the refnum is invalid, and may be returned from a subsequent CMUseValue or
CMNewValue call to designate another value.
*/