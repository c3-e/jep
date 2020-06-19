#ifndef _Included_c3_zoo_py_JepInterface
#define _Included_c3_zoo_py_JepInterface

jstring C3_JepInterface_dispatchString(JNIEnv*, jobject);
jobjectArray C3_JepInterface_dispatchArray(JNIEnv*, jobject);
jobject C3_JepInterface_dispatchObject(JNIEnv*, jobject);
jobject C3_JepInterface_dispatchClass(JNIEnv*, jobject);
jint C3_JepInterface_dispatchInt(JNIEnv*, jobject);
jbyte C3_JepInterface_dispatchByte(JNIEnv*, jobject);
jdouble C3_JepInterface_dispatchDouble(JNIEnv*, jobject);
jfloat C3_JepInterface_dispatchFloat(JNIEnv*, jobject);
jlong C3_JepInterface_dispatchLong(JNIEnv*, jobject);
jboolean C3_JepInterface_dispatchBoolean(JNIEnv*, jobject);

#endif // ndef java_lang_reflect_Member
