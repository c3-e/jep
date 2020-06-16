/*
   jep - Java Embedded Python

   Copyright (c) 2004-2019 JEP AUTHORS.

   This file is licensed under the the zlib/libpng License.

   This software is provided 'as-is', without any express or implied
   warranty. In no event will the authors be held liable for any
   damages arising from the use of this software.

   Permission is granted to anyone to use this software for any
   purpose, including commercial applications, and to alter it and
   redistribute it freely, subject to the following restrictions:

   1. The origin of this software must not be misrepresented; you
   must not claim that you wrote the original software. If you use
   this software in a product, an acknowledgment in the product
   documentation would be appreciated but is not required.

   2. Altered source versions must be plainly marked as such, and
   must not be misrepresented as being the original software.

   3. This notice may not be removed or altered from any source
   distribution.
*/

#include "jep_platform.h"

#ifndef _Included_pyjc3object
#define _Included_pyjc3object


extern PyTypeObject PyJC3Object_Type;

/*
 * The common fields for PyJC3Object. The usage of this macro is similar to
 * PyObject_HEAD. Any type which extends PyJC3Object and requires additional
 * fields must start the struct definition with PyObject_HEAD followed
 * immediatly by PyJC3Object_FIELDS and then any custom fields for the subtype.
 *
 * These fields are the JNI objects for the Java object and the Class of that
 * object. As well as a Python dict for the attributes and a Python string
 * containing the fully qualified java class name.
 */
#define PyJC3Object_FIELDS \
    jobject   object;    \
    jclass    clazz;     \
    PyObject *attr;      \
    PyObject *javaClassName;

typedef struct {
    PyObject_HEAD
    PyJC3Object_FIELDS
} PyJC3Object;

/*
 * Create a new instance of PyJC3Object or one of it's subtypes that wraps
 * the object provided. If the class of the object is known it can be passed
 * in, or the final argument can be NULL and this function will figure it out.
 */
PyObject* PyJC3Object_New(JNIEnv*, PyTypeObject*, jobject, jclass);

#define PyJC3Object_Wrap(env, jobj, jcls) \
    PyJC3Object_New(env, &PyJC3Object_Type, jobj, jcls)

#define PyJC3Object_Check(pyobj) \
    PyObject_TypeCheck(pyobj, &PyJC3Object_Type)


#endif // ndef pyjc3object
