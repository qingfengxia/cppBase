
Thanks to the great modulerization design of FreeCAD, extracting TypeSystem, UnitSystem is straightforward.

## Overview of changelog
Minimise the code imcompatibility, in case python related code, preprocessing macro is used.

```cpp
#if FC_BUILD_PYTHON
#include <CXX/Objects.hxx> 
#endif

#if FC_BUILD_PYBIND
#include <pybind11/pybind11.h>
using py=pybind11;
#endif
```

## `Interpreter` class needs rewritten


## Console

Depends on how this FreeCAD_Base module is used, input and output stream could be directed to other stream like within GUI.

### Console class has been commented out
Console() is not used directly, but Exception classes may use `Console()`
`//#include "Console.h"`

```c++
#ifdef FC_DEBUG
        Console().Warning("\"%s\" is not registered\n", sScriptName);
#endif
```

```c++

FileException
```

### `Base::Stream` is replaced by `std::ofstream`

Recently Windows 10 has utf8 support

Why `Base::Stream` is needed?
> The ofstream class is provided for convenience. On Windows
platforms it opens a stream with UCS-2 encoded file name
while on Linux platforms the file name is UTF-8 encoded.
 @author Werner Mayer

`FileInfo.h  TimeInfo.h`  etc is not included yet. 


