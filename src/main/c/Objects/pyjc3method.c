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

#include "Jep.h"

/*
 * https://bugs.python.org/issue2897
 * structmember.h must be included to use PyMemberDef
 */
#include "structmember.h"


// called internally to make new PyJC3MethodObject instances.
// throws python exception and returns NULL on error.
PyJC3MethodObject* PyJC3Method_New(JNIEnv *env, jobject rmethod)
{
    jstring          methodName  = NULL;
    jstring          typeName  = NULL;
    PyObject        *pyname = NULL;
    PyJC3MethodObject *pym    = NULL;

    if (PyType_Ready(&PyJC3Method_Type) < 0) {
        return NULL;
    }

    methodName = C3_JepInterface_getMethodName(env, rmethod);
    typeName = C3_JepInterface_getTypeName(env, rmethod);

    if (process_java_exception(env) || !jname) {
        return NULL;
    }
    pyname = jstring_As_PyString(env, jname);
    (*env)->DeleteLocalRef(env, jname);

    pym                = PyObject_NEW(PyJC3MethodObject, &PyJC3Method_Type);
    pym->rmethod       = (*env)->NewGlobalRef(env, rmethod);
    pym->methodName    = methodName;
    pym->typeName      = typeName;
    pym->parameters    = NULL;
    pym->lenParameters = -1;
    pym->pyMethodName  = pyname;
    pym->isStatic      = -1;
    pym->returnTypeId  = -1;

    return pym;
}

// 1 if successful, 0 if failed.
static int pyjc3method_init(JNIEnv *env, PyJC3MethodObject *self)
{
    jobject           returnType             = NULL;
    jobjectArray      paramArray             = NULL;
    jint              modifier               = -1;
    jboolean          isStatic               = JNI_FALSE;

    if ((*env)->PushLocalFrame(env, JLOCAL_REFS) != 0) {
        process_java_exception(env);
        return 0;
    }

    returnType = C3_JepInterface_getReturnType(env, self->rmethod);
    if (process_java_exception(env) || !returnType) {
        goto EXIT_ERROR;
    }

    self->returnTypeId = get_jtype(env, returnType);
    if (process_java_exception(env)) {
        goto EXIT_ERROR;
    }

    paramArray = C3_JepInterface_getParameterTypes(env, self->rmethod);
    if (process_java_exception(env) || !paramArray) {
        goto EXIT_ERROR;
    }

    self->parameters    = (*env)->NewGlobalRef(env, paramArray);
    self->lenParameters = (*env)->GetArrayLength(env, paramArray);


    modifier = C3_JepInterface_getMemberModifiers(env, self->rmethod);
    if (process_java_exception(env)) {
        goto EXIT_ERROR;
    }

    isStatic = C3_JepInterface_isStatic(env, modifier);
    if (process_java_exception(env)) {
        goto EXIT_ERROR;
    }

    if (isStatic == JNI_TRUE) {
        self->isStatic = 1;
    } else {
        self->isStatic = 0;
    }

    (*env)->PopLocalFrame(env, NULL);
    return 1;

EXIT_ERROR:
    (*env)->PopLocalFrame(env, NULL);

    if (!PyErr_Occurred()) {
        PyErr_SetString(PyExc_RuntimeError, "Unknown");
    }
    return 0;
}


static void pyjc3method_dealloc(PyJC3MethodObject *self)
{
#if USE_DEALLOC
    JNIEnv *env  = pyembed_get_env();
    if (env) {
        if (self->parameters) {
            (*env)->DeleteGlobalRef(env, self->parameters);
        }
        if (self->rmethod) {
            (*env)->DeleteGlobalRef(env, self->rmethod);
        }
    }

    Py_CLEAR(self->pyMethodName);

    PyObject_Del(self);
#endif
}


int PyJC3Method_Check(PyObject *obj)
{
    return PyObject_TypeCheck(obj, &PyJC3Method_Type);
}

