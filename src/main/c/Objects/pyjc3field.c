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

   ---
   Fields really don't have to be represented as python objects,
   but it is nice to have garbage collection and to be able
   to cast to PyObject.
*/

#include "Jep.h"

static void pyjc3field_dealloc(PyJC3FieldObject *self)
{
#if USE_DEALLOC
    JNIEnv *env  = pyembed_get_env();
    if (env) {
        if (self->c3field) {
            (*env)->DeleteGlobalRef(env, self->c3field);
        }
    }

    Py_CLEAR(self->pyFieldName);

    PyObject_Del(self);
#endif
}


PyJC3FieldObject* PyJC3Field_New(JNIEnv *env, jobject c3field)
{
    PyJC3FieldObject *pyf;
    jstring          jstr        = NULL;

    if (PyType_Ready(&PyJC3Field_Type) < 0) {
        return NULL;
    }

    pyf              = PyObject_NEW(PyJC3FieldObject, &PyJC3Field_Type);
    pyf->c3field      = (*env)->NewGlobalRef(env, c3field);
    pyf->pyFieldName = NULL;
    pyf->fieldTypeId = -1;
    pyf->isConstant    = -1;
    pyf->init        = 0;

    // ------------------------------ get field name

    jstr = C3_JepInterface_getFieldName(env, c3field);
    if (process_java_exception(env) || !jstr) {
        goto EXIT_ERROR;
    }

    pyf->pyFieldName = jstring_As_PyString(env, jstr);

    (*env)->DeleteLocalRef(env, jstr);


    return pyf;

EXIT_ERROR:
    if (pyf) {
        pyjc3field_dealloc(pyf);
    }
    return NULL;
}

static int pyjc3field_init(JNIEnv *env, PyJC3FieldObject *self)
{
    jboolean         isConstant     = JNI_TRUE;

    if ((*env)->PushLocalFrame(env, JLOCAL_REFS) != 0) {
        process_java_exception(env);
        return 0;
    }

    // ------------------------------ get fieldid


    // ------------------------------ get return type
    //printf("pyjc3field init: %s\n", PyString_AsString(self->pyFieldName));
    //fflush(stdout);

    self->fieldType = C3_JepInterface_getType(env, self->c3field);
    if (process_java_exception(env) || !self->fieldType) {
        goto EXIT_ERROR;
    }
    //printf("pyjc3field init 2\n");
    //fflush(stdout);

    self->fieldTypeId = get_jtype(env, self->fieldType);
    if (process_java_exception(env)) {
        goto EXIT_ERROR;
    }
    //printf("pyjc3field init 3\n");
    //fflush(stdout);

    // ------------------------------ get isConstant

    if (process_java_exception(env)) {
        goto EXIT_ERROR;
    }


    //printf("pyjc3field init 4\n");
    //fflush(stdout);

    isConstant = C3_JepInterface_isFieldConstant(env, self->c3field);
    if (process_java_exception(env)) {
        goto EXIT_ERROR;
    }

    //printf("pyjc3field init 5\n");
    //fflush(stdout);

    if (isConstant == JNI_TRUE) {

        //printf("pyjc3field init static\n");
        //fflush(stdout);
        self->isConstant = 1;
    } else {
        self->isConstant = 0;
    }
    self->fieldType = (*env)->NewGlobalRef(env, self->fieldType);

    //printf("pyjc3field init 7\n");
    //fflush(stdout);
    (*env)->PopLocalFrame(env, NULL);
    self->init = 1;
    return 1;

EXIT_ERROR:
    (*env)->PopLocalFrame(env, NULL);

    if (!PyErr_Occurred()) {
        PyErr_SetString(PyExc_RuntimeError, "Unknown");
    }

    return 0;
}


int PyJC3Field_Check(PyObject *obj)
{
    if (PyObject_TypeCheck(obj, &PyJC3Field_Type)) {
        return 1;
    }
    return 0;
}


