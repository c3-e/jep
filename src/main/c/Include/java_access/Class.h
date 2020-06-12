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

#ifndef _Included_java_lang_Class
#define _Included_java_lang_Class

jclass       java_lang_Class_getComponentType(JNIEnv*, jclass);
jobjectArray java_lang_Class_getConstructors(JNIEnv*, jclass);
jobjectArray C3_JepInterface_getConstructors(JNIEnv*, jclass);
jobjectArray java_lang_Class_getDeclaredClasses(JNIEnv*, jclass);
jobjectArray java_lang_Class_getFields(JNIEnv*, jclass);
jobjectArray C3_JepInterface_getFields(JNIEnv*, jclass);
jobjectArray java_lang_Class_getMethods(JNIEnv*, jclass);
jobjectArray C3_JepInterface_getMethods(JNIEnv*, jclass);
jint         java_lang_Class_getModifiers(JNIEnv*, jclass);
jstring      java_lang_Class_getName(JNIEnv*, jclass);
jstring      java_lang_Class_getSimpleName(JNIEnv*, jclass);
jboolean     java_lang_Class_isArray(JNIEnv*, jclass);
jboolean     C3_JepInterface_isC3Class(JNIEnv*, jclass);
jobject      java_lang_Class_newInstance(JNIEnv*, jclass);
jboolean     java_lang_Class_isInterface(JNIEnv*, jclass);

#endif // ndef java_lang_Class
