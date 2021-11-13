cmake_minimum_required(VERSION 3.0)

set(PPP_FC_BASE ON)
set(FC_USE_PYTHON OFF)
set(PPP_USE_PYBIND OFF)

if(ON)
#if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
    # I am a standalone project
    # the output lib has strange SOVERSION suffix, if add_subdirectory() to a parent project
    if(PPP_FC_BASE)
        project(FC_BASE CXX)
    else()
        project(TypeSystem CXX)
    endif()
    set(PROJECT_BRIEF " TypeSystem/Base module extracted from FreeCAD by Qingfeng Xia")
    #project version definition
    set(CMAKE_BUILD_TYPE Debug)

    # std can and should be applied to target only
    set(CMAKE_CXX_STANDARD 14)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
else()
    message(STATUS "I am called from other project with add_subdirectory()")
endif()

# it is fine to use clang, but more warning.
#SET (CMAKE_CXX_COMPILER             "/usr/bin/clang++")
SET_PROPERTY(GLOBAL PROPERTY TARGET_SUPPORTS_SHARED_LIBS TRUE)

#####################################################
set(FreeCADBase_SOURCES 
    BaseClass.cpp
    Type.cpp
    Exception.cpp  # fialed to compile
    Factory.cpp  # this can be compiled
    #Tools.cpp
    #Console.cpp
)

SET(FreeCADBase_UNITAPI_SRCS
    UnitsApi.cpp
    UnitsApi.h
    UnitsSchema.h
    UnitsSchema.cpp
    UnitsSchemaInternal.h
    UnitsSchemaInternal.cpp
    UnitsSchemaMKS.h
    UnitsSchemaMKS.cpp
    UnitsSchemaImperial1.h
    UnitsSchemaImperial1.cpp
    UnitsSchemaCentimeters.h
    UnitsSchemaCentimeters.cpp
    UnitsSchemaMmMin.h
    UnitsSchemaMmMin.cpp
    UnitsSchemaFemMilliMeterNewton.h
    UnitsSchemaFemMilliMeterNewton.cpp
    Quantity.h
    Quantity.cpp
    QuantityParser.l
    QuantityParser.y
    Unit.h
    Unit.cpp
)

SET(FreeCADBase_GEOM_SRCS
    Axis.cpp
    #Builder3D.cpp
    CoordinateSystem.cpp
    DualQuaternion.cpp
    Matrix.cpp
    Placement.cpp
    Rotation.cpp
    Tools2D.cpp
    Vector3D.cpp
    ViewProj.cpp
)

SET(FreeCADBase_PYTHON_SRCS
    Interpreter.cpp
)


###############################################

set(MyBase_LINK_LIBS "")
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
)
if(PPP_FC_BASE)
    add_definitions("-DFC_BUILD_BASE")
    list(APPEND FreeCADBase_SOURCES  ${FreeCADBase_UNITAPI_SRCS})
    list(APPEND FreeCADBase_SOURCES  ${FreeCADBase_GEOM_SRCS})

    find_package(Boost REQUIRED COMPONENTS system thread filesystem)
    find_package(Qt5 REQUIRED COMPONENTS Core)

    list(APPEND MyBase_LINK_LIBS Qt5::Core)  #  ${Qt5Core_LIBRARIES}
    list(APPEND MyBase_LINK_LIBS Boost::filesystem Boost::filesystem)

    include_directories(
        ${Boost_INCLUDE_DIRS}
        ${Qt5Core_INCLUDE_DIRS}
    )

endif()


if(FC_USE_PYTHON)
    add_definitions("-DFC_BUILD_PYTHON")
endif()

if(PPP_USE_PYBIND)
    find_package(pybind11 REQUIRED)
    include_directories() # todo
    add_definitions("-DPPP_BUILD_PYBIND")
    # target_link_libraries(example PRIVATE pybind11::embed)
endif()


####################################################
set(MyBase_LIB "MyBase")
set(MyBase_TEST "MyBaseTest")
set(MyBase_MODULE "MyBase")


message("${FreeCADBase_SOURCES}")
add_library(${MyBase_LIB} SHARED "${FreeCADBase_SOURCES}")
#set_target_properties(${MyBase_LIB} PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(${MyBase_LIB} "${MyBase_LINK_LIBS}")
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


# add_executable(Sequencer_Test
#     SequencerTest.cpp
#     Sequencer.cpp
# )
# target_link_libraries(Sequencer_Test ${MyBase_LIB})

##########################################################
# To build shared libraries in Windows, we set CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS to TRUE.
# See https://cmake.org/cmake/help/v3.4/variable/CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS.html
# See https://blog.kitware.com/create-dlls-on-windows-without-declspec-using-new-cmake-export-all-feature/

if(WIN32)
    if( NOT MINGW)
        set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
    endif()
endif()

# Let's set compiler-specific flags
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    # G++
    target_compile_options(${MyBase_LIB} PRIVATE -Wall -Wextra)
else()
   if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
       target_compile_options(${MyBase_LIB} PRIVATE /EHsc /MTd /W2 /c)
       # Set the DLLEXPORT variable to export symbols
       target_compile_definitions(${MyBase_LIB} PRIVATE WIN_EXPORT)
   endif()
endif()

########################################################
# include python3 or it should be automatially detected by pybind11?
#add_subdirectory(pybind11)
#pybind11_add_module(${MyBase_MODULE} example.cpp)
#target_link_libraries(${MyBase_MODULE} PRIVATE ${MyBase__LIB})