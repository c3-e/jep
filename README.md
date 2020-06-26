[![image](https://img.shields.io/pypi/pyversions/Jep.svg)](https://pypi.python.org/pypi/jep)
[![image](https://img.shields.io/pypi/l/Jep.svg)](https://pypi.python.org/pypi/jep)
[![image](https://img.shields.io/pypi/v/Jep.svg)](https://pypie.python.org/pypi/jep)
[![image](https://img.shields.io/badge/docs-wiki-orange.svg)](https://github.com/ninia/jep/wiki)
[![image](https://img.shields.io/badge/docs-javadoc-orange.svg)](https://ninia.github.io/jep/javadoc)

## Development setup for C3 Jep

Run `./c3-jep install` to install the local version of this repo into your `jep_dev` conda environment. This
will create the environment if it does not exist.

To run the c3server tests that exercise the `(C3)JepInterface` features, run `./c3-jep test`. 

If you want the version of `jep` currently installed in the `jep_dev` environment to be used for all embedded actions
in a locally running `v8` c3server, set the enviroment variable `JEP_DEV_MODE=True` in the terminal/IDE that will run
the c3 server.




## C3 Contributions

### Changes made to support the C3 Python SDK

JEP wraps Java objects in `PyJObject`s objects in the Python interpreter. When (in Python) a `PyJObject` is created, or when an attribute is accessed on a `PyJObject`, Java reflection is used to .

For C3, we will create a new `PyJC3Object` (and corresponding `PyJC3Class`) object which calls static functions on the C3 type `JepInterface`, avoiding the performance cost of Java reflection. Searching for `C3_JepInterface` will show you a list of the functions invoked on this type.

#### What files are being changed and why:

1. src/main/c/Include/Jep.h, src/main/c/Include/pyjarray.h, src/main/c/Include/pyjautocloseable.h, src/main/c/Include/pyjbuffer.h, src/main/c/Include/pyjiterable.h, src/main/c/Include/pyjiterator.h, src/main/c/Include/pyjmap.h, src/main/c/Include/pyjmultimethod.h, src/main/c/Include/pyjnumber.h: Unclear if all of these files NEED to be updated. All of these files `#include`d either `PyJObject` or `PyJClass`  originally, so I chose to also include `PyJC3Object` and `PyJC3Class`. Note that some functions that were originally implemented on `PyJObject` and `PyJClass` have been moved to `PyJC3Object` or `PyJC3Class` (`PyJObject_Check` and `PyJClass_Check`), so it would make sense to now include these new `PyJC3` types in files that call these functions.

1. src/main/c/Jep/convert_j2p.c, src/main/c/Jep/convert_j2p.h: These files implement the logic to convert a Java object to a Python object. Within the implementation of `jobject_As_PyObject`, I have added the following logic: If the Java object is an `Object`, call to C3 server and check if it is a C3 object / C3 class. If so, create a `PyJC3Object` (or `PyJC3Class`). Otherwise, create a `PyJObject` (or `PyJClass`). Creating the `PyJC3Object`/`PyJC3Class` is implemented by `jobject_As_PyJC3Object` (which is called by `jobject_As_PyObject`).

1. src/main/c/Include/java_access/Class.h, src/main/c/Include/java_access/Class.c: This file originally implements functions to call Java.Lang.Class functions on Java objects from C. All functions that 1) use reflection or 2) have a Java.Lang.Reflection Object in the signature are replaced by new `C3_JepInterface_`... functions that call static methods on the C3 Type `JepInterface`.

1. src/main/c/Include/java_access/Field.h, src/main/c/Include/java_access/Field.c: This file originally implements functions to call Java.Lang.Reflect.Field functions on Java objects from C. All functions that 1) use reflection or 2) Have a Java.Lang.Reflection Object in the signature are replaced by new `C3_JepInterface_`... functions that call static methods on the C3 Type `JepInterface`.

1. src/main/c/Include/java_access/Member.h, src/main/c/Include/java_access/Member.c: This file originally implements functions to call Java.Lang.Reflect.Member functions on Java objects from C. All functions that 1) use reflection or 2) Have a Java.Lang.Reflection Object in the signature are replaced by new `C3_JepInterface_`... functions that call static methods on the C3 Type `JepInterface`.

1. src/main/c/Include/java_access/Constructor.h, src/main/c/Include/java_access/Constructor.c: This file originally implements functions to call Java.Lang.Reflect.Constructor functions on Java objects from C. All functions that 1) use reflection or 2) Have a Java.Lang.Reflection Object in the signature are replaced by new `C3_JepInterface_`... functions that call static methods on the C3 Type `JepInterface` to get `fieldId`.

1. src/main/c/Include/java_access/Method.h, src/main/c/Include/java_access/Method.c: This file originally implements functions to call Java.Lang.Reflect.Method functions on Java objects from C. All functions that 1) use reflection or 2) Have a Java.Lang.Reflection Object in the signature are replaced by new `C3_JepInterface_`... functions that call static methods on the C3 Type `JepInterface`.

