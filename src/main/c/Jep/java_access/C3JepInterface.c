#include "Jep.h"

static jmethodID getFieldValueStringC3 = 0;
static jmethodID dispatchStringC3 = 0;
static jmethodID dispatchStringMemberC3 = 0;
static jmethodID dispatchArrayC3 = 0;
static jmethodID dispatchClassC3 = 0;
static jmethodID dispatchObjectC3 = 0;
static jmethodID dispatchIntC3 = 0;
static jmethodID dispatchByteC3 = 0;
static jmethodID dispatchDoubleC3 = 0;
static jmethodID dispatchFloatC3 = 0;
static jmethodID dispatchLongC3 = 0;
static jmethodID dispatchBooleanC3 = 0;
static jmethodID dispatchVoidC3 = 0;
static jmethodID isFieldStaticC3 = 0;
static jmethodID getConstructorsC3    = 0;
static jmethodID getFieldsC3        = 0;
static jmethodID getMethodsC3        = 0;
static jmethodID isC3Class        = 0;
static jmethodID getTypeC3 = 0;
static jmethodID getMethodNameC3           = 0;
static jmethodID getTypeNameC3           = 0;
static jmethodID getModifiersC3           = 0;
static jmethodID getParameterTypesC3 = 0;
static jmethodID getConstructorParameterTypesC3 = 0;
static jmethodID getReturnTypeC3     = 0;
static jmethodID isVarArgsC3         = 0;
static jmethodID isPublicC3   = 0;
static jmethodID isStaticC3   = 0;
static jmethodID isAbstractC3 = 0;
static jmethodID getFieldNameC3 = 0;

jobjectArray C3_JepInterface_dispatchArray(JNIEnv* env, jstring tn, jstring mn, jobjectArray args)
{
    jobjectArray result = NULL;
    if (JNI_STATIC_METHOD(dispatchArrayC3, env, C3_JEPINTERFACE_TYPE, "dispatchArray", "(Ljava/lang/String;Ljava/lang/String;[Ljava/lang/Object;)[Ljava/lang/Object;")) {
        result = (jobjectArray) (*env)->CallStaticObjectMethod(env, C3_JEPINTERFACE_TYPE, dispatchArrayC3, tn, mn, args);
    }
    return result;
}

jobject C3_JepInterface_dispatchObject(JNIEnv* env, jstring tn, jstring mn, jobjectArray args)
{
    jobject result = NULL;
    if (JNI_STATIC_METHOD(dispatchObjectC3, env, C3_JEPINTERFACE_TYPE, "dispatchObject", "(Ljava/lang/String;Ljava/lang/String;[Ljava/lang/Object;)Ljava/lang/Object;")) {
        result = (jobject) (*env)->CallStaticObjectMethod(env, C3_JEPINTERFACE_TYPE, dispatchObjectC3, tn, mn, args);
    }
    return result;
}

jint C3_JepInterface_dispatchInt(JNIEnv* env, jstring tn, jstring mn, jobjectArray args)
{
    jint result = 0;
    if (JNI_STATIC_METHOD(dispatchIntC3, env, C3_JEPINTERFACE_TYPE, "dispatchInt", "(Ljava/lang/String;Ljava/lang/String;[Ljava/lang/Object;)I")) {
        result = (*env)->CallStaticIntMethod(env, C3_JEPINTERFACE_TYPE, dispatchIntC3, tn, mn, args);
    }
    return result;
}

jstring C3_JepInterface_dispatchString(JNIEnv* env, jstring tn, jstring mn, jobjectArray args)
{
    jstring result = NULL;
    if (JNI_STATIC_METHOD(dispatchStringC3, env, C3_JEPINTERFACE_TYPE, "dispatchString", "(Ljava/lang/String;Ljava/lang/String;[Ljava/lang/Object;)Ljava/lang/String;")) {
        result = (jstring) (*env)->CallStaticObjectMethod(env, C3_JEPINTERFACE_TYPE, dispatchStringC3, tn, mn, args);
    }
    return result;
}

jstring C3_JepInterface_dispatchStringMember(JNIEnv* env, jstring tn, jstring mn, jobject obj, jobjectArray args)
{
    jstring result = NULL;
    if (JNI_STATIC_METHOD(dispatchStringMemberC3, env, C3_JEPINTERFACE_TYPE, "dispatchStringMember",
                          "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/Object;[Ljava/lang/Object;)Ljava/lang/String;")) {
        result = (jstring) (*env)->CallStaticObjectMethod(env, C3_JEPINTERFACE_TYPE, dispatchStringMemberC3, tn, mn, obj, args);
    }
    return result;
}

