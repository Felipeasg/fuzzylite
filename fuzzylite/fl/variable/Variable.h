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

#ifndef FL_VARIABLE_H
#define FL_VARIABLE_H

#include "fl/fuzzylite.h"
#include "fl/defuzzifier/Centroid.h"

#include <string>
#include <vector>

namespace fl {

    class Term;

    /**
      
      The Variable class represents a linguistic variable of the fuzzy logic
      controller, and contains the linguistic terms and the possible value that
      the variable can take. The Variable class is the base class of
      InputVariable%s and OutputVariable%s.
      
      @author Juan Rada-Vilela, Ph.D.
      @see InputVariable
      @see OutputVariable
      @see Term
      @since 4.0
    
     */
    class FL_API Variable {
    private:
        void copyFrom(const Variable& source);

    protected:
        std::string _name;
        std::vector<Term*> _terms;
        scalar _value;
        scalar _minimum, _maximum;
        bool _enabled;
        bool _lockValueInRange;

    public:
        explicit Variable(const std::string& name = "",
                scalar minimum = -fl::inf,
                scalar maximum = fl::inf);
        Variable(const Variable& other);
        /**
          Deletes the terms in the current variable, and adds clones of the
          terms from the `other` variable.

          @param other is the other variable to copy from
          @return this variable, which contains a copy of the `other` variable
         */
        Variable& operator=(const Variable& other);
        virtual ~Variable();
        FL_DEFAULT_MOVE(Variable)

        /**
          Sets the name of the variable
          @param name is the name of the variable
         */
        virtual void setName(const std::string& name);

        /**
          Gets the name of the variable
          @return the name of the variable
         */
        virtual std::string getName() const;

        /**
          Sets the value of the variable (default: `fl::nan`). 
          @param value is the input value of an InputVariable, or the  
          output value of an OutputVariable.
         */
        virtual void setValue(scalar value);

        /**
          Gets the input value of an input variable, or the  
          output value of an output variable (default: `fl::nan`)
          @return the input value of an input variable, or the  
          output value of an output variable
         */
        virtual scalar getValue() const;

        /**
          Sets the range of the variable between `[minimum, maximum]` (default: `(-inf, +inf)`)
          @param minimum is the minimum value
          @param maximum is the maximum value
         */
        virtual void setRange(scalar minimum, scalar maximum);
        /**
          Gets the magnitude of the range of the variable as the 
          difference between maximum and minimum values (default: `fl::nan`)
          @return maximum - minimum
         */
        virtual scalar range() const;

        /**
          Sets the minimum value of the range of the variable (default: -`fl::inf`)
          @param minimum is the minimum value of the range
         */
        virtual void setMinimum(scalar minimum);
        /**
          Gets the minimum value of the range of the variable (default: -`fl::inf`)
          @return the minimum value of the range of the variable
         */
        virtual scalar getMinimum() const;

        /**
          Sets the maximum value of the range of the variable (default: `fl::inf`)
          @param maximum is the maximum value of the range
         */
        virtual void setMaximum(scalar maximum);
        /**
          Gets the maximum value of the range of the variable (default: `fl::inf`)
          @return the maximum value of the range of the variable
         */
        virtual scalar getMaximum() const;

        /**
          Sets whether the variable is enabled (default: `true`).
          
          @param enabled is a boolean that enables the variable if `true`, or 
          disables the variable if `false`.
         */
        virtual void setEnabled(bool enabled);
        /**
          Gets whether the variable is enabled (default: `true`).
          
          @return `true`, if variable is enabled; `false`, if the variable is disabled
         */
        virtual bool isEnabled() const;