// get value from java object field.
// returns new reference.
PyObject* pyjc3field_get(PyJC3FieldObject *self, PyJC3Object* pyjobject)
{

    //NOTE: THE CURRENT IMPLEMENTATION OF ACCESSING CONSTANT FIELDS WORKS WHEN USED ON AN INSTANCE OF A TYPE (e.g. my_dog.goodBoy), BUT
    // MAY NEED TO BE UPDATED DEPENDING ON HOW TYPES/C3 VARIABLE IS HANDLED IN EMBEDDED MODE (i.e. c3.Dog.goodBoy or c3.DogBreed.HUSKY)

    // It may end up being easier to pass the parameter object to java and determine whether it is a type or instance there.


    PyObject *result = NULL;
    JNIEnv   *env;

    env = pyembed_get_env();
    //printf("pyjc3field get 1\n");
    //fflush(stdout);
    if (!self) {
    //printf("pyjc3field get no self\n");
    //fflush(stdout);
        PyErr_Format(PyExc_RuntimeError, "Invalid self object.");
        return NULL;
    }

    if (!self->init) {

        if (!pyjc3field_init(env, self) || PyErr_Occurred()) {
    //printf("pyjc3field get failed init\n");
    //fflush(stdout);
            return NULL;
        }
    }

    if (!pyjobject->object && !self->isConstant) {
    //printf("pyjc3field get not static\n");
    //fflush(stdout);
        PyErr_SetString(PyExc_TypeError, "Field is not constant.");
        return NULL;
    }


    //printf("pyjc3field get fieldTypeId %d\n", self->fieldTypeId);
    //fflush(stdout);

    switch (self->fieldTypeId) {

    case JSTRING_ID: {
        jstring     jstr;

        if (self->isConstant) {

            //printf("pyjc3field get static string field %d\n", self->fieldTypeId);
            //fflush(stdout);

            jstr = C3_JepInterface_getConstantFieldValueString(env,
                                                               pyjobject->typeName,
                                                               PyObject_As_jstring(env, self->pyFieldName));
        } else {
            //printf("pyjc3field get non-static string field %d\n", self->fieldTypeId);
            //fflush(stdout);
            jstr = (jstring) C3_JepInterface_getFieldValueString(env,
                                                    pyjobject->object,
                                                    PyObject_As_jstring(env, self->pyFieldName));
        }
        if (process_java_exception(env)) {

    //printf("pyjc3field get java exception\n");
    //fflush(stdout);
            return NULL;
        }

        if (jstr == NULL) {

    //printf("pyjc3field get string is null %d\n", self->fieldTypeId);
    //fflush(stdout);
            Py_RETURN_NONE;
        }

        result = jstring_As_PyString(env, jstr);
        (*env)->DeleteLocalRef(env, jstr);
        break;
    }

    case JCLASS_ID: {
        jobject obj;

        if (self->isConstant)
            obj = C3_JepInterface_getConstantFieldValueClass(env,
                                                               pyjobject->typeName,
                                                               PyObject_As_jstring(env, self->pyFieldName));
        else
            obj = C3_JepInterface_getFieldValueClass(env,
                                                      pyjobject->object,
                                                      PyObject_As_jstring(env, self->pyFieldName));

        if (process_java_exception(env)) {
            return NULL;
        }

        if (obj == NULL) {
            Py_RETURN_NONE;
        }

        result = PyJClass_Wrap(env, obj);
        (*env)->DeleteLocalRef(env, obj);
        break;
    }

    case JOBJECT_ID: {
        jobject obj;

        if (self->isConstant)
            obj = C3_JepInterface_getConstantFieldValueObject(env,
                                                               pyjobject->typeName,
                                                               PyObject_As_jstring(env, self->pyFieldName));
        else
            obj = C3_JepInterface_getFieldValueObject(env,
                                                              pyjobject->object,
                                                              PyObject_As_jstring(env, self->pyFieldName));

        if (process_java_exception(env)) {
            return NULL;
        }

        if (obj == NULL) {
            Py_RETURN_NONE;
        }

        result = jobject_As_PyObject(env, obj);
        (*env)->DeleteLocalRef(env, obj);
        break;
    }

    case JARRAY_ID: {
        PyErr_Format(PyExc_RuntimeError,
                             "TODO: C3 ARRAY CURRENTLY UNSUPPORTED!!");
                Py_RETURN_NONE;
        jobject obj;

        if (self->isConstant)
            obj = C3_JepInterface_getConstantFieldValueArray(env,
                                                               pyjobject->typeName,
                                                               PyObject_As_jstring(env, self->pyFieldName));
        else
            obj = C3_JepInterface_getFieldValueArray(env,
                                                            pyjobject->object,
                                                            PyObject_As_jstring(env, self->pyFieldName));

        if (process_java_exception(env)) {
            return NULL;
        }

        if (obj == NULL) {
            Py_RETURN_NONE;
        }

        result = pyjarray_new(env, obj);
        (*env)->DeleteLocalRef(env, obj);
        break;
    }
    case JINT_ID: {
        jint ret;

        if (self->isConstant)
            ret = C3_JepInterface_getConstantFieldValueInt(env,
                                                               pyjobject->typeName,
                                                               PyObject_As_jstring(env, self->pyFieldName));
        else
            ret = C3_JepInterface_getFieldValueInt(env,
                                                          pyjobject->object,
                                                          PyObject_As_jstring(env, self->pyFieldName));

        if (process_java_exception(env)) {
            return NULL;
        }

        result = jint_As_PyObject(ret);
        break;
    }

    case JBYTE_ID: {
        jbyte ret;

        if (self->isConstant)
            ret = C3_JepInterface_getConstantFieldValueByte(env,
                                                               pyjobject->typeName,
                                                               PyObject_As_jstring(env, self->pyFieldName));
        else
            ret = C3_JepInterface_getFieldValueByte(env,
                                                            pyjobject->object,
                                                            PyObject_As_jstring(env, self->pyFieldName));

        if (process_java_exception(env)) {
            return NULL;
        }

        result = jbyte_As_PyObject(ret);
        break;
    }

//    case JCHAR_ID: {
//        jchar ret;
//
//        if (self->isConstant)
//            ret = (*env)->GetStaticCharField(env,
//                                             pyjobject->clazz,
//                                             self->fieldId);
//        else
//            ret = C3_JepInterface_getFieldValueChar(env,
//                                                          pyjobject->object,
//                                                          PyObject_As_jstring(env, self->pyFieldName));
//
//        if (process_java_exception(env)) {
//            return NULL;
//        }
//        result = jchar_As_PyObject(ret);
//        break;
//    }

//    case JSHORT_ID: {
//        jshort ret;
//
//        if (self->isConstant)
//            ret = (*env)->GetStaticShortField(env,
//                                              pyjobject->clazz,
//                                              self->fieldId);
//        else
//            ret = (*env)->GetShortField(env,
//                                        pyjobject->object,
//                                        self->fieldId);
//
//        if (process_java_exception(env)) {
//            return NULL;
//        }
//
//        result = jshort_As_PyObject(ret);
//        break;
//    }

    case JDOUBLE_ID: {
        jdouble ret;

        if (self->isConstant)
            ret = C3_JepInterface_getConstantFieldValueDouble(env,
                                                               pyjobject->typeName,
                                                               PyObject_As_jstring(env, self->pyFieldName));
        else
            ret = C3_JepInterface_getFieldValueDouble(env,
                                                              pyjobject->object,
                                                              PyObject_As_jstring(env, self->pyFieldName));

        if (process_java_exception(env)) {
            return NULL;
        }

        result = jdouble_As_PyObject(ret);
        break;
    }

    case JFLOAT_ID: {
        jfloat ret;

        if (self->isConstant)
            ret = C3_JepInterface_getConstantFieldValueFloat(env,
                                                               pyjobject->typeName,
                                                               PyObject_As_jstring(env, self->pyFieldName));
        else
            ret = C3_JepInterface_getFieldValueFloat(env,
                                                            pyjobject->object,
                                                            PyObject_As_jstring(env, self->pyFieldName));

        if (process_java_exception(env)) {
            return NULL;
        }

        result = jfloat_As_PyObject(ret);
        break;
    }

    case JLONG_ID: {
        jlong ret;

        if (self->isConstant)
            ret = C3_JepInterface_getConstantFieldValueLong(env,
                                                               pyjobject->typeName,
                                                               PyObject_As_jstring(env, self->pyFieldName));
        else
            ret = C3_JepInterface_getFieldValueLong(env,
                                                            pyjobject->object,
                                                            PyObject_As_jstring(env, self->pyFieldName));

        if (process_java_exception(env)) {
            return NULL;
        }

        result = jlong_As_PyObject(ret);
        break;
    }


    case JBOOLEAN_ID: {
        jboolean ret;

        if (self->isConstant) {
            //printf("pyjc3field get constant boolean field %d\n", self->fieldTypeId);
            //fflush(stdout);
            ret = C3_JepInterface_getConstantFieldValueBoolean(env,
                                                              pyjobject->typeName,
                                                               PyObject_As_jstring(env, self->pyFieldName));
        } else {
            //printf("pyjc3field get non-constant boolean field %d\n", self->fieldTypeId);
            //fflush(stdout);
            ret = C3_JepInterface_getFieldValueBoolean(env,
                                                       pyjobject->object,
                                                       PyObject_As_jstring(env, self->pyFieldName));
        }
        if (process_java_exception(env)) {
            return NULL;
        }

        result = jboolean_As_PyObject(ret);
        break;
    }

    default:
        PyErr_Format(PyExc_RuntimeError,
                     "Unknown field type %i.",
                     self->fieldTypeId);
        Py_RETURN_NONE;
    }

    return result;
}

