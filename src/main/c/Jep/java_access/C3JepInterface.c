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
static jmethodID dispatchVoidC3 = 0;


static jmethodID dispatchStringMemberC3 = 0;
static jmethodID dispatchArrayMemberC3 = 0;
static jmethodID dispatchClassMemberC3 = 0;
static jmethodID dispatchObjectMemberC3 = 0;
static jmethodID dispatchIntMemberC3 = 0;
static jmethodID dispatchByteMemberC3 = 0;
static jmethodID dispatchDoubleMemberC3 = 0;
static jmethodID dispatchFloatMemberC3 = 0;
static jmethodID dispatchLongMemberC3 = 0;
static jmethodID dispatchBooleanMemberC3 = 0;
static jmethodID dispatchVoidMemberC3 = 0;

static jmethodID getFieldValueStringC3 = 0;
static jmethodID getFieldValueArrayC3 = 0;
static jmethodID getFieldValueClassC3 = 0;
static jmethodID getFieldValueObjectC3 = 0;
static jmethodID getFieldValueIntC3 = 0;
static jmethodID getFieldValueByteC3 = 0;
static jmethodID getFieldValueDoubleC3 = 0;
static jmethodID getFieldValueFloatC3 = 0;
static jmethodID getFieldValueLongC3 = 0;
static jmethodID getFieldValueBooleanC3 = 0;

static jmethodID getConstantFieldValueStringC3 = 0;
static jmethodID getConstantFieldValueArrayC3 = 0;
static jmethodID getConstantFieldValueClassC3 = 0;
static jmethodID getConstantFieldValueObjectC3 = 0;
static jmethodID getConstantFieldValueIntC3 = 0;
static jmethodID getConstantFieldValueByteC3 = 0;
static jmethodID getConstantFieldValueDoubleC3 = 0;
static jmethodID getConstantFieldValueFloatC3 = 0;
static jmethodID getConstantFieldValueLongC3 = 0;
static jmethodID getConstantFieldValueBooleanC3 = 0;

static jmethodID isFieldConstantC3 = 0;
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


//STATIC FUNCTIONS


jstring C3_JepInterface_dispatchString(JNIEnv* env, jstring tn, jstring mn, jobjectArray args)
{
    jstring result = NULL;
    if (JNI_STATIC_METHOD(dispatchStringC3, env, C3_JEPINTERFACE_TYPE, "dispatchString", "(Ljava/lang/Object;Ljava/lang/String;)Ljava/lang/String;")) {
        result = (jstring) (*env)->CallStaticObjectMethod(env, C3_JEPINTERFACE_TYPE, dispatchStringC3, tn, mn, args);
    }
    return result;
}


jobjectArray C3_JepInterface_dispatchArray(JNIEnv* env, jstring tn, jstring mn, jobjectArray args)
{
    jobjectArray result = NULL;
    if (JNI_STATIC_METHOD(dispatchArrayC3, env, C3_JEPINTERFACE_TYPE, "dispatchArray", "(Ljava/lang/Object;Ljava/lang/String;)[Ljava/lang/Object;")) {
        result = (jobjectArray) (*env)->CallStaticObjectMethod(env, C3_JEPINTERFACE_TYPE, dispatchArrayC3, tn, mn, args);
    }
    return result;
}

jobject C3_JepInterface_dispatchObject(JNIEnv* env, jstring tn, jstring mn, jobjectArray args)
{
    jobject result = NULL;
    if (JNI_STATIC_METHOD(dispatchObjectC3, env, C3_JEPINTERFACE_TYPE, "dispatchObject", "(Ljava/lang/Object;Ljava/lang/String;)Ljava/lang/Object;")) {
        result = (jobject) (*env)->CallStaticObjectMethod(env, C3_JEPINTERFACE_TYPE, dispatchObjectC3, tn, mn, args);
    }
    return result;
}

jobject C3_JepInterface_dispatchClass(JNIEnv* env, jstring tn, jstring mn, jobjectArray args)
{
    jobject result = NULL;
    if (JNI_STATIC_METHOD(dispatchClassC3, env, C3_JEPINTERFACE_TYPE, "dispatchClass", "(Ljava/lang/Object;Ljava/lang/String;)Ljava/lang/Object;")) {
        result = (jobject) (*env)->CallStaticObjectMethod(env, C3_JEPINTERFACE_TYPE, dispatchClassC3, tn, mn, args);
    }
    return result;
}

