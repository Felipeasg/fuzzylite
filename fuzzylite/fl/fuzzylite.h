/*
 Copyright © 2010-2015 by FuzzyLite Limited.
 All rights reserved.

 This file is part of fuzzylite®.

 fuzzylite® is free software: you can redistribute it and/or modify it under
 the terms of the FuzzyLite License included with the software.

 You should have received a copy of the FuzzyLite License along with 
 fuzzylite®. If not, see <http://www.fuzzylite.com/license/>.

 fuzzylite® is a registered trademark of FuzzyLite Limited.
 */

#ifndef FL_FUZZYLITE_H
#define FL_FUZZYLITE_H

#include <algorithm>
#include <cmath>
#include <iostream>
#include <sstream>
#include <limits>
#include <memory>
#include <cstddef>

#ifndef FL_VERSION
#define FL_VERSION "?"
#endif

#ifndef FL_DATE
#define FL_DATE "?"
#endif

#ifndef FL_BUILD_PATH
#define FL_BUILD_PATH ""
#endif

#if defined(_WIN32) || defined(WIN32)
#define FL_WINDOWS
#endif

#if defined(unix) || defined(__unix__) || defined(__unix)
#define FL_UNIX
#endif

#ifdef __APPLE__
#define FL_APPLE
#endif

#define FL__FILE__ std::string(__FILE__).substr(std::string(FL_BUILD_PATH).size())

#define FL_LOG_PREFIX FL__FILE__ << " [" << __LINE__ << "]:"

#define FL_AT FL__FILE__, __LINE__, __FUNCTION__


#define FL_LOG(message) {if (fl::fuzzylite::logging()){std::cout << FL_LOG_PREFIX << message << std::endl;}}
#define FL_LOGP(message) {if (fl::fuzzylite::logging()){std::cout << message << std::endl;}}

#define FL_DEBUG_BEGIN if (fl::fuzzylite::debug()){
#define FL_DEBUG_END }

#define FL_DBG(message) FL_DEBUG_BEGIN\
        std::cout << FL__FILE__ << "::" << __FUNCTION__ << "[" << __LINE__ << "]:" \
                << message << std::endl;\
        FL_DEBUG_END


#ifdef FL_WINDOWS
#include <ciso646> //alternative operator spellings:
//#define and &&
//#define or ||
//#define not !
//#define bitand &
//#define bitor |

//TODO: Address warning 4251 by exporting members?
//http://www.unknownroad.com/rtfm/VisualStudio/warningC4251.html
#ifdef _MSC_VER
#pragma warning (disable:4251)
#endif

//fuzzylite as a shared library is exported
//Applications linking with fuzzylite as a shared library need to import

//fuzzylite as a static library does not export or import
//Applications linking with fuzzylite as a static library do not import

#if defined(FL_EXPORT_LIBRARY)
#define FL_API __declspec(dllexport)
#elif defined(FL_IMPORT_LIBRARY)
#define FL_API __declspec(dllimport)
#else
#define FL_API
#endif

#else
#define FL_API
#endif

/**
  fuzzylite namespace
  @author Juan Rada-Vilela, Ph.D.
 */
namespace fl {
    /**
      Represents floating-point values (typedef to float or double).
     */
#ifdef FL_USE_FLOAT
    typedef float scalar;
#else
    /**
      Represents floating-point values as doubles.
     */
    typedef double scalar;
#endif
    /**
      Represents the Not-A-Number scalar value
     */
    const scalar nan = std::numeric_limits<scalar>::quiet_NaN();
    /**
      Represents the infinity scalar value
     */
    const scalar inf = std::numeric_limits<scalar>::infinity();

#ifdef FL_CPP11
    //C++11 defines

    //Pointers
    /**
      Represents the C++11 null pointer
     */
    const std::nullptr_t null = nullptr;
#define FL_unique_ptr std::unique_ptr
#define FL_move_ptr(x) std::move(x)

    //Identifiers
#define FL_IOVERRIDE override
#define FL_IFINAL final
#define FL_IDEFAULT = default
#define FL_IDELETE = delete
#define FL_INOEXCEPT noexcept