int PyJC3Method_GetParameterCount(PyJC3MethodObject *method, JNIEnv *env)
{
    if (!method->parameters && !pyjc3method_init(env, method)) {
        return -1;
    }
    return method->lenParameters;
}


int PyJC3Method_CheckArguments(PyJC3MethodObject* method, JNIEnv *env,
                             PyObject* args)
{
    int matchTotal = 1;
    int parampos;

    if (PyJC3Method_GetParameterCount(method, env) != (PyTuple_Size(args) - 1)) {
        return 0;
    }

    for (parampos = 0; parampos < method->lenParameters; parampos += 1) {
        PyObject* param       = PyTuple_GetItem(args, parampos + 1);
        int       paramTypeId;
        int       match;
        jclass    paramType   = (jclass) (*env)->GetObjectArrayElement(env,
                                method->parameters, parampos);

        if (process_java_exception(env) || !paramType) {
            match = 0;
            break;
        }

        paramTypeId = get_jtype(env, paramType);

        match = pyarg_matches_jtype(env, param, paramType, paramTypeId);
        (*env)->DeleteLocalRef(env, paramType);
        if (PyErr_Occurred()) {
            match = 0;
            break;
        }

        if (!match) {
            break;
        }
        matchTotal += match;
    }

    return matchTotal;
}

