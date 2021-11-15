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
git+ssh://git@

OpenCASCADE, also have the macro to enable type system.
```cpp
#include <Standard_Type.hxx>

IMPLEMENT_STANDARD_RTTIEXT(ShapeUpgrade_Tool,Standard_Transient)
```



###  top up over FreeCAD's implementation of TypeSystem

1. error string, when forget to init/register the class
2. it is thread-unsafe during type init, but it should be  thread-safe as no modification to the type information.
3. template class are supported by a new macro `TYPE_SOURCE_TEMPLATE`
4. example code <./TypeTest.cpp>
5. types can be registered by `class::init()` and `Type::destruct()` and `init()` again
