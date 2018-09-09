CMReference *CMNewReference(CMValue value,
CMObject referencedObject,
CMReference theReferenceData)

/* This is the only way to get a persistent reference to an object that can be saved in a
value, and then read from the value and used to refer to that object when the container is
opened in another environment. CMNewReference does some bookkeeping behind the
scenes and returns a token (theReferenceData) that will refer to referencedObject,
but this reference will only be valid in the context of value!
The caller should write the theReferenceData to the value. It can be embedded
in any way in the value: encrypted, compressed, whatever you want. The size of
theReferenceData is determined by the size of the CMReference type.
*/
CMObject CMGetReferencedObject(CMValue value,
CMReference theReferenceData)

/* Provides the object refNum corresponding to theReferenceData.
value must be the value that contained theReferenceData. Values from many
containers may be present at the same time, and the caller may not be aware of what
container a given reference is from, especially in the presence of I/O redirection. Furthermore,
the reference may have been “fixed up” using the other references routines below.
Such fixups only apply to a hidden reference table associated with the value, so the value
must be used as the context for converting the persistent reference.

*/

CMReference *CMSetReference(CMValue value,
CMObject referencedObject,
CMReference theReferenceData);

/*
This call is similar to CMNewReference() except that here the caller defines the
CMReference key to associate with an object. The specified key must be a nonzero value.
The (input) pointer to theReferenceData key is returned.
In all cases the specified CMReference key is associated with the specified referencedObject.
These associations are maintained in a persistent table attached to the
value. If theReferenceData key is new, a new reference is recorded. If theReferenceData
key matches one of the previously recorded keys in the table the reference
associated with that key is changed to associate it with the (new) referencedObject.
This call can be used to “fix up” existing references if a value is copied as part of a
structure or moved to a new environment. It can also be used to associate object references
with pre-existing keys in the value data.
The only difference between CMNewReference() and CMSetReference() is that
with CMNewReference(), the Container Manager defines the CMReference key, while
with CMSetReference() the caller can define the key. The net result is the same; the
keys are recorded in a persistent form attached to the value.
Note that multiple references to the same object can be recorded by passing different
keys as theReferenceData.
Once these associations are recorded, they may be counted, deleted, and accessed
using CMCountReferences(), CMDeleteReference(), and CMGetNextReference()
respectively.
*/

void CMDeleteReference(CMValue value,
CMReference theReferenceData);

/* 
This call deletes a single object reference created by CMNewReference() or CMSetReference()
associated with the theReferenceData key in the reference table
attached to the value.
The value‘s reference table is searched for the specified theReferenceData key.
If it is found, the association is removed. If it is not found this routine does nothing. It is
not an error if the theReferenceData key is not found.
CMCount CMCountReferences(CMValue value);
Returns the total number of references in the reference table attached to the value.
These references were recorded by CMNewReference() or CMSetReference().
*/

CMReference *CMGetNextReference(CMValue value,
CMReference currReferenceData);

/* 
This routine returns the next reference key following the currReferenceData key
in the reference table for the specified value.
If currReferenceData is 0, then the first object reference key is returned. If
currReferenceData is not 0, the next reference key after currReferenceData is
returned. The next reference key is stored into currReferenceData and the pointer to
currReferenceData is returned as the function result. NULL is returned and currReferenceData
is undefined if there are no references following the key passed in as
currReferenceData. 
*/