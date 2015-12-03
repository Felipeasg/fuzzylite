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

#ifndef FL_OPERATION_H
#define FL_OPERATION_H

#include "fl/fuzzylite.h"

#include "fl/Exception.h"

#include <string>
#include <vector>

namespace fl {

    /**
    
      The Operation class (or Op type definition) is a general purpose class
      that contains methods for numeric and string manipulation, amongst other
      functions.
    
      @author Juan Rada-Vilela, Ph.D.
      @since 4.0
    
     */
    class Operation {
    public:

        /**
          Returns the minimum between the two parameters
          @param a
          @param b
          @return @f$\min(a,b)@f$
         */
        template <typename T>
        static T min(T a, T b);

        /**
          Returns the maximum between the two parameters
          @param a
          @param b
          @return @f$\max(a,b)@f$
         */
        template <typename T>
        static T max(T a, T b);

        /**
          Returns @f$x@f$ bounded in @f$[\min,\max]@f$
          @param x is the value to be bounded
          @param min is the minimum value of the range
          @param max is the maximum value of the range
          @return @f$
          \begin{cases}
          \min & \mbox{if $x < \min$} \cr
          \max & \mbox{if $x > \max$} \cr
          x & \mbox{otherwise}
          \end{cases}
          @f$
         */
        template <typename T>
        static T bound(T x, T min, T max);

        /**
          Indicates whether @f$x@f$ is within the boundaries (open or closed)
          @param x is the value
          @param min is the minimum of the range
          @param max is the maximum of the range
          @param geq determines whether the maximum is a closed interval
          @param leq determines whether the minimum is a closed interval
          @return @f$
          \begin{cases}
          x \in [\min,\max] & \mbox{if $geq \wedge leq$} \cr
          x \in (\min,\max] & \mbox{if $geq \wedge \bar{leq}$} \cr
          x \in [\min, \max) & \mbox{if $\bar{geq} \wedge leq$} \cr
          x \in (\min, \max) & \mbox{if $\bar{geq} \wedge \bar{leq}$} \cr
          \end{cases}
          @f$
         */
        template <typename T>
        static bool in(T x, T min, T max, bool geq = true, bool leq = true);

        /**
          Indicates whether @f$x@f$ is infinity
          @param x is the value
          @return a boolean indicating whether  @f$x@f$  is infinity
         */
        template <typename T>
        static bool isInf(T x);

        /**
          Indicates whether @f$x@f$ is not-a-number (NaN)
          @param x is the value
          @return a boolean indicating whether @f$x@f$ is not-a-number (NaN)
         */
        template <typename T>
        static bool isNaN(T x);

        /**
          Indicates whether @f$x@f$ is finite, that is, @f$x \not\in
          \{\pm\infty, \mathrm{NaN}\}@f$
          @param x is the value
          @return a boolean indicating whether  @f$x@f$  is finite
         */
        template <typename T>
        static bool isFinite(T x);

        /**
          Returns whether @f$a@f$ is less than @f$b@f$ at the given `macheps`
          @param a
          @param b
          @param macheps is the minimum difference upon which two
          floating-point values are considered equivalent
          @return a boolean indicating whether @f$a@f$ is less than @f$b@f$ at
          the given `macheps`
         */
        static bool isLt(scalar a, scalar b, scalar macheps = fl::fuzzylite::macheps());
        /**
          Returns whether @f$a@f$ is less than or equal to @f$b@f$ at the given
          `macheps`
          @param a
          @param b
          @param macheps is the minimum difference upon which two
          floating-point values are considered equivalent
          @return a boolean indicating whether @f$a@f$ is less than or equal to
          @f$b@f$ at the given `macheps`
         */
        static bool isLE(scalar a, scalar b, scalar macheps = fl::fuzzylite::macheps());
        /**
          Returns whether @f$a@f$ is equal to @f$b@f$ at the given `macheps`
          @param a
          @param b
          @param macheps is the minimum difference upon which two
          floating-point values are considered equivalent
          @return a boolean indicating whether @f$a@f$ is equal to @f$b@f$ at
          the given `macheps`
         */
        static bool isEq(scalar a, scalar b, scalar macheps = fl::fuzzylite::macheps());
        /**
          Returns whether @f$a@f$ is greater than @f$b@f$ at the given `macheps`
          @param a
          @param b
          @param macheps is the minimum difference upon which two
          floating-point values are considered equivalent
          @return a boolean indicating whether @f$a@f$ is greater than @f$b@f$
          at the given `macheps`
         */
        static bool isGt(scalar a, scalar b, scalar macheps = fl::fuzzylite::macheps());
        /**
          Returns whether @f$a@f$ is greater than or equal to @f$b@f$ at the
          given `macheps`
          @param a
          @param b
          @param macheps is the minimum difference upon which two
          floating-point values are considered equivalent
          @return a boolean indicating whether @f$a@f$ is greater than or equal
          to @f$b@f$ at the given `macheps`
         */
        static bool isGE(scalar a, scalar b, scalar macheps = fl::fuzzylite::macheps());

