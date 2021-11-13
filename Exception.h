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


#ifndef BASE_EXCEPTION_H
#define BASE_EXCEPTION_H

#include <exception>
#include <stdexcept>
#include <string>

#if FC_BUILD_BASE
//#include <signal.h>
//#include "FileInfo.h"
#endif

#include "BaseClass.h"

/* MACROS FOR THROWING EXCEPTIONS */

/// the macros do NOT mark any message for translation
/// If you want to mark text for translation, use the QT_TRANSLATE_NOOP macro
/// with the context "Exceptions" and the right throwing macro from below (the one ending in T)
/// example:
/// THROWMT(Base::ValueError,QT_TRANSLATE_NOOP("Exceptions","The multiplicity cannot be increased beyond the degree of
/// the B-Spline."));
///
/// N.B.: The QT_TRANSLATE_NOOP macro won't translate your string. It will just allow lupdate to identify that string
/// for translation so that if you ask for a translation (and the translator have provided one) at that time it gets
/// translated (e.g. in the UI before showing the message of the exception).

#ifdef _MSC_VER

#define THROW(exception)                                                                                               \
    {                                                                                                                  \
        exception myexcp;                                                                                              \
        myexcp.setDebugInformation(__FILE__, __LINE__, __FUNCSIG__);                                                   \
        throw myexcp;                                                                                                  \
    }
#define THROWM(exception, message)                                                                                     \
    {                                                                                                                  \
        exception myexcp(message);                                                                                     \
        myexcp.setDebugInformation(__FILE__, __LINE__, __FUNCSIG__);                                                   \
        throw myexcp;                                                                                                  \
    }
#define THROWMF_FILEEXCEPTION(message, filenameorfileinfo)                                                             \
    {                                                                                                                  \
        FileException myexcp(message, filenameorfileinfo);                                                             \
        myexcp.setDebugInformation(__FILE__, __LINE__, __FUNCSIG__);                                                   \
        throw myexcp;                                                                                                  \
    }

#define THROWT(exception)                                                                                              \
    {                                                                                                                  \
        exception myexcp;                                                                                              \
        myexcp.setDebugInformation(__FILE__, __LINE__, __FUNCSIG__);                                                   \
        myexcp.setTranslatable(true);                                                                                  \
        throw myexcp;                                                                                                  \
    }
#define THROWMT(exception, message)                                                                                    \
    {                                                                                                                  \
        exception myexcp(message);                                                                                     \
        myexcp.setDebugInformation(__FILE__, __LINE__, __FUNCSIG__);                                                   \
        myexcp.setTranslatable(true);                                                                                  \
        throw myexcp;                                                                                                  \
    }
#define THROWMFT_FILEEXCEPTION(message, filenameorfileinfo)                                                            \
    {                                                                                                                  \
        FileException myexcp(message, filenameorfileinfo);                                                             \
        myexcp.setDebugInformation(__FILE__, __LINE__, __FUNCSIG__);                                                   \
        myexcp.setTranslatable(true);                                                                                  \
        throw myexcp;                                                                                                  \
    }

#elif defined(__GNUC__)

#define THROW(exception)                                                                                               \
    {                                                                                                                  \
        exception myexcp;                                                                                              \
        myexcp.setDebugInformation(__FILE__, __LINE__, __PRETTY_FUNCTION__);                                           \
        throw myexcp;                                                                                                  \
    }
#define THROWM(exception, message)                                                                                     \
    {                                                                                                                  \
        exception myexcp(message);                                                                                     \
        myexcp.setDebugInformation(__FILE__, __LINE__, __PRETTY_FUNCTION__);                                           \
        throw myexcp;                                                                                                  \
    }
#define THROWMF_FILEEXCEPTION(message, filenameorfileinfo)                                                             \
    {                                                                                                                  \
        FileException myexcp(message, filenameorfileinfo);                                                             \
        myexcp.setDebugInformation(__FILE__, __LINE__, __PRETTY_FUNCTION__);                                           \
        throw myexcp;                                                                                                  \
    }

#define THROWT(exception)                                                                                              \
    {                                                                                                                  \
        exception myexcp;                                                                                              \
        myexcp.setDebugInformation(__FILE__, __LINE__, __PRETTY_FUNCTION__);                                           \
        myexcp.setTranslatable(true);                                                                                  \
        throw myexcp;                                                                                                  \
    }
