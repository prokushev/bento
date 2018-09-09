CMObject CMNewObject(CMContainer targetContainer);

/*

A refnum to a new object in the designated container is returned. At this point the
object has nothing but an identity.

*/


CMProperty CMGetNextObjectProperty(CMObject theObject,
CMProperty currProperty);

/*

A refnum for the next property defined for this object is returned. currProperty
is generally a refNum previously returned from this routine. Successive calls to this
routine will thus yield all the properties for the given object.
This routine returns the refNum for the next property defined for the given object. If
there are no more properties defined for this object, NULL is returned. If currProperty
is NULL, the refNum for the first property for the object is returned.

*/

CMObject CMGetNextObjectWithProperty(CMContainer targetContainer,
CMObject currObject,
CMProperty property)

/*
This routine returns the refNum for the next object in the container that has the
given property. currObject is generally a refNum previously returned from this
routine. Successive calls to this routine will thus yield all the objects with the given property.
If currObject is NULL, the search starts with the first object in the container. If there
is no next object with the given property, NULL is returned.
*/

CMContainer CMGetObjectContainer(CMObject theObject);

/*
The container of the designated object is returned.

*/

CMGlobalName CMGetGlobalName(CMObject theObject);

/*

The name of the designated object is returned. This operation is typically used on
types and properties, but it can be applied to any object with a Globally Unique Name
property. NULL is returned if the object does not have a Globally Unique Name.

*/

CMRefCon CMGetObjectRefCon(CMObject theObject)

/*

This routine returns the user's "refCon" (reference constant) that s/he may associate
with any object refNum (i.e., a CMObject). The refCon is a CM_ULONG that the user may
use in any way. It is not touched by the API except to initialize it to 0 when the object is
read into memory.
Note that the refCon is not preserved across closed containers, i.e., it is not saved in
the TOC.

*/

void CMSetObjectRefCon(CMObject theObject,
CMRefCon refCon)

/* 
This routine is used to set the user's "refCon" (reference constant) to be assoicated
with an object. The refCon is a CM_ULONG that the user may use in any way. It is not
touched by the API.
Note that the refCon is not preserved across closed containers, i.e., it is not saved in
the TOC.
*/

VOID CMDeleteObject(CMObject theObject);

/*

The specified object and all its properties and values are deleted. It is an error to use
the object refnum after this call has been made.
A deleted object will be treated by all Bento operations as though it does not exist.
For example, it will not be found by CMGetNextObject, etc.
Objects containing values that are currently open embedded containers cannot be
deleted. Also, some objects created and used in the management of the TOC itself cannot
be deleted.
*/

VOID CMDeleteObjectProperty(CMObject theObject,
CMProperty theProperty);

/*

The designated object property is deleted along with all of its values.. It is an error
to use the refnum of any value of this property of this object after this call has been made.
A deleted object property will be treated by all Bento operations as though it does
not exist. For example, it will not be found by CMGetNextObjectProperty, etc.
Object properties containing values that are currently open embedded containers
cannot be deleted. Also, some object properties created and used in the management of
the TOC itself cannot be deleted.
*/

VOID CMReleaseObject(CMObject theObject);

/* The association between the object refnum and the designated object is destroyed.
After this call the refnum is invalid and may be returned from one of the object calls to
designate another object.
This call is also used to destroy the association between properties and types and
their associated refnums.
32 API Definit
*/
