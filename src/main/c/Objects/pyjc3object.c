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

/* Set the object attributes from the cache */
static int pyjc3object_init(JNIEnv *env, PyJC3Object *pyjob)
{

    jstring className     = NULL;
    jstring typeName      = NULL;
    PyObject *pyClassName = NULL;
    JepThread *jepThread  = NULL;
    PyObject *cachedAttrs = NULL;

    if ((*env)->PushLocalFrame(env, JLOCAL_REFS) != 0) {
        process_java_exception(env);
        return 0;
    }

    /*
     * Attach the attribute java_name to the PyJC3Object instance to assist
     * developers with understanding the type at runtime.
     */
    className = java_lang_Class_getName(env, pyjob->clazz);
    if (process_java_exception(env) || !className) {
        goto EXIT_ERROR;
    }
    pyjob->javaClassName = pyClassName;

    typeName = C3_JepInterface_getTypeName(env, pyjob->object);
        if (process_java_exception(env) || !typeName) {
            goto EXIT_ERROR;
        }

    pyClassName = jstring_As_PyString(env, className);
    pyjob->typeName = (*env)->NewGlobalRef(env, typeName);
    (*env)->DeleteLocalRef(env, typeName);

    /*
     * Get methods for the PyJC3Object, optimized for performance.  The code
     * below is very similar to previous versions except methods are now
     * cached in memory.
     *
     * Previously every time you instantiate a PyJC3Object, Jep would get the
     * complete list of methods through reflection, turn them into PyJC3Methods,
     * and add them as attributes to the PyJC3Object.
     *
     * Now Jep retains a Python dictionary in memory with a key of the fully
     * qualified Java classname to a list of PyJC3Methods and PyJC3MultiMethods.
     * Since the Java methods will never change at runtime for a particular
     * Class, this is safe and drastically speeds up PyJC3Object instantiation
     * by reducing reflection calls. We continue to set and reuse the
     * PyJC3Methods and PyJC3MultiMethods attributes on the PyJC3Object instance,
     * but if pyjc3object_getattro sees a PyJC3Method or PyJC3MultiMethod, it will
     * put it inside a PyMethod and return that, enabling the reuse of the
     * PyJC3Method or PyJC3MultiMethod for this particular object instance.
     *
     * We have the GIL at this point, so we can safely assume we're
     * synchronized and multiple threads will not alter the dictionary at the
     * same time.
     */
    jepThread = pyembed_get_jepthread();
    if (jepThread == NULL) {
        goto EXIT_ERROR;
    }
    if (jepThread->fqnToPyJAttrs == NULL) {
        jepThread->fqnToPyJAttrs = PyDict_New();
    }

    cachedAttrs = PyDict_GetItem(jepThread->fqnToPyJAttrs, pyClassName);
    if (cachedAttrs == NULL) {
        int i, len = 0;
        jobjectArray methodArray = NULL;
        jobjectArray fieldArray  = NULL;

        cachedAttrs = PyDict_New();

        methodArray = C3_JepInterface_getMethods(env, pyjob->object);
        if (process_java_exception(env) || !methodArray) {
            goto EXIT_ERROR;
        }

        /*
         * For each method, create a new PyJC3Method object and either add it to
         * the cached methods list or a PyJC3MultiMethod.
         */
        len = (*env)->GetArrayLength(env, methodArray);
        for (i = 0; i < len; i++) {
            PyJC3MethodObject *pymethod = NULL;
            // jobject rmethod = NULL;
            jobject c3method = NULL;
            c3method = (*env)->GetObjectArrayElement(env, methodArray, i);
            // pymethod = PyJC3Method_New(env, rmethod);
            pymethod = PyJC3Method_New(env, c3method, pyjob->typeName);
            if (!pymethod) {
                continue;
            }

            /*
             * For every method of this name, check to see if a PyJC3Method or
             * PyJC3MultiMethod is already in the cache with the same name. If
             * so, turn it into a PyJC3MultiMethod or add it to the existing
             * PyJC3MultiMethod.
             */
            if (pymethod->pyMethodName && PyString_Check(pymethod->pyMethodName)) {
                PyObject* cached = PyDict_GetItem(cachedAttrs, pymethod->pyMethodName);
                if (cached == NULL) {
                    if (PyDict_SetItem(cachedAttrs, pymethod->pyMethodName,
                                       (PyObject*) pymethod) != 0) {
                        goto EXIT_ERROR;
                    }
                } else if (PyJC3Method_Check(cached)) {
                    PyObject* multimethod = PyJC3MultiMethod_New((PyObject*) pymethod, cached);
                    PyDict_SetItem(cachedAttrs, pymethod->pyMethodName, multimethod);
                    Py_DECREF(multimethod);
                } else if (PyJC3MultiMethod_Check(cached)) {
                    PyJC3MultiMethod_Append(cached, (PyObject*) pymethod);
                }
            }

            Py_DECREF(pymethod);
            (*env)->DeleteLocalRef(env, c3method);
        } // end of looping over available methods

        // TODO C3: Do we want to use fields or only allow accessor methods? For performance reasons we may want to
        // switch to fields. If not, we certainly need to update the methods returned from getMethods to include
        // the modifiers like `withName`

        //  process fields
        // fieldArray = java_lang_Class_getFields(env, pyjob->clazz);
        //printf("About to get fields\n");
        //fflush(stdout);
        fieldArray = C3_JepInterface_getFields(env, pyjob->object);
        if (process_java_exception(env) || !fieldArray) {
            //printf("getFields java error\n");
            //fflush(stdout);
            goto EXIT_ERROR;
        }

        // for each field, create a pyjc3field object and
        // add to the internal members list.
        len = (*env)->GetArrayLength(env, fieldArray);
        for (i = 0; i < len; i++) {
            //jobject          rfield   = NULL;
            jobject          c3field   = NULL;
            PyJC3FieldObject *pyjfield = NULL;

            //rfield = (*env)->GetObjectArrayElement(env, fieldArray, i);
            c3field = (*env)->GetObjectArrayElement(env, fieldArray, i);

            // pyjfield = PyJField_New(env, rfield);
            pyjfield = PyJC3Field_New(env, c3field);
            if (!pyjfield) {
                continue;
            }
            //printf("setting field: %s\n", PyString_AsString(pyjfield->pyFieldName));
            //fflush(stdout);

            if (pyjfield->pyFieldName && PyString_Check(pyjfield->pyFieldName)) {
                if (PyDict_SetItem(cachedAttrs, pyjfield->pyFieldName,
                                   (PyObject*) pyjfield) != 0) {
                    goto EXIT_ERROR;
                }
            }

            Py_DECREF(pyjfield);
            (*env)->DeleteLocalRef(env, c3field);
        }
        (*env)->DeleteLocalRef(env, fieldArray);

        PyDict_SetItem(jepThread->fqnToPyJAttrs, pyClassName, cachedAttrs);
        Py_DECREF(cachedAttrs); // fqnToPyJAttrs will hold the reference
    } // end of setting up cache for this Java Class

    if (pyjob->object) {
        Py_INCREF(cachedAttrs);
        pyjob->attr = cachedAttrs;
    } else {
        /* PyJC3Type may add additional attributes so use a copy */
        pyjob->attr = PyDict_Copy(cachedAttrs);
    }

    (*env)->PopLocalFrame(env, NULL);
    return 1;


EXIT_ERROR:
    (*env)->PopLocalFrame(env, NULL);
    return 0;
}