void C3_JepInterface_dispatchVoid(JNIEnv* env, jstring tn, jstring mn, jobjectArray args)
{
    if (JNI_STATIC_METHOD(dispatchVoidC3, env, C3_JEPINTERFACE_TYPE, "dispatchVoid", "(Ljava/lang/String;Ljava/lang/String;[Ljava/lang/Object;)")) {
        (*env)->CallStaticVoidMethod(env, C3_JEPINTERFACE_TYPE, dispatchVoidC3, tn, mn, args);
    }
}

jfloat C3_JepInterface_dispatchFloat(JNIEnv* env, jstring tn, jstring mn, jobjectArray args)
{
    jfloat result = 0;
    if (JNI_STATIC_METHOD(dispatchFloatC3, env, C3_JEPINTERFACE_TYPE, "dispatchFloat", "(Ljava/lang/String;Ljava/lang/String;[Ljava/lang/Object;)F")) {
        result = (*env)->CallStaticFloatMethod(env, C3_JEPINTERFACE_TYPE, dispatchFloatC3, tn, mn, args);
    }
    return result;
}

jbyte C3_JepInterface_dispatchByte(JNIEnv* env, jstring tn, jstring mn, jobjectArray args)
{
   jbyte result = 0;
   if (JNI_STATIC_METHOD(dispatchByteC3, env, C3_JEPINTERFACE_TYPE, "dispatchByte", "(Ljava/lang/String;Ljava/lang/String;[Ljava/lang/Object;)B")) {
       result = (*env)->CallStaticByteMethod(env, C3_JEPINTERFACE_TYPE, dispatchByteC3, tn, mn, args);
   }
   return result;
}

jobject C3_JepInterface_dispatchClass(JNIEnv* env, jstring tn, jstring mn, jobjectArray args)
{
    jobject result = NULL;
    if (JNI_STATIC_METHOD(dispatchClassC3, env, C3_JEPINTERFACE_TYPE, "dispatchClass", "(Ljava/lang/String;Ljava/lang/String;[Ljava/lang/Object;)Ljava/lang/Object;")) {
        result = (jobject) (*env)->CallStaticObjectMethod(env, C3_JEPINTERFACE_TYPE, dispatchClassC3, tn, mn, args);
    }
    return result;
}

jboolean C3_JepInterface_dispatchBoolean(JNIEnv* env, jstring tn, jstring mn, jobjectArray args)
{
    jboolean result = JNI_FALSE;
    if (JNI_STATIC_METHOD(dispatchDoubleC3, env, C3_JEPINTERFACE_TYPE, "dispatchBoolean", "(Ljava/lang/String;Ljava/lang/String;[Ljava/lang/Object;)Z")) {
        result = (*env)->CallStaticBooleanMethod(env, C3_JEPINTERFACE_TYPE, dispatchBooleanC3, tn, mn, args);
    }
    return result;
}

jdouble C3_JepInterface_dispatchDouble(JNIEnv* env, jstring tn, jstring mn, jobjectArray args)
{
    jdouble result = 0;
    if (JNI_STATIC_METHOD(dispatchDoubleC3, env, C3_JEPINTERFACE_TYPE, "dispatchDouble", "(Ljava/lang/String;Ljava/lang/String;[Ljava/lang/Object;)D")) {
        result = (*env)->CallStaticDoubleMethod(env, C3_JEPINTERFACE_TYPE, dispatchDoubleC3, tn, mn, args);
    }
    return result;
}

jlong C3_JepInterface_dispatchLong(JNIEnv* env, jstring tn, jstring mn, jobjectArray args)
{
    jlong result = 0;
    if (JNI_STATIC_METHOD(dispatchLongC3, env, C3_JEPINTERFACE_TYPE, "dispatchLong", "(Ljava/lang/String;Ljava/lang/String;[Ljava/lang/Object;)L")) {
        result = (*env)->CallStaticLongMethod(env, C3_JEPINTERFACE_TYPE, dispatchLongC3, tn, mn, args);
    }
    return result;
}

jobjectArray C3_JepInterface_getConstructors(JNIEnv* env, jobject obj)
{
    jobjectArray result = NULL;
    Py_BEGIN_ALLOW_THREADS
    if (JNI_STATIC_METHOD(getConstructorsC3, env, C3_JEPINTERFACE_TYPE, "getConstructors",
                   "(Ljava/lang/Object;)[Ljava/lang/reflect/Constructor;")) {
        result = (jobjectArray) (*env)->CallStaticObjectMethod(env, C3_JEPINTERFACE_TYPE, getConstructorsC3, obj);
    }
    Py_END_ALLOW_THREADS
    return result;
}


