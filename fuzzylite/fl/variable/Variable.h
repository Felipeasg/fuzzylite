/*
 Author: Juan Rada-Vilela, Ph.D.
 Copyright © 2010-2015 FuzzyLite Limited.
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

    class FL_API Variable {
    private:
        std::string _name;
        std::vector<Term*> _terms;
        scalar _value;
        scalar _minimum, _maximum;
        bool _enabled;
        bool _lockValueInRange;

        void copyFrom(const Variable& source);

    public:
        explicit Variable(const std::string& name = "",
                scalar minimum = -fl::inf,
                scalar maximum = fl::inf);
        explicit Variable(const Variable& other);
        Variable& operator=(const Variable& other);
        virtual ~Variable();
        FL_DEFAULT_MOVE(Variable)

        virtual void setName(const std::string& name);
        virtual std::string getName() const;

        virtual void setValue(scalar value);
        virtual scalar getValue() const;

        virtual void setRange(scalar minimum, scalar maximum);
        virtual scalar range() const;

        virtual void setMinimum(scalar minimum);
        virtual scalar getMinimum() const;

        virtual void setMaximum(scalar maximum);
        virtual scalar getMaximum() const;

        virtual void setEnabled(bool enabled);
        virtual bool isEnabled() const;

        virtual void setLockValueInRange(bool lockValueInRange);
        virtual bool isLockValueInRange() const;

        virtual std::string fuzzify(scalar x) const;
        virtual Term* highestMembership(scalar x, scalar* yhighest = fl::null) const;

        virtual std::string toString() const;

        /**
         * Operations for iterable datatype _terms
         */
        virtual void sort();
        virtual void addTerm(Term* term);
        virtual void insertTerm(Term* term, std::size_t index);
        virtual Term* getTerm(std::size_t index) const;
        virtual Term* getTerm(const std::string& name) const;
        virtual bool hasTerm(const std::string& name) const;
        virtual Term* removeTerm(std::size_t index);
        virtual std::size_t numberOfTerms() const;
        virtual void setTerms(const std::vector<Term*>& terms);
        virtual const std::vector<Term*>& terms() const;
        virtual std::vector<Term*>& terms();

    };

}

#endif /* FL_VARIABLE_H */