        /**
          Linearly interpolates the parameter @f$x@f$ in range
          `[fromMin,fromMax]` to a new value in the range `[toMin,toMax]`
          @param x is the source value to interpolate
          @param fromMin is the minimum value of the source range 
          @param fromMax is the maximum value of the source range
          @param toMin is the minimum value of the target range
          @param toMax is the maximum value of the target range
          @param bounded determines whether the resulting value is bounded to
          the range
          @return the source value linearly interpolated to the target range:
          @f$ y = y_a + (y_b - y_a) \dfrac{x-x_a}{x_b-x_a} @f$
         */
        static scalar scale(scalar x, scalar fromMin, scalar fromMax,
                scalar toMin, scalar toMax, bool bounded = false);

        /**
          Adds two values
          @param a
          @param b
          @return @f$a+b@f$
         */
        static scalar add(scalar a, scalar b);
        /**
          Subtracts two values
          @param a
          @param b
          @return @f$a-b@f$
         */
        static scalar subtract(scalar a, scalar b);
        /**
          Multiplies two values
          @param a
          @param b
          @return @f$a\times b@f$
         */
        static scalar multiply(scalar a, scalar b);
        /**
          Divides two values
          @param a
          @param b
          @return @f$a/b@f$
         */
        static scalar divide(scalar a, scalar b);
        /**
          Computes the modulo
          @param a
          @param b
          @return @f$a \mod b@f$
         */
        static scalar modulo(scalar a, scalar b);

        /**
          Computes the logical AND 
          @param a
          @param b
          @return @f$
          \begin{cases}
          1.0 & \mbox{if $a=1 \wedge b=1$}\cr
          0.0 & \mbox{otherwise}
          \end{cases}
          @f$
         */
        static scalar logicalAnd(scalar a, scalar b);
        /**
          Computes the logical OR 
          @param a
          @param b
          @return @f$
          \begin{cases}
          1.0 & \mbox{if $a=1 \vee b=1$}\cr
          0.0 & \mbox{otherwise}
          \end{cases}
          @f$
         */
        static scalar logicalOr(scalar a, scalar b);
        /**
          Returns the complement of the value
          @param a
          @return @f$
          \begin{cases}
          0.0 & \mbox{if $a=1$}\cr
          1.0 & \mbox{otherwise}
          \end{cases}
          @f$
         */
        static scalar logicalNot(scalar a);
        /**
          Negates the value
          @param a
          @return -a
         */
        static scalar negate(scalar a);
        /**
          Rounds the value to the nearest integer
          @param x
          @return @f$
          \begin{cases}
          \lfloor x + 0.5 \rfloor & \mbox{if $x > 0$}\cr
          \lceil x - 0.5 \rceil & \mbox{otherwise}
          \end{cases}
          @f$
         */
        static scalar round(scalar x);