        /**
          Sets whether the variable locks the current value within the 
          range of the variable (default: `false`).
          
          Locking the value of an InputVariable means that the input value 
          will always be considered to lie within the range
          `[minimum,maximum]`, taking the `minimum` and `maximum` values whenever
          the `value` is less than `minimum` or greater than `maximum` (respectively) 
          without ever changing the input `value`. Refer to 
          {@link Antecedent#activationDegree()}.
          
          Locking the value of an OutputVariable means that defuzzifiers will 
          ensure that the output value is within the range of the variable, 
          adjusting the output value if necessary. Refer to {@link OutputVariable#defuzzify()}.
           
          @param lockValueInRange is a boolean that indicates whether to lock 
          the value in range
         */
        virtual void setLockValueInRange(bool lockValueInRange);

        /**
          Gets whether the variable locks the current value within the 
          range of the variable (default: `false`). 
          
          Locking the value of an InputVariable means that the input value 
          will always be considered to lie within the range
          `[minimum,maximum]`, taking the `minimum` and `maximum` values whenever
          the `value` is less than `minimum` or greater than `maximum` (respectively) 
          without ever changing the input `value`. Refer to 
          {@link Antecedent#activationDegree()}.
          
          Locking the value of an OutputVariable means that defuzzifiers will 
          ensure that the output value is within the range of the variable, 
          adjusting the output value if necessary. Refer to {@link OutputVariable#defuzzify()}.
           
          @return `true`, if the variable locks the value in range; `false`, otherwise
         */
        virtual bool isLockValueInRange() const;

        /**
          Evaluates the membership function of value @f$x@f$ for each
          term @f$i@f$, resulting in a fuzzy value in the form
          @f$\tilde{x}=\sum_i{\mu_i(x)/i}@f$
          @return the fuzzy value expressed as @f$\sum_i{\mu_i(x)/i}@f$
         */
        virtual std::string fuzzify(scalar x) const;

        /**
          Gets the term which has the highest membership function value for
          @f$x@f$. 
          @param x is the value of interest
          @param[out] yhighest is a pointer where the highest membership 
          function value will be stored
          @return the term @f$if@f$ which maximimizes @f$\mu_i(x)@f$
         */
        virtual Term* highestMembership(scalar x, scalar* yhighest = fl::null) const;

        /**
          Gets the representation of the variable in the 
          FuzzyLite Language (FLL)
          @return the variable in FLL
          @see FllExporter
         */
        virtual std::string toString() const;

        /**
          Sorts the terms in ascending order according to their centroids
         */
        virtual void sort();
        /**
          Adds a term to the variable
          @param term is the term to add
         */
        virtual void addTerm(Term* term);
        /**
          Inserts the term in the variable
          @param term is the term to insert
          @param index is the index where the term will be inserted
         */
        virtual void insertTerm(Term* term, std::size_t index);
        /**
          Gets the term at the given index
          @param index is the position of the term in the vector
          @return the term at the given index
         */
        virtual Term* getTerm(std::size_t index) const;
        /**
          Gets the term of the given name.
          @param name is the name of the term to retrieve
          @return the term of the given name
          @throws Exception if the term is not found
         */
        virtual Term* getTerm(const std::string& name) const;
        /**
          Gets whether a term of the given name has been added
          @param name the name of the term 
          @return `true`, if the term of the given name is found; `false`, otherwise
         */
        virtual bool hasTerm(const std::string& name) const;
        /**
          Removes the term at the given index
          @param index the index of the term to remove
          @return the removed term
         */
        virtual Term* removeTerm(std::size_t index);
        /**
          Gets the number of terms added to the variable
          @return the number of terms in the variable
         */
        virtual std::size_t numberOfTerms() const;
        /**
          Sets the terms of the variable
          @param terms is a vector of terms
         */
        virtual void setTerms(const std::vector<Term*>& terms);
        /**
          Gets an immutable vector of the terms
          @return an immutable vector of terms
         */
        virtual const std::vector<Term*>& terms() const;
        /**
          Gets a mutable vector of the terms
          @return a mutable vector of terms
         */
        virtual std::vector<Term*>& terms();

    };

}

#endif /* FL_VARIABLE_H */