PyObject* PyJC3Object_New(JNIEnv *env, PyTypeObject* type, jobject obj,
                        jclass class)
{
    PyJC3Object *pyjob = PyObject_NEW(PyJC3Object, type);

    if (obj) {
        pyjob->object = (*env)->NewGlobalRef(env, obj);
    } else {
        /* THis should only happen for pyjc3type*/
        pyjob->object = NULL;
    }
    if (class) {
        pyjob->clazz = (*env)->NewGlobalRef(env, class);
    } else {
        class = (*env)->GetObjectClass(env, obj);
        pyjob->clazz = (*env)->NewGlobalRef(env, class);
        (*env)->DeleteLocalRef(env, class);
        class = NULL;
    }

    if (pyjc3object_init(env, pyjob)) {
        return (PyObject*) pyjob;
    }
    Py_DECREF((PyObject*) pyjob);
    return NULL;
}

static void pyjc3object_dealloc(PyJC3Object *self)
{
#if USE_DEALLOC
    JNIEnv *env = pyembed_get_env();
    if (env) {
        if (self->object) {
            (*env)->DeleteGlobalRef(env, self->object);
        }
        if (self->clazz) {
            (*env)->DeleteGlobalRef(env, self->clazz);
        }
        if (self->typeName) {
            (*env)->DeleteGlobalRef(env, self->typeName);
        }
    }

    Py_CLEAR(self->attr);
    Py_CLEAR(self->javaClassName);

    PyObject_Del(self);
#endif
}