        /**
          Returns whether @f$a@f$ is greater than or equal to @f$b@f$ at the
          default `macheps`
          @param a
          @param b
          @return a boolean indicating whether @f$a@f$ is greater than or equal
          to @f$b@f$ at the default `macheps`
         */
        static scalar gt(scalar a, scalar b);
        /**
          Returns whether @f$a@f$ is greater than or equal to @f$b@f$ at the
          default `macheps`
          @param a
          @param b
          @return a boolean indicating whether @f$a@f$ is greater than or equal
          to @f$b@f$ at the default `macheps`
         */
        static scalar ge(scalar a, scalar b);
        /**
          Returns whether @f$a@f$ is equal to @f$b@f$ at the default `macheps`
          @param a
          @param b
          @return a boolean indicating whether @f$a@f$ is equal to @f$b@f$ at
          the default `macheps`
         */
        static scalar eq(scalar a, scalar b);
        /**
          Returns whether @f$a@f$ is different from @f$b@f$ at the default
          `macheps`
          @param a
          @param b
          @return a boolean indicating whether @f$a@f$ is different from
          @f$b@f$ at the default `macheps`
         */
        static scalar neq(scalar a, scalar b);
        /**
          Returns whether @f$a@f$ is less than or equal to @f$b@f$ at the
          default `macheps`
          @param a
          @param b
          @return a boolean indicating whether @f$a@f$ is less than or equal to
          @f$b@f$ at the default `macheps`
         */
        static scalar le(scalar a, scalar b);
        /**
          Returns whether @f$a@f$ is less than @f$b@f$ at the default `macheps`
          @param a
          @param b
          @return a boolean indicating whether @f$a@f$ is less than @f$b@f$ at
          the default `macheps`
         */
        static scalar lt(scalar a, scalar b);

        /**
          Increments @f$x@f$ by the unit, treating the entire vector as a
          number. For example, incrementing a few times @f$x_0=\{0,0\}@f$
          within boundaries @f$[0,1]@f$ results in: @f$x_1=\{0,1\}@f$,
          @f$x_2=\{1,0\}@f$, @f$x_3=\{1,1\}@f$, @f$x_4=\{0,0\}@f$.
          @param x is the vector to increment
          @param min is the minimum value of the dimension 
          @param max is the maximum value of the dimension 
          @return a boolean indicating if the increment of @f$x@f$ leads to
          overflow (e.g., @f$x_4@f$ returns `true`)
         */
        static bool increment(std::vector<int>& x, std::vector<int>& min, std::vector<int>& max);
        /**
          Increments @f$x@f$ by the unit at the given position, treating the
          entire vector as a number. For example, incrementing
          @f$x_0=\{0,0,0\}@f$ within boundaries @f$[0,1]@f$ at the second
          position results in: @f$x_1=\{0,1,0\}@f$, @f$x_2=\{1,0,0\}@f$,
          @f$x_3=\{1,1,0\}@f$, @f$x_4=\{0,0,0\}@f$.
          @param x is the vector to increment
          @param position is the position of the vector to increment, where
          smaller values lead to higher significance digits
          @param min is the minimum value of the dimension 
          @param max is the maximum value of the dimension 
          @return a boolean indicating if the increment of @f$x@f$ leads to
          overflow (e.g., @f$x_4@f$ returns `true`)
         */
        static bool increment(std::vector<int>& x, int position, std::vector<int>& min, std::vector<int>& max);

        /**
          Computes the mean of the sample
          @param x is the sample
          @return @f$\dfrac{\sum_i{x_i}}{|x|}@f$
         */
        static double mean(const std::vector<scalar>& x);
        /**
          Computes the variance of the sample
          @param x is the sample
          @return  @f$ \sum_i{ (x_i - \bar{x})^2 } / (|x| - 1) @f$
         */
        static double variance(const std::vector<scalar>& x);
        /**
          Computes the variance of the sample using the given mean
          @param x is the sample
          @param mean is the mean value of the sample
          @return  @f$ \sum_i{ (x_i - \bar{x})^2 } / (|x| - 1) @f$
         */
        static double variance(const std::vector<scalar>& x, scalar mean);
        /**
          Computes the standard deviation of the sample
          @param x
          @return @f$ \sqrt{\mbox{variance}(x, \bar{x})} @f$
         */
        static double standardDeviation(const std::vector<scalar>& x);
        /**
          Computes the standard deviation of the sample using the given mean
          @param x
          @param mean is the mean value of x
          @return @f$ \sqrt{\mbox{variance}(x, \bar{x})} @f$
         */
        static double standardDeviation(const std::vector<scalar>& x, scalar mean);

        /**
          Returns a valid name for variables
          @param name
          @return an name whose characters are in `[a-zA-Z_0-9.]`
         */
        static std::string validName(const std::string& name);

