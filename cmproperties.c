/* 
All types and properties must be registered before they can be used. The operations
behave the same on standard types and properties as on normal types and properties.
However, standard types and properties will not actually be given TOC entries for their
descriptions just because they are registered. If additional, non-standard properties are
added to the description of a standard type or property, they will be stored.
The refnum returned from registration can be used in exactly the same manner as an
object refnum in the object and value operations.
Types and properties may be registered more than once; the refnum returned from
all the different registrations of the same type is the same. Identity of types is defined by
string equality of their names.

*/

CMType CMRegisterType(CMContainer targetContainer,
const CMGlobalName name);

/* 

The designated type is registered in the designated container, and a refnum for it is
returned. If a type with that name already exists, the refNum for it is returned.
Standard types may be registered, but this is not required.

*/

CMProperty CMRegisterProperty(CMContainer targetContainer,
const CMGlobalName name);

/*

The designated property is registered in the designated container, and a refnum for
it is returned. If a property with that name already exists, the refNum for it is returned.
Standard properties may be registered, but this is not required.


*/

CMBoolean CMIsType(CMObject theObject);
CMBoolean CMIsProperty(CMObject theObject);

/*
These operations test the designated object and return non-zero if it is a type description
or a property description, respectively, otherwise 0.
*/

CMType CMGetNextType(CMContainer targetContainer,
CM CMType currType);

/*

A refnum for the next type registered in the same container is returned. currType
is generally a refNum previously returned from this routine. Successive calls to this
routine will thus yield all the type descriptions in the container.
Types are returned in order of increasing ID. If there are no larger type IDs registered,
NULL is returned. To begin the iteration, pass NULL as the type refnum.

*/

CMProperty CMGetNextProperty(CMContainer targetContainer,
CMProperty currProperty);

/*
A refun for the next property registered in the same container is returned.
currProperty is generally a refNum previously returned from this routine. Successive
calls to this routine will thus yield all the property descriptions in the container.
Properties are returned in order of increasing ID. If there are no larger property IDs
registered, NULL is retured. To begin the iteration, pass NULL as the property refnum.

*/

CMCount CMAddBaseType(CMType type,
CMType baseType)

/*

This routine defines base types for a given type so that layered dynamic values can
be created. Base types essentially provide type inheritance. See the chapter on Types and
Dynamic Values for a full description of how base types are used.
A base type is added to the specified type. For each call to CMAddBaseType() for
the type a new base type is recorded. They are recorded in the order of the calls. The total
number of base types recorded for the type is retuned. 0 is returned if there is an error and
the error reporter returns.
It is currently an error to attempt to add the same base type more than once to the
type.

*/

CMCount CMRemoveBaseType(CMType type,
CMType baseType)

/* 
The specified base type previously added to the specifed type by CMAddBase-
Type() is removed. If NULL is specified as the baseType, all base types are removed. The
number of base types remaining for the type is returned.
Note, no error is reported if the specified base type is not present or the type has no
base types.
*/
