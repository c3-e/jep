/*
   jep - Java Embedded Python

   Copyright (c) 2016-2019 JEP AUTHORS.

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

#include "Jep.h"

static jmethodID getParameterTypes = 0;
static jmethodID getParameterTypesC3 = 0;

jobjectArray C3_JepInterface_getConstructorParameterTypes(JNIEnv* env,
        jobject this)
{
    jobjectArray result = NULL;
    if (JNI_STATIC_METHOD(getParameterTypesC3, env, C3_JEPINTERFACE_TYPE, "getConstructorParameterTypes",
                   "()[Ljava/lang/Class;")) {
        result = (jobjectArray) (*env)->CallStaticObjectMethod(env, C3_JEPINTERFACE_TYPE, getParameterTypesC3, this);
    }
    return result;
}


jobjectArray java_lang_reflect_Constructor_getParameterTypes(JNIEnv* env,
        jobject this)
{
    jobjectArray result = NULL;
    if (JNI_METHOD(getParameterTypes, env, JCONSTRUCTOR_TYPE, "getParameterTypes",
                   "()[Ljava/lang/Class;")) {
        result = (jobjectArray) (*env)->CallObjectMethod(env, this, getParameterTypes);
    }
    return result;
}
