#include "Jep.h"

static jmethodID dispatchStringC3 = 0;
static jmethodID dispatchArrayC3 = 0;
static jmethodID dispatchClassC3 = 0;
static jmethodID dispatchObjectC3 = 0;
static jmethodID dispatchIntC3 = 0;
static jmethodID dispatchByteC3 = 0;
static jmethodID dispatchDoubleC3 = 0;
static jmethodID dispatchFloatC3 = 0;
static jmethodID dispatchLongC3 = 0;
static jmethodID dispatchBooleanC3 = 0;


jstring C3_JepInterface_dispatchString(JNIEnv* env, jobject this)
{
    jstring result = NULL;
    if (JNI_STATIC_METHOD(dispatchStringC3, env, C3_JEPINTERFACE_TYPE, "dispatchString", "(args blah blah)Ljava/lang/String;")) {
        result = (jstring) (*env)->CallStaticObjectMethod(env, C3_JEPINTERFACE_TYPE, dispatchStringC3, this);
    }
    return result;
}

jobjectArray C3_JepInterface_dispatchArray(JNIEnv* env, jobject this)
{
    jobjectArray result = NULL;
    if (JNI_STATIC_METHOD(dispatchArrayC3, env, C3_JEPINTERFACE_TYPE, "dispatchObject", "(args blah blah)[Ljava/lang/Object;")) {
        result = (jobjectArray) (*env)->CallStaticObjectMethod(env, C3_JEPINTERFACE_TYPE, dispatchArrayC3, this);
    }
    return result;
}

jobject C3_JepInterface_dispatchObject(JNIEnv* env, jobject this)
{
    jobject result = NULL;
    if (JNI_STATIC_METHOD(dispatchObjectC3, env, C3_JEPINTERFACE_TYPE, "dispatchObject", "(args blah blah)Ljava/lang/Object;")) {
        result = (jobject) (*env)->CallStaticObjectMethod(env, C3_JEPINTERFACE_TYPE, dispatchObjectC3, this);
    }
    return result;
}

jobject C3_JepInterface_dispatchClass(JNIEnv* env, jobject this)
{
    jobject result = NULL;
    if (JNI_STATIC_METHOD(dispatchClassC3, env, C3_JEPINTERFACE_TYPE, "dispatchClass", "(args blah blah)Ljava/lang/Object;")) {
        result = (jobject) (*env)->CallStaticObjectMethod(env, C3_JEPINTERFACE_TYPE, dispatchClassC3, this);
    }
    return result;
}

jint C3_JepInterface_dispatchInt(JNIEnv* env, jobject this)
{
    jint result = 0;
    if (JNI_STATIC_METHOD(dispatchIntC3, env, C3_JEPINTERFACE_TYPE, "dispatchInt", "(args blah blah)I")) {
        result = (*env)->CallStaticIntMethod(env, C3_JEPINTERFACE_TYPE, dispatchIntC3, this);
    }
    return result;
}

jbyte C3_JepInterface_dispatchByte(JNIEnv* env, jobject this)
{
    jbyte result = 0;
    if (JNI_STATIC_METHOD(dispatchByteC3, env, C3_JEPINTERFACE_TYPE, "dispatchByte", "(args blah blah)B")) {
        result = (*env)->CallStaticByteMethod(env, C3_JEPINTERFACE_TYPE, dispatchByteC3, this);
    }
    return result;
}

jdouble C3_JepInterface_dispatchDouble(JNIEnv* env, jobject this)
{
    jdouble result = 0;
    if (JNI_STATIC_METHOD(dispatchDoubleC3, env, C3_JEPINTERFACE_TYPE, "dispatchDouble", "(args blah blah)D")) {
        result = (*env)->CallStaticDoubleMethod(env, C3_JEPINTERFACE_TYPE, dispatchDoubleC3, this);
    }
    return result;
}

jfloat C3_JepInterface_dispatchFloat(JNIEnv* env, jobject this)
{
    jfloat result = 0;
    if (JNI_STATIC_METHOD(dispatchFloatC3, env, C3_JEPINTERFACE_TYPE, "dispatchFloat", "(args blah blah)F")) {
        result = (*env)->CallStaticFloatMethod(env, C3_JEPINTERFACE_TYPE, dispatchFloatC3, this);
    }
    return result;
}

jlong C3_JepInterface_dispatchLong(JNIEnv* env, jobject this)
{
    jlong result = 0;
    if (JNI_STATIC_METHOD(dispatchByteC3, env, C3_JEPINTERFACE_TYPE, "dispatchLong", "(args blah blah)L")) {
        result = (*env)->CallStaticLongMethod(env, C3_JEPINTERFACE_TYPE, dispatchLongC3, this);
    }
    return result;
}

jboolean C3_JepInterface_dispatchBoolean(JNIEnv* env, jobject this)
{
    jboolean result = JNI_FALSE;
    if (JNI_STATIC_METHOD(dispatchDoubleC3, env, C3_JEPINTERFACE_TYPE, "dispatchBoolean", "(args blah blah)Z")) {
        result = (*env)->CallStaticBooleanMethod(env, C3_JEPINTERFACE_TYPE, dispatchBooleanC3, this);
    }
    return result;
}