// call toString() on jobject. returns null on error.
// expected to return new reference.
static PyObject* pyjc3object_str(PyJC3Object *self)
{
    PyObject   *pyres     = NULL;
    JNIEnv     *env;

    env   = pyembed_get_env();
    if (self->object) {
        pyres = jobject_As_PyString(env, self->object);
    } else {
        pyres = jobject_As_PyString(env, self->clazz);
    }

    return pyres;
}


static PyObject* pyjc3object_richcompare(PyJC3Object *self,
                                       PyObject *_other,
                                       int opid)
{
    JNIEnv *env;

    if (PyType_IsSubtype(Py_TYPE(_other), &PyJC3Object_Type)) {
        PyJC3Object *other = (PyJC3Object *) _other;
        jboolean eq;

        jobject target, other_target;

        target = self->object;
        other_target = other->object;

        // lack of object indicates it's a pyjc3type
        if (!target) {
            target = self->clazz;
        }
        if (!other_target) {
            other_target = other->clazz;
        }

        if (opid == Py_EQ && (self == other || target == other_target)) {
            Py_RETURN_TRUE;
        }

        env = pyembed_get_env();
        eq = JNI_FALSE;
        // skip calling Object.equals() if op is > or <
        if (opid != Py_GT && opid != Py_LT) {
            eq = java_lang_Object_equals(env, target, other_target);
        }

        if (process_java_exception(env)) {
            return NULL;
        }

        if (((eq == JNI_TRUE) && (opid == Py_EQ || opid == Py_LE || opid == Py_GE)) ||
                (eq == JNI_FALSE && opid == Py_NE)) {
            Py_RETURN_TRUE;
        } else if (opid == Py_EQ || opid == Py_NE) {
            Py_RETURN_FALSE;
        } else {
            /*
             * All Java objects have equals, but we must rely on Comparable for
             * the more advanced operators.  Java generics cannot actually
             * enforce the type of other in self.compareTo(other) at runtime,
             * but for simplicity let's assume if they got it to compile, the
             * two types can be compared. If the types aren't comparable to
             * one another, a ClassCastException will be thrown.
             *
             * In Python 2 we will allow the ClassCastException to halt the
             * comparison, because it will most likely return
             * NotImplemented in both directions and Python 2 will devolve to
             * comparing the pointer address.
             *
             * In Python 3 we will catch the ClassCastException and return
             * NotImplemented, because there's a chance the reverse comparison
             * of other.compareTo(self) will work.  If both directions return
             * NotImplemented (due to ClassCastException), Python 3 will
             * raise a TypeError.
             */
            jint result;
#if PY_MAJOR_VERSION >= 3
            jthrowable exc;
#endif

            if (!(*env)->IsInstanceOf(env, self->object, JCOMPARABLE_TYPE)) {
                const char* jname = PyString_AsString(self->javaClassName);
                PyErr_Format(PyExc_TypeError, "Invalid comparison operation for Java type %s",
                             jname);
                return NULL;
            }

            result = java_lang_Comparable_compareTo(env, target, other_target);
#if PY_MAJOR_VERSION >= 3
            exc = (*env)->ExceptionOccurred(env);
            if (exc != NULL) {
                if ((*env)->IsInstanceOf(env, exc, CLASSCAST_EXC_TYPE)) {
                    /*
                     * To properly meet the richcompare docs we detect
                     * ClassException and return NotImplemented, enabling
                     * Python to try the reverse operation of
                     * other.compareTo(self).  Unfortunately this only safely
                     * works in Python 3.
                     */
                    (*env)->ExceptionClear(env);
                    Py_INCREF(Py_NotImplemented);
                    return Py_NotImplemented;
                }
            }
#endif
            if (process_java_exception(env)) {
                return NULL;
            }

            if ((result == -1 && opid == Py_LT) || (result == -1 && opid == Py_LE) ||
                    (result == 1 && opid == Py_GT) || (result == 1 && opid == Py_GE)) {
                Py_RETURN_TRUE;
            } else {
                Py_RETURN_FALSE;
            }
        }
    }

    /*
     * Reaching this point means we are comparing a Java object to a Python
     * object.  You might think that's not allowed, but the python doc on
     * richcompare indicates that when encountering NotImplemented, allow the
     * reverse comparison in the hopes that that's implemented.  This works
     * surprisingly well because it enables Python comparison operations on
     * things such as pyjc3object != Py_None or
     * assertSequenceEqual(pyjlist, pylist) where each list has the same
     * contents.  This saves us from having to worry about if the Java object
     * is on the left side or the right side of the operator.
     *
     * In short, this is intentional to keep comparisons working well.
     */
    Py_INCREF(Py_NotImplemented);
    return Py_NotImplemented;
}