jint C3_JepInterface_dispatchInt(JNIEnv* env, jstring tn, jstring mn, jobjectArray args)
{
    jint result = 0;
    if (JNI_STATIC_METHOD(dispatchIntC3, env, C3_JEPINTERFACE_TYPE, "dispatchInt", "(Ljava/lang/Object;Ljava/lang/String;)I")) {
        result = (*env)->CallStaticIntMethod(env, C3_JEPINTERFACE_TYPE, dispatchIntC3, tn, mn, args);
    }
    return result;
}

jbyte C3_JepInterface_dispatchByte(JNIEnv* env, jstring tn, jstring mn, jobjectArray args)
{
   jbyte result = 0;
   if (JNI_STATIC_METHOD(dispatchByteC3, env, C3_JEPINTERFACE_TYPE, "dispatchByte", "(Ljava/lang/Object;Ljava/lang/String;)B")) {
       result = (*env)->CallStaticByteMethod(env, C3_JEPINTERFACE_TYPE, dispatchByteC3, tn, mn, args);
   }
   return result;
}

jdouble C3_JepInterface_dispatchDouble(JNIEnv* env, jstring tn, jstring mn, jobjectArray args)
{
    jdouble result = 0;
    if (JNI_STATIC_METHOD(dispatchDoubleC3, env, C3_JEPINTERFACE_TYPE, "dispatchDouble", "(Ljava/lang/Object;Ljava/lang/String;)D")) {
        result = (*env)->CallStaticDoubleMethod(env, C3_JEPINTERFACE_TYPE, dispatchDoubleC3, tn, mn, args);
    }
    return result;
}

jfloat C3_JepInterface_dispatchFloat(JNIEnv* env, jstring tn, jstring mn, jobjectArray args)
{
    jfloat result = 0;
    if (JNI_STATIC_METHOD(dispatchFloatC3, env, C3_JEPINTERFACE_TYPE, "dispatchFloat", "(Ljava/lang/Object;Ljava/lang/String;)F")) {
        result = (*env)->CallStaticFloatMethod(env, C3_JEPINTERFACE_TYPE, dispatchFloatC3, tn, mn, args);
    }
    return result;
}

jlong C3_JepInterface_dispatchLong(JNIEnv* env, jstring tn, jstring mn, jobjectArray args)
{
    jlong result = 0;
    if (JNI_STATIC_METHOD(dispatchLongC3, env, C3_JEPINTERFACE_TYPE, "dispatchLong", "(Ljava/lang/Object;Ljava/lang/String;)L")) {
        result = (*env)->CallStaticLongMethod(env, C3_JEPINTERFACE_TYPE, dispatchLongC3, tn, mn, args);
    }
    return result;
}

jboolean C3_JepInterface_dispatchBoolean(JNIEnv* env, jstring tn, jstring mn, jobjectArray args)
{
    jboolean result = JNI_FALSE;
    if (JNI_STATIC_METHOD(dispatchBooleanC3, env, C3_JEPINTERFACE_TYPE, "dispatchBoolean", "(Ljava/lang/Object;Ljava/lang/String;)Z")) {
        result = (*env)->CallStaticBooleanMethod(env, C3_JEPINTERFACE_TYPE, dispatchBooleanC3, tn, mn, args);
    }
    return result;
}

void C3_JepInterface_dispatchVoid(JNIEnv* env, jstring tn, jstring mn, jobjectArray args)
{
    if (JNI_STATIC_METHOD(dispatchVoidC3, env, C3_JEPINTERFACE_TYPE, "dispatchVoid", "(Ljava/lang/Object;Ljava/lang/String;)")) {
        (*env)->CallStaticVoidMethod(env, C3_JEPINTERFACE_TYPE, dispatchVoidC3, tn, mn, args);
    }
}



// MEMBER FUNCTIONS



jstring C3_JepInterface_dispatchStringMember(JNIEnv* env, jstring tn, jstring mn, jobject obj, jobjectArray args)
{
    jstring result = NULL;
    if (JNI_STATIC_METHOD(dispatchStringMemberC3, env, C3_JEPINTERFACE_TYPE, "dispatchStringMember",
                          "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/Object;[Ljava/lang/Object;)Ljava/lang/String;")) {
        result = (jstring) (*env)->CallStaticObjectMethod(env, C3_JEPINTERFACE_TYPE, dispatchStringMemberC3, tn, mn, obj, args);
    }
    return result;
}