        //@todo remove this method
        static int isValidForName(int character);

        /**
          Replaces the substrings that are equal to the given expression
          @param str is the target string 
          @param find is the string to find
          @param replace is the string to replace the findings
          @param replaceAll whether all the substrings are to be replaced or
          just the first string
          @return `str` with the replacements made
          @todo rename method to create replaceFirst and replaceAll
         */
        static std::string findReplace(const std::string& str, const std::string& find,
                const std::string& replace, bool replaceAll = true);

        /**
          Splits the string around the given delimiter
          @param str is the string to split
          @param delimiter is the substrings on which the string will be split
          @param ignoreEmpty whether the empty strings are discarded
          @return the string split around the given delimiter
         */
        static std::vector<std::string> split(const std::string& str,
                const std::string& delimiter = " ", bool ignoreEmpty = true);

        /**
          Removes whitespace at the beginning and end of the text
          @param text 
          @return a space-trimmed string
         */
        static std::string trim(const std::string& text);

        /**
          Replaces every matching character in the text with the given
          replacement
          @param text is the string to have replacements
          @param matchesChar is a pointer to a method that indicates whether
          the given character is a match
          @param replacement a string to replace a matching character
          @return the string with every matching character replaced
         */
        static std::string format(const std::string& text, int matchesChar(int),
                const std::string& replacement = "");

        /**
          Intentionally results in a compiler error in C++11 (or linker error
          in C++98) in order to avoid the deprecated usage of this method
          @param x is irrelevant
          @param quiet is irrelevant
          @param alternative is irrelevant
          @return nothing
          @deprecated the method has been removed since version 5.0
         */
        static scalar toScalar(const std::string& x, bool quiet,
                scalar alternative = fl::nan) FL_IDELETE;

        /**
          Parses the given string into a scalar value
          @param x is the string to parse
          @return the given string into a scalar value
          @throws fl::Exception if the string does not contain a scalar value
         */
        static scalar toScalar(const std::string& x); //throws fl::Exception

        /**
          Parses the given string into a scalar value without throwing an
          exception
          @param x is the string to parse
          @param alternative is the value to return if the string does not
          contain a scalar value
          @return the given string into a scalar value or the alternative value
          if the string does not contain a scalar value
         */
        static scalar toScalar(const std::string& x, scalar alternative) FL_INOEXCEPT;

        /**
          Indicates whether the string can be converted to a numeric value. 
          @param x
          @return a boolean indicating whether the string can be converted to a
          numeric value
         */
        static bool isNumeric(const std::string& x);

        /**
          Returns a string representation of the given value
          @param x is the value 
          @param decimals is the number of decimals utilised
          @return a string representation of the given value 
         */
        template <typename T>
        static std::string str(T x, int decimals = fuzzylite::decimals());

        /**
          Joins a vector of elements by the given separator into a single
          string. The elements are represented as strings utilizing the {@link
          #str()} method on each element
          @param x is the vector of elements
          @param separator is the string to add between the elements
          @return a single string joining the vector of elements by the given
          separator
         */
        template <typename T>
        static std::string join(const std::vector<T>& x, const std::string& separator);

        /**
          Joins a variadic number of elements by the given separator into a
          single string. The elements are represented as strings utilizing the
          {@link #str()} method on each element
          @param items is the number of elements to join
          @param separator is the string to add between the elements
          @param first is the first element, which defines the type of the
          subsequent elements
          @param ... are the remaining elements to join
          @return a single string joining the variadic number of elements by
          the given separator
         */
        template <typename T>
        static std::string join(int items, const std::string& separator, T first, ...);
    };

    /**A shortened type to refer to Operation*/
    typedef Operation Op;
}


/**
  Template implementation
 */

#include "fl/defuzzifier/Defuzzifier.h"
#include "fl/norm/Norm.h"
#include "fl/norm/SNorm.h"
#include "fl/norm/TNorm.h"

#include <algorithm>
#include <iomanip>
#include <cstdarg>
#include <cctype>


namespace fl {

    template <typename T>
    inline T Operation::min(T a, T b) {
        if (isNaN(a)) return b;
        if (isNaN(b)) return a;
        return a < b ? a : b;
    }