#define THROWMT(exception, message)                                                                                    \
    {                                                                                                                  \
        exception myexcp(message);                                                                                     \
        myexcp.setDebugInformation(__FILE__, __LINE__, __PRETTY_FUNCTION__);                                           \
        myexcp.setTranslatable(true);                                                                                  \
        throw myexcp;                                                                                                  \
    }
#define THROWMFT_FILEEXCEPTION(message, filenameorfileinfo)                                                            \
    {                                                                                                                  \
        FileException myexcp(message, filenameorfileinfo);                                                             \
        myexcp.setDebugInformation(__FILE__, __LINE__, __PRETTY_FUNCTION__);                                           \
        myexcp.setTranslatable(true);                                                                                  \
        throw myexcp;                                                                                                  \
    }

#else

#define THROW(exception)                                                                                               \
    {                                                                                                                  \
        exception myexcp;                                                                                              \
        myexcp.setDebugInformation(__FILE__, __LINE__, __func__);                                                      \
        throw myexcp;                                                                                                  \
    }
#define THROWM(exception, message)                                                                                     \
    {                                                                                                                  \
        exception myexcp(message);                                                                                     \
        myexcp.setDebugInformation(__FILE__, __LINE__, __func__);                                                      \
        throw myexcp;                                                                                                  \
    }
#define THROWMF_FILEEXCEPTION(message, filenameorfileinfo)                                                             \
    {                                                                                                                  \
        FileException myexcp(message, filenameorfileinfo);                                                             \
        myexcp.setDebugInformation(__FILE__, __LINE__, __func__);                                                      \
        throw myexcp;                                                                                                  \
    }

#define THROWT(exception)                                                                                              \
    {                                                                                                                  \
        exception myexcp;                                                                                              \
        myexcp.setDebugInformation(__FILE__, __LINE__, __func__);                                                      \
        myexcp.setTranslatable(true);                                                                                  \
        throw myexcp;                                                                                                  \
    }
#define THROWMT(exception, message)                                                                                    \
    {                                                                                                                  \
        exception myexcp(message);                                                                                     \
        myexcp.setDebugInformation(__FILE__, __LINE__, __func__);                                                      \
        myexcp.setTranslatable(true);                                                                                  \
        throw myexcp;                                                                                                  \
    }
#define THROWMFT_FILEEXCEPTION(message, filenameorfileinfo)                                                            \
    {                                                                                                                  \
        FileException myexcp(message, filenameorfileinfo);                                                             \
        myexcp.setDebugInformation(__FILE__, __LINE__, __func__);                                                      \
        myexcp.setTranslatable(true);                                                                                  \
        throw myexcp;                                                                                                  \
    }


#endif

namespace Base
{

    class BaseExport Exception : public BaseClass
    {
        TYPESYSTEM_HEADER();

    public:
        virtual ~Exception() throw()
        {
        }

        Exception& operator=(const Exception& inst);

        virtual const char* what(void) const throw();

        /// Reports exception. It includes a mechanism to only report an exception once.
        virtual void ReportException(void) const;

        inline void setMessage(const char* sMessage);
        inline void setMessage(const std::string& sMessage);
        // what may differ from the message given by the user in
        // derived classes
        inline std::string getMessage() const;
        inline std::string getFile() const;
        inline int getLine() const;
        inline std::string getFunction() const;

        /// setter methods for including debug information
        /// intended to use via macro for autofilling of debugging information
        inline void setDebugInformation(const std::string& file, const int line, const std::string& function);

        inline bool getTranslatable() const;
        inline void setTranslatable(bool translatable);
        /*
        /// returns a Python dictionary containing the exception data
        virtual PyObject * getPyObject(void);
        /// returns sets the exception data from a Python dictionary
        virtual void setPyObject( PyObject * pydict);
        */

    protected:
        /* sMessage may be:
         * - a UI compliant string susceptible to being translated and shown to the user in the UI
         * - a very technical message not intended to be translated or shown to the user in the UI
         * The preferred way of throwing an exception is using the macros above.
         * This way, the file, line, and function are automatically inserted. */
        Exception(const char* sMessage);
        Exception(const std::string& sMessage);
        Exception(void);
        Exception(const Exception& inst);

