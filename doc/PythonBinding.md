## Python interface support

It has been tested out, diff binding can cooperate well with each other, based on the same C-API.

https://github.com/qingfengxia/python_wrap

### translate from CXX to Pybind11

pybind11: defined objects
handle, object, bool_, int_, float_, str, bytes, tuple, list, dict, slice, none, capsule, iterable, iterator, function, buffer, array

diff API,  Py::Dict   setkey() 
CXX2pybind11_Map

### Exception, the translaton is not necessary, it is easy to to in pybind11



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

### Automatically generate Python binding for C++ API

see Python wrapping chapter in the ebook: Module developer's guide to FreeCAD's source code