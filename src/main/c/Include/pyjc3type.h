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

/*
 * A PyJC3TypeObject is a PyJC3Object with a __call__ method attached, where
 * the call method can invoke the Java object's constructors. This represents a C3 Type.
 */

#include "jep_platform.h"
#include "pyjc3object.h"
#ifndef _Included_pyjc3type
#define _Included_pyjc3type

extern PyTypeObject PyJC3Type_Type;

typedef struct {
    PyObject_HEAD
    PyJC3Object_FIELDS
    /*
     * A python callable, either a PyJC3Constructor or PyJC3MultiMethod with many
     * PyJC3Constructors
     */
    PyObject  *constructor;
} PyJC3TypeObject;

PyObject* PyJC3Type_Wrap(JNIEnv*, jobject);

#define PyJC3Type_Check(pyobj) \
    PyObject_TypeCheck(pyobj, &PyJC3Type_Type)


#endif // ndef pyjc3type