jobjectArray C3_JepInterface_dispatchArrayMember(JNIEnv* env, jstring tn, jstring mn, jobject obj, jobjectArray args)
{
    jobjectArray result = NULL;
    if (JNI_STATIC_METHOD(dispatchArrayMemberC3, env, C3_JEPINTERFACE_TYPE, "dispatchArrayMember", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/Object;[Ljava/lang/Object;)[Ljava/lang/Object;")) {
        result = (jobjectArray) (*env)->CallStaticObjectMethod(env, C3_JEPINTERFACE_TYPE, dispatchArrayMemberC3, tn, mn, obj, args);
    }
    return result;
}


jobject C3_JepInterface_dispatchObjectMember(JNIEnv* env, jstring tn, jstring mn, jobject obj, jobjectArray args)
{
    jobject result = NULL;
    if (JNI_STATIC_METHOD(dispatchObjectMemberC3, env, C3_JEPINTERFACE_TYPE, "dispatchObjectMember", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/Object;[Ljava/lang/Object;)Ljava/lang/Object;")) {
        result = (jobject) (*env)->CallStaticObjectMethod(env, C3_JEPINTERFACE_TYPE, dispatchObjectMemberC3, tn, mn, obj, args);
    }
    return result;
}


jobject C3_JepInterface_dispatchClassMember(JNIEnv* env, jstring tn, jstring mn, jobject obj, jobjectArray args)
{
    jobject result = NULL;
    if (JNI_STATIC_METHOD(dispatchClassMemberC3, env, C3_JEPINTERFACE_TYPE, "dispatchClassMember", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/Object;[Ljava/lang/Object;)Ljava/lang/Object;")) {
        result = (jobject) (*env)->CallStaticObjectMethod(env, C3_JEPINTERFACE_TYPE, dispatchClassMemberC3, tn, mn, obj, args);
    }
    return result;
}

jint C3_JepInterface_dispatchIntMember(JNIEnv* env, jstring tn, jstring mn, jobject obj, jobjectArray args)
{
    jint result = 0;
    if (JNI_STATIC_METHOD(dispatchIntMemberC3, env, C3_JEPINTERFACE_TYPE, "dispatchIntMember", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/Object;[Ljava/lang/Object;)I")) {
        result = (*env)->CallStaticIntMethod(env, C3_JEPINTERFACE_TYPE, dispatchIntMemberC3, tn, mn, obj, args);
    }
    return result;
}


jbyte C3_JepInterface_dispatchByteMember(JNIEnv* env, jstring tn, jstring mn, jobject obj, jobjectArray args)
{
   jbyte result = 0;
   if (JNI_STATIC_METHOD(dispatchByteMemberC3, env, C3_JEPINTERFACE_TYPE, "dispatchByteMember", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/Object;[Ljava/lang/Object;)B")) {
       result = (*env)->CallStaticByteMethod(env, C3_JEPINTERFACE_TYPE, dispatchByteMemberC3, tn, mn, obj, args);
   }
   return result;
}


jdouble C3_JepInterface_dispatchDoubleMember(JNIEnv* env, jstring tn, jstring mn, jobject obj, jobjectArray args)
{
    jdouble result = 0;
    if (JNI_STATIC_METHOD(dispatchDoubleMemberC3, env, C3_JEPINTERFACE_TYPE, "dispatchDoubleMember", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/Object;[Ljava/lang/Object;)D")) {
        result = (*env)->CallStaticDoubleMethod(env, C3_JEPINTERFACE_TYPE, dispatchDoubleMemberC3, tn, mn, obj, args);
    }
    return result;
}


jfloat C3_JepInterface_dispatchFloatMember(JNIEnv* env, jstring tn, jstring mn, jobject obj, jobjectArray args)
{
    jfloat result = 0;
    if (JNI_STATIC_METHOD(dispatchFloatMemberC3, env, C3_JEPINTERFACE_TYPE, "dispatchFloatMember", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/Object;[Ljava/lang/Object;)F")) {
        result = (*env)->CallStaticFloatMethod(env, C3_JEPINTERFACE_TYPE, dispatchFloatMemberC3, tn, mn, obj, args);
    }
    return result;
}

jlong C3_JepInterface_dispatchLongMember(JNIEnv* env, jstring tn, jstring mn, jobject obj, jobjectArray args)
{
    jlong result = 0;
    if (JNI_STATIC_METHOD(dispatchLongMemberC3, env, C3_JEPINTERFACE_TYPE, "dispatchLongMember", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/Object;[Ljava/lang/Object;)L")) {
        result = (*env)->CallStaticLongMethod(env, C3_JEPINTERFACE_TYPE, dispatchLongMemberC3, tn, mn, obj, args);
    }
    return result;
}

jboolean C3_JepInterface_dispatchBooleanMember(JNIEnv* env, jstring tn, jstring mn, jobject obj, jobjectArray args)
{
    jboolean result = JNI_FALSE;
    if (JNI_STATIC_METHOD(dispatchBooleanMemberC3, env, C3_JEPINTERFACE_TYPE, "dispatchBooleanMember", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/Object;[Ljava/lang/Object;)Z")) {
        result = (*env)->CallStaticBooleanMethod(env, C3_JEPINTERFACE_TYPE, dispatchBooleanMemberC3, tn, mn, obj, args);
    }
    return result;
}

void C3_JepInterface_dispatchVoidMember(JNIEnv* env, jstring tn, jstring mn, jobject obj, jobjectArray args)
{
    if (JNI_STATIC_METHOD(dispatchVoidMemberC3, env, C3_JEPINTERFACE_TYPE, "dispatchVoidMember", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/Object;[Ljava/lang/Object;)")) {
        (*env)->CallStaticVoidMethod(env, C3_JEPINTERFACE_TYPE, dispatchVoidMemberC3, tn, mn, obj, args);
    }
}



// Field Accessors
jstring C3_JepInterface_getFieldValueString(JNIEnv* env, jobject obj, jstring fieldName)
{
    jstring result = NULL;
    if (JNI_STATIC_METHOD(getFieldValueStringC3, env, C3_JEPINTERFACE_TYPE, "getFieldValueString", "(Ljava/lang/Object;Ljava/lang/String;)Ljava/lang/String;")) {
        result = (jstring) (*env)->CallStaticObjectMethod(env, C3_JEPINTERFACE_TYPE, getFieldValueStringC3, obj, fieldName);
    }
    return result;
}


jobjectArray C3_JepInterface_getFieldValueArray(JNIEnv* env, jobject obj, jstring fieldName)
{
    jobjectArray result = NULL;
    if (JNI_STATIC_METHOD(getFieldValueArrayC3, env, C3_JEPINTERFACE_TYPE, "getFieldValueArray", "(Ljava/lang/Object;Ljava/lang/String;)[Ljava/lang/Object;")) {
        result = (jobjectArray) (*env)->CallStaticObjectMethod(env, C3_JEPINTERFACE_TYPE, getFieldValueArrayC3, obj, fieldName);
    }
    return result;
}

jobject C3_JepInterface_getFieldValueObject(JNIEnv* env, jobject obj, jstring fieldName)
{
    jobject result = NULL;
    if (JNI_STATIC_METHOD(getFieldValueObjectC3, env, C3_JEPINTERFACE_TYPE, "getFieldValueObject", "(Ljava/lang/Object;Ljava/lang/String;)Ljava/lang/Object;")) {
        result = (jobject) (*env)->CallStaticObjectMethod(env, C3_JEPINTERFACE_TYPE, getFieldValueObjectC3, obj, fieldName);
    }
    return result;
}

jobject C3_JepInterface_getFieldValueClass(JNIEnv* env, jobject obj, jstring fieldName)
{
    jobject result = NULL;
    if (JNI_STATIC_METHOD(getFieldValueClassC3, env, C3_JEPINTERFACE_TYPE, "getFieldValueClass", "(Ljava/lang/Object;Ljava/lang/String;)Ljava/lang/Object;")) {
        result = (jobject) (*env)->CallStaticObjectMethod(env, C3_JEPINTERFACE_TYPE, getFieldValueClassC3, obj, fieldName);
    }
    return result;
}

jint C3_JepInterface_getFieldValueInt(JNIEnv* env, jobject obj, jstring fieldName)
{
    jint result = 0;
    if (JNI_STATIC_METHOD(getFieldValueIntC3, env, C3_JEPINTERFACE_TYPE, "getFieldValueInt", "(Ljava/lang/Object;Ljava/lang/String;)I")) {
        result = (*env)->CallStaticIntMethod(env, C3_JEPINTERFACE_TYPE, getFieldValueIntC3, obj, fieldName);
    }
    return result;
}

jbyte C3_JepInterface_getFieldValueByte(JNIEnv* env, jobject obj, jstring fieldName)
{
   jbyte result = 0;
   if (JNI_STATIC_METHOD(getFieldValueByteC3, env, C3_JEPINTERFACE_TYPE, "getFieldValueByte", "(Ljava/lang/Object;Ljava/lang/String;)B")) {
       result = (*env)->CallStaticByteMethod(env, C3_JEPINTERFACE_TYPE, getFieldValueByteC3, obj, fieldName);
   }
   return result;
}

jdouble C3_JepInterface_getFieldValueDouble(JNIEnv* env, jobject obj, jstring fieldName)
{
    jdouble result = 0;
    if (JNI_STATIC_METHOD(getFieldValueDoubleC3, env, C3_JEPINTERFACE_TYPE, "getFieldValueDouble", "(Ljava/lang/Object;Ljava/lang/String;)D")) {
        result = (*env)->CallStaticDoubleMethod(env, C3_JEPINTERFACE_TYPE, getFieldValueDoubleC3, obj, fieldName);
    }
    return result;
}

jfloat C3_JepInterface_getFieldValueFloat(JNIEnv* env, jobject obj, jstring fieldName)
{
    jfloat result = 0;
    if (JNI_STATIC_METHOD(getFieldValueFloatC3, env, C3_JEPINTERFACE_TYPE, "getFieldValueFloat", "(Ljava/lang/Object;Ljava/lang/String;)F")) {
        result = (*env)->CallStaticFloatMethod(env, C3_JEPINTERFACE_TYPE, getFieldValueFloatC3, obj, fieldName);
    }
    return result;
}

jlong C3_JepInterface_getFieldValueLong(JNIEnv* env, jobject obj, jstring fieldName)
{
    jlong result = 0;
    if (JNI_STATIC_METHOD(getFieldValueLongC3, env, C3_JEPINTERFACE_TYPE, "getFieldValueLong", "(Ljava/lang/Object;Ljava/lang/String;)L")) {
        result = (*env)->CallStaticLongMethod(env, C3_JEPINTERFACE_TYPE, getFieldValueLongC3, obj, fieldName);
    }
    return result;
}

jboolean C3_JepInterface_getFieldValueBoolean(JNIEnv* env, jobject obj, jstring fieldName)
{
    jboolean result = JNI_FALSE;
    if (JNI_STATIC_METHOD(getFieldValueBooleanC3, env, C3_JEPINTERFACE_TYPE, "getFieldValueBoolean", "(Ljava/lang/Object;Ljava/lang/String;)Z")) {
        result = (*env)->CallStaticBooleanMethod(env, C3_JEPINTERFACE_TYPE, getFieldValueBooleanC3, obj, fieldName);
    }
    return result;
}


// Static Field Accessors


jstring C3_JepInterface_getConstantFieldValueString(JNIEnv* env, jstring typeName, jstring fieldName)
{
    jstring result = NULL;
    if (JNI_STATIC_METHOD(getConstantFieldValueStringC3, env, C3_JEPINTERFACE_TYPE, "getConstantFieldValueString", "(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;")) {
        result = (jstring) (*env)->CallStaticObjectMethod(env, C3_JEPINTERFACE_TYPE, getConstantFieldValueStringC3, typeName, fieldName);
    }
    return result;
}


jobjectArray C3_JepInterface_getConstantFieldValueArray(JNIEnv* env, jstring typeName, jstring fieldName)
{
    jobjectArray result = NULL;
    if (JNI_STATIC_METHOD(getConstantFieldValueArrayC3, env, C3_JEPINTERFACE_TYPE, "getConstantFieldValueArray", "(Ljava/lang/String;Ljava/lang/String;)[Ljava/lang/Object;")) {
        result = (jobjectArray) (*env)->CallStaticObjectMethod(env, C3_JEPINTERFACE_TYPE, getConstantFieldValueArrayC3, typeName, fieldName);
    }
    return result;
}

jobject C3_JepInterface_getConstantFieldValueObject(JNIEnv* env, jstring typeName, jstring fieldName)
{
    jobject result = NULL;
    if (JNI_STATIC_METHOD(getConstantFieldValueObjectC3, env, C3_JEPINTERFACE_TYPE, "getConstantFieldValueObject", "(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/Object;")) {
        result = (jobject) (*env)->CallStaticObjectMethod(env, C3_JEPINTERFACE_TYPE, getConstantFieldValueObjectC3, typeName, fieldName);
    }
    return result;
}

jobject C3_JepInterface_getConstantFieldValueClass(JNIEnv* env, jstring typeName, jstring fieldName)
{
    jobject result = NULL;
    if (JNI_STATIC_METHOD(getConstantFieldValueClassC3, env, C3_JEPINTERFACE_TYPE, "getConstantFieldValueClass", "(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/Object;")) {
        result = (jobject) (*env)->CallStaticObjectMethod(env, C3_JEPINTERFACE_TYPE, getConstantFieldValueClassC3, typeName, fieldName);
    }
    return result;
}

jint C3_JepInterface_getConstantFieldValueInt(JNIEnv* env, jstring typeName, jstring fieldName)
{
    jint result = 0;
    if (JNI_STATIC_METHOD(getConstantFieldValueIntC3, env, C3_JEPINTERFACE_TYPE, "getConstantFieldValueInt", "(Ljava/lang/String;Ljava/lang/String;)I")) {
        result = (*env)->CallStaticIntMethod(env, C3_JEPINTERFACE_TYPE, getConstantFieldValueIntC3, typeName, fieldName);
    }
    return result;
}

jbyte C3_JepInterface_getConstantFieldValueByte(JNIEnv* env, jstring typeName, jstring fieldName)
{
    jbyte result = 0;
    if (JNI_STATIC_METHOD(getConstantFieldValueByteC3, env, C3_JEPINTERFACE_TYPE, "getConstantFieldValueByte", "(Ljava/lang/String;Ljava/lang/String;)B")) {
        result = (*env)->CallStaticByteMethod(env, C3_JEPINTERFACE_TYPE, getConstantFieldValueByteC3, typeName, fieldName);
    }
    return result;
}

jdouble C3_JepInterface_getConstantFieldValueDouble(JNIEnv* env, jstring typeName, jstring fieldName)
{
    jdouble result = 0;
    if (JNI_STATIC_METHOD(getConstantFieldValueDoubleC3, env, C3_JEPINTERFACE_TYPE, "getConstantFieldValueDouble", "(Ljava/lang/String;Ljava/lang/String;)D")) {
        result = (*env)->CallStaticDoubleMethod(env, C3_JEPINTERFACE_TYPE, getConstantFieldValueDoubleC3, typeName, fieldName);
    }
    return result;
}

jfloat C3_JepInterface_getConstantFieldValueFloat(JNIEnv* env, jstring typeName, jstring fieldName)
{
    jfloat result = 0;
    if (JNI_STATIC_METHOD(getConstantFieldValueFloatC3, env, C3_JEPINTERFACE_TYPE, "getConstantFieldValueFloat", "(Ljava/lang/String;Ljava/lang/String;)F")) {
        result = (*env)->CallStaticFloatMethod(env, C3_JEPINTERFACE_TYPE, getConstantFieldValueFloatC3, typeName, fieldName);
    }
    return result;
}

jlong C3_JepInterface_getConstantFieldValueLong(JNIEnv* env, jstring typeName, jstring fieldName)
{
    jlong result = 0;
    if (JNI_STATIC_METHOD(getConstantFieldValueLongC3, env, C3_JEPINTERFACE_TYPE, "getConstantFieldValueLong", "(Ljava/lang/String;Ljava/lang/String;)L")) {
        result = (*env)->CallStaticLongMethod(env, C3_JEPINTERFACE_TYPE, getConstantFieldValueLongC3, typeName, fieldName);
    }
    return result;
}

jboolean C3_JepInterface_getConstantFieldValueBoolean(JNIEnv* env, jstring typeName, jstring fieldName)
{
    jboolean result = JNI_FALSE;
    if (JNI_STATIC_METHOD(getConstantFieldValueBooleanC3, env, C3_JEPINTERFACE_TYPE, "getConstantFieldValueBoolean", "(Ljava/lang/String;Ljava/lang/String;)Z")) {
        result = (*env)->CallStaticBooleanMethod(env, C3_JEPINTERFACE_TYPE, getConstantFieldValueBooleanC3, typeName, fieldName);
    }
    return result;
}



// OTHER

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


jboolean C3_JepInterface_isFieldConstant(JNIEnv* env, jobject ft)
{
    jboolean result = JNI_FALSE;
    if (isFieldConstantC3
            || (isFieldConstantC3 = (*env)->GetStaticMethodID(env, C3_JEPINTERFACE_TYPE, "isFieldConstant",
                           "(Lc3/platform/type/FieldType;)Z"))) {
        result = (*env)->CallStaticBooleanMethod(env, C3_JEPINTERFACE_TYPE, isFieldConstantC3, ft);
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