// pyjc3method_call.
// easy. :-)
static PyObject* pyjc3method_call(PyJC3MethodObject *self,
                                PyObject *args,
                                PyObject *keywords)
{
    JNIEnv        *env              = NULL;
    Py_ssize_t     lenPyArgsGiven   = 0;
    int            lenJArgsExpected = 0;
    /* The number of normal arguments before any varargs */
    int            lenJArgsNormal   = 0;
    PyObject      *firstArg         = NULL;
    PyJC3Object     *instance         = NULL;
    PyObject      *result           = NULL;
    int            pos              = 0;
    jvalue        *jargs            = NULL;
    /* if params includes pyjarray instance */
    int            foundArray       = 0;

    if (keywords != NULL) {
        PyErr_Format(PyExc_RuntimeError, "Keywords are not supported.");
        return NULL;
    }
    lenPyArgsGiven = PyTuple_Size(args);

    env = pyembed_get_env();
    lenJArgsExpected = PyJC3Method_GetParameterCount(self, env);
    if (lenJArgsExpected == -1) {
        return NULL;
    }
    /* Python gives one more arg than java expects for self/this. */
    if (lenJArgsExpected != lenPyArgsGiven - 1) {
        jboolean varargs = C3_JepInterface_isVarArgs(env, self->rmethod);
        if (process_java_exception(env)) {
            return NULL;
        }
        if (!varargs || lenJArgsExpected > lenPyArgsGiven) {
            PyErr_Format(PyExc_RuntimeError,
                         "Invalid number of arguments: %i, expected %i.",
                         (int) lenPyArgsGiven,
                         lenJArgsExpected + 1);
            return NULL;
        }
        /* The last argument will be handled as varargs, so not a normal arg */
        lenJArgsNormal = lenJArgsExpected - 1;
    } else {
        /* No varargs, all args are normal */
        lenJArgsNormal = lenJArgsExpected;
    }

    firstArg = PyTuple_GetItem(args, 0);
    if (!PyJC3Object_Check(firstArg)) {
        PyErr_SetString(PyExc_RuntimeError,
                        "First argument to a java method must be a java object.");
        return NULL;

    }
    instance = (PyJC3Object*) firstArg;

    // validate we can call this method
    if (!instance->object && self->isStatic != JNI_TRUE) {
        PyErr_Format(PyExc_RuntimeError,
                     "Instantiate this class before "
                     "calling an object method.");
        return NULL;
    }

    if ((*env)->PushLocalFrame(env, JLOCAL_REFS + lenJArgsExpected) != 0) {
        process_java_exception(env);
        return NULL;
    }

    jargs = (jvalue *) PyMem_Malloc(sizeof(jvalue) * lenJArgsExpected);
    if (jargs == NULL) {
        (*env)->PopLocalFrame(env, NULL);
        return PyErr_NoMemory();
    }
    for (pos = 0; pos < lenJArgsNormal; pos++) {
        PyObject *param = NULL;
        int paramTypeId = -1;
        jclass paramType = (jclass) (*env)->GetObjectArrayElement(env,
                           self->parameters, pos);

        param = PyTuple_GetItem(args, pos + 1);
        if (PyErr_Occurred()) {
            goto EXIT_ERROR;
        }

        paramTypeId = get_jtype(env, paramType);
        if (paramTypeId == JARRAY_ID) {
            foundArray = 1;
        }

        jargs[pos] = convert_pyarg_jvalue(env, param, paramType, paramTypeId, pos);
        if (PyErr_Occurred()) {
            if (pos == (lenJArgsExpected - 1)
                    && PyErr_ExceptionMatches(PyExc_TypeError)) {
                jboolean varargs = C3_JepInterface_isVarArgs(env, self->rmethod);
                if ((*env)->ExceptionOccurred(env)) {
                    /* Cannot convert to python since there is already a python exception */
                    (*env)->ExceptionClear(env);
                    goto EXIT_ERROR;
                }
                if (varargs) {
                    /* Retry the last arg as array for varargs */
                    PyErr_Clear();
                    lenJArgsNormal -= 1;
                } else {
                    goto EXIT_ERROR;
                }
            }
        }

        (*env)->DeleteLocalRef(env, paramType);
    }
    if (lenJArgsNormal + 1 == lenJArgsExpected) {
        /* Need to process last arg as varargs. */
        PyObject *param = NULL;
        jclass paramType = (jclass) (*env)->GetObjectArrayElement(env,
                           self->parameters, lenJArgsExpected - 1);
        if (lenPyArgsGiven == lenJArgsExpected) {
            /*
             * Python args are normally one longer than expected to allow for
             * this/self so if it isn't then nothing was given for the varargs
             */
            param = PyTuple_New(0);
        } else {
            param = PyTuple_GetSlice(args, lenJArgsExpected, lenPyArgsGiven);
        }
        if (PyErr_Occurred()) {
            goto EXIT_ERROR;
        }

        jargs[lenJArgsExpected - 1] = convert_pyarg_jvalue(env, param, paramType,
                                      JARRAY_ID,
                                      lenJArgsExpected - 1);
        Py_DecRef(param);
        if (PyErr_Occurred()) {
            goto EXIT_ERROR;
        }
        (*env)->DeleteLocalRef(env, paramType);
    }


    // ------------------------------ call based off return type

    switch (self->returnTypeId) {

    case JSTRING_ID: {
        jstring jstr;
        Py_BEGIN_ALLOW_THREADS;

        jstr = (jstring) C3_JepInterface_Dispatch(
                   self->typeName,
                   self->methodName,
                   jargs);

        Py_END_ALLOW_THREADS;
        if (!process_java_exception(env) && jstr != NULL) {
            result = jstring_As_PyString(env, jstr);
            (*env)->DeleteLocalRef(env, jstr);
        }

        break;
    }

    case JARRAY_ID: {
        jobjectArray obj;
        Py_BEGIN_ALLOW_THREADS;

        obj = (jobjectArray) C3_JepInterface_Dispatch(
                           self->typeName,
                           self->methodName,
                           jargs);

        Py_END_ALLOW_THREADS;
        if (!process_java_exception(env) && obj != NULL) {
            result = pyjarray_new(env, obj);
        }

        break;
    }

    case JCLASS_ID: {
        jobject obj;
        Py_BEGIN_ALLOW_THREADS;

        obj = C3_JepInterface_Dispatch(
                           self->typeName,
                           self->methodName,
                           jargs);

        Py_END_ALLOW_THREADS;
        if (!process_java_exception(env) && obj != NULL) {
            result = PyJC3Class_Wrap(env, obj);
        }

        break;
    }

    case JOBJECT_ID: {
        jobject obj;
        Py_BEGIN_ALLOW_THREADS;

        obj = C3_JepInterface_Dispatch(
                                   self->typeName,
                                   self->methodName,
                                   jargs);

        Py_END_ALLOW_THREADS;
        if (!process_java_exception(env) && obj != NULL) {
            result = jobject_As_PyObject(env, obj);
        }

        break;
    }

    case JINT_ID: {
        jint ret;
        Py_BEGIN_ALLOW_THREADS;

        ret = (jint) C3_JepInterface_Dispatch(
                                   self->typeName,
                                   self->methodName,
                                   jargs);

        Py_END_ALLOW_THREADS;
        if (!process_java_exception(env)) {
            result = jint_As_PyObject(ret);
        }

        break;
    }

    case JBYTE_ID: {
        jbyte ret;
        Py_BEGIN_ALLOW_THREADS;

        ret = (jbyte) C3_JepInterface_Dispatch( // TODO C3 CASTING FROM jobject TO jbyte, jint, ETC IN THIS WAY PROBABLY WONT WORK. WE WILL NEED A UNIQUE FUNCTION TO CALL C3.Dispatch PER RETURN TYPE
                                   self->typeName,
                                   self->methodName,
                                   jargs);

        Py_END_ALLOW_THREADS;
        if (!process_java_exception(env)) {
            result = jbyte_As_PyObject(ret);
        }

        break;
    }

    case JCHAR_ID: {
        jchar ret;
        Py_BEGIN_ALLOW_THREADS;

        ret = (jchar) C3_JepInterface_Dispatch( // TODO C3 CASTING FROM jobject TO jbyte, jint, ETC IN THIS WAY PROBABLY WONT WORK. WE WILL NEED A UNIQUE FUNCTION TO CALL C3.Dispatch PER RETURN TYPE
                                   self->typeName,
                                   self->methodName,
                                   jargs);

        Py_END_ALLOW_THREADS;
        if (!process_java_exception(env)) {
            result = jchar_As_PyObject(ret);
        }
        break;
    }

    case JSHORT_ID: {
        jshort ret;
        Py_BEGIN_ALLOW_THREADS;

        ret = (jshort) C3_JepInterface_Dispatch( // TODO C3 CASTING FROM jobject TO jbyte, jint, ETC IN THIS WAY PROBABLY WONT WORK. WE WILL NEED A UNIQUE FUNCTION TO CALL C3.Dispatch PER RETURN TYPE
                                   self->typeName,
                                   self->methodName,
                                   jargs);

        Py_END_ALLOW_THREADS;
        if (!process_java_exception(env)) {
            result = jshort_As_PyObject(ret);
        }

        break;
    }

    case JDOUBLE_ID: {
        jdouble ret;
        Py_BEGIN_ALLOW_THREADS;

        ret = (jdouble) C3_JepInterface_Dispatch( // TODO C3 CASTING FROM jobject TO jbyte, jint, ETC IN THIS WAY PROBABLY WONT WORK. WE WILL NEED A UNIQUE FUNCTION TO CALL C3.Dispatch PER RETURN TYPE
                                   self->typeName,
                                   self->methodName,
                                   jargs);

        Py_END_ALLOW_THREADS;
        if (!process_java_exception(env)) {
            result = jdouble_As_PyObject(ret);
        }

        break;
    }

    case JFLOAT_ID: {
        jfloat ret;
        Py_BEGIN_ALLOW_THREADS;

        ret = (jfloat) C3_JepInterface_Dispatch( // TODO C3 CASTING FROM jobject TO jbyte, jint, ETC IN THIS WAY PROBABLY WONT WORK. WE WILL NEED A UNIQUE FUNCTION TO CALL C3.Dispatch PER RETURN TYPE
                                   self->typeName,
                                   self->methodName,
                                   jargs);

        Py_END_ALLOW_THREADS;
        if (!process_java_exception(env)) {
            result = jfloat_As_PyObject(ret);
        }

        break;
    }

    case JLONG_ID: {
        jlong ret;
        Py_BEGIN_ALLOW_THREADS;

        ret = (jlong) C3_JepInterface_Dispatch( // TODO C3 CASTING FROM jobject TO jbyte, jint, ETC IN THIS WAY PROBABLY WONT WORK. WE WILL NEED A UNIQUE FUNCTION TO CALL C3.Dispatch PER RETURN TYPE
                                   self->typeName,
                                   self->methodName,
                                   jargs);

        Py_END_ALLOW_THREADS;
        if (!process_java_exception(env)) {
            result = jlong_As_PyObject(ret);
        }

        break;
    }

    case JBOOLEAN_ID: {
        jboolean ret;
        Py_BEGIN_ALLOW_THREADS;

        ret = (jboolean) C3_JepInterface_Dispatch( // TODO C3 CASTING FROM jobject TO jbyte, jint, ETC IN THIS WAY PROBABLY WONT WORK. WE WILL NEED A UNIQUE FUNCTION TO CALL C3.Dispatch PER RETURN TYPE
                                   self->typeName,
                                   self->methodName,
                                   jargs);

        Py_END_ALLOW_THREADS;
        if (!process_java_exception(env)) {
            result = jboolean_As_PyObject(ret);
        }

        break;
    }

    default:
        Py_BEGIN_ALLOW_THREADS;

        // i hereby anoint thee a void method
        C3_JepInterface_Dispatch(
                       self->typeName,
                       self->methodName,
                       jargs);

        Py_END_ALLOW_THREADS;
        process_java_exception(env);
        break;
    }

    PyMem_Free(jargs);
    (*env)->PopLocalFrame(env, NULL);

    if (PyErr_Occurred()) {
        return NULL;
    }

    // re pin array objects if needed
    if (foundArray) {
        for (pos = 0; pos < lenJArgsNormal; pos++) {
            PyObject *param = PyTuple_GetItem(args, pos + 1);     /* borrowed */
            if (param && pyjarray_check(param)) {
                pyjarray_pin((PyJArrayObject *) param);
            }
        }
    }

    if (result == NULL) {
        Py_RETURN_NONE;
    }

    return result;

EXIT_ERROR:
    PyMem_Free(jargs);
    (*env)->PopLocalFrame(env, NULL);
    return NULL;
}