    //Constructors
#define FL_DEFAULT_COPY(Class) \
    Class(const Class&) = default; \
    Class& operator=(const Class&) = default;
#define FL_DEFAULT_MOVE(Class) \
    Class(Class&&) = default; \
    Class& operator=(Class&&) = default;
#define FL_DEFAULT_COPY_AND_MOVE(Class) \
    Class(const Class&) = default; \
    Class& operator=(const Class&) = default;\
    Class(Class&&) = default; \
    Class& operator=(Class&&) = default;

#define FL_DISABLE_COPY(Class) \
    Class(const Class &) = delete;\
    Class &operator=(const Class &) = delete;

#else
    //C++98 defines

    //Pointers
    /**
      Represents the C++98 null pointer
     */
    const long null = 0L;
#define FL_unique_ptr std::auto_ptr
#define FL_move_ptr(x) x

    //Identifiers
#define FL_IOVERRIDE
#define FL_IFINAL
#define FL_IDEFAULT
#define FL_IDELETE
#define FL_INOEXCEPT throw()

    //Constructors
#define FL_DEFAULT_COPY(Class)
#define FL_DEFAULT_MOVE(Class)
#define FL_DEFAULT_COPY_AND_MOVE(Class)

#define FL_DISABLE_COPY(Class) \
    Class(const Class &);\
    Class &operator=(const Class &);

#endif
}


namespace fl {

    /**
      Information and global static settings of the library
      @author Juan Rada-Vilela, Ph.D.
      @since 4.0
     */
    class FL_API fuzzylite {
    protected:
        static int _decimals;
        static scalar _macheps;
        static bool _debug;
        static bool _logging;

    public:
        /**
          Returns the name of the `fuzzylite` library
          @return the name of the `fuzzylite` library
         */
        static std::string name();
        /**
          Returns the name of the `fuzzylite` library including the long version
          @return the name of the `fuzzylite` library including the long version
         */
        static std::string fullname();
        /**
          Returns the version of the `fuzzylite` library
          @return the version of the `fuzzylite` library
         */
        static std::string version();
        /**
          Returns the version of the `fuzzylite` library including the release date
          @return the version of the `fuzzylite` library including the release date
         */
        static std::string longVersion();
        /**
          Returns the license under which the `fuzzylite` library is released
          @return the license under which the `fuzzylite` library is released
         */
        static std::string license();
        /**
          Returns the name of the author of the `fuzzylite` library
          @return "Juan Rada-Vilela, Ph.D."
         */
        static std::string author();
        /**
          Returns the name of the company that owns the `fuzzylite` library
          @return "FuzzyLite Limited"
         */
        static std::string company();
        /**
          Returns the website of the `fuzzylite` library
          @return "http://www.fuzzylite.com/"
         */
        static std::string website();

        /**
          Returns the release date of the `fuzzylite` library
          @return the release date of the `fuzzylite` library
         */
        static std::string date();
        /**
          Returns the platform under which the `fuzzylite` library was built
          @return `Unix` or `Windows`
         */
        static std::string platform();

        /**
          Returns the name of the type of the floating-point variables
          @return `double` or `float`
         */
        static std::string floatingPoint();

        /**
          Indicates whether the library is running in debug mode
          @return a boolean indicating whether the library is running in debug mode
         */
        static bool debug();
        /**
          Sets whether the library is set to run in debug mode
          @param debug is a boolean indicating whether the library is set to run in debug mode
         */
        static void setDebug(bool debug);

        /**
          Returns the number of decimals utilized when formatting scalar values
          @return the number of decimals utilized when formatting scalar values (default is 3)
         */
        static int decimals();
        /**
          Sets the number of decimals utilized when formatting scalar values
          @param decimals is the number of decimals to utilize when formatting scalar values
         */
        static void setDecimals(int decimals);

        /**
          Returns the minimum difference upon which two floating-point values are considered equivalent
          @return the minimum difference upon which two floating-point values are considered equivalent (default is 1e-6)
         */
        static scalar macheps();
        /**
          Sets the minimum difference (machine epsilon) upon which two floating-point values are considered equivalent 
          @param macheps is the minimum difference (machine epsilon) upon which two floating-point values are considered equivalent (default is 1e-6)
         */
        static void setMachEps(scalar macheps);

        /**
          Returns whether the library is set to log information using the macro FL_LOG
          @return a boolean indicating whether the library is set to log information using the macro FL_LOG
         */
        static bool logging();
        /**
          Sets whether the library is set to log information using the macro FL_LOG
          @param logging is a boolean indicating whether the library is set to log information using the macro FL_LOG
         */
        static void setLogging(bool logging);

    };
}


#endif  /* FL_FUZZYLITE_H */