    template <typename T>
    inline T Operation::max(T a, T b) {
        if (isNaN(a)) return b;
        if (isNaN(b)) return a;
        return a > b ? a : b;
    }

    template <typename T>
    inline T Operation::bound(T x, T min, T max) {
        if (isGt(x, max)) return max;
        if (isLt(x, min)) return min;
        return x;
    }

    template <typename T>
    inline bool Operation::in(T x, T min, T max, bool geq, bool leq) {
        bool left = geq ? isGE(x, min) : isGt(x, min);
        bool right = leq ? isLE(x, max) : isLt(x, max);
        return (left and right);
    }

    template <typename T>
    inline bool Operation::isInf(T x) {
        return std::abs(x) == fl::inf;
    }

    template <typename T>
    inline bool Operation::isNaN(T x) {
        return not (x == x);
    }

    template<typename T>
    inline bool Operation::isFinite(T x) {
        return not (isNaN(x) or isInf(x));
    }

    inline bool Operation::isLt(scalar a, scalar b, scalar macheps) {
        return not isEq(a, b, macheps) and a < b;
    }

    inline bool Operation::isLE(scalar a, scalar b, scalar macheps) {
        return isEq(a, b, macheps) or a < b;
    }

    inline bool Operation::isEq(scalar a, scalar b, scalar macheps) {
        return a == b or std::fabs(a - b) < macheps or (isNaN(a) and isNaN(b));
    }

    inline bool Operation::isGt(scalar a, scalar b, scalar macheps) {
        return not isEq(a, b, macheps) and a > b;
    }

    inline bool Operation::isGE(scalar a, scalar b, scalar macheps) {
        return isEq(a, b, macheps) or a > b;
    }

    inline scalar Operation::scale(scalar x, scalar fromMin, scalar fromMax, scalar toMin, scalar toMax, bool bounded) {
        scalar result = (toMax - toMin) / (fromMax - fromMin) * (x - fromMin) + toMin;
        return bounded ? fl::Op::bound(result, toMin, toMax) : result;
    }

    inline scalar Operation::add(scalar a, scalar b) {
        return a + b;
    }

    inline scalar Operation::subtract(scalar a, scalar b) {
        return a - b;
    }

    inline scalar Operation::multiply(scalar a, scalar b) {
        return a * b;
    }

    inline scalar Operation::divide(scalar a, scalar b) {
        return a / b;
    }

    inline scalar Operation::modulo(scalar a, scalar b) {
        return fmod(a, b);
    }

    inline scalar Operation::logicalAnd(scalar a, scalar b) {
        return (isEq(a, 1.0) and isEq(b, 1.0)) ? 1.0 : 0.0;
    }

    inline scalar Operation::logicalOr(scalar a, scalar b) {
        return (isEq(a, 1.0) or isEq(b, 1.0)) ? 1.0 : 0.0;
    }

    inline scalar Operation::logicalNot(scalar a) {
        return isEq(a, 1.0) ? 0.0 : 1.0;
    }

    inline scalar Operation::negate(scalar a) {
        return -a;
    }

    inline scalar Operation::round(scalar x) {
        return (x > 0.0) ? std::floor(x + 0.5) : std::ceil(x - 0.5);
    }

    inline scalar Operation::gt(scalar a, scalar b) {
        return isGt(a, b);
    }

    inline scalar Operation::ge(scalar a, scalar b) {
        return isGE(a, b);
    }

    inline scalar Operation::eq(scalar a, scalar b) {
        return isEq(a, b);
    }

    inline scalar Operation::neq(scalar a, scalar b) {
        return not isEq(a, b);
    }

    inline scalar Operation::le(scalar a, scalar b) {
        return isLE(a, b);
    }

    inline scalar Operation::lt(scalar a, scalar b) {
        return isLt(a, b);
    }

    inline bool Operation::increment(std::vector<int>& x, std::vector<int>& min, std::vector<int>& max) {
        return increment(x, -1 + x.size(), min, max);
    }

    inline bool Operation::increment(std::vector<int>& x, int position, std::vector<int>& min, std::vector<int>& max) {
        if (x.empty() or position < 0) return true;

        bool overflow = false;
        if (x.at(position) < max.at(position)) {
            ++x.at(position);
        } else {
            overflow = (position == 0);
            x.at(position) = min.at(position);
            --position;
            if (position >= 0) {
                overflow = increment(x, position, min, max);
            }
        }
        return overflow;
    }