// get attribute 'name' for object.
// uses obj->attr dict for storage.
// returns new reference.
static PyObject* pyjc3object_getattro(PyObject *obj, PyObject *name)
{
    //printf("getattro\n");
    //fflush(stdout);
    //printf("%s\n", PyString_AsString(name));
    //fflush(stdout);

    PyObject *ret = PyObject_GenericGetAttr(obj, name);
    if (ret == NULL) {
        //printf("getattro: null\n");
        //fflush(stdout);
        return NULL;
    } else if (PyJC3Method_Check(ret) || PyJC3MultiMethod_Check(ret)) {

        //printf("getattro: method\n");
        //fflush(stdout);
        /*
         * TODO Should not bind non-static methods to pyjclass objects, but not
         * sure yet how to handle multimethods and static methods.
         */
#if PY_MAJOR_VERSION >= 3
        PyObject* wrapper = PyMethod_New(ret, (PyObject*) obj);
#else
        PyObject* wrapper = PyMethod_New(ret, (PyObject*) obj,
                                         (PyObject*) Py_TYPE(obj));
#endif
        Py_DECREF(ret);
        return wrapper;
    } else if (PyJC3Field_Check(ret)) {

        //printf("getattro: field %s\n", PyString_AsString(name));
        //fflush(stdout);
        // PyObject *resolved = pyjfield_get((PyJFieldObject *) ret, (PyJC3Object*) obj);
        PyObject *resolved = pyjc3field_get((PyJC3FieldObject *) ret, (PyJC3Object*) obj);
        Py_DECREF(ret);
        return resolved;
    } else {

        //printf("getattro: none %s\n", PyString_AsString(name));
        //fflush(stdout);
    }
    return ret;
}


// set attribute v for object.
// uses obj->attr dictionary for storage.
static int pyjc3object_setattro(PyJC3Object *obj, PyObject *name, PyObject *v)
{
    PyObject *cur = NULL;
    if (v == NULL) {
        PyErr_Format(PyExc_TypeError,
                     "Deleting attributes from PyJC3Objects is not allowed.");
        return -1;
    }

    cur = PyDict_GetItem(obj->attr, name);
    if (PyErr_Occurred()) {
        return -1;
    }

    if (cur == NULL) {
        PyErr_Format(PyExc_AttributeError, "'%s' object has no attribute '%s'.",
                     PyString_AsString(obj->javaClassName), PyString_AsString(name));
        return -1;
    }

    if (!PyJField_Check(cur)) {
        if (PyJC3Method_Check(cur) || PyJC3MultiMethod_Check(cur)) {
            PyErr_Format(PyExc_AttributeError, "'%s' object cannot assign to method '%s'.",
                         PyString_AsString(obj->javaClassName), PyString_AsString(name));
        } else {
            PyErr_Format(PyExc_AttributeError,
                         "'%s' object cannot assign to attribute '%s'.",
                         PyString_AsString(obj->javaClassName), PyString_AsString(name));
        }
        return -1;
    }
    //return pyjfield_set((PyJFieldObject *) cur, obj, v);
    return pyjc3field_set((PyJC3FieldObject *) cur, obj, v);
}

