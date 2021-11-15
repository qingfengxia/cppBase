# Cross-platform C++ BaseClass and TypeSystem, UnitSystem, Geometry (FreeCAD Base module)

Extracted by Qingfeng Xia,  2019-2021

It is extracted from FreeCAD project, <https://github.com/FreeCAD/FreeCAD>, it has the same license as FreeCAD: LGPL v2.1+

This piece of code extraction personal work is NOT sponsored by Qingfeng Xia's employment.

v0.19 master branch,  Nov 13, 2021. 

## Features

Most features from FreeCAD Base module, except for XML related IO. 
Conversion from PyCxx to pybind11 will be experimented here.

+ `BaseClass` and TypeSystem for C++:  extracted from FreeCAD's Base module
  if only TypeSystem is needed, this can be configured by cmake `set(FC_TYPESYSTEM_ONLY ON)`

+ Collection of some header only libraries to catch Python productivity: json, argparse

+ Design pattern:  Factory, Observer

+ Unit and Quantity System
+ Fundametnal classes for gometry: 
   Vector3D, Boundbox, Axis, Matrix, Quaternion, VievProjection, 2D Shapes, OpenInventor Builder3D


Todo:
- `std::shared_ptr<T>` replace all void*
- python wrapping helper, using pybind11



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


### Tutorial for C++ TypeSystem

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

```c++
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


## Collection of Design pattern

+ Design Patterns in C++ with Real Examples
<https://github.com/ehsangazar/design-patterns-cpp>

+ 
<https://github.com/JakubVojvoda/design-patterns-cpp>

### included design patterns

+ AbstractFactory
+ Observor


## Collection of some header only libraries

+ toml11: header only lib: https://github.com/ToruNiina/toml11

 https://github.com/skystrife/cpptoml

+ python style C++17 argparse: https://github.com/p-ranav/argparse

+ json: https://nlohmann.github.io/json/

see more header-only open source libraries at :https://awesomeopensource.com/projects/header-only


## More doc in doc subfolder

<doc/FreeCADBaseChangeLog.md>
<doc/PythonBinding.md>
<doc/TypeSystem.md>