    inline double Operation::mean(const std::vector<scalar>& x) {
        if (x.size() == 0) return fl::nan;
        scalar sum = 0.0;
        for (std::size_t i = 0; i < x.size(); ++i) sum += x.at(i);
        return sum / x.size();
    }

    inline double Operation::standardDeviation(const std::vector<scalar>& x) {
        if (x.size() <= 1) return 0.0;
        return standardDeviation(x, mean(x));
    }

    inline double Operation::standardDeviation(const std::vector<scalar>& x, scalar mean) {
        if (x.size() <= 1) return 0.0;
        return std::sqrt(variance(x, mean));
    }

    inline double Operation::variance(const std::vector<scalar>& x) {
        if (x.size() <= 1) return 0.0;
        return variance(x, mean(x));
    }

    inline double Operation::variance(const std::vector<scalar>& x, scalar mean) {
        if (x.size() <= 1) return 0.0;
        scalar result = 0;
        for (std::size_t i = 0; i < x.size(); ++i) {
            result += (x.at(i) - mean) * (x.at(i) - mean);
        }
        result /= -1 + x.size();
        return result;
    }



    //Text Operations:

    inline std::string Operation::validName(const std::string& name) {
        if (trim(name).empty()) return "unnamed";
        std::ostringstream ss;
        for (std::size_t i = 0; i < name.length(); ++i) {
            char c = name[i];
            if (c == '_' or c == '.' or isalnum(c)) {
                ss << c;
            }
        }
        return ss.str();
    }

    inline int Operation::isValidForName(int character) {
        return character == '_' or character == '.' or isalnum(character);
    }

    inline std::string Operation::findReplace(const std::string& str, const std::string& find,
            const std::string& replace, bool replaceAll) {
        std::ostringstream result;
        std::size_t fromIndex = 0, nextIndex;
        do {
            nextIndex = str.find(find, fromIndex);
            result << str.substr(fromIndex, nextIndex - fromIndex);
            if (nextIndex != std::string::npos)
                result << replace;
            fromIndex = nextIndex + find.size();
        } while (replaceAll and nextIndex != std::string::npos);
        return result.str();
    }

    inline std::vector<std::string> Operation::split(const std::string& str,
            const std::string& delimiter, bool ignoreEmpty) {
        std::vector<std::string> result;
        if (str.empty() or delimiter.empty()) {
            result.push_back(str);
            return result;
        }
        std::string::const_iterator position = str.begin(), next = str.begin();
        while (next != str.end()) {
            next = std::search(position, str.end(), delimiter.begin(), delimiter.end());
            std::string token(position, next);
            if (not (token.empty() and ignoreEmpty)) {
                result.push_back(token);
            }
            if (next != str.end()) {
                position = next + delimiter.size();
            }
        }
        return result;
    }

    inline std::string Operation::trim(const std::string& text) {
        if (text.empty()) return text;
        if (not (std::isspace(text.at(0)) or std::isspace(text.at(text.size() - 1))))
            return text;
        std::size_t start = 0, end = text.size() - 1;
        while (start <= end and std::isspace(text.at(start))) {
            ++start;
        }
        while (end >= start and std::isspace(text.at(end))) {
            --end;
        }
        std::size_t length = end - start + 1;
        if (length <= 0) return "";
        return text.substr(start, length);
    }

    inline std::string Operation::format(const std::string& text, int matchesChar(int),
            const std::string& replacement) {
        std::ostringstream ss;
        std::string::const_iterator it = text.begin();
        while (it != text.end()) {
            if (matchesChar(*it)) {
                ss << *it;
            } else {
                ss << replacement;
            }
            ++it;
        }
        return ss.str();
    }

