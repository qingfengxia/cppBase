/***************************************************************************
 *   (c) Jürgen Riegel (juergen.riegel@web.de) 2002                        *
 *                                                                         *
 *   This file is part of the FreeCAD CAx development system.              *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Library General Public License (LGPL)   *
 *   as published by the Free Software Foundation; either version 2 of     *
 *   the License, or (at your option) any later version.                   *
 *   for detail see the LICENCE text file.                                 *
 *                                                                         *
 *   FreeCAD is distributed in the hope that it will be useful,            *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Library General Public License for more details.                  *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with FreeCAD; if not, write to the Free Software        *
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  *
 *   USA                                                                   *
 *                                                                         *
 *   Juergen Riegel 2002                                                   *
 ***************************************************************************/


#include "Exception.h"
#include <iostream>
#include <typeinfo>

//FC_LOG_LEVEL_INIT("Exception", true, true);

using namespace Base;


TYPESYSTEM_SOURCE(Base::Exception, Base::BaseClass);


Exception::Exception(void)
        : _line(0)
        , _isTranslatable(false)
        , _isReported(false)
{
    _sErrMsg = "FreeCAD Exception";
}

Exception::Exception(const Exception& inst)
        : _sErrMsg(inst._sErrMsg)
        , _file(inst._file)
        , _line(inst._line)
        , _function(inst._function)
        , _isTranslatable(inst._isTranslatable)
        , _isReported(inst._isReported)
{
}

Exception::Exception(const char* sMessage)
        : _sErrMsg(sMessage)
        , _line(0)
        , _isTranslatable(false)
        , _isReported(false)
{
}

Exception::Exception(const std::string& sMessage)
        : _sErrMsg(sMessage)
        , _line(0)
        , _isTranslatable(false)
        , _isReported(false)
{
}

Exception& Exception::operator=(const Exception& inst)
{
    _sErrMsg = inst._sErrMsg;
    _file = inst._file;
    _line = inst._line;
    _function = inst._function;
    return *this;
}

const char* Exception::what(void) const throw()
{
    return _sErrMsg.c_str();
}

void Exception::ReportException(void) const
{
    if (!_isReported)
    {
        std::string str = "";

        if (!_sErrMsg.empty())
            str += (_sErrMsg + " ");

        if (!_function.empty())
        {
            str += "In ";
            str += _function;
            str += " ";
        }

        std::string _linestr = std::to_string(_line);

        if (!_file.empty() && !_linestr.empty())
        {
            // strip absolute path
            std::size_t pos = _file.find("src");

            if (pos != std::string::npos)
            {
                str += "in ";
                str += _file.substr(pos);
                str += ":";
                str += _linestr;
            }
        }

        std::cerr << "Exception" << str.c_str() << std::endl;
        // Console().Error("Exception (%s): %s \n",Console().Time(),str.c_str());
        _isReported = true;
    }
}

// python related function has been commented out
#if FC_BUILD_PYTHON
PyObject * Exception::getPyObject(void)
{
    Py::Dict edict;
    edict.setItem("sclassname", Py::String(typeid(*this).name()));
    edict.setItem("sErrMsg", Py::String(this->getMessage()));
    edict.setItem("sfile", Py::String(this->getFile()));
    edict.setItem("iline", Py::Long(this->getLine()));

    edict.setItem("sfunction", Py::String(this->getFunction()));
    edict.setItem("swhat", Py::String(this->what()));
    edict.setItem("btranslatable", Py::Boolean(this->getTranslatable()));
    edict.setItem("breported", Py::Boolean(this->_isReported));
    return Py::new_reference_to(edict);
}

void Exception::setPyObject( PyObject * pydict)
{
    if (pydict!=NULL) {
        Py::Dict edict(pydict);
        if (edict.hasKey("sfile"))
            _file = static_cast<std::string>(Py::String(edict.getItem("sfile")));

        if (edict.hasKey("sfunction"))
            _function = static_cast<std::string>(Py::String(edict.getItem("sfunction")));

        if (edict.hasKey("sErrMsg"))
            _sErrMsg = static_cast<std::string>(Py::String(edict.getItem("sErrMsg")));

        if (edict.hasKey("iline"))

        _line = static_cast<long>(Py::Long(edict.getItem("iline")));

        if (edict.hasKey("btranslatable"))
            _isTranslatable = static_cast<bool>(Py::Boolean(edict.getItem("btranslatable")));
        if (edict.hasKey("breported"))
            _isReported = static_cast<bool>(Py::Boolean(edict.getItem("breported")));
    }
}

#endif

// ---------------------------------------------------------

TYPESYSTEM_SOURCE(Base::AbortException, Base::Exception);

AbortException::AbortException(const char* sMessage)
        : Exception(sMessage)
{
}

AbortException::AbortException()
{
    _sErrMsg = "Aborted operation";
}

AbortException::AbortException(const AbortException& inst)
        : Exception(inst)
{
}

const char* AbortException::what() const throw()
{
    return Exception::what();
}

// ---------------------------------------------------------
// why no TYPESYSTEM_SOURCE macro here for this class

NotImplementedError::NotImplementedError()
        : Exception()
{
}

NotImplementedError::NotImplementedError(const char* sMessage)
        : Exception(sMessage)
{
}

NotImplementedError::NotImplementedError(const std::string& sMessage)
        : Exception(sMessage)
{
}

NotImplementedError::NotImplementedError(const NotImplementedError& inst)
        : Exception(inst)
{
}

#if FC_BUILD_PYTHON
PyObject* NotImplementedError::getPyExceptionType() const
{
    return PyExc_NotImplementedError;
}
#endif
// ---------------------------------------------------------
// ---------------------------------------------------------

OverflowError::OverflowError()
  : Exception()
{
}

OverflowError::OverflowError(const char * sMessage)
  : Exception(sMessage)
{
}

OverflowError::OverflowError(const std::string& sMessage)
  : Exception(sMessage)
{
}

#if FC_BUILD_PYTHON
PyObject *OverflowError::getPyExceptionType() const {
    return PyExc_OverflowError;
}
#endif
// ---------------------------------------------------------

UnderflowError::UnderflowError()
  : Exception()
{
}

UnderflowError::UnderflowError(const char * sMessage)
  : Exception(sMessage)
{
}

UnderflowError::UnderflowError(const std::string& sMessage)
  : Exception(sMessage)
{
}

// PyObject *UnderflowError::getPyExceptionType() const {
//     return PyExc_ArithmeticError;
// }

// ---------------------------------------------------------

ValueError::ValueError()
  : Exception()
{
}

ValueError::ValueError(const char * sMessage)
  : Exception(sMessage)
{
}

ValueError::ValueError(const std::string& sMessage)
  : Exception(sMessage)
{
}

// PyObject *ValueError::getPyExceptionType() const {
//     return PyExc_ValueError;
// }

// ---------------------------------------------------------

UnitsMismatchError::UnitsMismatchError()
  : Exception()
{
}

UnitsMismatchError::UnitsMismatchError(const char * sMessage)
  : Exception(sMessage)
{
}

UnitsMismatchError::UnitsMismatchError(const std::string& sMessage)
  : Exception(sMessage)
{
}

// PyObject *UnitsMismatchError::getPyExceptionType() const {
//     return PyExc_ArithmeticError;
// }

// ---------------------------------------------------------
ParserError::ParserError()
  : Exception()
{
}

ParserError::ParserError(const char * sMessage)
  : Exception(sMessage)
{
}

ParserError::ParserError(const std::string& sMessage)
  : Exception(sMessage)
{
}