cmake_minimum_required(VERSION 2.8)

# comment this out, if later used as add_subdirectory()
project(CppBase)

set(PROJECT_BRIEF "BaseClass and TypeSystem extracted from FreeCAD by Qingfeng Xia")
#project version definition

set(CMAKE_BUILD_TYPE Debug)

# it is fine to use clang, but more warning.
#SET (CMAKE_CXX_COMPILER   "/usr/bin/clang++")

# std can and should be applied to target only
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

####################################################
set(MyBase_LIB "MyBase")
set(MyBase_TEST "MyBaseTest")
set(MyBase_MODULE "MyBase")

set(MyBase_SOURCES 
    BaseClass.cpp
    Type.cpp
    #Exception.cpp  # fialed to compile
    #Factory.cpp  # this can be compiled
)
add_library(${MyBase_LIB} SHARED ${MyBase_SOURCES})
set_target_properties(${MyBase_LIB} PROPERTIES OUTPUT_NAME "pppBase")

# This will name your output .so files "libsomething.1.0" which is pretty useful
set_target_properties(${MyBase_LIB}
PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION}
)

##############################################################
add_executable(${MyBase_TEST}
    TypeTest.cpp
)
#add_dependencies(MyTypeTest, MyType)
target_link_libraries(${MyBase_TEST} ${MyBase_LIB})
set_target_properties(${MyBase_TEST} PROPERTIES OUTPUT_NAME "pppBaseTest")


add_executable(Sequencer_Test
    SequencerTest.cpp
    Sequencer.cpp
)
target_link_libraries(Sequencer_Test ${MyBase_LIB})

##########################################################
# To build shared libraries in Windows, we set CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS to TRUE.
# See https://cmake.org/cmake/help/v3.4/variable/CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS.html
# See https://blog.kitware.com/create-dlls-on-windows-without-declspec-using-new-cmake-export-all-feature/

if(WIN32)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

# Let's set compiler-specific flags
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    # G++
    target_compile_options(${MyBase_LIB} PRIVATE -Wall -Wextra)
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
    # MSVC
    target_compile_options(${MyBase_LIB} PRIVATE /EHsc /MTd /W2 /c)
    # Set the DLLEXPORT variable to export symbols
    target_compile_definitions(${MyBase_LIB} PRIVATE WIN_EXPORT)
endif()

########################################################
# include python3 or it should be automatially detected by pybind11?
#add_subdirectory(pybind11)
#pybind11_add_module(${MyBase_MODULE} example.cpp)
#target_link_libraries(${MyBase_MODULE} PRIVATE ${MyBase__LIB})