jobjectArray C3_JepInterface_getMethods(JNIEnv* env, jobject obj)
{
    jobjectArray result = NULL;
    Py_BEGIN_ALLOW_THREADS
    if (JNI_STATIC_METHOD(getMethodsC3, env, C3_JEPINTERFACE_TYPE, "getMethods",
                   "(Ljava/lang/Object;)[Lc3/platform/type/MethodType;")) {
        result = (jobjectArray) (*env)->CallStaticObjectMethod(env, C3_JEPINTERFACE_TYPE, getMethodsC3, obj);
    }
    Py_END_ALLOW_THREADS
    return result;
}

jobjectArray C3_JepInterface_getFields(JNIEnv* env, jobject obj)
{
    jobjectArray result = NULL;
    Py_BEGIN_ALLOW_THREADS
    if (JNI_STATIC_METHOD(getFieldsC3, env, C3_JEPINTERFACE_TYPE, "getFields",
                   "(Ljava/lang/Object;)[Lc3/platform/type/FieldType;")) {
        result = (jobjectArray) (*env)->CallStaticObjectMethod(env, C3_JEPINTERFACE_TYPE, getFieldsC3, obj);
    }
    Py_END_ALLOW_THREADS
    return result;
}

jboolean C3_JepInterface_isC3Class(JNIEnv* env, jclass this)
{
    jboolean result = JNI_FALSE;
    Py_BEGIN_ALLOW_THREADS
    if (JNI_STATIC_METHOD(isC3Class, env, C3_JEPINTERFACE_TYPE, "isC3Class", "(Ljava/lang/Class;)Z")) {
        result = (*env)->CallStaticBooleanMethod(env, C3_JEPINTERFACE_TYPE, isC3Class, this);
    }
    Py_END_ALLOW_THREADS
    return result;
}


jclass C3_JepInterface_getType(JNIEnv* env, jobject obj)
{
    jclass result = NULL;
    if (JNI_STATIC_METHOD(getTypeC3, env, C3_JEPINTERFACE_TYPE, "getType", "(Lc3/platform/type/FieldType;)Ljava/lang/Class;")) {
        result = (jclass) (*env)->CallStaticObjectMethod(env, C3_JEPINTERFACE_TYPE, getTypeC3, obj);
    }
    return result;
}


jint C3_JepInterface_getMemberModifiers(JNIEnv* env, jobject obj)
{
    jint result = 0;
    if (JNI_STATIC_METHOD(getModifiersC3, env, C3_JEPINTERFACE_TYPE, "getMemberModifiers", "()I")) {
        result = (*env)->CallStaticIntMethod(env, C3_JEPINTERFACE_TYPE, getModifiersC3, obj);
    }
    return result;
}

jobjectArray C3_JepInterface_getParameterTypes(JNIEnv* env,
        jobject obj)
{
    jobjectArray result = NULL;
    if (JNI_STATIC_METHOD(getParameterTypesC3, env, C3_JEPINTERFACE_TYPE, "getParameterTypes",
                   "(Lc3/platform/type/MethodType;)[Ljava/lang/Class;")) {
        result = (jobjectArray) (*env)->CallStaticObjectMethod(env, C3_JEPINTERFACE_TYPE, getParameterTypesC3, obj);
    }
    return result;
}

jclass C3_JepInterface_getReturnType(JNIEnv* env, jobject obj)
{
    jclass result = NULL;
    if (JNI_STATIC_METHOD(getReturnTypeC3, env, C3_JEPINTERFACE_TYPE, "getReturnType",
                   "(Lc3/platform/type/MethodType;)Ljava/lang/Class;")) {
        result = (jclass) (*env)->CallStaticObjectMethod(env, C3_JEPINTERFACE_TYPE, getReturnTypeC3, obj);
    }
    return result;
}


jboolean C3_JepInterface_isVarArgs(JNIEnv* env, jobject obj)
{
    jboolean result = JNI_FALSE;
    if (JNI_STATIC_METHOD(isVarArgsC3, env, C3_JEPINTERFACE_TYPE, "isVarArgs", "()Z")) {
        result = (*env)->CallStaticBooleanMethod(env, C3_JEPINTERFACE_TYPE, isVarArgsC3, obj);
    }
    return result;
}