int pyjc3field_set(PyJC3FieldObject *self, PyJC3Object* pyjobject, PyObject *value)
{
    if (!self) {
        PyErr_Format(PyExc_RuntimeError, "C3 Objs are immutable, so setting fields is not supported.");
        return -1;
    }
}

PyTypeObject PyJC3Field_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "jep.PyJC3Field",
    sizeof(PyJC3FieldObject),
    0,
    (destructor) pyjc3field_dealloc,            /* tp_dealloc */
    0,                                        /* tp_print */
    0,                                        /* tp_getattr */
    0,                                        /* tp_setattr */
    0,                                        /* tp_compare */
    0,                                        /* tp_repr */
    0,                                        /* tp_as_number */
    0,                                        /* tp_as_sequence */
    0,                                        /* tp_as_mapping */
    0,                                        /* tp_hash  */
    0,                                        /* tp_call */
    0,                                        /* tp_str */
    0,                                        /* tp_getattro */
    0,                                        /* tp_setattro */
    0,                                        /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,                       /* tp_flags */
    "jfield",                                 /* tp_doc */
    0,                                        /* tp_traverse */
    0,                                        /* tp_clear */
    0,                                        /* tp_richcompare */
    0,                                        /* tp_weaklistoffset */
    0,                                        /* tp_iter */
    0,                                        /* tp_iternext */
    0,                                        /* tp_methods */
    0,                                        /* tp_members */
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