    protected:
        std::string _sErrMsg;
        std::string _file;
        int _line;
        std::string _function;
        bool _isTranslatable;
        mutable bool _isReported;
    };

    inline void Exception::setMessage(const char* sMessage)
    {
        _sErrMsg = sMessage;
    }

    inline void Exception::setMessage(const std::string& sMessage)
    {
        _sErrMsg = sMessage;
    }

    inline std::string Exception::getMessage() const
    {
        return _sErrMsg;
    }

    inline std::string Exception::getFile() const
    {
        return _file;
    }

    inline int Exception::getLine() const
    {
        return _line;
    }

    inline std::string Exception::getFunction() const
    {
        return _function;
    }

    inline void Exception::setDebugInformation(const std::string& file, const int line, const std::string& function)
    {
        _file = file;
        _line = line;
        _function = function;
    }

    inline bool Exception::getTranslatable() const
    {
        return _isTranslatable;
    }

    inline void Exception::setTranslatable(bool translatable)
    {
        _isTranslatable = translatable;
    }


    /**
     * The NotImplementedError can be used to indicate that an invoked function is not implemented.
     * @author Werner Mayer
     */
    class BaseExport NotImplementedError : public Exception
    {
        //TYPESYSTEM_HEADER();
    public:
        /// Construction
        NotImplementedError();
        NotImplementedError(const char* sMessage);
        NotImplementedError(const std::string& sMessage);
        /// Construction
        NotImplementedError(const NotImplementedError& inst);
        /// Destruction
        virtual ~NotImplementedError() throw()
        {
        }
        // virtual PyObject* getPyExceptionType() const override;
    };

    /**
     * The AbortException is thrown if a pending operation was aborted.
     * @author Werner Mayer
     */
    class BaseExport AbortException : public Exception
    {
        TYPESYSTEM_HEADER();
    public:
        /// Construction
        AbortException(const char* sMessage);
        /// Construction
        AbortException();
        /// Construction
        AbortException(const AbortException& inst);

        /// Destruction
        virtual ~AbortException() throw()
        {
        }
        /// Description of the exception
        virtual const char* what() const throw();
    };

/**
 * The OverflowError can be used to indicate overflows of numbers.
 * @author Werner Mayer
 */
class BaseExport OverflowError : public Exception
{
public:
  /// Construction
  OverflowError();
  OverflowError(const char * sMessage);
  OverflowError(const std::string& sMessage);
  /// Destruction
  virtual ~OverflowError() throw() {}
#if FC_BUILD_PYTHON
  virtual PyObject * getPyExceptionType() const override;
#endif
};

/**
 * The UnderflowError can be used to indicate underflows of numbers.
 * @author Werner Mayer
 */
class BaseExport UnderflowError : public Exception
{
public:
  /// Construction
  UnderflowError();
  UnderflowError(const char * sMessage);
  UnderflowError(const std::string& sMessage);
  /// Destruction
  virtual ~UnderflowError() throw() {}
#if FC_BUILD_PYTHON
  virtual PyObject * getPyExceptionType() const override;
#endif
};

/**
 * The UnitsMismatchError can be used to indicate that quantities with different units are used.
 * @author Werner Mayer
 */
class BaseExport UnitsMismatchError : public Exception
{
public:
  /// Construction
  UnitsMismatchError();
  UnitsMismatchError(const char * sMessage);
  UnitsMismatchError(const std::string& sMessage);
  /// Destruction
  virtual ~UnitsMismatchError() throw() {}
#if FC_BUILD_PYTHON
  virtual PyObject * getPyExceptionType() const override;
#endif
};

/**
 * The ValueError can be used to indicate the usage of a wrong value.
 * @author Werner Mayer
 */
class BaseExport ValueError : public Exception
{
public:
  /// Construction
  ValueError();
  ValueError(const char * sMessage);
  ValueError(const std::string& sMessage);
  /// Destruction
  virtual ~ValueError() throw() {}
  //virtual PyObject * getPyExceptionType() const override;
};

/**
 * The ParserError can be used to indicate the parsing error.
 * @author Werner Mayer
 */
class BaseExport ParserError : public Exception
{
public:
  /// Construction
  ParserError();
  ParserError(const char * sMessage);
  ParserError(const std::string& sMessage);
  /// Destruction
  virtual ~ParserError() throw() {}
};

} // namespace Base

#endif // BASE_EXCEPTION_H