jboolean C3_JepInterface_isPublic(JNIEnv* env, jint mod)
{
    jboolean result = JNI_FALSE;
    if (isPublicC3
            || (isPublicC3 = (*env)->GetStaticMethodID(env, C3_JEPINTERFACE_TYPE, "isPublic",
                           "(I)Z"))) {
        result = (*env)->CallStaticBooleanMethod(env, C3_JEPINTERFACE_TYPE, isPublicC3, mod);
    }
    return result;
}

jboolean C3_JepInterface_isStatic(JNIEnv* env,
        jobject obj)
{
    jboolean result = JNI_FALSE;
    if (JNI_STATIC_METHOD(isStaticC3, env, C3_JEPINTERFACE_TYPE, "isStatic",
                   "(Lc3/platform/type/MethodType;)Z")) {
        result = (*env)->CallStaticBooleanMethod(env, C3_JEPINTERFACE_TYPE, isStaticC3, obj);
    }
    return result;
}

jboolean C3_JepInterface_isAbstract(JNIEnv* env, jobject method)
{
    jboolean result = JNI_FALSE;
    if (isAbstractC3
            || (isAbstractC3 = (*env)->GetStaticMethodID(env, C3_JEPINTERFACE_TYPE, "isAbstract",
                             "(Lc3/platform/type/MethodType;)Z"))) {
        result = (*env)->CallStaticBooleanMethod(env, C3_JEPINTERFACE_TYPE, isAbstractC3, method);
    }
    return result;
}


jboolean C3_JepInterface_isFieldStatic(JNIEnv* env, jobject ft)
{
    jboolean result = JNI_FALSE;
    if (isFieldStaticC3
            || (isFieldStaticC3 = (*env)->GetStaticMethodID(env, C3_JEPINTERFACE_TYPE, "isFieldStatic",
                           "(Lc3/platform/type/FieldType;)Z"))) {
        result = (*env)->CallStaticBooleanMethod(env, C3_JEPINTERFACE_TYPE, isFieldStaticC3, ft);
    }
    return result;
}

jobjectArray C3_JepInterface_getConstructorParameterTypes(JNIEnv* env,
        jobject obj)
{
    jobjectArray result = NULL;
    if (JNI_STATIC_METHOD(getConstructorParameterTypesC3, env, C3_JEPINTERFACE_TYPE, "getConstructorParameterTypes",
                   "(Lc3/platform/type/MethodType;)[Ljava/lang/Class;")) {
        result = (jobjectArray) (*env)->CallStaticObjectMethod(env, C3_JEPINTERFACE_TYPE, getConstructorParameterTypesC3, obj);
    }
    return result;
}

jstring C3_JepInterface_getTypeName(JNIEnv* env, jobject obj)
{
    jstring result = NULL;
    if (JNI_STATIC_METHOD(getTypeNameC3, env, C3_JEPINTERFACE_TYPE, "getTypeName", "(Ljava/lang/Object;)Ljava/lang/String;")) {
        result = (jstring) (*env)->CallStaticObjectMethod(env, C3_JEPINTERFACE_TYPE, getTypeNameC3, obj);
    }
    return result;
}

jstring C3_JepInterface_getMethodName(JNIEnv* env, jobject obj)
{
    jstring result = NULL;
    if (JNI_STATIC_METHOD(getMethodNameC3, env, C3_JEPINTERFACE_TYPE, "getMethodName", "(Lc3/platform/type/MethodType;)Ljava/lang/String;")) {
        result = (jstring) (*env)->CallStaticObjectMethod(env, C3_JEPINTERFACE_TYPE, getMethodNameC3, obj);
    }
    return result;
}

jstring C3_JepInterface_getFieldName(JNIEnv* env, jobject obj)
{
    jstring result = NULL;
    if (JNI_STATIC_METHOD(getFieldNameC3, env, C3_JEPINTERFACE_TYPE, "getFieldName", "(Lc3/platform/type/FieldType;)Ljava/lang/String;")) {
        result = (jstring) (*env)->CallStaticObjectMethod(env, C3_JEPINTERFACE_TYPE, getFieldNameC3, obj);
    }
    return result;
}

jstring C3_JepInterface_getFieldValueString(JNIEnv* env, jobject obj, jstring fieldName)
{
    jstring result = NULL;
    if (JNI_STATIC_METHOD(getFieldValueStringC3, env, C3_JEPINTERFACE_TYPE, "getFieldValueString", "(Ljava/lang/Object;Ljava/lang/String;)Ljava/lang/String;")) {
        result = (jstring) (*env)->CallStaticObjectMethod(env, C3_JEPINTERFACE_TYPE, getFieldValueStringC3, obj, fieldName);
    }
    return result;
}
