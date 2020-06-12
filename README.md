.. image:: https://img.shields.io/pypi/pyversions/Jep.svg
    :target: https://pypi.python.org/pypi/jep

.. image:: https://img.shields.io/pypi/l/Jep.svg
    :target: https://pypi.python.org/pypi/jep

.. image:: https://img.shields.io/pypi/v/Jep.svg
    :target: https://pypie.python.org/pypi/jep
	
.. image:: https://img.shields.io/badge/docs-wiki-orange.svg
    :target: https://github.com/ninia/jep/wiki

.. image:: https://img.shields.io/badge/docs-javadoc-orange.svg
    :target: https://ninia.github.io/jep/javadoc


## C3 Contributions
Here, I will document changes made to support the C3 Python SDK.

JEP wraps Java objects in `PyJObject`s objects. When a `PyJObject` is created, or when an attribute is accessed on a `PyJObject` object, Java reflection is used.

For C3, we will create a new `PyJC3Object` (and corresponding `PyJC3Class`) object which calls static functions on the C3 type `JepInterface` (in leu of Java reflection). Searching for `C3_JepInterface` will show you a list of the functions invoked on this type.

Below, I will list what files we change, and why we are changing them.

1. src/main/c/Include/Jep.h, src/main/c/Include/pyjarray.h, src/main/c/Include/pyjautocloseable.h, src/main/c/Include/pyjbuffer.h, src/main/c/Include/pyjiterable.h, src/main/c/Include/pyjiterator.h, src/main/c/Include/pyjmap.h, src/main/c/Include/pyjmultimethod.h, src/main/c/Include/pyjnumber.h: Truthfully, I am not sure if all of these files NEED to be updated. All of these files `#include`d either `PyJObject` or `PyJClass`  originally, so I chose to also include `PyJC3Object` and `PyJC3Class`. Note that some functions that were originally implemented on `PyJObject` and `PyJClass` have been moved to `PyJC3Object` or `PyJC3Class` (`PyJObject_Check` and `PyJClass_Check`), so it would make sense to now include these new `PyJC3` types in files that call these functions.
1. src/main/c/Jep/convert_j2p.c, src/main/c/Jep/convert_j2p.h: These files implement the logic to convert a Java object to a Python object. Within the implementation of `jobject_As_PyObject`, I have added the following logic: In the condition that the Java object is an `Object`, call to C3 server and check if it is a C3 object / C3 class. If so, create a `PyJC3Object` (or `PyJC3Class`), else, create a `PyJObject` (or `PyJClass`). Creating the `PyJC3Object`/`PyJC3Class` is implemented by `jobject_As_PyJC3Object` (which is called by `jobject_As_PyObject`).
1. src/main/c/Include/java_access/Class.h, src/main/c/Include/java_access/Class.c: This file originally implements functions to call Java.Lang.Class functions on Java objects from C. All functions that 1) Invoke reflection or 2) Have a Java.Lang.Reflection Object in the signature are replaced by new `C3_JepInterface_`... functions that call static methods on the C3 Type `JepInterface`.
1. src/main/c/Include/java_access/Field.h, src/main/c/Include/java_access/Field.c: This file originally implements functions to call Java.Lang.Reflect.Field functions on Java objects from C. All functions that 1) Invoke reflection or 2) Have a Java.Lang.Reflection Object in the signature are replaced by new `C3_JepInterface_`... functions that call static methods on the C3 Type `JepInterface`.
1. src/main/c/Include/java_access/Member.h, src/main/c/Include/java_access/Member.c: This file originally implements functions to call Java.Lang.Reflect.Member functions on Java objects from C. All functions that 1) Invoke reflection or 2) Have a Java.Lang.Reflection Object in the signature are replaced by new `C3_JepInterface_`... functions that call static methods on the C3 Type `JepInterface`. Note that I have added the function `C3_JepInterface_getId`. Assuming that we may not be able to implement `C3_JepInterface_getMethods` to return a list of reflection objects, we will not be able to do `self->fieldId = (*env)->FromReflectedField(env, self->rfield);`
to get `fieldId`. Thus, we will need to use this new function I introduced.
1. src/main/c/Objects/pyjmethod.h, src/main/c/Objects/pyjmethod.c: This is the biggest TODO; I missed java reflection calls in this file. We will need to make a new `PyJC3Method` type, and have `PyJC3Object`s/`PyJC3Class`s use these methods. `PyJC3Method` will use the functions I added to src/main/c/Include/java_access/Method.h. This refactor is driven by the fact that reflection is currently used in every method call. We could check that the method is a C3 method on every call, and conditionally not use reflection. This approach would be less performant than just making a `PyJC3Method` object that always uses C3 APIs (this way, we don't have to make a conditional check during every method invocation to decide whether to use reflection or not). I have left TODOs in this file
1. src/main/c/Include/java_access/Method.h, src/main/c/Include/java_access/Method.c: This file originally implements functions to call Java.Lang.Reflect.Method functions on Java objects from C. All functions that 1) Invoke reflection or 2) Have a Java.Lang.Reflection Object in the signature are replaced by new `C3_JepInterface_`... functions that call static methods on the C3 Type `JepInterface`.
1. src/main/c/Include/java_access/Modifier.h, src/main/c/Include/java_access/Modifier.c: This file originally implements functions to call Java.Lang.Reflect.Modifier functions on Java objects from C. All functions that 1) Invoke reflection or 2) Have a Java.Lang.Reflection Object in the signature are replaced by new `C3_JepInterface_`... functions that call static methods on the C3 Type `JepInterface`.
1. src/main/c/Include/jep_util.h: Introduce helper function `JNI_STATIC_METHOD` (similar to `JNI_METHOD`). This function calls a static JNI method, caching the method. This is useful as the functions we will invoke on the C3 type `JepInterface` are static. Also, `C3_JEPINTERFACE_TYPE` is added to the `CLASS_TABLE`, pointing to class `c3/zoo/py/JepInterface` (the c3 type). We use `C3_JEPINTERFACE_TYPE` to call functions on the C3 type `JepInterface`.
1. src/main/c/Include/pyjc3class.h, src/main/c/Include/pyjc3class.c: We introduce a new type `PyJC3Class`. src/main/c/Include/pyjc3class.h implements `PyJClass_Check`; this function now returns true if the `pyobj` arg is a `PyJClass` (original behavior) or a `PyJC3Class` (new behavior). We introduce `PyJC3Class` so that we can call C3 type system alternatives to java reflection calls when interacting with c3 java types from within JEP. An alternative implementation would be to only have `PyJClass` and conditionally check if the Java class is a C3 type to determine if Java reflection should be used. Ths alternative approach would be less performant, so it is not used.
1. src/main/c/Include/pyjc3object.h, src/main/c/Include/pyjc3object.c: All comments about `pyjc3class` vs `pyjclass` are symmetrical with `pyjc3object` vs `pyjobject`.
1. src/main/c/Include/pyjclass.h, src/main/c/Include/pyjobject.h: Import the corresponding `pyjc3` files which re-implement the aforementioned `_check` functions which were originally implemented in these files, but are now removed.
1. src/main/c/Include/pyjfield.h, src/main/c/Include/pyjfield.c: These objects are not very applicable since c3 java types don't typically have fields. Unlike `pyjmethod`s, `pyjfield`s don't seem to use java reflection on each call. In these files, we provide new implementations to create `pyjfield`s without reflection. These functions get called in `PyJC3Object` when objects are being created.
1. src/main/c/Jep/convert_p2j.c: The logic to create Java objects from Python objects live here. Here, I added some logic to use C3 type APIs (instead of Java reflection) to determine how to convert `callable` Python objects to Java.


