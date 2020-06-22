#ifndef _Included_c3_zoo_py_JepInterface
#define _Included_c3_zoo_py_JepInterface

jstring C3_JepInterface_getFieldValueString(JNIEnv*, jobject, jstring);
jstring C3_JepInterface_dispatchString(JNIEnv*, jstring, jstring, jobjectArray);
jstring C3_JepInterface_dispatchStringMember(JNIEnv*, jstring, jstring, jobject, jobjectArray);
jobjectArray C3_JepInterface_dispatchArray(JNIEnv*, jstring, jstring, jobjectArray);
jobject C3_JepInterface_dispatchObject(JNIEnv*, jstring, jstring, jobjectArray);
jobject C3_JepInterface_dispatchClass(JNIEnv*, jstring, jstring, jobjectArray);
jint C3_JepInterface_dispatchInt(JNIEnv*, jstring, jstring, jobjectArray);
jbyte C3_JepInterface_dispatchByte(JNIEnv*, jstring, jstring, jobjectArray);
jdouble C3_JepInterface_dispatchDouble(JNIEnv*, jstring, jstring, jobjectArray);
jfloat C3_JepInterface_dispatchFloat(JNIEnv*, jstring, jstring, jobjectArray);
jlong C3_JepInterface_dispatchLong(JNIEnv*, jstring, jstring, jobjectArray);
jboolean C3_JepInterface_dispatchBoolean(JNIEnv*, jstring, jstring, jobjectArray);
void C3_JepInterface_dispatchVoid(JNIEnv*, jstring, jstring, jobjectArray);
jboolean C3_JepInterface_isFieldStatic(JNIEnv*, jobject);
jobjectArray C3_JepInterface_getConstructors(JNIEnv*, jclass);
jobjectArray C3_JepInterface_getFields(JNIEnv*, jobject);
jobjectArray C3_JepInterface_getMethods(JNIEnv*, jobject);
jboolean     C3_JepInterface_isC3Class(JNIEnv*, jclass);
jobjectArray C3_JepInterface_getConstructorParameterTypes(JNIEnv*, jobject);
jclass  C3_JepInterface_getType(JNIEnv*, jobject);
jstring C3_JepInterface_getFieldName(JNIEnv*, jobject);
jstring C3_JepInterface_getTypeName(JNIEnv*, jobject);
jstring C3_JepInterface_getMethodName(JNIEnv*, jobject);
jint    C3_JepInterface_getMemberModifiers(JNIEnv*, jobject);
jclass       C3_JepInterface_getReturnType(JNIEnv*, jobject);
jboolean     C3_JepInterface_isVarArgs(JNIEnv*, jobject);
jobjectArray C3_JepInterface_getParameterTypes(JNIEnv*, jobject);
jboolean C3_JepInterface_isAbstract(JNIEnv*, jobject);
jboolean C3_JepInterface_isPublic(JNIEnv*, jint);

jboolean C3_JepInterface_isStatic(JNIEnv*, jobject);

#endif // ndef java_lang_reflect_Member
