# Cross-platform C++ BaseClass and type system

by Qingfeng Xia

It is extracted from FreeCAD project, it has the same license as FreeCAD: LGPL v2.1

This piece of code extraction personal work is NOT sponsored by Qingfeng Xia's employment.



Features:

+ Base class for C++
+ Type system:  extracted from FreeCAD's Base module <>
+ Collection of some header only libraries
+ Design pattern


Todo:
- shared_ptr<> replace all void*
- python wrapping helper
- cross-platform, OS, compiler `compatible.h`
- helper methods into BaseClass

https://atomheartother.github.io/c++/2018/07/12/CPPDynLib.html



## BaseClass

### Java and C# base class
C++ does not have a base/root class for all objects, but lot of other high level languages have.
see 

For a few C++ framework like QT, VTK, GTK, there is base class to provide shared functions
see: 
[QT: `QObject`](https://doc.qt.io/qt-5/qobject.html)
[VTK: `vtkObjectBase` and `vtkObject`](https://vtk.org/doc/nightly/html/classvtkObjectBase.html)


### Typical functions of base class

1. type system, implemented by c++ macro
2. reference counting, C++11 shared_pointer<> has this function
3. event/observer/subscription pattern, depends on the design of the framework
4. serialization,`std::to_string`

### help on script wrapping




## Type system 
### Type system for C++

C++ does not support runtime reflection to get class name, create instance from name (possible by factory pattern).

It does not relies on dynamic type information.
It does not require C++11 compiler.

Benefits: 
+ create instance from string name
+ get printable class name
+ inheritance tree

Qt's type or meta data system is more powerful, while if you need such a powerful system, just use QT. 

OpenCASCADE, also have the macro to enable type system.

```cpp
#include <Standard_Type.hxx>

IMPLEMENT_STANDARD_RTTIEXT(ShapeUpgrade_Tool,Standard_Transient)
```



###  top up over FreeCAD's implementation

1. error string, when forget to init/register the class
2. it is thread-unsafe during type init, but it should be  thread-safe as no modification to the type information.
3. template class are supported by a new macro `TYPE_SOURCE_TEMPLATE`
4. example code <./TypeTest.cpp>
5. types can be registered by `class::init()` and `Type::destruct()` and `init()` again

### usage

1. header file
In each class's header file (inc. header only class), `TYPESYSTEM_HEADER();` must be the first line of that class
Just like `Q_CLASS` for Qt meta system.

```
class CClass : public Base::BaseClass
{
    TYPESYSTEM_HEADER();

public:
    int d = 0;
};
```

2. source file
In very beginnning of the source file for that class, not within class scope. Or any other cpp file for header only class.
`TYPESYSTEM_SOURCE(CClass, Base::BaseClass);`
header only is not supported for static member data declaration. 

3. main source file
To use this type system: in `main()` or module initialization function (called in `main()`)
```
int main()
{
    using namespace Base;

    Type::init(); // init the type system
    // then init each class (actually register this class type), including the BaseClass
    BaseClass::init();  // this root class must be initialized

    // user classes init, can be wrap in a module init()
    CClass::init();



    Type::destruct();
    return 0;
}
```

see the [TypeTest source](TypeTest.cpp)


## Design pattern

+ Design Patterns in C++ with Real Examples
<https://github.com/ehsangazar/design-patterns-cpp>

+ 
<https://github.com/JakubVojvoda/design-patterns-cpp>

### included design patterns

+ AbstractFactory



## Collection of some header only libraries

+ toml11: header only lib: https://github.com/ToruNiina/toml11

 https://github.com/skystrife/cpptoml

+ python style C++17 argparse: https://github.com/p-ranav/argparse

+ json: https://nlohmann.github.io/json/

see more header-only open source libraries at :https://awesomeopensource.com/projects/header-only



## Python interface support
https://github.com/qingfengxia/python_wrap
### translate from CXX to Pybind, 

pybind11: defined objects
handle, object, bool_, int_, float_, str, bytes, tuple, list, dict, slice, none, capsule, iterable, iterator, function, buffer, array

diff API,  Py::Dict   setkey() 
CXX2pybind11_Map 

```cpp
//#include <CXX/Objects.hxx> 

#include <pybind11/pybind11.h>
using py=pybind11;
```


Exception, the translaton is not necessary, it is easy to to in pybind11



```Py_Return``` macro  in `Type.cpp`  it is actually macro defiend in `PyObjectBase.h`

`return Py_INCREF(Py_None), Py_None`

```Interpretor().importModule()```



```cpp
void Type::importModule(const char* TypeName)
{
  // cut out the module name
  string Mod = getModuleName(TypeName);
  // ignore base modules
  if (Mod != "App" && Mod != "Gui" && Mod != "Base") {
    // remember already loaded modules
    set<string>::const_iterator pos = loadModuleSet.find(Mod);
    if (pos == loadModuleSet.end()) {
      //Interpreter().loadModule(Mod.c_str());
#ifdef FC_LOGLOADMODULE
      Console().Log("Act: Module %s loaded through class %s \n",Mod.c_str(),TypeName);
#endif
      loadModuleSet.insert(Mod);
    }
  }
}
```

```cpp
/**
 * This method returns the Python wrapper for a C++ object. It's in the responsibility of 
 * the programmer to do the correct reference counting. Basically there are two ways how
 * to implement that: Either always return a new Python object then reference counting is
 * not a matter or return always the same Python object then the reference counter must be
 * incremented by one. However, it's absolutely forbidden to return always the same Python
 * object without incrementing the reference counter. 
 *
 * The default implementation returns 'None'.
 */
PyObject *BaseClass::getPyObject(void)
{
    assert(0);
    //Py_Return;
}

void BaseClass::setPyObject(PyObject *)
{
    assert(0);
}

```

### FreeCAD from xml to wrapping

see Python wrapping chapter in the ebook: Module developer's guide to FreeCAD's source code