    inline scalar Operation::toScalar(const std::string& x) {
        std::istringstream iss(x);
        scalar result;
        iss >> result;
        char strict;
        if (not (iss.fail() or iss.get(strict))) return result;

        std::ostringstream nan, pInf, nInf;
        nan << fl::nan;
        pInf << fl::inf;
        nInf << (-fl::inf);

        if (x == nan.str() or x == "nan")
            return fl::nan;
        if (x == pInf.str() or x == "inf")
            return fl::inf;
        if (x == nInf.str() or x == "-inf")
            return -fl::inf;

        std::ostringstream ex;
        ex << "[conversion error] from <" << x << "> to scalar";
        throw fl::Exception(ex.str(), FL_AT);
    }

    inline scalar Operation::toScalar(const std::string& x, scalar alternative) FL_INOEXCEPT {
        std::istringstream iss(x);
        scalar result;
        iss >> result;
        char strict;
        if (not (iss.fail() or iss.get(strict))) return result;

        std::ostringstream nan, pInf, nInf;
        nan << fl::nan;
        pInf << fl::inf;
        nInf << (-fl::inf);

        if (x == nan.str() or x == "nan")
            return fl::nan;
        if (x == pInf.str() or x == "inf")
            return fl::inf;
        if (x == nInf.str() or x == "-inf")
            return -fl::inf;

        return alternative;
    }

    inline bool Operation::isNumeric(const std::string& x) {
        try {
            fl::Op::toScalar(x);
            return true;
        } catch (std::exception& ex) {
            (void) ex;
            return false;
        }
    }

    template <typename T>
    inline std::string Operation::str(T x, int decimals) {
        std::ostringstream ss;
        ss << std::setprecision(decimals) << std::fixed;
        if (fl::Op::isNaN(x)) {
            ss << "nan";
        } else if (fl::Op::isInf(x)) {
            ss << (x < T(0) ? "-inf" : "inf");
        } else if (fl::Op::isEq(x, T(0))) {
            ss << 0.0;
        } else ss << x;
        return ss.str();
    }

    template <> FL_API
    inline std::string Operation::str(int x, int precision) {
        (void) precision;
        std::ostringstream ss;
        ss << x;
        return ss.str();
    }

    template <> FL_API
    inline std::string Operation::str(std::size_t x, int precision) {
        (void) precision;
        std::ostringstream ss;
        ss << x;
        return ss.str();
    }

    template <> FL_API
    inline std::string Operation::str(const std::string& x, int precision) {
        (void) precision;
        return x;
    }

    template <typename T>
    inline std::string Operation::join(const std::vector<T>& x,
            const std::string& separator) {
        std::ostringstream ss;
        for (std::size_t i = 0; i < x.size(); ++i) {
            ss << str(x.at(i));
            if (i + 1 < x.size()) ss << separator;
        }
        return ss.str();
    }

    template <> FL_API
    inline std::string Operation::join(const std::vector<std::string>& x,
            const std::string& separator) {
        std::ostringstream ss;
        for (std::size_t i = 0; i < x.size(); ++i) {
            ss << x.at(i);
            if (i + 1 < x.size()) ss << separator;
        }
        return ss.str();
    }

    template <typename T>
    inline std::string Operation::join(int items, const std::string& separator, T first, ...) {
        std::ostringstream ss;
        ss << str(first);
        if (items > 1) ss << separator;
        va_list args;
        va_start(args, first);
        for (int i = 0; i < items - 1; ++i) {
            ss << str(va_arg(args, T));
            if (i + 1 < items - 1) ss << separator;
        }
        va_end(args);
        return ss.str();
    }

    template <> FL_API
    inline std::string Operation::join(int items, const std::string& separator,
            float first, ...) {
        std::ostringstream ss;
        ss << str(first);
        if (items > 1) ss << separator;
        va_list args;
        va_start(args, first);
        for (int i = 0; i < items - 1; ++i) {
            ss << str(va_arg(args, double)); //automatic promotion
            if (i + 1 < items - 1) ss << separator;
        }
        va_end(args);
        return ss.str();
    }

    template <> FL_API
    inline std::string Operation::join(int items, const std::string& separator, const char* first, ...) {
        std::ostringstream ss;
        ss << first;
        if (items > 1) ss << separator;
        va_list args;
        va_start(args, first);
        for (int i = 0; i < items - 1; ++i) {
            ss << va_arg(args, const char*);
            if (i + 1 < items - 1) ss << separator;
        }
        va_end(args);
        return ss.str();
    }
}


#endif  /* FL_OPERATION_H */