static PyMemberDef pyjc3method_members[] = {
    {
        "__name__", T_OBJECT_EX, offsetof(PyJC3MethodObject, pyMethodName), READONLY,
        "method name"
    },
    {NULL}  /* Sentinel */
};


PyTypeObject PyJC3Method_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "jep.PyJC3Method",
    sizeof(PyJC3MethodObject),
    0,
    (destructor) pyjc3method_dealloc,           /* tp_dealloc */
    0,                                        /* tp_print */
    0,                                        /* tp_getattr */
    0,                                        /* tp_setattr */
    0,                                        /* tp_compare */
    0,                                        /* tp_repr */
    0,                                        /* tp_as_number */
    0,                                        /* tp_as_sequence */
    0,                                        /* tp_as_mapping */
    0,                                        /* tp_hash  */
    (ternaryfunc) pyjc3method_call,             /* tp_call */
    0,                                        /* tp_str */
    0,                                        /* tp_getattro */
    0,                                        /* tp_setattro */
    0,                                        /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,                       /* tp_flags */
    "Python Java Method",                                /* tp_doc */
    0,                                        /* tp_traverse */
    0,                                        /* tp_clear */
    0,                                        /* tp_richcompare */
    0,                                        /* tp_weaklistoffset */
    0,                                        /* tp_iter */
    0,                                        /* tp_iternext */
    0,                                        /* tp_methods */
    pyjc3method_members,                        /* tp_members */
    0,                                        /* tp_getset */
    0,                                        /* tp_base */
    0,                                        /* tp_dict */
    0,                                        /* tp_descr_get */
    0,                                        /* tp_descr_set */
    0,                                        /* tp_dictoffset */
    0,                                        /* tp_init */
    0,                                        /* tp_alloc */
    NULL,                                     /* tp_new */
};