1. src/main/c/Include/java_access/Modifier.h, src/main/c/Include/java_access/Modifier.c: This file originally implements functions to call Java.Lang.Reflect.Modifier functions on Java objects from C. All functions that 1) use reflection or 2) Have a Java.Lang.Reflection Object in the signature are replaced by new `C3_JepInterface_`... functions that call static methods on the C3 Type `JepInterface`.

1. src/main/c/Include/jep_util.h: Introduce helper function `JNI_STATIC_METHOD` (similar to `JNI_METHOD`). This function calls a static JNI method, caching the method. This is useful as the functions we will invoke on the C3 type `JepInterface` are static. Also, `C3_JEPINTERFACE_TYPE` is added to the `CLASS_TABLE`, pointing to class `c3/zoo/py/JepInterface` (the c3 type). We use `C3_JEPINTERFACE_TYPE` to call functions on the C3 type `JepInterface`.

1. src/main/c/Include/pyjc3class.h, src/main/c/Include/pyjc3class.c: We introduce a new type `PyJC3Class`. src/main/c/Include/pyjc3class.h implements `PyJClass_Check`; this function now returns true if the `pyobj` arg is a `PyJC3Class` (new behavior) or a `PyJClass` (original behavior). We introduce `PyJC3Class` so that we can directly call `C3` methods without using Java reflection calls when interacting with C3 Types from within JEP. An alternative implementation would be to only have `PyJClass` and conditionally check if the Java class is a C3 type to determine whether Java reflection should be used. This alternative approach would likely be less performant, since it would incur a check on every access or method call, so it is not used.

1. src/main/c/Include/pyjc3object.h, src/main/c/Include/pyjc3object.c: similar to `pyjc3class`

1. src/main/c/Include/pyjc3constructor.h, src/main/c/Include/pyjc3constructor.c: similar to `pyjc3class`

1. src/main/c/Include/pyjc3method.h, src/main/c/Include/pyjc3method.c: similar to `pyjc3class`

1. src/main/c/Include/pyjc3multimethod.h, src/main/c/Include/pyjc3multimethod.c: similar to `pyjc3class`

1. src/main/c/Include/pyjfield.h, src/main/c/Include/pyjfield.c: These objects are not very applicable since c3 java types don't typically have fields. Unlike `pyjmethod`s, `pyjfield`s don't seem to use java reflection on each call. In these files, we provide new implementations to create `pyjfield`s without reflection. These functions get called in `PyJC3Object` when objects are being created.

1. src/main/c/Jep/convert_p2j.c: The logic to create Java objects from Python objects lives here. Added some logic to use C3 type APIs (instead of Java reflection) to determine how to convert `callable` Python objects to Java.

1. src/main/c/Jep/jep_util.c: Updated to check for `PyJC3Class` and `PyJC3Object` along with the original PyJClass or PyJObject.


## C3 TODOs

Search "TODO C3" to see a list of TODOs for C3

#### Not Needed for PLAT-25012
* TODO C3 AVOID REFLECTION: When you call `getValue` in java, I believe `convert_p2j`s `pyobject_2_jobject` function is called. This function has been refactored to not reflect on C3. The same is not true when calling `invoke` on a JEP interpreter instance in java; we should fix this.
    * Note from Isaiah: this may not be necessary since we do not currently use `interpreter.invoke` in `TurboPy.java`
* TODO C3: static fields -- do we use/need these? If so, we simply need to add per-ValueType accessors.
* TODO C3: pyjc3field.set -- this is currently not handled properly
* TODO C3 (maybe): change handling of C3 collections


&nbsp;

&nbsp;

&nbsp;

&nbsp;

# Jep - Java Embedded Python

Jep embeds CPython in Java through JNI.

Some benefits of embedding CPython in a JVM:

  - Using the native Python interpreter may be much faster than
    alternatives.
  - Python is mature, well supported, and well documented.
  - Access to high quality Python modules, both native CPython
    extensions and Python-based.
  - Compilers and assorted Python tools are as mature as the language.
  - Python is an interpreted language, enabling scripting of established
    Java code without requiring recompilation.
  - Both Java and Python are cross platform, enabling deployment to
    different operating systems.

## Installation

Simply run `pip install jep` or download the source and run `python
setup.py build install`. Building and installing require the JDK,
Python, and optionally numpy to be installed beforehand.

## Dependencies

  - Python 2.7, 3.3, 3.4, 3.5, 3.6, 3.7, or 3.8
  - Java \>= 1.7
  - NumPy \>= 1.7 (optional)

## Notable features

  - Interactive Jep console much like Python's interactive console
  - Supports multiple, simultaneous, mostly sandboxed sub-interpreters
    or shared interpreters
  - Numpy support for Java primitive arrays

## Help

  - [Documentation](https://github.com/ninia/jep/wiki)
  - [JavaDoc](https://ninia.github.io/jep/javadoc)
  - [Mailing List](https://groups.google.com/d/forum/jep-project)
  - [Known Issues](https://github.com/ninia/jep/issues)
  - [Project Page](https://github.com/ninia/jep)

We welcome comments, contributions, bug reports, wiki documentation,
etc.

*Jep Team*