Jep - Java Embedded Python
===========================

Jep embeds CPython in Java through JNI.

Some benefits of embedding CPython in a JVM:

* Using the native Python interpreter may be much faster than
  alternatives.

* Python is mature, well supported, and well documented.

* Access to high quality Python modules, both native CPython
  extensions and Python-based.

* Compilers and assorted Python tools are as mature as the language.

* Python is an interpreted language, enabling scripting of established
  Java code without requiring recompilation.

* Both Java and Python are cross platform, enabling deployment to 
  different operating systems.


Installation
------------
Simply run ``pip install jep`` or download the source and run ``python setup.py build install``.
Building and installing require the JDK, Python, and optionally numpy to be installed beforehand.

Dependencies
------------
* Python 2.7, 3.3, 3.4, 3.5, 3.6, 3.7, or 3.8
* Java >= 1.7
* NumPy >= 1.7 (optional)

Notable features
----------------
* Interactive Jep console much like Python's interactive console
* Supports multiple, simultaneous, mostly sandboxed sub-interpreters or shared interpreters
* Numpy support for Java primitive arrays

Help
----
* `Documentation <https://github.com/ninia/jep/wiki>`_
* `JavaDoc <https://ninia.github.io/jep/javadoc>`_
* `Mailing List <https://groups.google.com/d/forum/jep-project>`_
* `Known Issues <https://github.com/ninia/jep/issues>`_
* `Project Page <https://github.com/ninia/jep>`_

We welcome comments, contributions, bug reports, wiki documentation, etc.

*Jep Team*