static Py_hash_t pyjc3object_hash(PyJC3Object *self)
{
    JNIEnv *env    = pyembed_get_env();
    Py_hash_t hash = -1;

    if (self->object) {
        hash = java_lang_Object_hashCode(env, self->object);
    } else {
        hash = java_lang_Object_hashCode(env, self->clazz);
    }
    if (process_java_exception(env)) {
        return -1;
    }

    /*
     * This seems odd but Python expects -1 for error occurred. Other Python
     * built-in types then return -2 if the actual hash is -1.
     */
    if (hash == -1) {
        hash = -2;
    }

    return hash;
}

/*
 * Creates a PyJMonitor that can emulate a Java synchronized(self) {...} block.
 */
static PyObject* pyjc3object_synchronized(PyObject* self, PyObject* args)
{
    PyObject   *monitor = NULL;
    PyJC3Object  *thisObj = (PyJC3Object*) self;

    if (thisObj->object) {
        // PyJC3Object
        monitor = PyJMonitor_New(thisObj->object);
    } else {
        // PyJC3Type
        monitor = PyJMonitor_New(thisObj->clazz);
    }

    return monitor;
}

static PyMethodDef pyjc3object_methods[] = {
    {
        "synchronized",
        pyjc3object_synchronized,
        METH_NOARGS,
        "synchronized that emulates Java's synchronized { obj } and returns a Python ContextManager"
    },

    { NULL, NULL }
};


static PyMemberDef pyjc3object_members[] = {
    {"__dict__", T_OBJECT, offsetof(PyJC3Object, attr), READONLY},
    {"java_name", T_OBJECT, offsetof(PyJC3Object, javaClassName), READONLY},
    {0}
};


PyTypeObject PyJC3Object_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "jep.PyJC3Object",                          /* tp_name */
    sizeof(PyJC3Object),                        /* tp_basicsize */
    0,                                        /* tp_itemsize */
    (destructor) pyjc3object_dealloc,           /* tp_dealloc */
    0,                                        /* tp_print */
    0,                                        /* tp_getattr */
    0,                                        /* tp_setattr */
    0,                                        /* tp_compare */
    0,                                        /* tp_repr */
    0,                                        /* tp_as_number */
    0,                                        /* tp_as_sequence */
    0,                                        /* tp_as_mapping */
    (hashfunc) pyjc3object_hash,                /* tp_hash  */
    0,                                        /* tp_call */
    (reprfunc) pyjc3object_str,                 /* tp_str */
    (getattrofunc) pyjc3object_getattro,        /* tp_getattro */
    (setattrofunc) pyjc3object_setattro,        /* tp_setattro */
    0,                                        /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT |
    Py_TPFLAGS_BASETYPE,                      /* tp_flags */
    "C3 Python Object",                       /* tp_doc */
    0,                                        /* tp_traverse */
    0,                                        /* tp_clear */
    (richcmpfunc) pyjc3object_richcompare,      /* tp_richcompare */
    0,                                        /* tp_weaklistoffset */
    0,                                        /* tp_iter */
    0,                                        /* tp_iternext */
    pyjc3object_methods,                        /* tp_methods */
    pyjc3object_members,                        /* tp_members */
    0,                                        /* tp_getset */
    0,                                        /* tp_base */
    0,                                        /* tp_dict */
    0,                                        /* tp_descr_get */
    0,                                        /* tp_descr_set */
    offsetof(PyJC3Object, attr),                /* tp_dictoffset */
    0,                                        /* tp_init */
    0,                                        /* tp_alloc */
    NULL,                                     /* tp_new */
};
